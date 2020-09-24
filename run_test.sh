#!/bin/bash

while IFS= read -r line;  
do ./a.out $line ; 
done < input.txt