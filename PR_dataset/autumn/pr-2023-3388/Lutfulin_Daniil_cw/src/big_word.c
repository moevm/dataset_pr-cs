#include "big_word.h"

size_t get_big_word_len(){
    wchar_t word[MAX_BIG_WORD_LEN];
    fgetws(word,MAX_BIG_WORD_LEN*sizeof(wchar_t),stdin);
    return (wcslen(word)-1);
}

Sentence *replace_big_word(Sentence *sentence, size_t big_word_len){
    if (sentence->len<big_word_len){
        return sentence;
    }
    Sentence *new_sentence = malloc(sizeof(Sentence));
    if(new_sentence == NULL)
        leave(MEM_ERROR);
        
    wchar_t big_word[] = BIG_WORD;
    size_t replace_len = wcslen(big_word);
    size_t size_piece = 2*replace_len;
    size_t cur_size = size_piece;
    new_sentence->data = malloc((cur_size)*sizeof(wchar_t));
        if(new_sentence->data == NULL)
        leave(MEM_ERROR);

    size_t new_i = 0; 
    size_t old_i = 0;
    size_t word_start=0, cur_len=0;
    while(old_i<sentence->len){
        new_sentence->data[new_i++] = sentence->data[old_i++];
        if (new_i >= cur_size){
            cur_size+=size_piece;
            new_sentence->data = realloc(new_sentence->data,cur_size*sizeof(wchar_t));
        }
        if(wcschr(L" ,.", sentence->data[old_i]) || old_i == sentence->len){
            cur_len = new_i - word_start;
            if(cur_len > big_word_len){
                new_i = word_start + replace_len;
                if (new_i >= cur_size){
                    cur_size+=size_piece;
                    new_sentence->data = realloc(new_sentence->data, cur_size*sizeof(wchar_t));
                }
                if(!new_sentence->data)
                    leave(MEM_ERROR);
                new_sentence->data[word_start] = SENT_END;
                new_sentence->data = wcscat(new_sentence->data, big_word);
                cur_len = 0;
            }else{
                cur_len = 0;
                word_start = new_i;
            }
            while(wcschr(L" ,.", sentence->data[old_i])){
                new_sentence->data[new_i++] = sentence->data[old_i++];
                if (new_i >= cur_size){
                    cur_size+=size_piece;
                    new_sentence->data = realloc(new_sentence->data,cur_size*sizeof(wchar_t));
                }
            }
            word_start = new_i;
        }
    }
        new_sentence->data[new_i] = SENT_END;
        new_sentence->len = wcslen(new_sentence->data);
        free(sentence->data);
        free(sentence);
        return new_sentence;
}


void replace_big_in_text(Text *text,size_t big_word_len){
    for(size_t i = 0; i<(text->len);i++){
        text->data[i] = replace_big_word(text->data[i],big_word_len);
    }
}
