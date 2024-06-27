#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


int num_sent = 0;

char **text_input();
char **primary_changes(char **text);
char **words_is_numbers(char **text);
char **upper_sort(char **text);
char **del_by_word(char **text, char *word);
char **digit_conversion(char **text);
char **word_doubling(char **text);
char *slide_and_paste(char *sent, char *word, int start);
char *word_input();
int cmp(const void* str1, const void* str2);
void text_output(char **text);
void text_free(char **text);
void display_information();

int main() {
    printf("Course work for option 4.3, created by BRYZGALOV NIKITA.\n");
    int subtask_number, error_check;
    error_check = scanf("%d", &subtask_number) -1;

    if (error_check) {
        printf("Error: failed to read the subtask number.\n");
        return 0;
    } else if ((subtask_number < 0 || subtask_number > 5) && subtask_number != 9) {
        printf("Error: subtask number is incorrect.\n");
        return 0;
    }

    if (subtask_number == 5) {
        display_information();
        return 0;
    }

    char *word;

    if (subtask_number == 3) {
        word = word_input();
        if (word == NULL) {
            printf("Error: word could not read or an empty word was entered.\n");
            free(word);
            return 0;
        }
    }

    char **text = primary_changes(text_input());
    //char **text = text_input();
    if (num_sent == 0) {
        text_free(text);
        printf("Error: text could not be read or empty text was entered.\n");
        return 0;
    }

    switch (subtask_number) {
        case 0:
            text_output(text);
            break;
        case 1:
            text = words_is_numbers(text);
            if (num_sent == 0) {
                printf("Error: аll sentences have been removed.\n");
                text_free(text);
                return 0;
            }
            text_output(text);
            break;
        case 2:
            text = upper_sort(text);
            text_output(text);
            break;
        case 3:
            text = del_by_word(text, word);
            if (num_sent == 0) {
                printf("Error: аll sentences have been removed.\n");
                text_free(text);
                return 0;
            }
            free(word);
            text_output(text);
            break;
        case 4:
            text = digit_conversion(text);
            if (num_sent == 0) {
                printf("Error: memory allocation occurred incorrectly.\n");
                text_free(text);
                return 0;
            }
            text_output(text);
            break;
        case 9: 
            text = word_doubling(text);
            text_output(text);
            break;
    }

    text_free(text);
    return 0;
}

char **text_input() {
    int len_sent = 0, max_len_sent = 100, max_num_sent = 50, flag = 1;
    char **text = malloc(sizeof(char*) * max_num_sent);
    char **text_;
    char *sent = malloc(sizeof(char) * max_len_sent);
    char *sent_;
    char symbol, prev_symbol;

    while (flag) {
        symbol = getchar();

        if ((symbol == '\n') && (prev_symbol == '\n'))
            flag = 0;
        prev_symbol = symbol;

        if (((symbol == '\t') && (len_sent == 0)) || ((symbol == '\n') && (len_sent == 0)) || ((symbol == ' ') && (len_sent == 0)))
            continue;

        len_sent ++;
        if (len_sent >= max_len_sent) {
            max_len_sent += 100;
            sent_ = realloc(sent, sizeof(char) * max_len_sent);
            if (sent_ == NULL) {
                num_sent = 0;
                free(sent);
                return NULL;
            }
            sent = sent_;
        }
        sent[len_sent -1] = symbol;

        //if (symbol == '.' || flag == 0) {
        if (symbol == '.') {
            num_sent ++;
            if (num_sent >= max_num_sent) {
                max_num_sent += 50;
                text_ = realloc(text, sizeof(char*) * max_num_sent);
                if (text_ == NULL) {
                    num_sent = 0;
                    free(sent);
                    return NULL;
                }
                text = text_;
            }
            text[num_sent - 1] = malloc(sizeof(char) * max_len_sent);
            strcpy(text[num_sent - 1], sent);
            text[num_sent - 1][len_sent] = '\0';
            len_sent = 0, max_len_sent = 100;
            free(sent);
            sent = malloc(sizeof(char) * max_len_sent);
        }
    }
    free(sent);
    return text;
}

char **primary_changes(char **text) {
    int len, flag_del;
    for (int i = 0; i < (num_sent -1); i ++) {
        int j = i;
        while (j < num_sent) {
            flag_del = 0;
            len = strlen(text[i]);
            if (strlen(text[j]) == 1) flag_del = 1;
            if ((j > i) && (len == strlen(text[j]))) {
                flag_del = 1;
                for (int q = 0; q < len; q ++) {
                    if (tolower(text[i][q]) != tolower(text[j][q])) {
                        flag_del = 0;
                        break;
                    }
                }
            }

            if (flag_del) {
                free(text[j]);
                for (int q = j; q < (num_sent -1); q ++)
                    text[q] = text[q+1];
                num_sent --;
                j --;
            }
            j ++;
        }
    }
    return text;
}

char **words_is_numbers(char **text) {
    int flag_del;
    int i = 0;
    while (i < num_sent) {
        flag_del = 0;
        for (int j = 0; j < strlen(text[i]); j ++) {
            if (!((text[i][j] == ' ') || (text[i][j] == '\n') || (text[i][j] == '.') || (text[i][j] == ',') || (isdigit(text[i][j])))) {
                flag_del = 1;
                break;
            }
        }
        if (flag_del) {
                free(text[i]);
                for (int q = i; q < (num_sent -1); q ++)
                    text[q] = text[q+1];
                num_sent --;
                i --;
        }
        i ++;
    }
    return text;
}

