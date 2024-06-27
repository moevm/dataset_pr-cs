#include "../headers/read-text.h"


int check_end_of_text(int *end_of_text_flag, int end_of_sentence, int *amount_of_sentences){
    if (*end_of_text_flag){
        if (!end_of_sentence){
            wprintf(L"Error: <Введите току в конце последнего предложения, предложение не было считано>\n");
            (*amount_of_sentences) = 0;
        }
        return 1;
    }
    else{

        *end_of_text_flag = 1;
        return 0;
    }
}

void prepare_to_new_sentence(wchar_t **text, wchar_t ch, int *index_of_char, int *amount_of_sentences, int *capacity, int *end_of_sentence){
    text[*amount_of_sentences][*index_of_char] = ch;
    text[*amount_of_sentences][*index_of_char+1] = L'\0';
    (*amount_of_sentences)++;
    *index_of_char = 0;
    *capacity = *end_of_sentence = 1;
}

wchar_t **read_text(int *amount_of_sentences){
    setlocale(LC_ALL, "");
    wchar_t **text = malloc(sizeof(wchar_t*));
    text[*amount_of_sentences] = malloc(sizeof(wchar_t) * 10);
    wchar_t ch;
    int end_of_text_flag = 0, end_of_sentence = 0, capacity = 1, index_of_char=0;
    (*amount_of_sentences)++;
    while(1){
        ch = getwchar();
        if (ch == L'\n'){
            if (check_end_of_text(&end_of_text_flag, end_of_sentence, amount_of_sentences)){
                break;
            }
            text[*amount_of_sentences][index_of_char] = L' ';
            continue;
        }
        else end_of_text_flag = end_of_sentence = 0;

        if (index_of_char >= (capacity-2)){
            capacity*=2;
            text[*amount_of_sentences] = realloc(text[*amount_of_sentences], sizeof(wchar_t)*capacity);
        }
        if (ch == L'.'){
            prepare_to_new_sentence(text, ch, &index_of_char, amount_of_sentences, &capacity, &end_of_sentence);
            text = realloc(text, sizeof(wchar_t*)*((*amount_of_sentences)+1));
            text[*amount_of_sentences] = malloc(sizeof(wchar_t));
            continue;
        } else if((ch == L' ' || ch == L'\t') && index_of_char == 0) continue;

        text[*amount_of_sentences][index_of_char] = ch;
        index_of_char++;
    }
    return text;
}
