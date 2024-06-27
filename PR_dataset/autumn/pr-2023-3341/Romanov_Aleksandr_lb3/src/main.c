#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define N 256
#define END_OF_STRING '\0'

char *input(int* text_size, int *sentences );
char** split(char *text);
void delete_seven (char** arr, int* rows, int* res_rows);
void output(char** arr, int* rows, int* res_rows);
void trim(char** arr, int* rows);
void clear(char *text, char **arr, int *size, int* rows, int *res_rows);

int main() {

    int *size = (int*)malloc(sizeof(int));
    *size = 1;   
    int *rows = (int*)malloc(sizeof(int));
    *rows = 0;    
        
    char* text = input(size, rows);
    int *res_rows = (int*)malloc(sizeof(int));
    *res_rows = *rows;
    char** array = split(text);
    
    trim(array, rows);
    delete_seven(array, rows, res_rows);
    output(array, rows, res_rows);
    clear(text, array, size, rows, res_rows);
}

char *input(int* text_size, int *sentences ){

    int capacity = 1;
    char *text = (char*)malloc(sizeof(char));
    char ch = getchar();
    
    while (1){
        text[(*text_size)-1] = ch;
        if ((*text_size) >= capacity){
            capacity *= 2;
            text = (char*)realloc(text, capacity * sizeof(char));
        }
        (*text_size)++;
        if (ch ==  ';' || ch == '?' || ch == '.'){
            (*sentences)++;
        }
        if (ch == '!'){
            (*sentences)++;
            break;
        }
        ch = getchar();
    }
    return text;
}

char** split(char *text){

    int length = strlen(text);
    int start = 0;
    char **arr=(char**)malloc(sizeof(char*));
    int lines = 0;
    
    for (int i = 0; i < length; i++) {
        if (text[i] == '.'|| text[i] == '!'|| text[i] == '?'|| text[i] == ';') {
            char *line = (char*)malloc(N*sizeof(char));
            int k = 0;
            
            for (int j = start; j <= i; j++) {
                if (text[j]=='\n'){
                    continue;
                    }
                line[k]=text[j];
                k++;
            }
            
            lines++;
            line[k]=END_OF_STRING;
            arr=(char**)realloc(arr,(lines)*(sizeof(char*)));
            arr[lines-1]=(char*)malloc((1+strlen(line))*sizeof(char));
            strcpy(arr[lines-1], line);
            free(line);
            start = i + 1;
        }
    }
    return arr;
}

void delete_seven (char** arr, int* rows, int* res_rows){

    for (int i = 0; i<(*rows); i++){
        for (int j = 0; j<(strlen(arr[i])); j++){
            if (arr[i][j]=='7'){
                arr[i][0]='\0';
                (*res_rows)-=1;
            }
        }
    }
}

void output(char** arr, int* rows, int* res_rows){

    for (int q = 0; q<(*rows); q++){
        if (arr[q][0]!='\0')
            printf("%s\n", arr[q]);
    }
    printf("Количество предложений до %d и количество предложений после %d", (*rows)-1, (*res_rows)-1);
}

void trim(char** arr, int* rows){

    for (int i = 0; i<(*rows); i++){
        if (arr[i][0]==' ' || arr[i][0]=='\t'){
            for (int j = 0; j<(strlen(arr[i])); j++){
                arr[i][j] = arr[i][j+1];
            }
            arr[i][strlen(arr[i])]='\0';
        }
    }
}

void clear(char *text, char **arr, int *size, int* rows, int *res_rows){

    for (int i = 0; i<(*rows); i++){
        free(arr[i]);
    }
    
    free(size);
    free(rows);
    free(res_rows);
    free(text);
    free(arr);
}
