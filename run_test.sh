#!/bin/bash

rm output.txt
IFS=$' '

while read line line2 ; do
./a.out $line $line2 >> output.txt;
done < input.txt