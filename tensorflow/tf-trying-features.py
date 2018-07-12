import math
import shutil
import numpy as np
import pandas as pd
import tensorflow as tf

print(tf.__version__)
tf.logging.set_verbosity(tf.logging.INFO)
pd.options.display.max_rows = 10
pd.options.display.float_format = '{:.1f}'.format


df = pd.read_csv("https://storage.googleapis.com/ml_universities/california_housing_train.csv", sep=",")

'''
Examine and split the data

It's a good idea to get to know your data a little bit before you work with it.

We'll print out a quick summary of a few useful statistics on each column.
'''

df.head()
df.describe()

# Now, split the data into two parts -- training and evaluation.

np.random.seed(seed=1) #makes result reproducible
msk = np.random.rand(len(df)) < 0.8
traindf = df[msk]
evaldf = df[~msk]

'''
Training and Evaluation

In this exercise, we'll be trying to predict median_house_value It will be our label (sometimes also called a target).

We'll modify the feature_cols and input function to represent the features you want to use.

We divide total_rooms by households to get avg_rooms_per_house which we excect to positively correlate with median_house_value.

We also divide population by total_rooms to get avg_persons_per_room which we expect to negatively correlate with median_house_value.
'''

def add_more_features(df):
  df['avg_rooms_per_house'] = df['total_rooms'] / df['households'] #expect positive correlation
  df['avg_persons_per_room'] = df['population'] / df['total_rooms'] #expect negative correlation
  return df
 
 
 # Create pandas input function
def make_input_fn(df, num_epochs):
  return tf.estimator.inputs.pandas_input_fn(
    x = add_more_features(df),
    y = df['median_house_value'] / 100000, # will talk about why later in the course
    batch_size = 128,
    num_epochs = num_epochs,
    shuffle = True,
    queue_capacity = 1000,
    num_threads = 1
  )

# Define your feature columns
def create_feature_cols():
  return [
    tf.feature_column.numeric_column('housing_median_age'),
    tf.feature_column.bucketized_column(tf.feature_column.numeric_column('latitude'), boundaries = np.arange(32.0, 42, 1).tolist()),
    tf.feature_column.numeric_column('avg_rooms_per_house'),
    tf.feature_column.numeric_column('avg_persons_per_room'),
    tf.feature_column.numeric_column('median_income')
  ]

# Create estimator train and evaluate function
def train_and_evaluate(output_dir, num_train_steps):
  estimator = tf.estimator.LinearRegressor(model_dir = output_dir, feature_columns = create_feature_cols())
  train_spec = tf.estimator.TrainSpec(input_fn = make_input_fn(traindf, None), 
                                      max_steps = num_train_steps)
  eval_spec = tf.estimator.EvalSpec(input_fn = make_input_fn(evaldf, 1), 
                                    steps = None, 
                                    start_delay_secs = 1, # start evaluating after N seconds, 
                                    throttle_secs = 5)  # evaluate every N seconds
  tf.estimator.train_and_evaluate(estimator, train_spec, eval_spec)

# Launch tensorboard
from google.datalab.ml import TensorBoard

OUTDIR = './trained_model'
TensorBoard().start(OUTDIR)

# Run the model
shutil.rmtree(OUTDIR, ignore_errors = True)
train_and_evaluate(OUTDIR, 2000)

from tensorflow.python.tools import inspect_checkpoint
inspect_checkpoint.print_tensors_in_checkpoint_file("trained_model/model.ckpt-2000", tensor_name='linear/linear_model/housing_median_age/weights', all_tensors=False)
inspect_checkpoint.print_tensors_in_checkpoint_file("trained_model/model.ckpt-2000", tensor_name='linear/linear_model/median_income/weights', all_tensors=False)
inspect_checkpoint.print_tensors_in_checkpoint_file("trained_model/model.ckpt-2000", tensor_name='linear/linear_model/avg_rooms_per_house/weights', all_tensors=False)
inspect_checkpoint.print_tensors_in_checkpoint_file("trained_model/model.ckpt-2000", tensor_name='linear/linear_model/avg_persons_per_room/weights', all_tensors=False)
inspect_checkpoint.print_tensors_in_checkpoint_file("trained_model/model.ckpt-2000", tensor_name='linear/linear_model/latitude_bucketized/weights', all_tensors=False)
