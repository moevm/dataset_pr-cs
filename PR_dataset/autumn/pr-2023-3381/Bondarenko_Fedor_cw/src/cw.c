#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BLOCK_SIZE_FOR_TEXT 10
#define BLOCK_SIZE_FOR_SENTENCE 10
#define HELP_MSG "После вывода информацию о варианте курсовой работе программа ожидает ввода пользователем числа – номера команды:\n0 – вывод текста после первичной обязательной обработки,\n1 – вызов функции под номером 1 из списка задания,\n2 – вызов функции под номером 2 из списка задания,\n3 – вызов функции под номером 3 из списка задания,\n4 – вызов функции под номером 4 из списка задания,\n5 – вывод справки о функциях, которые реализует программа.\n"
#define MEMORY_ERR "Error: error re/allocating memory"
#define COMMAND_ERR "Error: Введенной команды не существует. (5 - вызов справки)\n"

void make_user_input(char*** text);
void output_text(char*** text, size_t* count);
void print_palindrome_sentence(char* sentence, char* is_palindrome);
void delete_all_repeated_sentences(char*** text, size_t* count);
void delete_all_numbers_from_sentence(char*** text, size_t count);
void check_sentence_for_palindrome(char** text, size_t count);
void delete_sentences_with_equals_first_and_last_chars(char*** text, size_t* count);
void sort_text(char*** text);
void func9(char*** text, size_t count, char* sentence);
void get_sentence_for_func9(char** sentence);

void free_text(char*** text, size_t* count);
size_t count_upper_letters(char* sentence);
size_t count_length_of_the_third_word(const char* sentence);
int compare(const void* str_a, const void* str_b);
int check_chars_equality(char symbol_a, char symbol_b);
int check_char_for_space(char symbol);
int terminate(char last_symbol, char current_symbol);
int check_is_the_end(char symbol);

size_t sentence_count = 0;
size_t max_sentence_capacity = 0;

int main() {
    
    size_t n = 6;

    puts("Course work for option 4.14, created by Bondarenko Fedor.");
    
    scanf("%ld\n", &n);

    char** text = (char**)malloc(BLOCK_SIZE_FOR_TEXT*sizeof(char*));
    for (size_t i = 0; i < BLOCK_SIZE_FOR_TEXT; i++) {
        text[i] = (char*)malloc(BLOCK_SIZE_FOR_SENTENCE*sizeof(char));
    }
    char* sentence = (char*)malloc(122*sizeof(char));

    switch(n) {

        case 0:
            make_user_input(&text);
            delete_all_repeated_sentences(&text, &sentence_count);
            output_text(&text, &sentence_count);
            break;
        case 1:
            make_user_input(&text);
            delete_all_repeated_sentences(&text, &sentence_count);
            delete_all_numbers_from_sentence(&text, sentence_count);
            output_text(&text, &sentence_count);
            break;
        case 2:
            make_user_input(&text);
            delete_all_repeated_sentences(&text, &sentence_count);
            check_sentence_for_palindrome(text, sentence_count);
            break;
        case 3:
            make_user_input(&text);
            delete_all_repeated_sentences(&text, &sentence_count);
            delete_sentences_with_equals_first_and_last_chars(&text, &sentence_count);
            output_text(&text, &sentence_count);
            break;
        case 4:
            make_user_input(&text);
            delete_all_repeated_sentences(&text, &sentence_count);
            sort_text(&text);
            output_text(&text, &sentence_count);
            break;
        case 5:
            printf("%s", HELP_MSG);
            sentence_count = BLOCK_SIZE_FOR_TEXT;
            break;
        case 9:
            get_sentence_for_func9(&sentence);
            make_user_input(&text);
            delete_all_repeated_sentences(&text, &sentence_count);
            func9(&text, sentence_count, sentence);
            break;
        default:
            printf("%s", COMMAND_ERR);
            sentence_count = BLOCK_SIZE_FOR_TEXT;
            break;
    }
    free_text(&text, &sentence_count);
    free(sentence);
    
    return 0;
}

