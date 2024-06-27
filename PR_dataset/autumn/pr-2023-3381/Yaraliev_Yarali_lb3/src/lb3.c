#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void readString(char **str) {
    int l = 1;
    char c = getchar();
    *str = malloc(l+1);
    (*str)[0] = c;
    
    while (!(strstr(*str,"Dragon flew away!"))){
        c = getchar();
        *str = realloc(*str,l+3);
        (*str)[l++] = c;
        (*str)[l] = '\0';
    }
    (*str)[l+1] = '\0';
}

void processString(char *str, char **str_output, int *c_before, int *c_after) {
    int l = strlen(str);
    *str_output = malloc(l+1);

    int i = 0;
    (*str_output)[i++] = str[0];
    for (int k = 1; k < l; k++){    
        if(isspace(str[k]) && ((str[k-1] == '.') || (str[k-1] == ';'))){
            (*str_output)[i++] = '\n';
            (*c_before)++;
            (*c_after)++;
        }
        else if(str[k] == '\n'){
            continue;
        }
        else if(~(isspace(str[k])) && ((str[k-1] == '.') || (str[k-1] == ';'))){
            (*str_output)[i++] = '\n';
            (*str_output)[i++] = str[k];
            (*c_before)++;
            (*c_after)++;
        }

        else if(str[k] == '?'){
            int start = k;
            while(((*str_output)[start] != '.') && ((*str_output)[start] != ';') && (start != -1)){
                (*str_output)[start--] = '\0';
            }
            k++;
            i = start+1;
            if (start != -1){
                (*str_output)[i++] = '\n';
            }
            (*str_output)[i] = str[k];
            (*str_output)[i+1] = '\0';
            (*c_before)++;
        }
        else{
            (*str_output)[i++] = str[k];
        }
    }
}

void printOutput(char *str_output, int c_before, int c_after) {
    for(int i = 0; str_output[i]; i++){
        printf("%c", str_output[i]);
    }
    printf("\nКоличество предложений до %d и количество предложений после %d", c_before, c_after);
}

int main(){
    char *str;
    char *str_output;
    int c_before = 0;
    int c_after = 0;
    
    readString(&str);
    processString(str, &str_output, &c_before, &c_after);
    printOutput(str_output, c_before, c_after);
    
    free(str);
    free(str_output);
    
    return 0;
}
