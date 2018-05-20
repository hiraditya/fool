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
