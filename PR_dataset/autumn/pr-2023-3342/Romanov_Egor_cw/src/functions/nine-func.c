#include "../headers/nine-func.h"


int check_word(wchar_t* f_word, wchar_t* s_word){
    if (wcslen(f_word) != wcslen(s_word)) return 0;

    for (int i=0;i<wcslen(f_word);i++){
        if (towlower(f_word[i]) != towlower(s_word[i])){
            return 0;
        }
    }
    return 1;
}

int check(wchar_t* word, wchar_t** sentence, int amount_of_sentence){
    for(int i=0;i<amount_of_sentence+1;i++){
        // wprintf(L"%ls %ls\n", word, sentence[i]);
        if(check_word(word, sentence[i])){
            return 1;
        }
    }
    return 0;
}

void function_nine(struct Text text, wchar_t** f_sent, int amount_of_words){
    for (int i=0;i<text.quantity_of_sentences;i++){
        int flag=1;
        for (int y=0;y<text.sentences[i].quantity_of_words;y++){
            if (!check(text.sentences[i].words[y].word, f_sent, amount_of_words)){
                flag=0;
                break;
            }
        }
        if (flag && i!=0){
            wprintf(L"%ls\n", text.sentences[i].sentence);
        }
    }
    // output(text);
}
