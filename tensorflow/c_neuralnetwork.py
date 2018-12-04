import math
import shutil
import numpy as np
import pandas as pd
import tensorflow as tf

## Set Up
# In this first cell, we'll load the necessary libraries.

tf.logging.set_verbosity(tf.logging.INFO)
pd.options.display.max_rows = 10
pd.options.display.float_format = '{:.1f}'.format

# Next, we'll load our data set.
df = pd.read_csv("https://storage.googleapis.com/ml_universities/california_housing_train.csv", sep=",")

'''
Examine the data
It's a good idea to get to know your data a little bit before you work with it.
We'll print out a quick summary of a few useful statistics on each column.
This will include things like mean, standard deviation, max, min, and various quantiles.
'''

df.head()

df.describe()

'''
This data is at the city block level, so these features reflect the total number of rooms in that block,
or the total number of people who live on that block, respectively.
Let's create a different, more appropriate feature. Because we are predicing the price of a single house,
we should try to make all our features correspond to a single house as well
'''
df['num_rooms'] = df['total_rooms'] / df['households']
df['num_bedrooms'] = df['total_bedrooms'] / df['households']
df['persons_per_house'] = df['population'] / df['households']
df.describe()
df.drop(['total_rooms', 'total_bedrooms', 'population', 'households'], axis = 1, inplace = True)
df.describe()

'''
Build a neural network model

In this exercise, we'll be trying to predict median_house_value. It will be our label (sometimes also called a target). We'll use the remaining columns as our input features.

To train our model, we'll first use the LinearRegressor interface. Then, we'll change to DNNRegressor
'''

featcols = {
  colname : tf.feature_column.numeric_column(colname) \
    for colname in 'housing_median_age,median_income,num_rooms,num_bedrooms,persons_per_house'.split(',')
}
# Bucketize lat, lon so it's not so high-res; California is mostly N-S, so more lats than lons
featcols['longitude'] = tf.feature_column.bucketized_column(tf.feature_column.numeric_column('longitude'),
                                                   np.linspace(-124.3, -114.3, 5).tolist())
featcols['latitude'] = tf.feature_column.bucketized_column(tf.feature_column.numeric_column('latitude'),
                                                  np.linspace(32.5, 42, 10).tolist())
featcols.keys()



# Split into train and eval
msk = np.random.rand(len(df)) < 0.8
traindf = df[msk]
evaldf = df[~msk]

SCALE = 100000
BATCH_SIZE= 100
OUTDIR = './housing_trained'
train_input_fn = tf.estimator.inputs.pandas_input_fn(x = traindf[list(featcols.keys())],
                                                    y = traindf["median_house_value"] / SCALE,
                                                    num_epochs = None,
                                                    batch_size = BATCH_SIZE,
                                                    shuffle = True)
eval_input_fn = tf.estimator.inputs.pandas_input_fn(x = evaldf[list(featcols.keys())],
                                                    y = evaldf["median_house_value"] / SCALE,  # note the scaling
                                                    num_epochs = 1, 
                                                    batch_size = len(evaldf), 
                                                    shuffle=False)

# ------------------------------Linear Regressor-------------------------------------
# Linear Regressor
def train_and_evaluate(output_dir, num_train_steps):
  myopt = tf.train.FtrlOptimizer(learning_rate = 0.01) # note the learning rate
  estimator = tf.estimator.LinearRegressor(
                       model_dir = output_dir, 
                       feature_columns = featcols.values(),
                       optimizer = myopt)
  
  #Add rmse evaluation metric
  def rmse(labels, predictions):
    pred_values = tf.cast(predictions['predictions'],tf.float64)
    return {'rmse': tf.metrics.root_mean_squared_error(labels*SCALE, pred_values*SCALE)}
  estimator = tf.contrib.estimator.add_metrics(estimator,rmse)
  
  train_spec=tf.estimator.TrainSpec(
                       input_fn = train_input_fn,
                       max_steps = num_train_steps)
  eval_spec=tf.estimator.EvalSpec(
                       input_fn = eval_input_fn,
                       steps = None,
                       start_delay_secs = 1, # start evaluating after N seconds
                       throttle_secs = 10,  # evaluate every N seconds
                       )
  tf.estimator.train_and_evaluate(estimator, train_spec, eval_spec)

# Run training    
shutil.rmtree(OUTDIR, ignore_errors = True) # start fresh each time
train_and_evaluate(OUTDIR, num_train_steps = (100 * len(traindf)) / BATCH_SIZE)


