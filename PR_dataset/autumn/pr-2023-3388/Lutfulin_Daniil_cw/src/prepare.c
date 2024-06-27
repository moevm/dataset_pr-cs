#include "prepare.h"

wchar_t *read(){
    wchar_t last_char;
    wchar_t cur_char;
    bool end_flag = false;
    size_t text_index = 0;
    wchar_t *input = (wchar_t*)malloc(sizeof(wchar_t));
    if (input == NULL)
        leave(MEM_ERROR);
    while(end_flag!= true){
        if(text_index%TEXT_PIECE==0){
            input = realloc(input, ((TEXT_PIECE+text_index+1)*sizeof(wchar_t)));
            if (input == NULL)
                leave(MEM_ERROR);
        }
        cur_char = getwchar();
        if(cur_char == WEOF)
            leave(INPUT_ERROR);
        if (cur_char == L'\n' && last_char == L'\n'){ 
            end_flag = true;
            input[--text_index] = SENT_END;
            break;
        }else{
            input[text_index++] = cur_char;
            last_char = cur_char;
            }
        }

    input = realloc(input, (text_index+1)*sizeof(wchar_t));
    if (input == NULL)
        leave(MEM_ERROR);
    return input;
}

Sentence* record_sentence(int *index, wchar_t *input){
    
    while (iswspace(input[(*index)])){
        (*index)++;
    }

    Sentence *sentence = (Sentence*)malloc(sizeof(Sentence));
    if (sentence == NULL)
        leave(MEM_ERROR);
    sentence->data = (wchar_t*)malloc(sizeof(wchar_t));
    if(sentence->data == NULL)
        leave(MEM_ERROR);
    size_t i = 0;
    do{ 
        sentence->data[i] = input[(*index)++];
        
        if (sentence->data[i] == SENT_END){
            if(input[*index-2] == L'.'){
                *index = -1;
                free(sentence->data);
                free(sentence);
                return NULL;
            }
            *index = -1;
            break;
        }
        if (i % TEXT_PIECE == 0){
            sentence->data = realloc(sentence->data, (TEXT_PIECE+i+1)*sizeof(wchar_t));
            if (sentence->data == NULL)
                leave(MEM_ERROR);
        }
        i++;
    } while(sentence->data[i-1] != (L'.'));
    sentence->data[i] = SENT_END;
    sentence->data = realloc(sentence->data, (i+1)*sizeof(wchar_t));
    if (sentence->data == NULL)
        leave(MEM_ERROR);
    sentence->len = i;
    return sentence;
}

bool check_same(Text *text, Sentence *sentence){
    bool is_same;
    if (text->len == 0)
        return false;
    for(size_t i = 0; i<text->len;i++){
        if (text->data[i]->len == sentence->len){
            is_same = true;
            for (size_t j = 0; j<sentence->len;j++){
                wchar_t a = towupper(text->data[i]->data[j]);
                wchar_t b = towupper(sentence->data[j]);
                if (a != b){
                    is_same = false;
                    break;
                    }
                }
            if(is_same)
                return true;
        }
    }
    return false;
}

Text* read_text_and_delete_repeats(){
    wchar_t *input = read();
    Text *text = (Text*)malloc(sizeof(Text));
    if(text == NULL)
        leave(MEM_ERROR);
    text->len = 0;
    text->data = (Sentence**)malloc(sizeof(Sentence*));
    if(text->data == NULL)
        leave(MEM_ERROR);
    int index = 0;
    while(index!=-1){
        Sentence *sentence = record_sentence(&index, input);
        if (sentence ==  NULL)
            break;
        if (!check_same(text, sentence)){
            text->data = realloc(text->data, (text->len+1)*sizeof(Sentence*));
            if(text->data == NULL)
                leave(MEM_ERROR);
            text->data[text->len] = sentence;
            text->len++;
        }else{
            free(sentence->data);
            free(sentence);
        }
    }
    free(input);
    return text;
}
