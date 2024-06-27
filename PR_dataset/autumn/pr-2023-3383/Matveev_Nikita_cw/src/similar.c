#include "similar.h"
void similar(struct Text start){
    
    int count = start.size;
    for (int i=0; i<count; i++){
        wchar_t* sent = wcsdup(start.sentences[i]);
        wchar_t* ptr;
        wchar_t* word;
        wchar_t** words = (wchar_t**)malloc(sizeof(wchar_t*));
        int mem =1;
        int len = 1;
        word = wcstok(sent, L",  .\n", &ptr);
        words[0] = wcsdup(word);
        while (word !=NULL){
            if (len +2>= mem){
                mem *= MEM_STEP;
                words = (wchar_t**)realloc(words, mem*sizeof(wchar_t*));
            }
            word = wcstok(NULL, L",  .\n", &ptr);
            if (word != NULL){
                words[len++] = wcsdup(word);
            }
        }
        int all_similar = 0;
        int num_sim[len];
        for (int j=0; j <len; j++){
            num_sim[j] =0;
        }
        for (int j = 0; j< len-1; j++){
            int same = 1;
            for (int jj = j+1; jj<len; jj++){
                if (wcscmp(words[j], words[jj])== 0 && num_sim[jj] != -1){
                    same++;
                    num_sim[jj] = -1;
                }
            }
            if (same!= 1){
                all_similar += same;
            }

        }
        wprintf(L"Одинаковых слов: %d\n",all_similar);
        for (int j =0; j<len; j++){
            free(words[j]);
        }
        free(sent);
        free(words);
    }
}
