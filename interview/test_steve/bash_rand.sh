#!/bin/bash

# $RANDOM returns a different random integer at each invocation.
# Nominal range: 0 - 32767 (signed 16-bit integer).

MAXCOUNT=5100
count=1

echo
echo "$MAXCOUNT random numbers:"
echo "-----------------"
while [ "$count" -le $MAXCOUNT ]      # Generate 10 ($MAXCOUNT) random integers.
do
  number=$RANDOM
  if [ $((count%2)) -eq 0 ];
  then
    echo "ADD_VALUE $((count+1)) $number" >> test_stev.txt;
  else
    echo "GET_VALUE $count" >> test_stev.txt;
  fi
  let "count += 1"  # Increment count.
done
echo "-----------------"
