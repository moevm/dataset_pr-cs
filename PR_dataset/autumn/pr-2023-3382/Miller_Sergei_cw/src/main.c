#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int num_snt = -1;


void start(){
    printf("Course work for option 4.3, created by Miller Sergei.\n");
}


int check_in(char** t, char* snt) {
    
    
    for (int i = 0; t[i]; ++i){
        int j = 0;
        int f = 0;
        while (t[i][j] && snt[j]){
            if (tolower(t[i][j]) != tolower(snt[j])){
                f = 1;
            }
            j++;
        }
        if (f == 0){
            return 0;
        }
    }
    return 1;
}


char** read(char** t){

    int size = 100;
    int i = 0;
    char a;
    int f = 0;
    do
    {
        if (i > size){
            size += 10;
            char** tmp_t = realloc(t, size*sizeof(char*));
            if (tmp_t != NULL){
                t = tmp_t;
            }
            else{
                printf("ERROR: Memory allocation");
                    free(tmp_t);
                    return 0;
            }
        }

        int j = 0;
        int size_i = 100;
        char* txt_i = malloc(size_i*sizeof(char));
        int del_n = 0;
        
        do
        {
            a = getchar();
            if (a == '\n' && del_n){
                f = 1;
                break;
            }
        
            if (j == 0 && a == '\n'){
                del_n = 1;
                continue;
            }

            if (j > size_i){
                size_i += 100;
                char* temp_t = realloc(t[i], size_i*sizeof(char));
                if (temp_t != NULL){
                    txt_i = temp_t;
                }
                else{
                    printf("ERROR: Memory allocation");
                    free(txt_i);
                    return 0;
                }

            }
            if (j == 0 && a == ' '){
                continue;
            }
            txt_i[j] = a;
            j++;
            

        } while (a != '.');

        
        
        txt_i[j] = '\n';
        txt_i[j + 1] = '\0';

        if(i == 0 || check_in(t, txt_i) == 1){
            t[i] = txt_i;
            i++;
            num_snt++;
        }
    } while (f != 1);
    return t;
}


void out(char** t){
    for (int i = 0; i < num_snt; i++){
        printf("%s", t[i]);
    }
    for (int i = 0; i < num_snt; i++){
        free(t[i]);
    }
    free(t);
}


void first(char** t){ 
    int f = 0;
    for (int i = 0; t[i]; i++){
        f = 0;
        for (int j = 0; t[i][j]; j++){
            if ((t[i][j] > '9' || t[i][j] < '0') && t[i][j] != ' ' && t[i][j] != '\n' && t[i][j] != '.' && t[i][j] != '\t' && t[i][j] != '\0'){
                f = 1;
            }
        }
        if (f == 0){
            for (int j = 0; t[i][j]; j++){
                printf("%c", t[i][j]);
            }
        }
    }
    for (int i = 0; t[i]; i++){
        free(t[i]);
    }
    free(t);
}


int cmp(const void* str1, const void* str2) { 
    char *s1 = *((char **) str1);
    char *s2 = *((char **) str2);
    int num_isupper_s1 = 0;
    int num_isupper_s2 = 0;
    for (int i = 0; s1[i]; i++){
        if (isupper(s1[i])) {
            num_isupper_s1++;
        }
    }
    for (int i = 0; s2[i]; i ++){
        if (isupper(s2[i])) {
            num_isupper_s2++;
        }
    }
    if (num_isupper_s1 > num_isupper_s2) 
        return -1;
    else if (num_isupper_s1 == num_isupper_s2) 
        return 0;
    return 1;
}


char **second(char **t) { 
    qsort(t, num_snt, sizeof(char *), cmp);
    return t;
}


char* word_input(){
    char* word = malloc(10 * sizeof(char));
    int i = 0;
    char a;
    int size = 10;
    do {

        a = getchar();
        if (i > size){
            size += 10;
            char* temp_t = realloc(word, size*sizeof(char));
            if (temp_t != NULL){
                word = temp_t;
            }
            else{
                printf("ERROR: Memory allocation");
                free(word);
                return NULL;
            }
        }
        if (a != '\n')
            word[i] = a;
        i++;

    } while (a != '\n');
    return word;
}

