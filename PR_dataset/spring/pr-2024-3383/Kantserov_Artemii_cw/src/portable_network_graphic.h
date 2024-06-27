#ifndef CW_START_PORTABLE_NETWORK_GRAPHIC_H
#define CW_START_PORTABLE_NETWORK_GRAPHIC_H

void info(struct Png* image);

int write_png_file(const char* file_name, struct Png* image);

int read_png_file(const char* file_name, struct Png* image);

#endif //CW_START_PORTABLE_NETWORK_GRAPHIC_H
