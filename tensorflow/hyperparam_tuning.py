import os
PROJECT = 'cloud-training-demos' # REPLACE WITH YOUR PROJECT ID
BUCKET = 'cloud-training-demos-ml' # REPLACE WITH YOUR BUCKET NAME
REGION = 'us-central1' # REPLACE WITH YOUR BUCKET REGION e.g. us-central1

# for bash
os.environ['PROJECT'] = PROJECT
os.environ['BUCKET'] = BUCKET
os.environ['REGION'] = REGION
os.environ['TFVERSION'] = '1.8'  # Tensorflow version

''''''' -----------------------------
%%bash
gcloud config set project $PROJECT
gcloud config set compute/region $REGION
''''''' -----------------------------

''''''' -----------------------------
%%bash
rm -rf house_prediction_module
mkdir house_prediction_module
mkdir house_prediction_module/trainer
touch house_prediction_module/trainer/__init__.py
''''''' -----------------------------

''''''' -----------------------------
%%writefile house_prediction_module/trainer/task.py
import argparse
import os
import json
import shutil

from . import model
    
if __name__ == '__main__' and "get_ipython" not in dir():
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '--learning_rate',
      type = float, 
      default = 0.01
  )
  parser.add_argument(
      '--batch_size',
      type = int, 
      default = 30
  )
  parser.add_argument(
      '--output_dir',
      help = 'GCS location to write checkpoints and export models.',
      required = True
  )
  parser.add_argument(
      '--job-dir',
      help = 'this model ignores this field, but it is required by gcloud',
      default = 'junk'
  )
  args = parser.parse_args()
  arguments = args.__dict__
  
  # Unused args provided by service
  arguments.pop('job_dir', None)
  arguments.pop('job-dir', None)
  
  # Append trial_id to path if we are doing hptuning
  # This code can be removed if you are not using hyperparameter tuning
  arguments['output_dir'] = os.path.join(
      arguments['output_dir'],
      json.loads(
          os.environ.get('TF_CONFIG', '{}')
      ).get('task', {}).get('trial', '')
  )
  
  # Run the training
  shutil.rmtree(arguments['output_dir'], ignore_errors=True) # start fresh each time
  
  # Pass the command line arguments to our model's train_and_evaluate function
  model.train_and_evaluate(arguments)
  
''''''' -----------------------------

%%writefile house_prediction_module/trainer/model.py

import numpy as np
import pandas as pd
import tensorflow as tf

tf.logging.set_verbosity(tf.logging.INFO)

# Read dataset and split into train and eval
df = pd.read_csv("https://storage.googleapis.com/ml_universities/california_housing_train.csv", sep = ",")
df['num_rooms'] = df['total_rooms'] / df['households']
np.random.seed(seed = 1) #makes split reproducible
msk = np.random.rand(len(df)) < 0.8
traindf = df[msk]
evaldf = df[~msk]

# Train and eval input functions
SCALE = 100000

def train_input_fn(df, batch_size):
  return tf.estimator.inputs.pandas_input_fn(x = traindf[["num_rooms"]],
                                             y = traindf["median_house_value"] / SCALE,  # note the scaling
                                             num_epochs = None,
                                             batch_size = batch_size, # note the batch size
                                             shuffle = True)

def eval_input_fn(df, batch_size):
  return tf.estimator.inputs.pandas_input_fn(x = evaldf[["num_rooms"]],
                                             y = evaldf["median_house_value"] / SCALE,  # note the scaling
                                             num_epochs = 1,
                                             batch_size = batch_size,
                                             shuffle = False)

# Define feature columns
features = [tf.feature_column.numeric_column('num_rooms')]

def train_and_evaluate(args):
  # Compute appropriate number of steps
  num_steps = (len(traindf) / args['batch_size']) / args['learning_rate']  # if learning_rate=0.01, hundred epochs

  # Create custom optimizer
  myopt = tf.train.FtrlOptimizer(learning_rate = args['learning_rate']) # note the learning rate

  # Create rest of the estimator as usual
  estimator = tf.estimator.LinearRegressor(model_dir = args['output_dir'], 
                                           feature_columns = features, 
                                           optimizer = myopt)
  #Add rmse evaluation metric
  def rmse(labels, predictions):
    pred_values = tf.cast(predictions['predictions'], tf.float64)
    return {'rmse': tf.metrics.root_mean_squared_error(labels * SCALE, pred_values * SCALE)}
  estimator = tf.contrib.estimator.add_metrics(estimator, rmse)

  train_spec = tf.estimator.TrainSpec(input_fn = train_input_fn(df = traindf, batch_size = args['batch_size']),
                                      max_steps = num_steps)
  eval_spec = tf.estimator.EvalSpec(input_fn = eval_input_fn(df = evaldf, batch_size = len(evaldf)),
                                    steps = None)
  tf.estimator.train_and_evaluate(estimator, train_spec, eval_spec)
  
''''''' -----------------------------

''''''' -----------------------------
%%bash
rm -rf house_trained
export PYTHONPATH=${PYTHONPATH}:${PWD}/house_prediction_module
gcloud ml-engine local train \
    --module-name=trainer.task \
    --job-dir=house_trained \
    --package-path=$(pwd)/trainer \
    -- \
    --batch_size=30 \
    --learning_rate=0.02 \
    --output_dir=house_trained

''''''' -----------------------------
%%writefile hyperparam.yaml
trainingInput:
  hyperparameters:
    goal: MINIMIZE
    maxTrials: 5
    maxParallelTrials: 1
    hyperparameterMetricTag: rmse
    params:
    - parameterName: batch_size
      type: INTEGER
      minValue: 8
      maxValue: 64
      scaleType: UNIT_LINEAR_SCALE
    - parameterName: learning_rate
      type: DOUBLE
      minValue: 0.01
      maxValue: 0.1
      scaleType: UNIT_LOG_SCALE
''''''' -----------------------------
%%bash
OUTDIR=gs://${BUCKET}/house_trained   # CHANGE bucket name appropriately
gsutil rm -rf $OUTDIR
export PYTHONPATH=${PYTHONPATH}:${PWD}/house_prediction_module
gcloud ml-engine jobs submit training house_$(date -u +%y%m%d_%H%M%S) \
   --config=hyperparam.yaml \
   --module-name=trainer.task \
   --package-path=$(pwd)/house_prediction_module/trainer \
   --job-dir=$OUTDIR \
   --runtime-version=$TFVERSION \
   --\
   --output_dir=$OUTDIR 
''''''' -----------------------------
''''''' -----------------------------
''''''' -----------------------------