int cmp(const void* str1, const void* str2) {
    char *str1_ = *((char **) str1);
    char *str2_ = *((char **) str2);
    int num_isupper_str1 = 0, num_isupper_str2 = 0;
    for (int i = 0; i < strlen(str1_); i ++)
        if (isupper(str1_[i])) num_isupper_str1 ++;
    for (int i = 0; i < strlen(str2_); i ++)
        if (isupper(str2_[i])) num_isupper_str2 ++;

    if (num_isupper_str1 > num_isupper_str2) return -1;
    else if (num_isupper_str1 == num_isupper_str2) return 0;
    else return 1;
}

char **upper_sort(char **text) {
    qsort(text, num_sent, sizeof(char *), cmp);
    return text;
}

void text_output(char **text) {
    for (int i = 0; i < num_sent; i ++)
        puts(text[i]);
}

char *word_input() {
    int len = 0, flag = 1;
    char *word = malloc(sizeof(char) * 1);
    char *word_;
    char symbol;
    // printf("Enter word: ");
    while (1) {
        symbol = getchar();
        if ((len == 0) && (symbol == '\n') && flag) {
            flag = 0;
            continue;
        }
        if ((symbol != ' ') && (symbol != '\n') && (symbol != '.')) {
            len ++;
            word_ = realloc(word, (len + 1) * sizeof(char));
            if (word_ == NULL) {
                return word_;
            }
            word = word_;
            word[len-1] = tolower(symbol);
        } else {break; }
    }
    if (len == 0) {
        return NULL;
    }
    word[len] = '\0';
    return word;
}

void text_free(char **text) {
    for (int i = 0; i < num_sent; i ++)
        free(text[i]);
    free(text);
}

char **del_by_word(char **text, char *word) {
    char *word_in_sent;
    int count_words, flag_del, flag, len = strlen(word);
    char *sent;
    int i = 0;
    while (i < num_sent) {
        sent = malloc((strlen(text[i]) + 1) * sizeof(char));
        strcpy(sent, text[i]);
        flag_del = 0;
        count_words = 0;
        word_in_sent = strtok(sent, " ,.");
        while (word_in_sent != NULL) {
            flag = 0;
            if (strlen(word_in_sent) == len) {
                flag = 1;
                for (int j = 0; j < len; j ++) {
                    if (tolower(word_in_sent[j]) != word[j]) {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag) count_words ++;
            word_in_sent = strtok(NULL, " ,.");
            if (count_words >= 2) {
                flag_del = 1;
                break;
            }
        }
        if (flag_del) {
                free(text[i]);
                for (int q = i; q < (num_sent -1); q ++)
                    text[q] = text[q+1];
                i --;
                num_sent --;
        }
        i ++;
        free(sent);
    }
    return text;
}

char *slide_and_paste(char *sent, char *word, int start) {
    char *sent_;
    int n = strlen(word) - 1;
    sent_ = realloc(sent, (sizeof(char) * (strlen(sent) + n + 5)));
    if (sent_ == NULL) {
        return NULL;
    }
    sent = sent_;
    int len = strlen(sent);
    for (int i = (len + n + 1); i >= (start + n); i --)
        sent[i] = sent[i-n];
    for (int i = 0; i < (n+1); i ++)
        sent[start + i] = word[i];
    return sent;
}

char **digit_conversion(char **text) {
    int len, j;
    for (int i = 0; i < num_sent; i ++) {
        len = strlen(text[i]);
        j = 0;
        while (j < len) {
            if (isdigit(text[i][j])) {
                switch (text[i][j]) {
                    case '0':
                        text[i] = slide_and_paste(text[i], "zero", j);
                        break;
                    case '1':
                        text[i] = slide_and_paste(text[i], "one", j);
                        break;
                    case '2':
                        text[i] = slide_and_paste(text[i], "two", j);
                        break;
                    case '3':
                        text[i] = slide_and_paste(text[i], "three", j);
                        break;
                    case '4':
                        text[i] = slide_and_paste(text[i], "four", j);
                        break;
                    case '5':
                        text[i] = slide_and_paste(text[i], "five", j);
                        break;
                    case '6':
                        text[i] = slide_and_paste(text[i], "six", j);
                        break;
                    case '7':
                        text[i] = slide_and_paste(text[i], "seven", j);
                        break;
                    case '8':
                        text[i] = slide_and_paste(text[i], "eight", j);
                        break;
                    case '9':
                        text[i] = slide_and_paste(text[i], "nine", j);
                        break;
                }
            }
            j ++;
            len = strlen(text[i]);
        }
        if (text[i] == NULL) {
            num_sent = 0;
            return NULL;
        }
    }
    return text;
}

char **word_doubling(char **text) {
    int new_len;
    char *sent;
    char *new_sent;
    for (int i = 0; i < num_sent; i ++) {
        sent = text[i];
        new_len = (strlen(sent) * 2 + 10);
        new_sent = malloc(sizeof(char) * new_len);
        strcpy(new_sent, sent);
        new_sent[strlen(sent) -1] = ' ';
        new_sent = strcat(new_sent, sent);
        new_sent[strlen(sent)*2] = '\0';
        free(sent);
        text[i] = malloc(sizeof(char) * new_len);
        strcpy(text[i], new_sent);
        free(new_sent);
    }
    return text;
}

void display_information() {
    printf("Displaying help about the functions implemented in the program:\n");
    printf("0 – Output text after initial mandatory processing.\n");
    printf("1 – Print all sentences in which all words consist only of numbers.\n");
    printf("2 – Sort sentences by reducing the number of capital letters in it.\n");
    printf("3 – Delete all sentences in which a certain word (which - the user enters it into your program after selecting this action) occurs 2 or more times.\n");
    printf("4 - Transform all sentences so that each occurrence of a digit is replaced by the corresponding substring (0-“Zero”, 1-“One”, 2-“Two”, etc.).\n");
    printf("5 – Display information about the functions that the program implements.\n");
}
