#ifndef FLAGS_PROCESSING_H
#define FLAGS_PROCESSING_H

#include "structures.h"
#include "info_functions.h"

void init_param(Parameters* param);
void check_parameters(Parameters* param);
void parse_command_line(int argc, char* argv[], Parameters* param);

#endif
