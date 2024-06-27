#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** cw_switch(char r, int* ptr_text_count);
char** cw_input(int* ptr_text_count);
int cw_check_duplicate(char** text, char* sentence, int* ptr_text_count);
void cw_option_1(char** text, int* ptr_text_count);
char** cw_option_2(char** text, int* ptr_text_count);
char** cw_option_3(char** text, int* ptr_text_count);
char** cw_option_4(char** text, int* ptr_text_count);
void cw_option_5();
char** cw_option_9(char** text, int* ptr_text_count, char* str);
int cw_compare_sentence(const void* a, const void* b);
int cw_count_words(char* sentence);
void cw_output(char** text, int text_count);

int main(){
    printf("Course work for option 4.7, created by Khangulyan Sargis.\n");
    char r = getchar();
    char** text;
    int text_count = 0;
    int* ptr_text_count = &text_count;
    text = cw_switch(r, ptr_text_count);
    if (text != NULL)
        cw_output(text, text_count);
    return 0;
}



char** cw_input(int* ptr_text_count){
  //  if (getchar() != '\n'){
  //      printf("Error: incorrect option!\n");
  //      return NULL;
  //  }
    char** text = (char**)malloc(sizeof(char*));
    int text_char_count = 0;

    while (1){
        char* sentence = (char*)malloc(sizeof(char));
        char symbol = ' ';
        int sentence_count = 0;
        int r = 0;
        int f = 0;

        while (symbol != '.'){
            symbol = getchar();

            if (isalnum(symbol))
                f = 1;
            
            if (symbol == '\n')
                r += 1;
            else
                r = 0;

            if (r == 2){
                if (f) 
                    sentence[sentence_count-1] = '.';
                break;
            }

            sentence[sentence_count++] = symbol;
            sentence = realloc(sentence, sizeof(char)*(sentence_count + 1));
        }

        sentence[sentence_count] = '\0';
        while (isspace(sentence[0])) {
            memmove(sentence, sentence + 1, strlen(sentence));
        }

        if (strlen(sentence) == 1){
            printf("Error: incorrect text input!\n");
            return NULL;
        }

        if (cw_check_duplicate(text, sentence, ptr_text_count) && strlen(sentence) > 1){
            text[(*ptr_text_count)++] = sentence;
            text_char_count += strlen(sentence);
            text = realloc(text, sizeof(char*)*((*ptr_text_count) + 1));
        }

        if (r == 2){
            break;
        }
    }
    
    if (text_char_count == 0){
        printf("Error: incorrect text input!\n");
        return NULL;
    }

    return text;
}



int cw_check_duplicate(char** text, char* sentence, int* ptr_text_count){
    for (int i = 0; i < (*ptr_text_count); i++){
        if (strlen(text[i]) == strlen(sentence)){
            int r = 0;
            for (int j = 0; j < strlen(text[i]); j++){
                if (tolower(text[i][j]) != tolower(sentence[j])){
                    r = 1;
                    break;
                }
            }
            if (r == 0)
                return 0;
        }
    }
    return 1;
}



char** cw_switch(char r, int* ptr_text_count){
    char** text;
    switch (r){
        case '0': {
            text = cw_input(ptr_text_count);
            return text;
            break;
        }
        case '1': {
            text = cw_input(ptr_text_count);
            cw_option_1(text, ptr_text_count);
            return NULL;
            break;
        }
        case '2': {
            text = cw_input(ptr_text_count);
            return cw_option_2(text, ptr_text_count);
            break;
        }
        case '3': {
            text = cw_input(ptr_text_count);
            return cw_option_3(text, ptr_text_count);
            break;
        }
        case '4': {
            text = cw_input(ptr_text_count);
            return cw_option_4(text, ptr_text_count);
            break;
        }
        case '5': {
            cw_option_5();
            return NULL;
            break;
        }
        case '9': {
            getchar();
            char str[121];
            fgets(str, 122, stdin);
            
            text = cw_input(ptr_text_count);
            return cw_option_9(text, ptr_text_count, str);
            break;
        }
        default: {
            printf("Error: incorrect option!\n");
            return NULL;
            break;
        }
    }
}



