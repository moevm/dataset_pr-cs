#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>

char** split(char *text, int *rows);
char *input(int* text_size, int* rows);

int vowel(char let);
int initializer(char switch_ch);
int output_manager(char switch_ch);
int comp (const void* a, const void* b);

void info();
void delete_words(char* text);
void trim(char** arr, int* rows);
void output(char** arr, int* rows);
void connector(char* text, int* rows);
void change_heroes(char** arr, int* rows);
void delete_unlucky(char** arr, int* rows);
void advanced_output(char** arr, int* rows);
void delete_duplicates(char **arr, int *rows);
void clear(int* size,  int* lines, char* text, char** arr);

int main(){
    printf("Course work for option 4.9, created by Romanov Aleksandr\n");
    char switch_ch;
    //printf("Введите число от 1 до 5 ");
    scanf("%c\n", &switch_ch);
    output_manager(switch_ch);
}


int output_manager(char switch_ch){

    if(isdigit(switch_ch)==0){
        printf("Error: было введено не число");
        return 0;
    }
    
    int switcher = switch_ch - '0';

    if(switcher<0 || (switcher>5 && switcher!=9)){
        printf("Error: было введено некорректное число");
        return 0;
    }
    
    if (switcher == 5){
    	info();
    	return 0;

    }
    
    int *rows = (int*)malloc(sizeof(int));
    int *size = (int*)malloc(sizeof(int));
    *size = 1;   
    *rows = 0;

    char *text = input(size, rows);
    char **arr = split(text, rows);


    trim(arr, rows);
    delete_duplicates(arr, rows); 

    switch(switcher){
    	case 0:
    	    output(arr, rows);
            break;
    	case 1:
    	    change_heroes(arr, rows);
    	    printf("\n");
    	    output(arr, rows);
    	    break;
    	case 2:
    	    qsort(arr, (*rows), sizeof(char*), comp);
    	    output(arr, rows);    	    
    	    break;
    	case 3:
	        delete_unlucky(arr, rows);
	        output(arr, rows);
    	    break;
    	case 4:
    	    advanced_output(arr, rows);
    	    break;
        case 9:
            connector(text, rows);
            break;
    	default:
    	    printf("We are not supposed to be here...");
    	    break;
    }
    return 1;
} 


char *input(int* text_size, int* rows){

    int capacity = 1;
    char *text = (char*)malloc(sizeof(char));
    char ch = getchar();
    char prev_ch = 'z';
    
    while (1){
        text[(*text_size)-1] = ch;
        if ((*text_size) >= capacity){
            capacity *= 2;
            text = (char*)realloc(text, capacity * sizeof(char));
        }
        (*text_size)++;
        if(ch=='.'){
            (*rows)++;
        }

        if (ch == '\n' && prev_ch=='\n'){
            int end = strlen(text)-1;
            while((text[end]=='\n'||text[end]==' ')){
                end--;
            }
            if (text[end]=='.'){
                text[end+1]='\0';
                break;
            }
            else{
                text[end+1]='.';
                (*rows)++;
                text[end+2]='\0';
                break;
            }
        }
        prev_ch = ch;
        ch = getchar();
    }
    return text;
}

char** split(char *text, int* rows){
    int length = strlen(text);
    int start = 0;
    int end = 0;
    int line = 0;
    char** arr = (char**)malloc(((*rows)) * sizeof(char*)); 

    for(int i = 0; i < length; i++){
        if(text[i] == '.'){
            end = i;
            arr[line] = (char*)malloc((end - start + 2) * sizeof(char)); 
            int symb = 0;
            for(int j = start; j <= end; j++){
                arr[line][symb] = text[j];
                symb++;
            }
            arr[line][symb] = '\0';
            line++;
            if(i + 1 < length){
                start = i + 1;
            }
            else{
                break;
            }
        }
    }
    return arr;
}

void delete_duplicates(char **arr, int *rows){
        for(int i = 0; i<(*rows); i++){
        int len_first = strlen(arr[i]);
        for(int j = i+1; j<(*rows); j++){
            int flag = 0;
            int len_second = strlen(arr[j]);
            if(len_first==len_second){
                for(int x = 0; x<strlen(arr[i]); x++){
                    if(tolower(arr[i][x])==tolower(arr[j][x])){
                        flag++;
                    }
                if (flag==len_second){
                    arr[j][0]='\0';
                }
                }
            }
        }
    }
}

void info(){
    printf("function 1 : change substring Robin to substring I am Batman\n");
    printf("function 2 : sort the sentences by the number of commas\n");
    printf("function 3 : delete all the sentences where the sum of digits equals 13\n");
    printf("function 4 : print only sentences begining with avowel or a digit\n");
    printf("function 5 : shows information about available functions\n");
}

