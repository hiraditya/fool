#!/usr/bin/python
'''
A program to monitor a running process and prints
the time when it finishes.
'''
import datetime
#import subprocess
import commands
import time
import sys

def main(argv):
  if len(argv) < 2:
    sys.stderr.write("Usage: %s <action>" % (argv[0],))
    return 1
  output = commands.getoutput("ps -e")
  while argv[1] in output:
    output = commands.getoutput("ps -e")
    print argv[1], " running", datetime.datetime.now() 
    #print output
    time.sleep(30)
  sys.stderr.write("Process finished at %s\n" % datetime.datetime.now())

if __name__ == "__main__":
  sys.exit(main(sys.argv))
