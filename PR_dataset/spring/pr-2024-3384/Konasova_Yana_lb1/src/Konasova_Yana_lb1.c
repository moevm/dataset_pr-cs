#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define MASSIV 100
#define STEP 20

char* read_sent() {
    char* arr = malloc(MASSIV);
    int size_arr = MASSIV;
    char symb_now ;
    int amount_sym = 0;
    while ((symb_now = getchar()) != '\n' && symb_now!=EOF) {
        if (amount_sym >= size_arr - 1) {
            size_arr += STEP;
            arr = (char*)realloc(arr, size_arr);
        }
        arr[amount_sym] = symb_now;
        arr[amount_sym + 1] = '\0';
        amount_sym++;
    }
    return arr;
}

int main() {
    char** arr1 = malloc(MASSIV * sizeof(char*));
    char* f = "Fin.";
    int size_arr1 = MASSIV;
    int k = 0;
    while (1) {
        if (k>=size_arr1-1){
            size_arr1+=STEP;
            arr1=(char**)realloc(arr1, size_arr1*sizeof(char*));
        }
        arr1[k] = read_sent();
        if (strcmp(arr1[k], f) == 0) { 
            break;
        }
        k++;
    }


    regex_t reegex;
    int val;
    const char* pattern = "([a-zA-Z]+://)?(www\\.)?([a-zA-Z0-9-]+(\\.[a-zA-Z0-9]+)+)/((\\w+/)*)([a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+))*$";
    
    val = regcomp(&reegex, pattern, REG_EXTENDED);

    if (val != 0) {
        fprintf(stderr, "Ошибка компиляции регулярного выражения\n");
        free(arr1);
        return 1;
    }
    int suc=0;
    regmatch_t matches[9];
    for (int i=0; i<k; i++){
        if (regexec(&reegex, arr1[i], 9, matches, 0) == 0){
            for (int j=0; j<9; j++){
                if (matches[j].rm_so==-1){
                    break;
                }
            }
            if (suc>0){
                printf("\n");
            }
            
            for(int j = matches[3].rm_so; j<matches[3].rm_eo; j++){
                printf("%c", arr1[i][j]);
            }
            
            printf(" - ");
            for(int j = matches[7].rm_so; j<matches[7].rm_eo; j++){
                printf("%c", arr1[i][j]);
            }
            suc++;
            
        }
    }


    regfree(&reegex);
    for (int i = 0; i<k ; i++) {
        free(arr1[i]);
    }

    free(arr1);

    return 0;
}
