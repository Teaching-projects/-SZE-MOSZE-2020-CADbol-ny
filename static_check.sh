#!/bin/bash

FILE=./errors.txt
error_count=$(cat "$FILE" | wc -l)
echo "$error_count errors found"
if [ $error_count -lt 0 ]
then
  exit 1
fi
  exit 0