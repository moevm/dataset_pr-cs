#ifndef ctype
#include <ctype.h>
#endif
#ifndef stdlib
#include <stdlib.h>
#endif
#ifndef string
#include <string.h>
#endif

#include "conversiontobinary.h"


void conversiontobinary(char ***sentences, size_t *cnt_sentences){
    int isnum = 0;
    size_t num_start_index;
    char *num_str = NULL;
    int num;
    size_t num_bin_len;
    for (size_t i = 0; i < *cnt_sentences; i++){
        for (size_t j = 0; (*sentences)[i][j]; j++){
            if (isdigit((*sentences)[i][j]) && isnum==0){
                num_start_index = j;
                num_str = realloc(num_str, sizeof(char)*(j-num_start_index+2));
                num_str[j-num_start_index] = (*sentences)[i][j];
                num_str[j-num_start_index+1] = '\0';
                isnum = 1;
            }
            else if (isdigit((*sentences)[i][j]) && isnum==1){
                num_str = realloc(num_str, sizeof(char)*(j-num_start_index+2));
                num_str[j-num_start_index] = (*sentences)[i][j];
                num_str[j-num_start_index+1] = '\0';
            }
            else if (!isdigit((*sentences)[i][j]) && isnum==1){
                // *перевод до текущего j (не включая), выделение памяти*
                num = atoi(num_str);
                free(num_str);
                num_str = NULL;
                num_bin_len = 0;
                while (num){
                    num_bin_len += 1;
                    num_str = realloc(num_str, sizeof(char)*(num_bin_len+1));
                    num_str[num_bin_len] = '\0';
                    num_str[num_bin_len-1] = (num % 2)+'0';
                    num /= 2;
                }
                num_str = realloc(num_str, sizeof(char)*(num_bin_len+3));
                for (size_t m = strlen(num_str)+2; m != 1; m--){
                    num_str[m] = num_str[m-2];
                }
                num_str[0] = '0';
                num_str[1] = 'b';
                for (size_t k = num_start_index; num_str[0]; k++){
                    if (!isdigit((*sentences)[i][k])){
                        (*sentences)[i] = realloc((*sentences)[i], (strlen((*sentences)[i])+2)*sizeof(char));
                        for (size_t m = strlen((*sentences)[i])+1; m != k; m--){
                            (*sentences)[i][m] = (*sentences)[i][m-1];
                        }
                        j++;
                    }
                    (*sentences)[i][k] = num_str[0];
                    for (size_t m = 0; num_str[m]; m++){
                        num_str[m] = num_str[m+1];
                    }
                }
                isnum = 0;
            }
        }
    }
}
