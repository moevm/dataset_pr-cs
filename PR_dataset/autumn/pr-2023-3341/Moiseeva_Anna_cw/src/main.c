#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#define BUFFER_SIZE 1024 
#define COUNT_NUMS 10

void command_zero();
void command_five();
int command_block(int);
void print_nums(char**, int);
void reverse(char*);
void del_physics(char**, int);
void sort_words_len_three(char**, int);
void del_double_words(char**, int);

char* input_text(int* len) {
    char* text = (char*)calloc(BUFFER_SIZE, sizeof(char));
    int current_size = BUFFER_SIZE;
    int i = 0;
    char c;

    while (1) {
        c = getchar();
        if (c == '\n' && i == 0){
            continue;
        }
        text[i++] = c;
        if (i == current_size - 1) {
            current_size += BUFFER_SIZE;
            char* temp = realloc(text, current_size*sizeof(char));
            text = temp;  
        }
        if (c == '.'){
            (*len)++;
        }
        if (i >= 2 && text[i-2] == '\n' && text[i-1] == '\n') {
            break;
        }
    }

    text[i-2] = '\0'; 
    return text;
}


char** split_sentences(char* text, int count) {
    int capacity = BUFFER_SIZE;
    int i = 0;
    char** sentences = (char**)calloc(count, sizeof(char*));
    
    char *sentence = strtok(text, ".");
    while (sentence != NULL) {
        if (i >= count) {
            capacity *= 2;
            char** sentences = realloc(sentences, capacity * sizeof(char*));
        }

        if (sentence[0] == ' ' || sentence[0] == '\t' || sentence[0] == '\n') {
            sentence++;
        }
        sentences[i++] = sentence;
        sentence = strtok(NULL, ".");
    }
    return sentences;
}

char** del_duplicates(char** sentences, int* len){
    int del_sentences = 0;
    for (int i = 0; i < (*len); i++){
        for (int j = i + 1; j < (*len); j++){
            if (sentences[i] != NULL && sentences[j] != NULL){
                if (strcasecmp(sentences[i], sentences[j]) == 0){
                    sentences[j] = NULL;
                    del_sentences++;
                }
            }   
        }
    }
    int index = 0;
    char** res_sentences = (char**)calloc((*len) - del_sentences, sizeof(char*)); 
    for (int k = 0; k < (*len); k++){
        if (sentences[k] != NULL){
            res_sentences[index++] = sentences[k];
        }
    }
    (*len) -= del_sentences;
    return res_sentences;
}

void print_nums(char** sentences, int len) {
    int digits_count[COUNT_NUMS] = {0};

    for (int i = 0; i < len; i++) {
        char* sentence = sentences[i];
        for (int j = 0; sentence[j]; j++) {
            if (isdigit(sentence[j])) {
                digits_count[sentence[j] - '0']++;
            }
        }
    }

    for (int i = 0; i < COUNT_NUMS; i++) {
        if(digits_count[i] > 0) {
            printf("Цифра %d встречается %d раз\n", i, digits_count[i]);
        }
    }

    int total_count = 0;
    for (int i = 0; i < COUNT_NUMS; i++) {
        total_count += digits_count[i];
    }
    if (total_count == 0){
        printf("В исходной строке нет цифр.\n");
    }
}


void reverse(char* sentence) {
    int length = strlen(sentence);
    int start = 0; 
    int end = length - 1;
    char temp[length + 1];

    for (int i = 0; i < length; ++i) {
        temp[i] = ' ';
    }
    temp[length] = '\0';
    while (start <= end) {
        while (start < length && isspace(sentence[start])) {
            start++;
        }
        while (end >= 0 && isspace(sentence[end])) {
            end--;
        }
        if (start <= end) {
            temp[start] = sentence[end];
            temp[end] = sentence[start];
            start++;
            end--;
        }
    }
    strcpy(sentence, temp);
}

void del_physics(char** txt, int len){
    for (int i = 0; i < len; i++){
        if (strstr(txt[i], "physics") == NULL){
            printf("%s.\n", txt[i]);
        }
    }
}

int count_three_letter_words(char* sentence) {
    int count = 0;
    char* word = strtok(sentence, " ");
    while (word != NULL) {
        if (strlen(word) == 3) {
            count++;
        }
        word = strtok(NULL, " "); 
    }
    return count;
}

int three_letter_word_comp(const void* a, const void* b) {
    const char* sentence_a = *(const char**)a;
    const char* sentence_b = *(const char**)b;
    char* copy_a = (char*)malloc(strlen(sentence_a) + 1);
    char* copy_b = (char*)malloc(strlen(sentence_b) + 1);
 
    strcpy(copy_a, sentence_a);
    strcpy(copy_b, sentence_b);
    int count_a = count_three_letter_words(copy_a);
    int count_b = count_three_letter_words(copy_b);
    free(copy_a);
    free(copy_b);
    return count_b - count_a;
}

void sort_words_len_three(char** sentences, int num_sentences) {
    qsort(sentences, num_sentences, sizeof(char*), three_letter_word_comp);
    for (int i = 0; i < num_sentences; i++) {
        printf("%s.\n", sentences[i]);
    }
}

