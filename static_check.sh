#!/bin/bash

FILE=./errors.txt
if test -f "$FILE"; then
    exit 1
fi
  exit 0