void third(char** t, char* wrd) { 
    
    int cnt_sent;
    char* sent;
    char* word_in_sent;
    for (int i = 0; i < num_snt; i++){

        sent = malloc((strlen(t[i]) + 1) * sizeof(char));
        strcpy(sent, t[i]);
        word_in_sent = strtok(sent, " ,.");
        cnt_sent = 0;
        while (word_in_sent != NULL) {
            int flag = 0;
            if (strlen(word_in_sent) == strlen(wrd)) {
                flag = 1;
                for (int j = 0; wrd[j]; j++) {
                    if (tolower(word_in_sent[j]) != wrd[j]) {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag){
                cnt_sent++;
            }
            word_in_sent = strtok(NULL, " ,.");
        }
        if (cnt_sent >= 2){
            free(t[i]);
            for (int k = i; k < num_snt - 1; k++){
                t[k] = t[k + 1];

            }
            num_snt--;
            i--;
        }
        free(sent);
    }
}



char* change(char* t, char* num, int len, int start){ 
    int tlen = strlen(t);
    len--;
    char* temp_t = realloc(t, (tlen + len + 10)*sizeof(char));
    if (temp_t != NULL){
        t = temp_t;
    }
    else{
        printf("ERROR: Memory allocation");
        free(temp_t);
        return NULL;
    }
    
    tlen = strlen(t);
    for (int i = (tlen + len + 1); i != (start + len); i--){
        t[i] = t[i - len];
    }
    int j = 0;
    for (int i = start; i != start + len + 1; i++){
        t[i] = num[j];
        j++;
    }
    return t;
}

void fourth(char** t){
    for (int i = 0; t[i]; i++){
        int len_ti = strlen(t[i]);
        int j = 0;
        while(j < len_ti){
            if (isdigit(t[i][j])){
                switch (t[i][j])
                {
                case '0':
                    t[i] = change(t[i], "zero", 4, j);
                    break;
                case '1':
                    t[i] = change(t[i], "one", 3, j);
                    break;
                case '2':
                    t[i] = change(t[i], "two", 3, j);
                    break;
                case '3':
                    t[i] = change(t[i], "three", 5, j);
                    break;
                case '4':
                    t[i] = change(t[i], "four", 4, j);
                    break;
                case '5':
                    t[i] = change(t[i], "five", 4, j);
                    break;
                case '6':
                    t[i] = change(t[i], "six", 3, j);
                    break;
                case '7':
                    t[i] = change(t[i], "seven", 5, j);
                    break;
                case '8':
                    t[i] = change(t[i], "eight", 5, j);
                    break;
                case '9':
                    t[i] = change(t[i], "nine", 4, j);
                    break;
                }
            }
            j++;
            len_ti = strlen(t[i]);
            
        }
    }
}


void display_inf(){
    printf("1 – Print all sentences in which all words consist only of numbers.\n");
    printf("2 – Sort sentences by reducing the number of capital letters in it.\n");
    printf("3 – Delete all sentences in which a certain word (which - the user enters it into your program after selecting this action) occurs 2 or more times.\n");
    printf("4 - Transform all sentences so that each occurrence of a digit is replaced by the corresponding substring (0-“Zero”, 1-“One”, 2-“Two”, etc.).\n");
    printf("5 – Display information about the functions that the program implements.\n");
}





void nine(char** t, int n){
    
    for (int i = 0; i < num_snt; i++){
        for(int k = 0; k < n; k++){
            int j = 0;
            while (t[i][j]){
                if (t[i][j] == '.'){
                    if (k != n - 1){
                        printf(" ");
                    }
                    break;
                }
                printf("%c", t[i][j]);
                j++;
            }
            
        }
        printf(".\n");
    }
    for (int i = 0; i < num_snt; i++){
        free(t[i]);
    }
    free(t);

}






int main(){

    start();

    int nom_task;
    scanf("%d", &nom_task);
    char* w;
    int n;
    if (nom_task == 9){
        scanf("%d", &n);
    }
    if (nom_task != 5){
        if (nom_task == 3){
            w = word_input();
        }
        char** t = malloc(100*sizeof(char*));
        t = read(t);
        if (nom_task == 9){
            nine(t, n);
            return 0;
        }
        if(num_snt == 0){
            printf("Error: text could not be read or empty text was entered.\n");
        return 0;
        }
        if (nom_task == 1){
            first(t);
        }
        else if (nom_task == 2){
            t = second(t);
            out(t);
        }
        else if (nom_task == 3){
            third(t, w);
            out(t);
        }
        else{
            fourth(t);
            out(t);
        }
        
        
    }
    else{
        display_inf();
    }
    
    return 0;
}
