//
// Created by rect on 17.11.2023.
//

#ifndef CW_INPUTOUTPUT_H
#define CW_INPUTOUTPUT_H

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#include "structs.h"

int getChoice();
Text getText();
void printText(Text text);
Sentence getSentence(int *nCounter);
#endif //CW_INPUTOUTPUT_H
