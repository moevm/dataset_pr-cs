#ifndef CHECKDATA_H
#define CHECKDATA_H

#define FILE_ERROR 40

#define FILE_FORMAT_ERROR 41

#define MISSING_ARGUMENTS_ERROR 42

#define ARGUMENTS_ERROR 43

#define MULTIPLE_TASK_ERROR 44

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <png.h>

void raiseError(const char* message, int error);
void checkExtraArgs(OptParams* opt);
void checkCopy(Png* image, OptParams* opt);
void checkColor(RGB color);
void checkReplace(Png* image, OptParams* opt);
void checkOrnament(Png* image, OptParams* opt);
void checkRects(Png* image, OptParams* opt);
void checkOutside(Png* image, OptParams* opt);

extern const char* fileTypeError;
extern const char* inputError;
extern const char* outputIsImputError;

extern const char* colorError;
extern const char* patternError;
extern const char* thicknessError;
extern const char* countError;

extern const char* argsError;
extern const char* taskError;

#endif