#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <wctype.h>
#include <string.h>

#include "structures.h"
#include "sortComp.h"
#include "actions.h"
#include "initialization.h"
#include "informations.h"

int main() {
    setlocale(LC_ALL, "");
    int option = start();
    
        switch (option)
        {
        case L'0': ;
            struct Text text = MakingStruct();
            justOut(&text);
            break;
        case L'1': ;
            struct Text text_1 = MakingStruct();
            coloredOut(&text_1, text_1.len, text_1.dotChecker);
            break;
        case L'2': ;
            struct Text text_2 = MakingStruct();
            HihghtSigns(&text_2);
            break;
        case L'3': ;
            struct Text text_3 = MakingStruct();
            sortSentencesByLastWordLength(&text_3);
            break;
        case L'4': ;
            struct Text text_4 = MakingStruct();
            deleteDigits(&text_4, text_4.len, text_4.dotChecker);
            break;
        case L'8': ;
            struct Text text_8 = MakingStruct();
            palindroms(&text_8, text_8.len, text_8.dotChecker);
            break;
        case L'5': ;
            info();
            break;
        default: ;
            wprintf(L"Error: Oops! Вы должны ввести любую цифру от 0 до 5 включительно.\n");
            break;
        }
    return 0;
}
