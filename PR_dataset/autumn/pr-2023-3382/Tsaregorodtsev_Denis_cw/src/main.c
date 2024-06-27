#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void input_text(char*** text, int* text_sentense){
    char character = '\0';
    char prev_character = '\0';
    char *sentence = malloc(10 * sizeof(char));
    int sentence_len = 0;
    while (1) {
        character = getchar();
        if ((character == '\n')&&(prev_character == '\n')){
            break;
        }
        prev_character = character;
        if ((sentence_len == 0)&&((character == ' ')||(character == '\t')||(character=='\n'))){
            continue;
        }
        if((sentence_len == 0) && (character == '.')){
            continue;
        }
        sentence[sentence_len++] = character;
        sentence = (char*)realloc(sentence, (sentence_len + 1) * sizeof(char));
        if (sentence == NULL){
                    printf("Error: Failed to allocate memory for sentense.\n");
                    exit(1);
                }
        if (character=='.'){
            sentence[sentence_len]='\0';
            (*text)[*text_sentense]= malloc((sentence_len + 1)  * sizeof(char));
            if ((*text)[*text_sentense] == NULL) {
                printf("Error: Failed to allocate memory for text_sentence.\n");
                exit(1);
            }
            strcpy((*text)[*text_sentense],sentence);
            (*text_sentense)++;
            *text = (char**)realloc((*text),((*text_sentense) + 1) * sizeof(char*));
            if ((*text) == NULL) {
                printf("Error: Failed to allocate memory for text.\n");
                exit(1);
            }
            free(sentence);
            sentence=malloc(10 * sizeof(char));
            if (sentence == NULL){
                printf("Error: Failed ti allocate memory for sentence");
                exit(1);
            }
            sentence_len=0;
        }
    }
    (*text)[(*text_sentense)] = '\0';
    free(sentence);
}
void input_replace_sentence(char** replace_sentence,int* len_replace_sentense){
    char symbol;
    while(1){
        symbol = getchar();
        if (symbol == '.'){
            break;
        }
        if(symbol=='\n' && (*len_replace_sentense) == 0){
            continue;
        }
        (*replace_sentence)[(*len_replace_sentense)++] = symbol;
        (*replace_sentence) = realloc((*replace_sentence),((*len_replace_sentense) + 2) * sizeof(char));
        if(replace_sentence == NULL){
            printf("Error: Failed to allocate memory");
            exit(1);
        }
    }
    (*replace_sentence)[*len_replace_sentense]='\0';
}
void delete_dublicates(char*** text, int* text_sentense) {
    for (int i = 0; (*text)[i]; i++) {
        for (int q = i + 1; (*text)[q]; q++) {
            int flag = 1;
            if (strlen((*text)[i]) == strlen((*text)[q])) {
                for (int j = 0; (*text)[i][j]; j++) {
                    if (tolower((*text)[i][j]) != tolower((*text)[q][j])) {
                        flag = 0;
                        break;
                    }
                }
            } else {
                flag = 0;
            }
            if (flag){
                free((*text)[q]);
                for (int d = q; (*text)[d]; d++) {
                    (*text)[d] = (*text)[d + 1];
                }
                free((*text)[*text_sentense]);
                (*text_sentense)--;
                q--;
            }
        }
    }
}
void output_text(char** text, int* text_len){
    if(*text_len == 0){
        printf("Error: text was not submitted");
        exit(1);
    }
    for(int i=0; i<(*text_len);i++){
        printf("%s\n", text[i]);
    }
}
void garbage_counter(char** text, int* text_sentence){
    int len_text=(*text_sentence);
    char for_zero[]="Clean";
    char for_one_to_five[]="Must be wached";
    char for_more_five[]="It is a dump";
    char** results = malloc(((len_text) + 1)* sizeof(char*));
    for(int i=0;text[i];i++){
        int counter = 0;
        for(int j=0;text[i][j];j++){
            if((tolower(text [i][j])=='g')&&(text[i][j - 1]==' ' || j==0)&&(strlen(text[i]) - j > 6)){
                if((tolower(text [i][j + 1])=='a')&&(tolower(text [i][j + 2])=='r')){
                    if((tolower(text [i][j + 3])=='b')&&(tolower(text [i][j + 4])=='a')){
                        if((tolower(text [i][j + 5])=='g')&&(tolower(text [i][j + 6])=='e')){
                            if((tolower(text [i][j + 7])=='.')||(tolower(text [i][j + 7])==' ')){
                                counter++;
                            }
                        }
                    }
                }
            }
        }
        if(counter == 0){
            results[i]=malloc((strlen(for_zero) + 1)*sizeof(char));
            if (results[i] == NULL) {
                printf("Error: Failed to allocate memory.\n");
                exit(1);
            }
            strcpy(results[i],for_zero);
        }
        if(counter > 0 && counter<6){
            results[i]=malloc((strlen(for_one_to_five) + 1)*sizeof(char));
            if (results[i] == NULL) {
                printf("Error: Failed to allocate memory.\n");
                exit(1);
            }
            strcpy(results[i],for_one_to_five);
        }
        if(counter>5){
            results[i]=malloc((strlen(for_more_five) + 1)*sizeof(char));
            if (results[i] == NULL) {
                printf("Error: Failed to allocate memory.\n");
                exit(1);
            }
            strcpy(results[i],for_more_five);
        }
    }
    output_text(results,&len_text);
    for(int i = 0;i<len_text;i++){
        free(results[i]);
    }
    free(results);
}
void number_replacement(char** text, int* text_sentence, char* replace_sentence,int* len_replace_sentense) {
    int len_sent = (*len_replace_sentense);
    int len_text = (*text_sentence);
    char* sentence = malloc((len_sent + 2) * sizeof(char));
    strcpy(sentence,replace_sentence);
    char** new_text = malloc((len_text + 2) * sizeof(char*));
    for (int i = 0; i < len_text; i++) {
        new_text[i] = malloc((strlen(text[i]) + 2) * sizeof(char));
    }
    for (int i = 0; i < len_text; i++) {
        int q = 0;
        for (int j = 0; j < strlen(text[i]); j++) {
            if (isdigit(text[i][j])) {
                int s = 0;
                new_text[i] = realloc(new_text[i], (strlen(new_text[i]) + strlen(text[i]) + len_sent + 2) * sizeof(char));
                if(new_text[i] == NULL){
                    printf("Error: Failed to allocate memory");
                    exit(1);
                }
                while(s < len_sent){
                    new_text[i][q++] = sentence[s++];
                }
            }else{
                new_text[i][q++] = text[i][j];
            }
        }
        new_text[i][q] = '\0';
    }
    output_text(new_text,&len_text);
    
    for (int i = 0; i < len_text; i++) {
        free(new_text[i]);
    }
    free(new_text);
    free(sentence);
}
void delete_sentense_with_isupper(char*** text, int* text_sentense){
    for (int i = 0; (*text)[i]; i++){
        int flag = 0;
        for (int j = 0; (*text)[i][j]; j++){
                if (isupper((*text)[i][j])&&((strlen((*text)[i]) - j) > 3)){
                    if((isupper((*text)[i][j + 1])) && (isupper((*text)[i][j + 2]))){
                        flag = 1;
                        break;
                    }    
                }
        }
        if (flag == 1){
            free((*text)[i]);
            for (int d = i; (*text)[d]; d++) {
                (*text)[d] = (*text)[d + 1];
            }
            free((*text)[*text_sentense]);
            (*text_sentense)--;
                i--;
        }
    
    }
    output_text(*text,&(*text_sentense));
}
int count_vowel_words(char* string) {
    int count = 0;
    int length = strlen(string);
    int i = 0;
    int flag = 0;
    while (i < length){
        if (isalpha(string[i])){
            if (!flag){
                if (tolower(string[i]) == 'a' || tolower(string[i]) == 'e' || 
                    tolower(string[i]) == 'i' || tolower(string[i]) == 'o' || 
                    tolower(string[i]) == 'u' || tolower(string[i]) == 'y'){
                    count++;
                }
                flag = 1;
            }
        }else{
            flag = 0;
        }
        i++;
    }
    return count;
}
int compare(const void* a, const void* b) {
    char** string_a = (char**)a;
    char** string_b = (char**)b;
    int vowel_words_a = count_vowel_words(*string_a);
    int vowel_words_b = count_vowel_words(*string_b);
    return vowel_words_b - vowel_words_a;
}
void new_output(char** text, int len_text,int* dubl){
    int dublicate = (*dubl) - 1;
    for(int i = 0;text[i];i++){
        int q=0;
        char* sent=malloc((strlen(text[i]) + 2));
        strcpy(sent, text[i]);
        for(int j=0;sent[j];j++){
            if (sent[j]=='.'){
                sent[j]=' ';
            }
        }
        while(q<dublicate){
            printf("%s",sent);
            q++;
        }
        free(sent);
        printf("%s\n",text[i]);
    }
}
void information_about_functions(){
    printf("\nInformation about the functions implemented in the program:\n");
    printf("0 – Output text after initial processing.\n");
    printf("1 – Counting for each sentence the number of words “garbage” in it (case-insensitive). Depending on the number, the output of the following lines: 0 - “Clean”, [1 5] - “Must be washed”, >5 - “It is a dump”.\n");
    printf("2 – Replacing all digits in sentences with the entered string.\n");
    printf("3 – Deleting all sentences in which there are three consecutive letters in uppercase.\n");
    printf("4 - Sorting by reducing the number of words starting with a vowel letter.\n");
    printf("5 – Information about the functions implemented in the program.\n");
}
int main(){
    printf("Course work for option 4.13, created by Tsaregorodtsev Denis.\n");
    int operation;
    scanf("%d", &operation);
    int text_sentense = 0;
    char** text = malloc((text_sentense + 1) * sizeof(char*));
    int len_replace_sentense = 0;
    char* replace_sentence = malloc((len_replace_sentense + 1) * sizeof(char));
    int dublicate;
    switch(operation){
        case 0:
            input_text(&text,&text_sentense);
            delete_dublicates(&text,&text_sentense);
            output_text(text,&text_sentense);
            break;
        case 1:
            input_text(&text,&text_sentense);
            delete_dublicates(&text,&text_sentense);
            garbage_counter(text,&text_sentense);
            break;
        case 2:
            input_replace_sentence(&replace_sentence,&len_replace_sentense);
            input_text(&text,&text_sentense);
            delete_dublicates(&text,&text_sentense);
            number_replacement(text,&text_sentense,replace_sentence,&len_replace_sentense);
            break;
        case 3:
            input_text(&text,&text_sentense);
            delete_dublicates(&text,&text_sentense);
            delete_sentense_with_isupper(&text,&text_sentense);
            break;
        case 4:
            input_text(&text,&text_sentense);
            delete_dublicates(&text,&text_sentense);
            qsort(text,text_sentense,sizeof(char*),compare);
            output_text(text,&text_sentense);
            break;
        case 5:
            information_about_functions();
            break;
        case 9:
            scanf("%d", &dublicate);
            input_text(&text,&text_sentense);
            delete_dublicates(&text,&text_sentense);
            new_output(text,text_sentense,&dublicate);
            break;
        default:
            printf("Error: Failed to read operation\n");
    }
    for(int i=0;i<text_sentense;i++){
        free(text[i]);
    }
    free(text);
    free(replace_sentence);
    return 0;
}