void make_user_input(char*** text) {

    size_t capacity_for_text = BLOCK_SIZE_FOR_TEXT;
    size_t sentence_index = 0;
    size_t flag = 1;

    while (1) {

        if (sentence_index == capacity_for_text-1) {
                capacity_for_text += BLOCK_SIZE_FOR_TEXT;
                *text = (char**)realloc(*text, capacity_for_text*sizeof(char*));
                if (*text == NULL) {
                    printf("%s", MEMORY_ERR);
                    break;
                }
                for (size_t i = sentence_index+1; i < capacity_for_text; i++) {
                    (*text)[i] = (char*)calloc(BLOCK_SIZE_FOR_SENTENCE, sizeof(char));
                }
            }

        char ch = getchar();
        char buffer = -1;
        char before_buffer = -2;
        size_t capacity_for_sentence = BLOCK_SIZE_FOR_SENTENCE;
        size_t char_index = 0;

        while (1) {

            if (max_sentence_capacity < char_index) {
                max_sentence_capacity = char_index+1;
            }

            if (char_index == 0 && check_char_for_space(ch)) {
                buffer = ch;
                ch = getchar();
                continue;
            }
            if (char_index == 0 && ch == '\n' && !terminate(buffer, ch)) {
                buffer = ch;
                ch = getchar();
                if (terminate(buffer, ch)) {
                    flag = 0;
                    break;
                }
                continue;    
            }

            (*text)[sentence_index][char_index++] = ch;
            
            if (char_index == capacity_for_sentence-1) {
                capacity_for_sentence += BLOCK_SIZE_FOR_SENTENCE;
                (*text)[sentence_index] = realloc((*text)[sentence_index], capacity_for_sentence*sizeof(char));
                if ((*text)[sentence_index] == NULL) {
                    printf("%s", MEMORY_ERR);
                    break;
                }
            }

            if (check_is_the_end(ch)) {
                (*text)[sentence_index++][char_index] = '\0';
                break;
            }

            before_buffer = buffer;
            buffer = ch;
            ch = getchar();
            if (terminate(buffer, ch)) {
                flag = 0;
                if (before_buffer != '.') {
                    (*text)[sentence_index][char_index-1] = '.';
                    (*text)[sentence_index][char_index] = '\0';
                    sentence_index++;
                }
                break;
            }
        }

        if (flag == 0) {
            break;
        }
    }

    sentence_count = sentence_index;
}

void output_text(char*** text, size_t* count) {
    for (size_t i = 0; i < (*count); i++) {
        printf("%s\n", (*text)[i]);
    }
}

