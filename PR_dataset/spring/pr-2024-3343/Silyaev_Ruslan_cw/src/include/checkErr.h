#ifndef CHECKERR_H
#define CHECKERR_H

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <png.h>

extern const char* inputError;
extern const char* outputError;
extern const char* multipyFuncError;
extern const char* argsError;
extern const char* colorError;
extern const char* typeError;
extern const char* thicknessError;
extern const char* fileTypeError;

void throwError(const char* message, int error);
void checkExtraArguments(Parametrs* par);
void checkColor(RGB color);
void checkFreq(Png* image, Parametrs* par);
void checkSquare(Png* image, Parametrs* par);
void checkExchange(Png* image, Parametrs* par);
void checkContrast(Png* image, Parametrs* par);

#endif