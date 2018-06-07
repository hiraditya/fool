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

# for bash
os.environ['PROJECT'] = PROJECT
os.environ['BUCKET'] = BUCKET
os.environ['REGION'] = REGION
os.environ['TFVERSION'] = '1.7'  # Tensorflow version

%bash
gcloud config set project $PROJECT
gcloud config set compute/region $REGION

%bash
PROJECT_ID=$PROJECT
AUTH_TOKEN=$(gcloud auth print-access-token)
SVC_ACCOUNT=$(curl -X GET -H "Content-Type: application/json" \
    -H "Authorization: Bearer $AUTH_TOKEN" \
    https://ml.googleapis.com/v1/projects/${PROJECT_ID}:getConfig \
    | python -c "import json; import sys; response = json.load(sys.stdin); \
    print response['serviceAccount']")

echo "Authorizing the Cloud ML Service account $SVC_ACCOUNT to access files in $BUCKET"
gsutil -m defacl ch -u $SVC_ACCOUNT:R gs://$BUCKET
gsutil -m acl ch -u $SVC_ACCOUNT:R -r gs://$BUCKET  # error message (if bucket is empty) can be ignored
gsutil -m acl ch -u $SVC_ACCOUNT:W gs://$BUCKET

'''
 Packaging up the code

Take your code and put into a standard Python package structure. model.py and task.py contain the Tensorflow code from earlier (explore the directory structure).
'''
!find taxifare
!cat taxifare/trainer/model.py

'''
Find absolute paths to your data
Note the absolute paths below. /content is mapped in Datalab to where the home icon takes you
'''
%bash
echo $PWD
rm -rf $PWD/taxi_trained
head -1 $PWD/taxi-train.csv
head -1 $PWD/taxi-valid.csv
'''
Running the Python module from the command-line 
'''
%bash
rm -rf taxifare.tar.gz taxi_trained
export PYTHONPATH=${PYTHONPATH}:${PWD}/taxifare
python -m trainer.task \
   --train_data_paths="${PWD}/taxi-train*" \
   --eval_data_paths=${PWD}/taxi-valid.csv  \
   --output_dir=${PWD}/taxi_trained \
   --train_steps=1000 --job-dir=./tmp

%bash
ls $PWD/taxi_trained/export/exporter/

%writefile ./test.json
{"pickuplon": -73.885262,"pickuplat": 40.773008,"dropofflon": -73.987232,"dropofflat": 40.732403,"passengers": 2}

%bash
model_dir=$(ls ${PWD}/taxi_trained/export/exporter)
gcloud ml-engine local predict \
    --model-dir=${PWD}/taxi_trained/export/exporter/${model_dir} \
    --json-instances=./test.json

'''
    Running locally using gcloud
'''
%bash
rm -rf taxifare.tar.gz taxi_trained
gcloud ml-engine local train \
   --module-name=trainer.task \
   --package-path=${PWD}/taxifare/trainer \
   -- \
   --train_data_paths=${PWD}/taxi-train.csv \
   --eval_data_paths=${PWD}/taxi-valid.csv  \
   --train_steps=1000 \
   --output_dir=${PWD}/taxi_trained
