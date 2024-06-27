#include <stdlib.h>

#include "output.h"
#include "help.h"
#include "error.h"
#include "structures.h"
#include "countWords.h"
#include "replaceNonAlphaWithCode.h"
#include "sortByLatinSymbols.h"
#include "removeUpperAndSpecialSymbolsCase.h"

#include "func9.h"

int textWillBeEntered(int testType) {
    if ((testType < 0 || testType > 5) && testType != 9) {
        throwTestTypeError();
        return 0;
    } else if (testType == 5) {
        help();
        return 0;
    }
    return 1;
}

void allocator(Text* text, int testType, wchar_t* str) {
    switch (testType)
    {
    case 0:
        printText(text);
        break;
    case 1:
        countWords(text);
        break;
    case 2:
        replaceNonAlphaWithCode(text);
        printText(text);
        break;
    case 3:
        sortByLatinSymbols(text);
        printText(text);
        break;
    case 4:
        removeUpperAndSpecialSymbolsCase(text);
        printText(text);
        break;
    case 9:
        func9(str, text);
        break;
    }
}
