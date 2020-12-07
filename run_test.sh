#!/bin/bash

rm -f good_output1.txt
IFS=$' '

./$1 preparedgame.json>> good_output1.txt <input.txt