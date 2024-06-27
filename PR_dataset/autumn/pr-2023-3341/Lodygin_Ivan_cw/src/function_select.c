#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include "structures.h"
#include "error_check.h"
#include "word_replacement.h"
#include "cmp.h"
#include "num_middle.h"
#include "symbols_changer.h"
#include "func9.h"

void function_select() {
    int num;
    wchar_t enter;
    wscanf(L"%d%c", &num, &enter);
    switch(num){
        case(0):{
            struct Text text = read_text();
            if(error_check(text) != 1){
                for(int i = 0; i < text.n; i++){
                    wprintf(L"%ls\n", text.sents[i]->str);
                }
            }
            break;
        }
        case(1):{
            struct Text text = read_text();
            if(error_check(text) != 1) word_replacement(text);
            break;
        }
        case(2):{
            struct Text text = read_text();
            if(error_check(text) != 1){
                qsort(text.sents, text.n, sizeof(struct Sentence *), cmp);
                for(int i = 0; i < text.n; i++) {
                    wprintf(L"%ls\n", text.sents[i]->str);
                }
            }
            break;
        }
        case(3):{
            struct Text text = read_text();
            if(error_check(text) != 1) num_middle(text);
            break;
        }
        case(4):{
            struct Text text = read_text();
            if(error_check(text) != 1) symbols_changer(text);
            break;
        }
        case(5):{
            wprintf(L"Function number 0 displays the text after initial processing.\nFunction number 1 in each sentence replaces the second word with the second word from the previous sentence.\nFunction number 2 sorts all sentences by the length of the third word.\nFunction number 3 displays all sentences that contain words with a number in the middle, highlighting such words in green.\nFunction number 4 in words replaces all symbols that appear several times in a row with one such symbol.\n");
            break;
        case(9):{
            wchar_t symbol;
	        wchar_t word[100];
	        int i = 0;
	        while(symbol != '\n'){
		        symbol = getwchar();
		        word[i] = towupper(symbol);
		        i++;
	        }
            struct Text text = read_text();
            func9(text, word);
            break;
        }
        }
        default:{
            wprintf(L"Error: the function number was entered incorrectly.\n");
        }
    }
}