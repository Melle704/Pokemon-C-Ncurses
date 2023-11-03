#!/bin/bash

# execute the make command
make clean

make

# open new terminal with profile.
gnome-terminal --maximize --title="Pokemon UvA" -e "./game"