int count_words(char** sentences, int num_sentences) {
    int total_words = 0;
    for (int i = 0; i < num_sentences; i++){
        const char* temp = sentences[i];
        while (*temp){
            if (*temp == ' ' || *(temp + 1) == '\0') {
                total_words++;
            }
            temp++;
        }
    }
    return total_words;
}

void fill_word_array(char** sentences, int num_sentences, char** words) {
    int word_id = 0;
    for (int k = 0; k < num_sentences; k++){
        char* sentence = sentences[k];
        int length = strlen(sentence);
        int start = 0;

        for (int j = 0; j < length; ++j){
            if (sentence[j] == ' ' || j == length - 1){
                int end = (sentence[j] == ' ') ? j : j + 1;
                int word_len = end - start;
                char* word = malloc(word_len + 1);
                memcpy(word, sentence + start, word_len);
                word[word_len] = '\0';
                words[word_id++] = word;
                start = j + 1;
            }
        }
    }
}

void mark_duplicated_words(char** words, int total_words, int* used_words) {
    for (int i = 0; i < total_words; i++){
        for (int j = 0; j < i; j++){
            if (strcasecmp(words[j], words[i]) == 0){
                used_words[j]++;
                break;
            }
        }
    }
}

void construct_sentences_without_duplicates(char** sentences, int num_sentences, char** words, int* used_words, int word_id) {
    for (int i = 0; i < num_sentences; i++){
        char new_sentence[100] = {0};
        char* sentence = sentences[i];
        int length = strlen(sentence);
        int start = 0, fl = 0;
        
        for (int j = 0; j < length; j++){
            if (sentence[j] == ' ' || j == length - 1){
                int end = (sentence[j] == ' ') ? j : j + 1;
                int word_len = end - start;
                char word[100] = {0};
                memcpy(word, sentence + start, word_len);
                int is_dupl = 0;
                for (int w = 0; w < word_id && !is_dupl; w++){
                    if (strcasecmp(words[w], word) == 0 && used_words[w] > 0){
                        is_dupl = 1;
                    }
                }
                if (!is_dupl){
                    if (fl) strcat(new_sentence, " ");
                    strcat(new_sentence, word);
                    fl = 1;
                }
                start = j + 1;
            }
        }
        strcpy(sentences[i], new_sentence);
    }
}

void del_double_words(char** sentences, int num_sentences){
    int total_words = count_words(sentences, num_sentences);
    char** words = (char**)malloc(total_words*sizeof(char*));
    int* used_words = (int*)calloc(total_words, sizeof(int));

    fill_word_array(sentences, num_sentences, words);
    mark_duplicated_words(words, total_words, used_words);
    construct_sentences_without_duplicates(sentences, num_sentences, words, used_words, total_words);
    for (int i = 0; i < num_sentences; i++){
        if (isalpha(sentences[i][0])) {
            printf("%s.\n", sentences[i]);
        }
    }

    for (int i = 0; i < total_words; i++){
        free(words[i]);
    }
    free(words);
    free(used_words);
}

int command_block(int command){
    if (command == 5){
        printf("Эта программа принимает на вход фрагмент текста и может выполнять различные алгоритмы в зависимости от команды, введенной пользователем.\n"
           "Нулевая команда позволяет вывести текст, обработанный согласно условию.\n"
           "Первая команда позволяет вывести список всех встречающихся в тексте цифр и частоту их упоминания.\n"
           "Вторая команда преобразует предложение таким образом, что символы, за исключением разделителей, идут в обратном порядке.\n"
           "Третья команда удаляет все предложения, содержащие слово \"physics\".\n"
           "Четвертая - отсортировать предложения по убыванию количества слов, длина которых равна 3.\n"
           "Пятая - вывести справку о выполняемых командах.\n"
           "Девятая - удаляет слова, которые встречаются в тексте больше одного раза.\n");
        return 0;
    }

    else{
        int num_sentences = 0;
        char* text = input_text(&num_sentences);
        char** sentences = split_sentences(text, num_sentences);
        char** sentences_no_dupl = del_duplicates(sentences, &num_sentences);
        switch(command){
            case 0:
                for (int i = 0; i < num_sentences; i++){
                    printf("%s.\n", sentences_no_dupl[i]);
                }
                break;
            case 1:
                print_nums(sentences_no_dupl, num_sentences);
                break;
            case 2:
                for (int i = 0; i < num_sentences; i++) {
                    reverse(sentences_no_dupl[i]);
                    printf("%s.\n", sentences_no_dupl[i]);
                }
                break;
            case 3:
                del_physics(sentences_no_dupl, num_sentences);
                break;
            case 4:
                sort_words_len_three(sentences_no_dupl, num_sentences);
                break;
            case 9:
                del_double_words(sentences_no_dupl, num_sentences);
                break;
            default:
                printf("Error: команды %d не существует.\n", command);
                break;
        }
        free(sentences);
        free(text);
        free(sentences_no_dupl);
        return 0;
    }
}

int main() {
    printf("Course work for option 4.7, created by Anna Moiseeva.\n");
    while (1) {
        int num_task = 0;
        scanf("%d", &num_task);
        if ((num_task >= 0 && num_task <= 5) || num_task == 9) {
            command_block(num_task);
            break;
        } else {
            printf("Error: неверная команда.\n");
            break;
        }
    }
}