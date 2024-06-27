
#ifndef FILES_INTERACTIONS_H
#define FILES_INTERACTIONS_H

#include "png_class.h"
#include <string>

Png* read_png_file(std::string file_name);
void save_png_file(Png* image, std::string save_path);


#endif