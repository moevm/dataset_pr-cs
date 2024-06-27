#include "option.h"

void option(int flag){
    if(flag == 5) help();
    else{
        struct Text text;
        switch(flag){
            case 0:
                text_input(&text);
                output_text(&text);
                break;
            case 1:
                text_input(&text);
                set_of_words(&text);
                break;
            case 2:
                text_input(&text);
                data_find(&text);
                output_text(&text);
                break;
            case 3:
                text_input(&text);
                sort(&text);
                output_text(&text);
                break;
            case 4:
                text_input(&text);
                delete_sentences(&text);
                break;
            case 9:
                wchar_t* word = (wchar_t*)calloc(BLOCK, sizeof(wchar_t));
                fgetws(word, BLOCK, stdin);
                text_input(&text);
                big_word(&text, word);
                break;
            default:
                error(0);
        }
    }
}