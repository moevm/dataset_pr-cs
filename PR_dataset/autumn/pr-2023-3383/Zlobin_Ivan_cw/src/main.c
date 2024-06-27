#include "main_lib.h"
#include "input.h"
#include "output.h"
#include "cleaning.h"
#include "len_of_word.h"
#include "word_mask.h"
#include "mask_input.h"
#include "middle_len_sort.h"
#include "small_end_len_sort.h"
#include "delete_words.h"
#include "func_description.h"
#include "func.h"

int main(void) {
    setlocale(LC_CTYPE,"");
    wprintf(L"Course work for option 5.2, created by Ivan Zlobin.\n");
    short int n;
    wscanf(L"%hd", &n);
    switch(n){
        case 0:{
            struct Text text=input();
            output(&text);
            cleaning(&text);
            break;
        }
        case 1:{
            wchar_t *mask=mask_input();
            //wprintf(L"%S\n", mask);
            struct Text text=input();
            word_mask(&text, mask);
            output(&text);
            break;
        }
        case 2:{
            struct Text text=input();
            middle_len_sort(&text);
            output(&text);
            cleaning(&text);
            break;
        }
        case 3:{
            struct Text text=input();
            small_end_sort(&text);
            output(&text);
            cleaning(&text);
            break;
        }
        case 4:{
            struct Text text=input();
            del_words(&text);
            output(&text);
            cleaning(&text);
            break;
        }
        case 5:{
            func_description();
            break;
        }
        case 9:{
            struct Text text=sec();
            output(&text);
            cleaning(&text);
            break;
        }
        default:
            wprintf(L"Error: некорректная команда\n");
            break;
     }
    return 0;
}