void trim(char** arr, int* rows){

    for (int i = 0; i<(*rows); i++){
        while (arr[i][0]==' ' || arr[i][0]=='\t' || arr[i][0]=='\n'){
            for (int j = 0; j<(strlen(arr[i])); j++){
                arr[i][j] = arr[i][j+1];
            }
            arr[i][strlen(arr[i])]='\0';
        }
    }
}

void delete_unlucky(char** arr, int* rows){
    
    for (int i = 0; i<(*rows); i++){
    int sum = 0;
        for (int j = 0; j<(strlen(arr[i])); j++){
            if (isdigit(arr[i][j])){
            	sum+=(arr[i][j]-'0');
            }
        if (sum == 13){
            arr[i][0] = '\0';
        }
        }
    }
}

int vowel(char letter){

    char vowels[] = {'A', 'E', 'I', 'O', 'Y', 'U'};

    for (int i = 0; i<5; i++){
    	if (toupper(letter) == vowels[i]){
    	    return 1;
    	}
    }
    return 0;
}

void advanced_output(char** arr, int* rows){

    for(int i = 0; i<(*rows); i++){
        if (arr[i][0]!='\0' && (isdigit(arr[i][0]) || vowel(arr[i][0]))){
            if (i==(*rows)-1){
                printf("%s", arr[i]);
                break;
            }
            printf("%s\n", arr[i]);
            }
    }
    
}

void output(char** arr, int* rows){

    for (int q = 0; q<(*rows); q++){
        if (arr[q][0]=='.'){
            continue;
        }
        else{
            if (arr[q][0]!=0){
                printf("%s\n", arr[q]);
        }
    }
        }


}



void change_heroes(char** arr, int* rows) {

    for (int i = 0; i < (*rows); i++) {
        char* pointer = strstr(arr[i], "Robin");
        while (pointer != NULL) {
            int len = strlen(arr[i]);
            int robin_len = strlen("Robin");
            int batman_len = strlen("I am Batman");
            int new_len = len - robin_len + batman_len;

            char* new_str = (char*)malloc((new_len + 1) * sizeof(char));

            int breakpoint = pointer - arr[i];
            strncpy(new_str, arr[i], breakpoint);
            new_str[breakpoint] = '\0';
            strcat(new_str, "I am Batman");
            strcat(new_str, arr[i] + breakpoint + robin_len);

            free(arr[i]);
            arr[i] = new_str;

            pointer = strstr(arr[i], "Robin");
        }
    }
}

int comp(const void* a, const void* b) {
    const char *first = *(const char**)a;
    const char *second = *(const char**)b;
    
    int commas_f = 0;
    int commas_s = 0;
    for(int i = 0; i < strlen(first); i++) {
        if (first[i] == ',') {
            commas_f++;
        }
    }
    for(int i = 0; i < strlen(second); i++) {
        if (second[i] == ',') {
            commas_s++;
        }
    }

    if (commas_f > commas_s) {
        return 1;
    } else if (commas_f < commas_s) {
        return -1;
    }
    return 0;
}

void clear(int* size,  int* lines, char* text, char** arr){
    for(int i = 0; i<(*lines)-1; i++){
        free(arr[i]);
    }
    free(arr);
    //free(text);
    free(size);
    free(lines);
}

void connector(char* text, int* rows){
    int length = strlen(text);
    int start = 0;
    int end = 0;
    int line = 0;
    char** arr = (char**)malloc(((*rows)) * sizeof(char*)); 
    char connect[100];
    int ender = 0;
    for (int i = 1; i<length; i++){
        if(text[i] == '\n'){
            ender = i;
            for(int j = 0; j<ender; j++){
                connect[j] = text[j];
            }
            connect[ender] = '\0';
            break;
        }
        

    }
    start = ender+1;
    for(int i = start; i < length; i++){
        if(text[i] == '.'){
            end = i-1;
            arr[line] = (char*)malloc((end - start + 2) * sizeof(char)); 
            int symb = 0;
            for(int j = start; j <= end; j++){
                arr[line][symb] = text[j];
                symb++;
            }
            arr[line][symb] = '\0';
            line++;
            if(i + 1 < length){
                start = i + 1;
            }
            else{
                break;
            }
        }
    }
    trim(arr, rows);
    if((*rows)%2==0){
        for(int i = 0; i<(*rows)/2; i++){
            printf("%s %s %s.\n", arr[i], connect ,arr[(*rows)-i-1]);
        }
    }
    else{
        int middle = (*rows)/2;
        for(int i = 0; i<(*rows)/2; i++){
            printf("%s %s %s.\n", arr[i], connect ,arr[(*rows)-i-1]);
        }
        printf("%s %s %s.\n", arr[middle], connect ,arr[middle]);
    }

}
