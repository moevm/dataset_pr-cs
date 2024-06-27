#ifndef MAIN_H
#define MAIN_H

#include "structs.h"
#include "parsing.h"
#include "png_file_io.h"
#include "image_processing.h"


#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h> 

#define HELP \
"--squared_lines - drawing a square with diagonals. Parametrs:\n	--left_up - coordinates of the upper-left corner.the value\
 is set in the format left.up, where left is the x coordinate, up is the y coordinate\n	--side_size - the size of the side\
  of the square.Accepts a number greater than 0 as input.\n	--thickness - line thickness.Accepts a number greater than 0 as in\
  put.\n	--color - line color.The color is set by the string rrr.ggg.bbb, where rrr/ggg/bbb are the numbers specifying the\
 color component. The example --color 255.0.0 sets the color red.\n	--fill - a binary flag that determines whether the square will\
 be filled in.\n	--fill_color - works similarly to the '--color` flag.\n--rgbfilter - allows you to either set the value of a given\
 component for the entire image in the range from 0 to 255. Parametrs:\n	--component_name - which component needs to be changed.\
 Possible values are red, green and `blue'.\n	--component_value - to which value the component needs to be changed.Takes\
 a value as a number from 0 to 255.\n--rotate - rotate the image (part) by 90/180/270 degrees. Parametrs:\n	--left_up - coordi\
 nates of the upper-left corner.the value is set in the format left.up, where left is the x coordinate, up is the y coordinate\n\
	--left_up - coordinates of the lower-right corner of the area. The value is set in the format right.down, where right is \
the x coordinate, down is the y coordinate.\n	--angle - angle of rotation. Possible values: 90, 180, 270.\n"

#define START_SENTENCE "Course work for option 4.24, created by Ekaterina Lobova.\n"

#define DEFAULT_VALUE "out.png"

#endif
