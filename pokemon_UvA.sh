#!/bin/bash

# Check the size of the users terminal.
cols=$(tput cols)
lines=$(tput lines)

# Check if the columns are at least 128 and rows are at least 112.
if [ "$cols" -lt 128 ] || [ "$lines" -lt 112 ]; then
    echo "Your terminal is too small, it should be at least 128x112 characters."
    echo "Use the included font, maximize your terminal and try to zoom out."
    echo "The current size is, cols: $cols, rows $lines."
    
    # Exit if the terminal size is too small.
    exit 1
fi

# Make the game executable.
make clean
make

# Open a new maximized terminal and run the game.
# gnome-terminal --maximize --title="Pokemon UvA" -e "./game"
./game