void cw_option_1(char** text, int* ptr_text_count){
    if (text != NULL){
        int r = 0;
        for (int i = 0; i < 10; i++){
            int count = 0;
            for (int j = 0; j < (*ptr_text_count); j++){
                for (int k = 0; k < strlen(text[j]); k++){
                    if (text[j][k] == (char) (i+48)){
                        count += 1;
                        r = 1;
                    }
                }
            }
            if (count != 0)
                printf("The number %d occurs %d times in the text.\n", i, count);
        }
        if (!r)
            printf("There are no numbers in the text!\n");
    }
}



char** cw_option_2(char** text, int* ptr_text_count){
    if (text != NULL){
        char* copy;
        char symbol;
        int copy_count;
        for (int i = 0; i < (*ptr_text_count); i++){
            copy = (char*)malloc(strlen(text[i]));
            copy_count = 0;

            for (int k = 0; k < strlen(text[i]); k++){
                symbol = text[i][strlen(text[i])-2-k];
                if (!(isspace(symbol)) && symbol != ',')
                    copy[copy_count++] = symbol;
            }
            copy[copy_count-1] = '\0';

            copy_count = 0;           
            for (int k = 0; k < strlen(text[i])-1; k++){
                if (!(isspace(text[i][k])) && text[i][k] != ',')
                    text[i][k] = copy[copy_count++];
            }
            free(copy);
        }
    }
    return text;
}



char** cw_option_3(char** text, int* ptr_text_count){
    if (text != NULL){
        int del_sent_count = 0;
        for (int i = 0; i < (*ptr_text_count); i++){
            if (strstr(text[i], "physics") != NULL){
                if (*(strstr(text[i], "physics") + 7) == ' ' || *(strstr(text[i], "physics") + 7) == ',' || *(strstr(text[i], "physics") + 7) == '.'){
                    text[i] = NULL;
                    del_sent_count += 1;
                }
            }
        }

        if (del_sent_count == (*ptr_text_count)){
            printf("There are no sentences without the word physics in the text!\n");
            return NULL;
        }
    }
    return text;
}



char** cw_option_4(char** text, int* ptr_text_count){
    if (text != NULL){
        qsort(text, (*ptr_text_count), sizeof(char*), cw_compare_sentence);
    }
    return text;
}



int cw_compare_sentence(const void* a, const void* b){
    int count_1 = cw_count_words(*(char**)a);
    int count_2 = cw_count_words(*(char**)b);
    if (count_1 == count_2)
        return 1;
    else
        return count_2 - count_1;
}



int cw_count_words(char* sentence){  
    int words_count = 0;
    int char_count = 0;
    for (int k = 0; k < strlen(sentence); k++){
        if (isalnum(sentence[k])){
            char_count += 1;
        }
        else{
            if (char_count == 3)
                words_count += 1;
            char_count = 0;
        }
    }
    return words_count;
}



void cw_option_5(){
    printf("=======================================================================================================\n");
    printf("0 - text output after initial processing.\n");
    printf("1 - displays a list of all the numbers found in the text and the frequency of their mention.\n");
    printf("2 - output of text converted in such a way that characters other than delimiters go in reverse order.\n");
    printf("3 - the output of the text in which all sentences with the word physics are deleted.\n");
    printf("4 - the output of the text sorted by decreasing the number of words, the length of which is 3.\n");
    printf("5 - output help about the functions that the program implements.\n");
    printf("=======================================================================================================\n");
}



char** cw_option_9(char** text, int* ptr_text_count, char* str){
    if (text != NULL){
        int str_count_uppers = 0;
        for (int i = 0; i < strlen(str); i++){
            if (isupper(str[i]))
                str_count_uppers++;
        }

        for (int j = 0; j < (*ptr_text_count); j++){
            int sentence_count_uppers = 0;
            for (int k = 0; k < strlen(text[j]); k++){
                if (isupper(text[j][k]))
                    sentence_count_uppers++;
            }

            if (sentence_count_uppers > str_count_uppers)
                text[j] = NULL;
        }
    }
    return text;
}



void cw_output(char **text, int text_count){
    for (int i = 0; i < text_count; i++){
        if (text[i] != NULL){
            if (i < text_count-1)
                printf("%s\n", text[i]);
            else
                printf("%s", text[i]);
        free(text[i]);
        }
    }
    free(text);
}