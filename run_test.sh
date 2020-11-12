#!/bin/bash

rm -f output.txt
IFS=$' '

./$1 scenario1.json>> good_output1.txt
./$1 scenario2.json>> good_output2.txt
