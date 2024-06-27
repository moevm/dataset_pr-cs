# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

int sum_of_digits(char* sentence){
    int amount = 0;
    while(*sentence){
        if (isdigit(*sentence)){
            amount += *sentence - '0';
        }
        sentence++;
    }
    return amount;
}

void clean_by_numbers(char** sentences, int* sentence_amount){
    int first_sum = sum_of_digits(sentences[0]);
    for (int j = 1; j < *sentence_amount; j++){
        int difference = 0;
        int current_sum = sum_of_digits(sentences[j]);
        if (current_sum > first_sum){
            difference = current_sum - first_sum;
            printf("(%d) %s\n", difference, sentences[j]);
        }
    }
} 

void print_processed_text(char** sentences, int* sentence_amount){
    for (int i = 0; i < *sentence_amount;i++){
        printf("%s\n", sentences[i]);
    }
}

void print_sentences(char **sentences, int* sentence_amount) {
    for (int i = 0; i < *sentence_amount; i++) {
        printf("%s\n", sentences[i]);
    }
}

void garbage_count(char** sentences, int* sentence_amount) {
    for (int i = 0; i < *sentence_amount; i++) {
        char *current = sentences[i];
        for (int j = 0; current[j]; j++) {
            current[j] = tolower(current[j]);
        }
        int amount_garbage = 0;
        char *position = current;
        while ((position = strstr(position, "garbage")) != NULL) {
            amount_garbage++;
            position += strlen("garbage"); 
        }
        if (amount_garbage == 0) {
            printf("Clean\n");
        }
        else {
            if (amount_garbage >= 1 && amount_garbage <= 5) {
                printf("Must be washed\n");
            }
            else {
                printf("It is a dump\n");
            }
        }
    }
}

void replace_digits(char** sentences, int sentence_amount, char *replace_word){
    int replace_len = strlen(replace_word);
    for (int i = 0; i < sentence_amount; i++) {
        char* current_sentence = sentences[i];
        int sentence_length = strlen(current_sentence);
        for (int j = 0; j < sentence_length; j++) {
            if (isdigit(current_sentence[j])) {
                char *new_sentence = realloc(current_sentence, sentence_length - 1 + replace_len + 1);
                current_sentence = new_sentence;
                memmove(current_sentence + j + replace_len, current_sentence + j + 1, sentence_length - j);
                memcpy(current_sentence + j, replace_word, replace_len);
                sentence_length = sentence_length - 1 + replace_len;
                j += replace_len - 1;
                current_sentence[sentence_length] = '\0'; 
            }
        }
        sentences[i] = current_sentence;
    }
}

int find_three_upper(const char* sentence){
    int upper_count = 0;
    int sentence_len = strlen(sentence);
    for (int i = 0; i < sentence_len; i++){
        if (isupper(sentence[i])){
            upper_count++;
            if (upper_count == 3){
                return 1;
            }
        }
        else {
            upper_count = 0;
        }
    }
    return 0;
}

void delete_upper(char** sentences, int* sentence_amount){
    int clear_amount = 0;
    for (int i = 0; i < *sentence_amount; i++){
        if (!find_three_upper(sentences[i])){
            sentences[clear_amount] = sentences[i];
            clear_amount++;
        }
        else{
            free(sentences[i]);
        }
    }
    *sentence_amount = clear_amount;
}

int sentence_vowel_count(const char* sentence) {
    int count = 0;
    const char* vowels = "euioaEUIOA";
    const char* separators = " ,.";
    int is_word_start = 1; 
    while (*sentence) {
        if (strchr(separators, *sentence)) {
            is_word_start = 1;
        } else if (is_word_start && strchr(vowels, *sentence)) {
            count++;
            is_word_start = 0;
        } else if (!strchr(separators, *sentence)) {
            is_word_start = 0;
        }
        sentence++;
    }
    return count;
}

int compare_by_vowels(const void *a, const void *b){
    char* sentence_1 = *(char**)a;
    char* sentence_2 = *(char**)b;
    int vowel_count_1 = sentence_vowel_count(sentence_1);
    int vowel_count_2 = sentence_vowel_count(sentence_2);
    return vowel_count_2 - vowel_count_1;
}

