# Status
https://status.cloud.google.com/

# List gcl zones
gcloud compute zones list

# create a vm
datalab create mydatalabvm --zone <ZONE>

## Notes on create labvm
 - Look back at Cloud Shell, and follow any prompts. If asked for a ssh passphrase, just hit return (for no passphrase).
 - If necessary, wait for Datalab to finish launching. Datalab is ready when you see a message prompting you to do a "Web Preview".
 - Click on the Web Preview icon on the top-right corner of the Cloud Shell ribbon. Switch or enter the port 8081.
 - If the cloud shell used for running the datalab command is closed or interrupted, the connection to your Cloud Datalab VM will terminate. If that happens, you may be able to reconnect using the command ‘datalab connect mydatalabvm' in your new Cloud Shell.
 
 

# Accessing notebooks
In Cloud Datalab home page (browser), navigate into "notebooks" and add a new notebook using the icon on the top left.

In the new notebook, enter the following commands in the cell, and click on Run (on the top navigation bar) to run the commands:
  %bash
  git clone https://github.com/GoogleCloudPlatform/training-data-analyst
  rm -rf training-data-analyst/.git
