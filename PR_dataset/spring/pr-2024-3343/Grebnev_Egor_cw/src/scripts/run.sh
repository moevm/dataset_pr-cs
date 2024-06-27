#!/bin/bash

FILE="./24.bmp"

MIRROR="--mirror --left_up 130.47 --right_down 297.325 --axis y" 
COLOR_REPLACE="--color_replace --old_color 255.255.255 --new_color 255.12.200"  
SPLIT="--info --split --number_x 20 --number_y 20 --thickness 2 --color 255.100.0" 
COPY="--copy --left_up 166.96 --right_down 166.248 --dest_left_up 250.247" 
PROC="--outside_ornament --thickness 10 --color 255.255.255"

COMMAND="./cw $PROC $FILE"


make
echo "$COMMAND"
echo "==========START========="
$COMMAND
echo "==========END==========="
make clean
