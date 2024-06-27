#pragma once


#define PRINT_HELP "You should pick one of six options: \n\
1) --help - shows help info, if you need some\n\
2) --info - shows information about input file\n\
3) --rect - draws rectangle. It has five important and one optioanal arguments: --left_up & --right_down (format: \"x.y\"), --thickness (positive number),\
 --color (format: \"r.g.b\"), --fill (true or false), --fill_color (important, if --fill = true; format: \"r.g.b\")\n\
4) --ornament - draws beatiful ornaments. Arguments: --pattern (circle, or rectangle, or semicircle), left_up & right_down (format: \"x.y\")\n\
5) --circle - draws circle. Arguments: --center (format: \"x.y\"), --radius (positive number), --thickness (positive number),\
 --color (format: \"r.g.b\"), --fill (true or false), --fill_color (important, if --fill = true; format: \"r.g.b\")\n\
6) --rotate - rotates the rectangle area by an angle. Arguments: --left_up & --right_down (format: \"x.y\"), --angle (90, or 180, or 270)\n\
Also, important arguments: -i (--input) & -o (--output) - for input and output file.\
 If --input is missing, last argument of comand line would be consider as input file."


#define HELP "Use --help or -h for more information."
#define UNKNOWN_ARG "Unknown argument or missing value for "
#define DEPENDECIES "Something wrong with arguments. Maybe there are too many arguments or not enough of them. \n\
Also the problem may be in incorrect data passed to the arguments.\n\
Bad arguments for "
#define OUTPUT "Output file have the same name as input file, or output file is missing"
#define INPUT "Input file is missing"
#define WRONG_FILE "That's the wrong file"




