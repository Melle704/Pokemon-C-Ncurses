#!/bin/bash

# execute the make command
make

# change the terminal profile to "square"
echo -e "\033]50;SetProfile=square\a"

# execute the ./spel command
./spel

