#include "start_and_choose_function.h"


int start(){
    wprintf(L"%ls\n",START_INFO);
    return 0;
}

void print_text(Text *text){
    for(size_t i =0; i<(text->len);i++)
        wprintf(L"%ls\n", text->data[i]->data);
}

void choose_function(){
    int function_number;
    wscanf(L"%d%*c", &function_number);
    size_t big_word_len;
    if(function_number == 5){
        leave(HELP);
    }else{
        if (function_number == 9)
            big_word_len = get_big_word_len();
        Text *text = read_text_and_delete_repeats();
        switch(function_number){
            case 0:
                print_text(text);
                break;
            case 1:
                print_palindromes(text);
                break;
            case 2:
                replace_special_in_text(text);
                print_text(text);
                break;
            case 3:
                sort_latin(text);
                print_text(text);
                break;
            case 4:
                text = delete_two_language_sentences(text);
                print_text(text);
                break;
            case 9:
                replace_big_in_text(text, big_word_len);
                print_text(text);
                break;
            default:
                leave(CHOOSE_FUNC_ERROR);
        }
	free_text(text);
    }
}

