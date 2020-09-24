#!/bin/bash

IFS=read r ;
for i in 'cat input.txt'; 
do echo "Eredmenyek:" $i | ./a.out ;
done