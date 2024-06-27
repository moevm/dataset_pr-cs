#include "structs.h"
#include "fourth_function.h"


struct Text kirill_latin(struct Text text){
    struct Sentence** new_sents = (struct Sentence**) malloc(sizeof(struct Sentence*) * text.size);
    int count_new_sents = 0;
    for (int i = 0; i < text.n; i++){
        int correct_sentence = 1;
        wchar_t* sentence = malloc((wcslen(text.sents[i]->str)+1) * sizeof(wchar_t));
        wcscpy(sentence, text.sents[i]->str);
        wchar_t seps[] = L" ,.";
        wchar_t *state;
        wchar_t *token = wcstok(sentence, seps, &state);
        while (token!=NULL){
            int cyr = 0, lat = 0;
            for (int j = 0; token[j]!=L'\0'; j++){
                if (towlower(token[j]) >= L'a' && towlower(token[j]) <= L'z') lat++;
                if (towlower(token[j]) >= L'а' && towlower(token[j]) <= L'я') cyr++;
            }
            if (cyr>0 && lat>0){
                correct_sentence = 0;
                break;
            }
            token = wcstok(NULL, seps, &state);
        }
        if (correct_sentence){
            new_sents[count_new_sents] = text.sents[i];
            count_new_sents++;
        }
        
    }
    struct Text new_text = {new_sents, count_new_sents, text.size, false};
    return new_text;
}
