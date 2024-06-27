#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define BLOCK_SIZE 10

int prov_upper(char* str, int len){
    int s=0;
    for(int i=0;i<len;i++){
        if(isupper(str[i])){
            s++;
        }
    }
    if(s>=2){
        return 1;
    }
    else{
        return 0;
    }
}


int main(){
    char* str = (char*)malloc(BLOCK_SIZE);
    int pam = BLOCK_SIZE;
    int len = 0;
    str[len] = getchar();
    int pred_before  = 0;
    int pred_after = 0;
    while(1){
        if(len == 0 && isspace(str[len])){
            str[len] = getchar();
            continue;
        }

        if(str[len] == '.' || str[len] == ';' || str[len] == '?'){
            str[len+1] = '\0';
            int prov=prov_upper(str,len);
            if(prov==0){
                puts(str);
                pred_after++;
            }
            pred_before++;
            free(str);
            str = (char*)malloc(BLOCK_SIZE);
            len = 0;
            pam = BLOCK_SIZE;
            str[len] = getchar();
            continue;
        }

        if(str[len] == '!'){
            str[len+1] = '\0';
            puts(str);
            break;
        }
        len++;
        if(len == pam){
            str = (char*)realloc(str, pam+BLOCK_SIZE);
            pam += BLOCK_SIZE;
        }
        str[len] = getchar();

    }

    printf("Количество предложений до %d и количество предложений после %d", pred_before , pred_after);
    return 0;
    
}
