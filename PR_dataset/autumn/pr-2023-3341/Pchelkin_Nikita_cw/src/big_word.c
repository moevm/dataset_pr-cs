#include "big_word.h" 

void big_word(struct Text* text, wchar_t* word){
    wchar_t* result;
    int size_limit = wcslen(word)-1;
    int size_of_word, word_start, word_end;
    int j, step;
    wchar_t* before;
    wchar_t* after;
    for(int i = 0; i < text->size; i++){
        step = 0;
        result = wcsdup(text->text[i].sentence);
        before = calloc(text->text[i].size, sizeof(wchar_t));
        after = calloc(text->text[i].size, sizeof(wchar_t));
        j = 0;
        while (j < text->text[i].size){
            size_of_word = 0;
            word_start = j;
            while(!wcschr(L"., \t", text->text[i].sentence[j])){
                size_of_word++;
                j++;
            }
            word_end = word_start + size_of_word;
            
            if(size_of_word > size_limit){

                wcsncpy(before, result, word_start+step);
                for(int k = word_end; k < text->text[i].size; k++){
                    after[k - word_end] = text->text[i].sentence[k];
                }
                swprintf(result, wcslen(result)+16, L"%ls(большое слово)%ls", before, after);
                step += 15-size_of_word;
            }
            j++;
        }
    wprintf(L"%ls\n", result);   
    }
}
