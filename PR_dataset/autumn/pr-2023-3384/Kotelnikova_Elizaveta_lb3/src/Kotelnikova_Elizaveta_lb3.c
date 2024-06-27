#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char* array_txt = malloc(200 * sizeof(char));
    array_txt[0] = '\0';
    int count_symb=0;
    int sum=200;
    char symb;
    int count_do=0;
    int count_posle=0;
    int new_or_old=0;
    while (symb!='!'){
        symb=getchar();
        if ((symb==' ' || symb=='\t') && new_or_old == 0){
            continue;
        }
        else{
        new_or_old=1;
        count_symb+=1;
        if (count_symb+2==sum){
            array_txt=realloc(array_txt, 20*sizeof(char));
            sum+=20;
        }
        if (symb=='.' || symb==';' || symb=='!'){
            new_or_old=0;
            count_do+=1;
            array_txt[count_symb-1]=symb;
            array_txt[count_symb]='\0';
            printf("%s\n", array_txt);
            free(array_txt);
            char* array_txt = malloc(200 * sizeof(char));
            sum=200;
            count_symb=0;
            continue;
        }
        if (symb=='?'){
            new_or_old=0;
            count_posle+=1;
            free(array_txt);
            char* array_txt = malloc(200 * sizeof(char));
            sum=200;
            count_symb=0;
            continue;
        }
        array_txt[count_symb-1]=symb;
        }
    }
    printf("Количество предложений до %d и количество предложений после %d", count_do-1+count_posle, count_do-1);
    free(array_txt);
    return 0;
}