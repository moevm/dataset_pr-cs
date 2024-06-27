#ifndef INFO_FUNCTIONS_H
#define INFO_FUNCTIONS_H

#include "structures.h"

void print_help();
void print_file_header(const BMP_FileHeader* header);
void print_info_header(const BMP_InfoHeader* header);

#endif
