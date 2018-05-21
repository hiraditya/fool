# Estimator API Features

- Quick model
- Easy checkpointing
- Out of memory datasets
- Train/eval/monitor
- Distributed training
- Hyper parameter tuning on ML-Engine
- Production

# Several linear regressors already available, for e.g.,

```
tf.estimator.LinearRegressor(featcols)
tf.estimator.DNNLinearCombinedClassifier
```

## Feature column
Tells the model what inputs to expect for e.g.,
  - Numeric column (tf.feature_column.numeric_column("sq_footage")
  - Categorical column (tf.feature_column.categorical_column_with_vocabulary_list("type", ["house", "apartment"])

Under the hood, feature column takes care of packing the inputs into the input vector of the model.
Both numpy arrays and pandas dataframes can be passed as feature columns.


# Training
During the training we need to describe a function which returns the feature column along with label

```
def train_input_fn():
  features = { "sq_footage":[1000,     3000,  ....],
               "type":      ["house", "apt", "apt", ....],
             }
             # Prices in thousands
  labels =                  [500, 1000, 1200, ...]

  return features, labels

model.train(train_input_fn, steps=100)

```

`steps` parameter runs #steps additional steps from the last checkpoint
`max_steps` runs only remaining steps from the last checkpoint. This can potentially return without running.

# Prediction
Model once trained can be used for prediction. The predict function in the model API

```
def predict_fn():
  features = { "sq_footage":[1000, 3000,],
               "type":    ["house", "apt"],
             }
  return features

# predict the price of features, returns a generator which can be used to iterate over the predictions.
predictions = model.predict(predict_fn)
```

# Checkpointing is useful in the following situations:
  - Continue training
  - Resume on failure
  - Predict from trained model

Note: Checkpointing is the default behavior. To disable checkpointing, remove/rename the folder.

```
tf.estimator.LinearRegressor(featcols, '/path/to/checkpointing_folder')
```


