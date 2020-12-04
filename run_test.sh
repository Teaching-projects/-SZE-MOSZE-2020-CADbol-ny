#!/bin/bash

rm -f output.txt
IFS=$'\n'

./$1 scenario3.json>> good_output1.txt <input.txt
