#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <stdbool.h>
#include <locale.h>

#include "structures.h"
#include "code_runner.h"
#include "delete_capital.h"
#include "input_func.h"
#include "print_func.h"
#include "shift_words.h"
#include "unique_symbols.h"
#include "words_len.h"
#include "replace_big_words.h"

int main(){
    setlocale(LC_ALL, "");
    int fs = 0;
    struct Text original_text;

    wprintf(L"Course work for option 5.13, created by Mikhail Murdasov\n");
    
    int option = change_option();

    switch(option){

        case 0: 
            code_runner(NULL, &original_text, true);
            break;
        
        case 1:
            code_runner(shift_words_in_a_sentence, &original_text, true);
            break;

        case 2:
            code_runner(unique_symbols, &original_text, false);
            break;

        case 3:
            code_runner(words_len, &original_text, false);
            break;

        case 4:
            code_runner(delete_capital, &original_text, true);
            break;

        case 5:
            README();
            break;

        case 9:
            fs = word();
            input_text(&original_text);
            replace_big_words(&original_text, fs);
            print_text(&original_text);
            break;
        default:
            print_error(L"Option number entered incorrectly!");
    }
    
    return 0;
}
