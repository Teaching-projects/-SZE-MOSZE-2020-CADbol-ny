#!/bin/bash

IFS=$`\n`

rm output.txt
echo `./a.out units/unit1.txt units/unit2.txt` >> output.txt
echo `./a.out units/unit1.txt units/unit3.txt` >> output.txt
echo `./a.out units/unit2.txt units/unit1.txt` >> output.txt
echo `./a.out units/unit2.txt units/unit3.txt` >>output.txt
echo` ./a.out units/unit3.txt units/unit2.txt` >>output.txt
echo `./a.out units/unit3.txt units/unit1.txt` >> output.txt
