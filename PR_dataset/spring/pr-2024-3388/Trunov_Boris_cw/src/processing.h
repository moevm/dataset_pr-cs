#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "bmp.h"
#include "read_bmp.h"
#include "save_bmp.h"
#include "reverse_color.h"
#include "gray_image.h"
#include "help.h"
#include "print_info_header.h"
#include "check_coords.h"
#include "failure.h"
#include "draw_line.h"
#include "check_line_metainfo.h"
#include "resize.h"
#include "defines.h"
#include "ramka.h"

int processing(int argc, char ** argv);
