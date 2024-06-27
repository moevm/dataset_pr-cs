#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>

#include "structures.h"
#include "delete_capital.h"
#include "input_func.h"
#include "print_func.h"
#include "shift_words.h"
#include "unique_symbols.h"
#include "words_len.h"

void code_runner(void (*func)(struct Text*), struct Text* text, bool print){

    if(func == NULL && print == true){
        input_text(text);
        print_text(text);
    }
    if(func != NULL && print == true){
        input_text(text);
        func(text);
        print_text(text);
    }
    if(func != NULL && print == false){
        input_text(text);
        func(text);
    }
}
