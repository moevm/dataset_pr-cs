#include "../include/cwfunc.h"

int word_suits(wchar_t *wordFromSentence, wchar_t *word){
    for (int i = 0; i < wcslen(wordFromSentence); i++){
        int exists = 0;
        for (int j = 0; j < wcslen(word); j++){
            if (towupper(word[j]) == towupper(wordFromSentence[i])){
                exists = 1;
            }
        }
        
        if (exists == 0){
            return 0;
        }
    }
    return 1;
}

void print_words(Sentence sentence, wchar_t* word){
    wchar_t* context;
    wchar_t* token = wcstok(sentence.chars, L" ,.", &context);
    while (token != NULL)
    {
        if (word_suits(token, word)){ 
            wprintf(L"%ls\n", token);
        }
        token = wcstok(NULL, L" ,.", &context);
    }
    
}

void print_words_from_text(wchar_t* word, Text text){
    for (int i = 0; i < text.size; i++){
        print_words(text.sentences[i], word);
    }
}