void delete_all_repeated_sentences(char*** text, size_t* count) {
    
    size_t count_sentences_to_delete = 0;

    for (size_t i = 0; i < (*count)-1; i++) {
        for (size_t j = i+1; j < (*count); j++) {
            if (strlen((*text)[i]) == strlen((*text)[j])) {
                size_t flag = 1;
                for (size_t k = 0; k < strlen((*text)[i]); k++) {
                    if (check_chars_equality((*text)[i][k], (*text)[j][k])) {
                        flag = 1;
                    } else {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    (*text)[j][0] = -1;
                }
            }
        }
    }

    for (size_t i = 0; i < (*count); i++) {
        if ((*text)[i][0] == -1) {
            count_sentences_to_delete++;
        }
    }

    size_t count_sentences_of_formatted_text = (*count) - count_sentences_to_delete;
    char** formatted_text = (char**)malloc(count_sentences_of_formatted_text*sizeof(char*));
    for (size_t i = 0; i < count_sentences_of_formatted_text; i++) {
        formatted_text[i] = (char*)calloc(max_sentence_capacity+1, sizeof(char));
    }

    size_t sentence_index = 0;
    for (size_t i = 0; i < (*count); i++) {
        if ((*text)[i][0] != -1) {
            strncpy(formatted_text[sentence_index++], (*text)[i], strlen((*text)[i]));
        }
    }

    size_t n = *count - *count%BLOCK_SIZE_FOR_TEXT + BLOCK_SIZE_FOR_TEXT;

    free_text(text, &n);

    *text = formatted_text;
    *count = count_sentences_of_formatted_text;    
}

void delete_all_numbers_from_sentence(char*** text, size_t count) {

    char** buffer_text = (char**)malloc(count*sizeof(char*));
    for (size_t i = 0; i < sentence_count; i++) {
        buffer_text[i] = (char*)calloc(strlen((*text)[i])+1, sizeof(char));
    }
    size_t sentence_index = 0;
    for (size_t i = 0; i < count; i++) {
        size_t char_index = 0;
        for (size_t j = 0; j < strlen((*text)[i]); j++) {
            if (!isdigit((*text)[i][j])) {
                buffer_text[sentence_index][char_index++] = (*text)[i][j];
            }
        }
        sentence_index++;
    }
    
    free_text(text, &count);

    *text = buffer_text;
}

void print_palindrome_sentence(char* sentence, char* is_palindrome) {
    printf("%s %s\n", sentence, is_palindrome);
}

void check_sentence_for_palindrome(char** text, size_t count) {

    char** buffer_text = (char**)malloc(count*sizeof(char*));
    for (size_t i = 0; i < count; i++) {
        buffer_text[i] = (char*)calloc(strlen(text[i])+1, sizeof(char));
    }

    char* buffer_sentence = (char*)calloc(sizeof("Nothing interesting"), sizeof(char));

    size_t sentence_index = 0;
    for (size_t i = 0; i < count; i++) {
        size_t char_index = 0;
        for (size_t j = 0; j < (strlen(text[i])-1); j++) {
            if (!isspace(text[i][j])) {
                buffer_text[sentence_index][char_index++] = text[i][j];
            }
        }
        sentence_index++;
    }

    for (size_t i = 0; i < sentence_index; i++) {
        size_t flag = 1;
        for (size_t j = 0; j < strlen(buffer_text[i])/2; j++) {
            if (buffer_text[i][j] != buffer_text[i][strlen(buffer_text[i]) - j - 1]) {
                flag = 0;
                break;
            }
        }

        if (flag) {
            strcpy(buffer_sentence, "Palindrome");
            print_palindrome_sentence(text[i], buffer_sentence);
        } else {
            strcpy(buffer_sentence, "Nothing interesting");
            print_palindrome_sentence(text[i], buffer_sentence);
        }
    }

    free(buffer_sentence);
    free_text(&buffer_text, &sentence_index);
}

void delete_sentences_with_equals_first_and_last_chars(char*** text, size_t* count) {

    for (size_t i = 0; i < (*count); i++) {
        if (strlen((*text)[i]) > 2) {
            if (check_chars_equality((*text)[i][0], (*text)[i][strlen((*text)[i])-2])) {
                (*text)[i][0] = -1;
            }
        } else {
            (*text)[i][0] = -1;
        }
    }

    size_t count_of_sentence_to_delete = 0; 
    for (size_t i = 0; i < (*count); i++) {
        if ((*text)[i][0] == -1) {
            count_of_sentence_to_delete++;
        }
    }
    size_t sentence_count_of_buffer_text = (*count) - count_of_sentence_to_delete;
    char** buffer_text = (char**)malloc(sentence_count_of_buffer_text*sizeof(char*));
    for (size_t i = 0; i < sentence_count_of_buffer_text; i++) {
        buffer_text[i] = (char*)calloc(max_sentence_capacity+1, sizeof(char));
    }

    size_t sentence_index = 0;
    for (size_t i = 0; i < (*count); i++) {
        if ((*text)[i][0] != -1) {
            strncpy(buffer_text[sentence_index++], (*text)[i], strlen((*text)[i]));
        }
    }

    free_text(text, count);
    
    *text = buffer_text;
    *count = sentence_count_of_buffer_text;
}

void sort_text(char*** text) {

    qsort(*text, sentence_count, sizeof(char*), compare);
}

void func9(char*** text, size_t count, char* sentence) {

    size_t count_in_first_sentence = count_upper_letters(sentence);

    for (size_t i = 0; i < count; i++) {
        if (count_in_first_sentence < count_upper_letters((*text)[i])) {
            (*text)[i][0] = -1;
        }
    }

    for (size_t i = 0; i < count; i++) {
        if ((*text)[i][0] != -1) {
            printf("%s\n", (*text)[i]);
        }
    }
}

void get_sentence_for_func9(char** sentence) {

    fgets((*sentence), 122, stdin);
    (*sentence)[strlen((*sentence))-1] = '\0';
}

size_t count_upper_letters(char* sentence) {

    size_t count = 0;
    for (size_t i = 0; i < strlen(sentence); i++) {
        if (isupper(sentence[i])) {
            count++;
        }
    }

    return count;
}

size_t count_length_of_the_third_word(const char* sentence) {

    size_t count_of_words = 0;
    size_t lenght_of_word = 0;
    for (size_t i = 1; i < strlen(sentence); i++) {
        if ((isspace(sentence[i]) || ispunct(sentence[i])) && isalnum(sentence[i-1])) {
            count_of_words++;
        }
        if (count_of_words == 2 && isalnum(sentence[i])) {
            lenght_of_word++;
        }
        if (count_of_words == 3) {
            break;
        }
    }

    if (count_of_words < 3) {
        lenght_of_word = 3;
    }

    return lenght_of_word;
}

void free_text(char*** text, size_t* count) {

    for (size_t i = 0; i < *count; i++) {
        free((*text)[i]);
    }
    free(*text);
}

int compare(const void* str_a, const void* str_b) {

    const char* first_str= *((const char**)str_a);
    const char* second_str = *((const char**)str_b);

    if (count_length_of_the_third_word(first_str) > count_length_of_the_third_word(second_str)) {
        return 1;
    } else if (count_length_of_the_third_word(second_str) > count_length_of_the_third_word(first_str)){
        return -1;
    }

    return 0;
}

int check_chars_equality(char symbol_a, char symbol_b) {

    if (tolower(symbol_a) == tolower(symbol_b)) {
        return 1;
    }

    return 0;
}

int check_char_for_space(char symbol) {

    if (symbol == ' ' || symbol == '\t') {
        return 1;
    }

    return 0;
}

int terminate(char last_symbol, char current_symbol) {

    if (last_symbol == '\n' && current_symbol == '\n') {
        return 1;
    }

    return 0;
}

int check_is_the_end(char symbol) {

    if (symbol == '.') {
        return 1;
    }

    return 0;
}
