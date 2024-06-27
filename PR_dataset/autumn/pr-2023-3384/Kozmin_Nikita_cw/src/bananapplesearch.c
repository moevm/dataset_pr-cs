#ifndef string
#include <string.h>
#endif
#ifndef stdio
#include <stdio.h>
#endif

#include "bananapplesearch.h"

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"


void bananapplesearch(char ***sentences, size_t *cnt_sentences){
    int isnewword;
    int isprint;

    // Проход по предложениям
    for (size_t i=0; i < *cnt_sentences; i++){
        isnewword = 1;
        isprint = 0;

        // Проход по символам предложений
        for (size_t j = 0; (*sentences)[i][j];){
            if (isnewword && !strncmp(&((*sentences)[i][j]), "banana", 6) && 
                    ( (*sentences)[i][j+6]==' ' || (*sentences)[i][j+6]==',' || (*sentences)[i][j+6]=='.' )){
                if (!isprint){
                    for (size_t k = 0; k < j; k++){
                        printf("%c", (*sentences)[i][k]);
                    }
                }
                isnewword = 0;
                isprint = 1;
                printf("%s", YELLOW);
                for (unsigned short k = 0; k < 6; k++){
                    printf("%c", (*sentences)[i][j]);
                    j++;
                }
                printf("%s", RESET);
            }
            else if (isnewword && !strncmp(&((*sentences)[i][j]), "apple", 5) && 
                    ( (*sentences)[i][j+5]==' ' || (*sentences)[i][j+5]==',' || (*sentences)[i][j+5]=='.' )){
                if (!isprint){
                    for (size_t k = 0; k < j; k++){
                        printf("%c", (*sentences)[i][k]);
                    }
                }
                isnewword = 0;
                isprint = 1;
                printf("%s", GREEN);
                for (unsigned short k = 0; k < 5; k++){
                    printf("%c", (*sentences)[i][j]);
                    j++;
                }
                printf("%s", RESET);
            }
            else{
                if (((*sentences)[i][j]==' ' || (*sentences)[i][j]==',')) isnewword = 1;
                else isnewword = 0;
                if (isprint) printf("%c", (*sentences)[i][j]);
                j++;
            }
        }
        if (isprint) printf("\n");
    }
}
