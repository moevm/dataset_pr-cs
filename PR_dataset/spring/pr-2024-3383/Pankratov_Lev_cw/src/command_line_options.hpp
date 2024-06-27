#ifndef COMMAND_LINE_OPTIONS_H_
#define COMMAND_LINE_OPTIONS_H_

#include <getopt.h>
#include <iostream>
#include <cctype>

#include "modules/core.hpp"
#include "modules/inverse.hpp"
#include "modules/gray_picture.hpp"
#include "modules/change_size.hpp"
#include "modules/draw_romb.hpp"

void processingFlags(int argc, char **argv);

#endif