#!/bin/bash

rm -f output.txt
IFS=$' '

./$1 scenario2.json>> good_output1.txt <input.txt
