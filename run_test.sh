#!/bin/bash

rm output.txt
while read -r line ; do
	echo `./a.out $line` >> output.txt
done<"input.txt"
