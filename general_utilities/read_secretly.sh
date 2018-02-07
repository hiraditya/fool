#!/bin/bash -e
HASHING_TOOLS='md5
shasum'

for HASHING_TOOL in $HASHING_TOOLS; do
  read -s -p 'Enter password to check: ' plainpass; echo; echo 'Hashed password: '; echo -n "$plainpass" | $HASHING_TOOL; unset plainpass
done
