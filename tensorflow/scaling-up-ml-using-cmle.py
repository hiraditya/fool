'''
In this lab, you will learn how to:

    Package up TensorFlow model
    Run training locally
    Run training on cloud
    Deploy model to cloud
    Invoke model to carry out predictions
'''

'''
 Scaling up ML using Cloud ML Engine

In this notebook, we take a previously developed TensorFlow model to predict taxifare rides and package it up so that it can be run in Cloud MLE. For now, we'll run this on a small dataset. The model that was developed is rather simplistic, and therefore, the accuracy of the model is not great either. However, this notebook illustrates how to package up a TensorFlow model to run it within Cloud ML.

Later in the course, we will look at ways to make a more effective machine learning model.

 Environment variables for project and bucket

Note that:

    Your project id is the unique string that identifies your project (not the project name). You can find this from the GCP Console dashboard's Home page. My dashboard reads: Project ID: cloud-training-demos

    Cloud training often involves saving and restoring model files. If you don't have a bucket already, I suggest that you create one from the GCP console (because it will dynamically check whether the bucket name you want is available). A common pattern is to prefix the bucket name by the project id, so that it is unique. Also, for cost reasons, you might want to use a single region bucket.

Change the cell below to reflect your Project ID and bucket name.
'''

import os
PROJECT = 'cloud-training-demos' # REPLACE WITH YOUR PROJECT ID
BUCKET = 'cloud-training-demos-ml' # REPLACE WITH YOUR BUCKET NAME
REGION = 'us-central1' # REPLACE WITH YOUR BUCKET REGION e.g. us-central1

