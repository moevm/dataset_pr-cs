#include "../include/print_replace_num.h"

void print_replace_num(Text text){
    int* nums_array = calloc(10, sizeof(int));
    for (int i = 0; i < text.size; i++){
        for (int k = 0; k < wcslen(text.sentences[i].chars); k++){
            if (text.sentences[i].chars[k] >= L'0' && text.sentences[i].chars[k] <= L'9'){
                nums_array[text.sentences[i].chars[k] - L'0']++;
            }
        }
    }
    for (int i = 0; i < text.size; i++){
        for (int k = 0; k < wcslen(text.sentences[i].chars); k++){
            if (text.sentences[i].chars[k] >= L'0' && text.sentences[i].chars[k] <= L'9'){
                wprintf(L"%d", nums_array[text.sentences[i].chars[k] - L'0']);
            } else{
                wprintf(L"%lc", text.sentences[i].chars[k]);
            }
        }
        wprintf(L"\n");
    }
    wprintf(L"\n");
    free(nums_array);
}
