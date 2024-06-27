#include "structs.h"
BMPFile* openBMPFile(char* filename);
void readRowsBMPFile(FILE* filepath, BMPFile* img);
BMPFile* readBMPFile(char* filename);
void writeBMPFile(char* filename, BMPFile* img);
void freeBMPFile(BMPFile* img);
//int is_bmp(char* arg);
