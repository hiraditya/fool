#!/usr/bin/python
#@author Aditya Kumar
#This python script is used in copying the directory structure
#from one directory-path to the other.

import os
import shutil
import sys
if __name__ == '__main__':
  os.system('rm -rf dm_dir')
  origPath = "/home/hiraditya/Downloads/hiphop/hiphop-aug17/hiphop-php"
  pathname = "/home/hiraditya/Downloads/hiphop/hiphop-aug17/hiphop-php/dm_dir/"
  for dirname, dirnames, filenames in os.walk(origPath):
    print "old dirname", dirname, "\n\t"
    newDir = dirname.replace(origPath,pathname)
    print "new dir name", newDir
    os.mkdir(newDir)

