#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CR_INFO "Course work for option 4.13, created by Yagudin Danil.\n"

char* input_text(int* len) {
    int buffer_size = 2;
    int current_size = 0;

    char *text = (char*)calloc(buffer_size, sizeof(char));

    char current_char = getchar();
    int flag = 0;

    while (flag < 2) { 
        if (current_char == '.'){
            (*len) ++;
        }

        text[current_size ++] = current_char;

        if (current_size + 1 >= buffer_size) {
            buffer_size *= 2;
            text = (char*)realloc(text, sizeof(char) * buffer_size);
        }

        current_char = getchar();

        if (current_char == '\n'){
            flag++; 
        }else{
            flag = 0; 
        }
    }

    text[current_size - 2] = '\0';

    return text;
}

char** split_text(char* text, int len){
    char** sentences = (char**)calloc(len, sizeof(char*));

    int i = 0;
    char* sentense = strtok(text, ".");
    while(sentense != NULL){
        while (isspace(*sentense)) {
    		sentense ++;
		}
        sentences[i ++] = sentense;
        sentense = strtok(NULL, ".");
    }

    return sentences;
} 

char** cleaner(char** sentence, int* len) {
    int clean_sen = 0;

    for (int i = 0; i < (*len); i ++){
        for (int j = i + 1; j < (*len); j ++){
            if (sentence[i] != NULL && sentence[j] != NULL) {
                if (strcasecmp(sentence[i], sentence[j]) == 0){
                sentence[j] = NULL;

                clean_sen ++;
                }
            }
        }
    }

    char** new_sent = (char**)calloc((*len) - clean_sen, sizeof(char*));

    int j = 0;
    for (int i = 0; i < (*len); i ++){
        if (sentence[i] != NULL){

            new_sent[j ++] = sentence[i];
        } 
    }
    (*len) -= clean_sen;

    return new_sent;
}

void garbage(char** sentence, int len) {
    for (int i = 0; i < len; i ++) {
        int counter = 0;

        char *str = strtok(sentence[i], " ,");
        while (str != NULL) {
            if (strcasecmp(str, "garbage") == 0) {
                counter ++;
            }
            str = strtok(NULL, " ,");
        }

        if (counter == 0) {
            printf("Clean\n");
        }
        if ((counter >= 1) && (counter <= 5)) {
            printf("Must be washed\n");
        }
        if (counter > 5){
            printf("It is a dump\n");
        }
    }
}

void replacer(char** sentence, int len){
    char* str = (char*)calloc(10000, sizeof(char));
    fgets(str, 10000, stdin);

    int str_len = strlen(str);
    if (str_len > 0) str[strlen(str) - 1] = '\0';
    str_len--;

    for (int i = 0; i < len; i ++){
        int cap = 2;
        char* new_sentence = (char*)calloc(cap, sizeof(char));
        int str_size = 0;
        for (int j = 0; j < strlen(sentence[i]); j ++){

            while ((str_size + 1) >= cap) {
                cap *= 2;
                new_sentence = realloc(new_sentence, sizeof(char) * cap);
            }

            if (isdigit(sentence[i][j])){

                while ((str_size + str_len + 1) >= cap){
                    cap *= 2;
                    new_sentence = realloc(new_sentence, sizeof(char) * cap);
                }

                int l = 0;
                while(l < str_len){
                    new_sentence[str_size] = str[l];
                    str_size++; l++;
                }
            }else{
                new_sentence[str_size] = sentence[i][j];
                str_size++;
            }

        }

        new_sentence[str_size] = '\0';
        printf("%s.\n", new_sentence);

    }
}

void up_del(char** sentence, int len){
    for (int i = 0; i < len; i ++) {
        for (int j = 0; j < strlen(sentence[i]); j ++) {
            if ( isupper(sentence[i][j]) && isupper(sentence[i][j + 1]) && isupper(sentence[i][j + 2]) ) {
                sentence[i] = NULL;
                break;
            }
        }
    }

    for (int i = 0; i < len; i ++){
        if (sentence[i] != NULL){
            printf("%s.\n", sentence[i]);
        }
    }
}

int down_counter(const char* sentence){
    int counter = 0;
    int flag = 0;

    while(*sentence){
        if (isalpha(*sentence)){
            if(!flag) {
                flag = 1;
                if (strchr("aeiouAEIOU", *sentence) != NULL){
                    counter ++;
                }
            }
        }else{
            flag = 0;
        }
        sentence ++;
    }

    return counter;
}

int compare_sent(const void* first, const void* second){
    const char* str_f = *(const void**)first;
    const char* str_s = *(const void**)second;

    int counter_f = down_counter(str_f);
    int counter_s = down_counter(str_s);

    return counter_s - counter_f;
}

void down_sort(char** sentence, int len){
    qsort(sentence, len, sizeof(char*), compare_sent);

    for (int i = 0; i < len; i ++){
        printf("%s.\n", sentence[i]);
    }
}

int dig_counter(const char* word){

    int counter = 0;

    while(*word){
        if (isdigit(*word) != 0){
        
            int num = atoi(word);
            counter += num;

        }
        word ++;
    }

    return counter;

}

int comp(const void* a, const void* b){

    const char* first = *(const char**)a;
    const char* second = *(const char**)b;

    int c_f = dig_counter(first);
    int c_s = dig_counter(second);

    if (c_f < c_s) {
        return -1;
    } else if (c_f > c_s) {
        return 1;
    } else {
        return 0;
    }

}

void curs(char** sentence, int len){

    for (int i = 0; i < len; i ++){
        char** words = (char**)calloc(1000, sizeof(char*));
        int words_size = 0;
        
        char* str = strtok(sentence[i], " ,");
        while(str != NULL){

            words[words_size ++] = str;
            str = strtok(NULL, " ,");

        }

        qsort(words, words_size, sizeof(char*), comp);

        for (int i = 0; i < words_size; i ++){
            
            if ((i + 1) >= words_size){
                printf("%s.\n", words[i]);
            }else{
                printf("%s ", words[i]);
            }

        }

    }

}

void output(int command){
    if (command == 5){
        printf("function info:\n\
        1 - For each sentence, count the number of words ""garbage"" in it. Depending on the quantity, it outputs: ""Clean"", ""Must be washed"", ""It is a dump"".\n\
        2 - Replaces all the numbers in the sentences with the entered string.\n\
        3 - Deletes all sentences that have three consecutive uppercase letters.\n\
        4 - Sorts sentences to reduce the number of words starting with a vowel letter.\n");
        return;
    } 

    int len = 0;
    char* text = input_text(&len);
    char** sentence = split_text(text, len);

    sentence = cleaner(sentence, &len);

    switch (command){
    case 0:
        for (int i = 0; i< len; i++){
        printf("%s.\n", sentence[i]);
        }
        return;
    case 1:
        garbage(sentence, len);
        return;
    case 2:
        replacer(sentence, len);
        return;
    case 3:
        up_del(sentence, len);
        return;
    case 4:
        down_sort(sentence, len);
        return;
    case 9:
        curs(sentence, len);
        return;
    default:
        printf("Error: no such function.\n");
        return;
    }
}

int main() {
    printf(CR_INFO);

    int command;
    scanf("%d", &command);

    output(command);
    return 0;
}
