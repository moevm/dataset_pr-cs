#include "model.h"
#include "sort.h"
void model(struct Text start){

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

        qsort(words, len, sizeof(wchar_t*), len_cmp);

        wchar_t* mask = wcsdup(words[0]);
        //до сюда все окей!

        for (int j =0; j<wcslen(mask); j++){
            for (int jj=1; jj<len; jj++){
                if (wcschr(words[jj], mask[j]) == NULL){
                    mask[j] = L'?';

                    break;
                }
            }
        }
        //ok
        wchar_t* so_mask = wcsdup(mask);
        //wprintf(L"%ls\n", mask);
        if (wcsspn(mask, L"?")==wcslen(mask)){
            free(mask);
            mask =wcsdup(L"*");
            wprintf(L"%ls\n", mask);
            free(mask);
            for (int j =0; j<len; j++){
                free(words[j]);
            }
            //free(word);
            free(so_mask);
            free(words);
            free(sent);
            continue;
        }


        int start_id = 0;
        int s_count =0;
        for (int j =0; j< wcslen(mask); j++){
            if (mask[j] != L'?'){
                start_id = j;
                break;
            }
            s_count++;
        }
        int flag_tab = 0;
        for (int j=1; j<len; j++){
            wchar_t** different_masks = (wchar_t**)malloc(5*sizeof(wchar_t*));
            int counter = 0;
            int lengthy = 0;
            for (int jj =0; jj<wcslen(mask); jj++){
                if (mask[jj] != L'?'){
                    wchar_t* mm = (&mask[jj]);
                    for (int w =0; w<wcslen(words[j]); w++){
                        if (words[j][w] == mask[jj]){
                            wchar_t* mb_mask = (wchar_t*)malloc((wcslen(mask)+1)* sizeof(wchar_t));
                            int good = 0;
                            wchar_t* wmm = &words[j][w];
                            while (*mm != L'\0' && *wmm != L'\0'){
                                if (*mm == *wmm ){
                                    mb_mask[good++] = *wmm;
                                    mm++;
                                    wmm++;
                                }
                                else {
                                    mb_mask[good++] = L'?';
                                    mm++;
                                    wmm++;
                                }

                            }
                            mb_mask[good] = L'\0';
                            lengthy++;
                            if (lengthy+2 >= 5){
                                different_masks = (wchar_t**)realloc(different_masks, (lengthy+2)*sizeof(wchar_t*));
                            }
                            mm = (&mask[jj]);
                            different_masks[counter++] = wcsdup(mb_mask);
                            free(mb_mask);

                        }
                    }
                }
            }
            qsort(different_masks, counter, sizeof(wchar_t*), cmp_mask);
            free(mask);
            mask = wcsdup(different_masks[0]);
            for (int clean =0; clean<counter; clean++){
                free(different_masks[clean]);
            }
            free(different_masks);


        }//цикл массива масок финиш
        //wprintf(L"%ls\n", mask);


        int q_flag =0;
        for (int j =1; j<len; j++){
            int lens_word=0;
            for (int jj=0; jj<wcslen(mask); jj++){
                if (words[j][lens_word++] == mask[jj] || mask[jj]==L'?'){
                    q_flag = -1;

                }
                else{
                    q_flag =1;
                    break;
                }
            }
            if (q_flag ==-1){
                break;
            }
        }
        int c =0;
        while (so_mask[c]!= mask[0]){
            so_mask[c] = L'?';
            c++;
        }
        //wprintf(L"%ls\n", so_mask);
        //wprintf(L"%d\n", c);
        //wprintf(L"%ls\n", mask);
        if (q_flag == 1){
            wchar_t* copy_mask = wcsdup(mask);
            mask = (wchar_t*)realloc(mask, (wcslen(mask)+c+1)*sizeof(wchar_t));
            for (int j =0; j<c; j++){
                mask[j] = L'?';
            }
            for (int j =0, jj=c; j<wcslen(copy_mask); j++){
                mask[jj++] = copy_mask[j];
            }
            mask[wcslen(copy_mask)+c] = L'\0';
            free(copy_mask);
        }


        //wprintf(L"%ls\n", mask);
        //wprintf(L"%d\n", wcslen(mask));
        wchar_t first_sy;
        int first_in = 0;
        for (int j = 0; j<wcslen(mask); j++){
            if (mask[j] != L'?'){
                first_sy = mask[j];
                first_in = j;
                break;
            }
        }

        wchar_t last_sy;
        int last_in =0;
        for (int j = 0; j<wcslen(mask); j++){
            if (mask[j] != L'?'){
                last_sy = mask[j];
                last_in = j;
            }
        }


        //ok
        int star_flag =0;
        for (int j=1; j<len; j++){
            if ((int)(wcschr(words[j], first_sy) - words[j]) > first_in){
                star_flag = 1;
                break;
            }
        }
        int flag_star =0;
        for (int j=1; j<len; j++){
            if ((int)(wcsrchr(words[j], last_sy) - words[j]) <=last_in){
                flag_star = 1;
                break;
            }
        }

        if (star_flag == 1){
            wchar_t* our_copy_mask = wcsdup(mask);
            //wprintf(L"%ls\n", our_copy_mask);
            int lenn = wcslen(mask);

            mask = (wchar_t*)realloc(mask, (lenn+2)*sizeof(wchar_t));
            mask[0] = L'*';
            for (int j =0, jj=1; j<wcslen(our_copy_mask); j++){
                mask[jj++] = our_copy_mask[j];
            }
            mask[lenn+1] = L'\0';
            free(our_copy_mask);
        }

        if (flag_star ==1){
            wchar_t* our_copy_mask = wcsdup(mask);
            int lenn = wcslen(mask);
            mask = (wchar_t*)realloc(mask, (lenn+2)*sizeof(wchar_t));
            for (int j =0, jj=0; j<wcslen(our_copy_mask); j++){
                mask[jj++] = our_copy_mask[j];
            }
            mask[lenn] = L'*';
            mask[lenn+1] = L'\0';
            free(our_copy_mask);
        }

        wprintf(L"%ls\n", mask);
        free(mask);
        for (int j =0; j<len; j++){
            free(words[j]);
        }
        //free(copy_mask);
        free(so_mask);
        free(words);
        free(sent);

    }//1 sentence finish
}