void sort_vowels(char** sentences, int* sentence_amount){
    qsort(sentences, *sentence_amount, sizeof(char *), compare_by_vowels);
}

void remove_unnecessary(char* sentence) {
    int i = 0, j = 0;
    while (sentence[i] == '\n' || sentence[i] == ' '){
        i++;
    }
    if (i > 0) {
        while (sentence[i] != '\0') {  
            sentence[j++] = sentence[i++];
        }
        sentence[j] = '\0'; 
    }
}

char** read_sentences(int* sentence_count) {
    int N = 100; 
    int k = 10; 
    int amount = 0; 
    int index = 0; 
    int previous_symbol = 0; 
    char** sentences = (char**)malloc(k * sizeof(char*)); 
    sentences[amount] = (char*)malloc(N * sizeof(char)); 
    char symbol;
    while (1) {
        symbol = getchar();
        if (symbol == '\n' && previous_symbol == '\n') {
            break;
        }
        if (index >= N - 1) {
            N *= 2;
            sentences[amount] = realloc(sentences[amount], N * sizeof(char));
        }
        if (symbol == '.') {
            sentences[amount][index++] = symbol;
            sentences[amount][index] = '\0';
            remove_unnecessary(sentences[amount]);
            amount++;
            if (amount == k) { 
                k *= 2;
                sentences = realloc(sentences, k * sizeof(char*));
            }
            sentences[amount] = (char*)malloc(N * sizeof(char));
            index = 0;
        } else {
            sentences[amount][index++] = symbol; 
        }
        previous_symbol = symbol; 
    }
    if (amount != k) {
        sentences[amount][index] = '\0';
    }
    *sentence_count = amount;
    return sentences;
}

void remove_duplicates(char** sentences, int *sentence_amount){
    for (int i = 0; i < *sentence_amount - 1;i++){
        for (int j = i+1; j < *sentence_amount;j++){
            if (strcmp(sentences[i], sentences[j]) == 0){
                free(sentences[j]);
                for (int k = j; k < *sentence_amount; k++){
                    sentences[k] = sentences[k+1];
                }
                (*sentence_amount)--;
                i--;
                j--;
            }
        }
    }
}

void print_info(){
    puts("List of commands:\n"
         "0 - print the processed text.\n"
         "1 - count amount of word 'garbage' in each sentence.\n"
         "2 - replace all the numbers in sentences with entered string.\n"
         "3 - delete sentences if there are more than three upper letters.\n"
         "4 - sort by decreasing amount of words starting with vowel.\n"
         "5 - print information about commands.");
}

int main(){
    puts("Course work for option 4.13, created by Yana Prokopovich.");
    int choice;
    scanf("%d", &choice);
    char replace_word[100]; 
    if ((choice < 0 || choice > 5) && choice != 8){
        printf("Error: wrong value for command.");
        return 0;
    }
    if (choice == 5){
        print_info();
        return 0;
    }
    if (choice == 2) {
        scanf("%s", replace_word);
    }
    int sentence_amount;
    char** sentences = read_sentences(&sentence_amount);
    remove_duplicates(sentences, &sentence_amount);
    switch(choice){
        case 0:
            print_processed_text(sentences, &sentence_amount);
            break;
        case 1:
            garbage_count(sentences, &sentence_amount);
            break;
        case 2:
            replace_digits(sentences, sentence_amount, replace_word);
            print_sentences(sentences, &sentence_amount);
            break;
        case 3:
            delete_upper(sentences, &sentence_amount);
            print_sentences(sentences, &sentence_amount);
            break;
        case 4:
            sort_vowels(sentences, &sentence_amount);
            print_sentences(sentences, &sentence_amount);
            break;
        case 8:
            clean_by_numbers(sentences, &sentence_amount);
            break;
    }
    for(int i = 0; i < sentence_amount; i++) {
        free(sentences[i]);
    }
    free(sentences);
    return 0;
}