'''
Sample output:
INFO:tensorflow:Using default config.
INFO:tensorflow:Using config: {'_keep_checkpoint_max': 5, '_save_checkpoints_secs': 600, '_train_distribute': None, '_num_worker_replicas': 1, '_session_config': None, '_is_chief': True, '_save_checkpoints_steps': None, '_model_dir': './housing_trained', '_master': '', '_task_type': 'worker', '_global_id_in_cluster': 0, '_log_step_count_steps': 100, '_num_ps_replicas': 0, '_save_summary_steps': 100, '_service': None, '_task_id': 0, '_cluster_spec': <tensorflow.python.training.server_lib.ClusterSpec object at 0x7f63d82dc2e8>, '_evaluation_master': '', '_tf_random_seed': None, '_keep_checkpoint_every_n_hours': 10000}
INFO:tensorflow:Using config: {'_keep_checkpoint_max': 5, '_save_checkpoints_secs': 600, '_train_distribute': None, '_num_worker_replicas': 1, '_session_config': None, '_is_chief': True, '_save_checkpoints_steps': None, '_model_dir': './housing_trained', '_master': '', '_task_type': 'worker', '_global_id_in_cluster': 0, '_log_step_count_steps': 100, '_tf_random_seed': None, '_save_summary_steps': 100, '_service': None, '_task_id': 0, '_cluster_spec': <tensorflow.python.training.server_lib.ClusterSpec object at 0x7f63d82dc240>, '_evaluation_master': '', '_num_ps_replicas': 0, '_keep_checkpoint_every_n_hours': 10000}
INFO:tensorflow:Running training and evaluation locally (non-distributed).
INFO:tensorflow:Start train and evaluate loop. The evaluate will happen after 10 secs (eval_spec.throttle_secs) or training is finished.

INFO:tensorflow:Saving dict for global step 13474: average_loss = 0.5720178, global_step = 13474, loss = 2016.9347, rmse = 75631.85
'''
# -----------------------------DNN Regressor-------------------------------------
# DNN Regressor
def train_and_evaluate(output_dir, num_train_steps):
  myopt = tf.train.FtrlOptimizer(learning_rate = 0.01) # note the learning rate
  estimator = tf.estimator.DNNRegressor(model_dir = output_dir,
                                hidden_units = [100, 50, 20],
                                feature_columns = featcols.values(),
                                optimizer = myopt,
                                dropout = 0.1)

  #Add rmse evaluation metric
  def rmse(labels, predictions):
    pred_values = tf.cast(predictions['predictions'],tf.float64)
    return {'rmse': tf.metrics.root_mean_squared_error(labels*SCALE, pred_values*SCALE)}
  estimator = tf.contrib.estimator.add_metrics(estimator,rmse)
  
  train_spec=tf.estimator.TrainSpec(
                       input_fn = train_input_fn,
                       max_steps = num_train_steps)
  eval_spec=tf.estimator.EvalSpec(
                       input_fn = eval_input_fn,
                       steps = None,
                       start_delay_secs = 1, # start evaluating after N seconds
                       throttle_secs = 10,  # evaluate every N seconds
                       )
  tf.estimator.train_and_evaluate(estimator, train_spec, eval_spec)

# Run training    
shutil.rmtree(OUTDIR, ignore_errors = True) # start fresh each time
train_and_evaluate(OUTDIR, num_train_steps = (100 * len(traindf)) / BATCH_SIZE)

'''
Sample output:
INFO:tensorflow:Using default config.
INFO:tensorflow:Using config: {'_keep_checkpoint_max': 5, '_save_checkpoints_secs': 600, '_train_distribute': None, '_num_worker_replicas': 1, '_session_config': None, '_is_chief': True, '_save_checkpoints_steps': None, '_model_dir': './housing_trained', '_master': '', '_task_type': 'worker', '_global_id_in_cluster': 0, '_log_step_count_steps': 100, '_num_ps_replicas': 0, '_save_summary_steps': 100, '_service': None, '_task_id': 0, '_cluster_spec': <tensorflow.python.training.server_lib.ClusterSpec object at 0x7f63cb2d7f98>, '_evaluation_master': '', '_tf_random_seed': None, '_keep_checkpoint_every_n_hours': 10000}
INFO:tensorflow:Using config: {'_keep_checkpoint_max': 5, '_save_checkpoints_secs': 600, '_train_distribute': None, '_num_worker_replicas': 1, '_session_config': None, '_is_chief': True, '_save_checkpoints_steps': None, '_model_dir': './housing_trained', '_master': '', '_task_type': 'worker', '_global_id_in_cluster': 0, '_log_step_count_steps': 100, '_tf_random_seed': None, '_save_summary_steps': 100, '_service': None, '_task_id': 0, '_cluster_spec': <tensorflow.python.training.server_lib.ClusterSpec object at 0x7f63cb2d7f60>, '_evaluation_master': '', '_num_ps_replicas': 0, '_keep_checkpoint_every_n_hours': 10000}
INFO:tensorflow:Running training and evaluation locally (non-distributed).
INFO:tensorflow:Start train and evaluate loop. The evaluate will happen after 10 secs (eval_spec.throttle_secs) or training is finished.
INFO:tensorflow:Saving dict for global step 13474: average_loss = 0.40677336, global_step = 13474, loss = 1434.2828, rmse = 63778.78
'''
