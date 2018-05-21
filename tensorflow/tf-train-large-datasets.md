# Datasets can be created from different file formats.
  - They generate input funciton for estimators
  - Datasets handle shuffling, epochs, batching ...
  - They offer rich API for working on and transforming the data.

Note: `tf.commands` do not execute any command. They only create a graph in memory which gets executed during training/inference.

Input functions are called when a model is instantiated.
  - It is not called everytime the model needs data.
  - It is called only once at model-creation time.
  - They are not expected to return any actual data.
  - They only return nodes, and these nodes return data when they are executed.
  - Arbitrarily complex function can be put in the input functions as long as they are supposed to execute only once.

```python
  def decode_line(row):
    # Decode the row as a csv. with the defaults for each column stated as follows.
    cols = tf.decode_csv(row, record_defaults=[[0], "house", [0]])
    # First and second columns are the square footage and type of real estate respectively.
    features = {'sq_footage' : cols[0], 'type' : cols[1]}
    # The label is the price used for training.
    label = cols[2] # price
    return features, label
  
  # For multiple files.
  # Loading a file with TextLineDataset, one file becomes a collection of text lines,
  # so that is one-to-many transformations and is applied with flat_map
  dataset = tf.data.Dataset.list_files("train.csv-*") \
                   .flat_map(tf.data.TextLineDataset) \
                   .map(decode_line) # Transforms a dataset of text lines into a dataset of features an labels.
'''  
  # For single file.
  dataset = tf.data.TextLineDataset("train1.csv") \
                   .map(decode_line) # Transforms a dataset of text lines into a dataset of features an labels.
'''

  # dataset shuffles and repeats it for 15 epochs and batches it into many batches of 128 elements.
  dataset = dataset.shuffle(1000) \
                   .repeat(15) \
                   .batch(128)

  # Return one batch of data everytime they get executed in the training loop.
  def input_fn():
    features, label = dataset.make_one_shot_iterator().get_next()
    return features, label


  # Launch the training loop. The model receives data from its input node features and label
  model.train(input_fn)

```
