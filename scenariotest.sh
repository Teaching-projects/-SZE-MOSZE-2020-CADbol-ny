#!/bin/bash

rm -f output.txt
IFS=$' '

./$1 scenario1.json >>testoutput1.txt
./$1 scenario2.json >>testoutput2.txt
