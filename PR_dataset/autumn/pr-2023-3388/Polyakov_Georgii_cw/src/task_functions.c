#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data_output.h"
#define FEATURE_DELETE_ALL_NUMBERS "1 function - void delete_all_numbers(char** sentences, int last_sentence_index) - removes all digits in every sentence."
#define FEATURE_IS_PALINDROM "2 function - void is_palindrom(char** sentences, int last_sentence_index) - checks each sentence: whether it is a palindrome, \nprints the original sentences, opposite them Palindrome, if it is a palindrome, otherwise Not interesting."
#define FEATURE_DELETE_SENTENCES "3 function - int delete_sentences(char** sentences, int last_sentence_index) - removes sentences from text if the first and last letter are the same.\nReturns the index of the last remaining sentence."
#define FEATURE_SORT_SENTENCES "4 function - void sort_sentences(char** sentences, int last_sentence_index) - sorts sentences by the length of the third word; if the third word is not in the sentence, then it considers the length to be three."
int third_word_length(const char *sentence) {
    if (sentence == NULL) {
        return 0;
    }

    int length = strlen(sentence);
    char* new_sentence = malloc(length+1);
    strcpy(new_sentence, sentence);
    char *word = strtok(new_sentence, ", .\n");
    for (int ind_word = 1; ind_word < 3 && word != NULL; ind_word++) {
        word = strtok(NULL, ", .\n");
    }
    if (word != NULL) {
        return strlen(word);
    } else {
        return 3;
    }
}
int count_nums(const char *word) {
    int count = 0;
    char* line_of_nums = malloc(1000*sizeof(char));
    int ind_number = 0;
    for (int ind_symbol = 0; ind_symbol < strlen(word); ind_symbol++){
        if (isdigit(word[ind_symbol])){
            line_of_nums[ind_number] = word[ind_symbol];
            ind_number++;
        }
    }
    long long result_number = atoll(line_of_nums);
    while (result_number>0){
        int digit = result_number%10;
        count+=digit;
        result_number = result_number/10;
    }
    return count;
}
int cmp_qsort(const void *a, const void *b){
    if (a == NULL || b == NULL) {
        return 0;
    }
    char *sentence = *((char **) a);
    char *sentence_another = *((char **) b);
    int len_sentence = third_word_length(sentence);
    int len_sentence_another = third_word_length(sentence_another);
    if (len_sentence == len_sentence_another) {
        return 0;
    }
    if (len_sentence<len_sentence_another){
        return -1;
    }else{
        return 1;
    }
}
int cmp_qsort_for_words(const void *a, const void *b){
    if (a == NULL || b == NULL) {
        return 0;
    }
    char *word = *((char **) a);
    char *word_another = *((char **) b);
    int count_digets = count_nums(word);
    int count_digets_another = count_nums(word_another);
    if (count_digets == count_digets_another) {
        return 0;
    }
    if (count_digets<count_digets_another){
        return -1;
    }else{
        return 1;
    }
}
void delete_all_numbers(char** sentences, int last_sentence_index){
    for (int ind_sentence = 0; ind_sentence < last_sentence_index; ind_sentence++) {
        int sentence_len = strlen(sentences[ind_sentence]);
        for (int ind_symbol = 0, k = 0; ind_symbol < sentence_len; ind_symbol++) {
            if (isdigit(sentences[ind_sentence][ind_symbol])) {
                memmove(&sentences[ind_sentence][ind_symbol], &sentences[ind_sentence][ind_symbol+1], sentence_len-(ind_symbol));
                ind_symbol--;
                sentence_len--;
            }
            if (sentences[ind_sentence][ind_symbol] == '.' && sentences[ind_sentence][ind_symbol-1]==' '){
                memmove(&sentences[ind_sentence][ind_symbol-1], &sentences[ind_sentence][ind_symbol], sentence_len-(ind_symbol-1));
                sentence_len--;
            }
        }
        sentences[ind_sentence][sentence_len] = '\0';
    }
}
void is_palindrom(char** sentences, int last_sentence_index){
    for (int ind_sentence = 0; ind_sentence < last_sentence_index; ind_sentence++) {
        char* sentence = sentences[ind_sentence];
        char* copy_sentence = malloc(strlen(sentence)+2);
        int ind_copy_sentence = 0;
        int flag_of_palindrom = 1;
        for (int ind_symbol = 0; ind_symbol < strlen(sentence); ind_symbol++){
            if (isalpha(sentence[ind_symbol])){
                copy_sentence[ind_copy_sentence] = tolower(sentence[ind_symbol]);
                ind_copy_sentence++;
            }else if (isdigit(sentence[ind_symbol])){
                copy_sentence[ind_copy_sentence] = sentence[ind_symbol];
                ind_copy_sentence++;
            };
        }
        int ind_symbol = 0;
        while (flag_of_palindrom && ind_symbol<ind_copy_sentence)
        {
            if (copy_sentence[ind_symbol] != copy_sentence[ind_copy_sentence-ind_symbol-1]){
                flag_of_palindrom = 0;
            }
            ind_symbol++;
        }

        printf("%s",sentence);
        if (flag_of_palindrom == 1) {
            printf("\tPalindrome\n");
        } else {
            printf("\tNothing interesting\n");
        }
    }
}
int delete_sentences(char** sentences, int last_sentence_index){
    for (int sentence_ind = 0; sentence_ind < last_sentence_index; sentence_ind++){
        if (tolower(sentences[sentence_ind][0]) == tolower(sentences[sentence_ind][strlen(sentences[sentence_ind])-2]) || strlen(sentences[sentence_ind])<3){
            free(sentences[sentence_ind]);
            last_sentence_index--;
            memmove(&sentences[sentence_ind],&sentences[sentence_ind+1], (last_sentence_index-sentence_ind)*sizeof(char*));
            sentence_ind--;
        }
    }
    return last_sentence_index;
}
void sort_sentences(char** sentences, int last_sentence_index){
    qsort(sentences, last_sentence_index, sizeof(char *), cmp_qsort);
}
void sort_words(char** sentences, int last_sentence_index){
    for (int ind_sentence = 0; ind_sentence<last_sentence_index; ind_sentence++){
        char* current_sentence = sentences[ind_sentence];
        char* word = strtok (current_sentence," ,");
        int last_word_index = 0;
        int counter_for_realloc = 1;
        char** words_separated = malloc(1000*sizeof(char*));
        while (word!=NULL){
            if (word[strlen(word)-1] == '.'){
                word[strlen(word)-1] = '\0';
            }
            words_separated[last_word_index] = word;
            last_word_index++;
            word = strtok (NULL," ,");
        }
        qsort(words_separated, last_word_index, sizeof(char *), cmp_qsort_for_words);
        for (int ind_word = 0; ind_word<last_word_index; ind_word++){
            if (ind_word+1<last_word_index){
                printf("%s ", words_separated[ind_word]);
            }
            else{
                printf("%s.\n", words_separated[ind_word]);
            }
        }
    }
}
void features_help(){
    char* feature_delete_numbers = FEATURE_DELETE_ALL_NUMBERS;
    char* feature_is_palindrom = FEATURE_IS_PALINDROM;
    char* feature_delete_sentences = FEATURE_DELETE_SENTENCES;
    char* feature_sort_sentences = FEATURE_SORT_SENTENCES;
    printf("%s\n%s\n%s\n%s", feature_delete_numbers, feature_is_palindrom, feature_delete_sentences, feature_sort_sentences);
}
