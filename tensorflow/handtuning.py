# notebooks/training-data-analyst > courses > machine_learning > deepdive > 05_artandscience and open a_handtuning.ipynb.

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
df.head()
df.describe()


'''
In this exercise, we'll be trying to predict median_house_value. It will be our label (sometimes also called a target). Can we use total_rooms as our input feature?  What's going on with the values for that feature?

This data is at the city block level, so these features reflect the total number of rooms in that block, or the total number of people who live on that block, respectively.  Let's create a different, more appropriate feature.  Because we are predicing the price of a single house, we should try to make all our features correspond to a single house as well
'''
df['num_rooms'] = df['total_rooms'] / df['households']
df.describe()

# Split into train and eval
np.random.seed(seed=1) #makes split reproducible
msk = np.random.rand(len(df)) < 0.8
traindf = df[msk]
evaldf = df[~msk]

'''
In this exercise, we'll be trying to predict median_house_value. It will be our label (sometimes also called a target). We'll use num_rooms as our input feature.

To train our model, we'll use the LinearRegressor estimator. The Estimator takes care of a lot of the plumbing, and exposes a convenient way to interact with data, training, and evaluation.
Let's scale the target values so that the default parameters are more appropriate.
'''
SCALE = 100000
OUTDIR = './housing_trained'
def train_and_evaluate(output_dir, num_train_steps):
  myopt = tf.train.FtrlOptimizer(learning_rate = 0.2) # note the learning rate
  estimator = tf.estimator.LinearRegressor(
                       model_dir = output_dir, 
                       feature_columns = [tf.feature_column.numeric_column('num_rooms')],
                       optimizer = myopt)
  
  #Add rmse evaluation metric
  def rmse(labels, predictions):
    pred_values = tf.cast(predictions['predictions'],tf.float64)
    return {'rmse': tf.metrics.root_mean_squared_error(labels*SCALE, pred_values*SCALE)}
  estimator = tf.contrib.estimator.add_metrics(estimator,rmse)
  
  train_spec=tf.estimator.TrainSpec(
                       input_fn = tf.estimator.inputs.pandas_input_fn(x = traindf[["num_rooms"]],
                                              y = traindf["median_house_value"] / SCALE,  # note the scaling
                                              num_epochs = None,
                                              batch_size = 512, # note the batch size
                                              shuffle = True),
                       max_steps = num_train_steps)
  eval_spec=tf.estimator.EvalSpec(
                       input_fn = tf.estimator.inputs.pandas_input_fn(x = evaldf[["num_rooms"]],
                                              y = evaldf["median_house_value"] / SCALE,  # note the scaling
                                              num_epochs = 1,
                                              shuffle = False),
                       steps = None,
                       start_delay_secs = 1, # start evaluating after N seconds
                       throttle_secs = 10,  # evaluate every N seconds
                       )
  tf.estimator.train_and_evaluate(estimator, train_spec, eval_spec)

# Run training    
shutil.rmtree(OUTDIR, ignore_errors = True) # start fresh each time
train_and_evaluate(OUTDIR, num_train_steps = 500) 
