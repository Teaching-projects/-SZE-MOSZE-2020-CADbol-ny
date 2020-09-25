#!/bin/bash

rm output.txt

while read file1 file2;
do
./a.out $file1 $file2 >> output.txt;
done < input.txt