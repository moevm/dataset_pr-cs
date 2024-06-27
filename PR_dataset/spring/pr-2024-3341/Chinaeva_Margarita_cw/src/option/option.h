#pragma once

#include "help.h"
#include <string.h>
#include "drawing.h"
#include "structs.h"
#include <getopt.h>

check_option do_check();
value do_value();
void check_flags(check_option check);
void get_options( int argc, char* argv[], check_option* check, value* values);
Rgb** do_option(check_option* check, Rgb** arr, value* values, BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);