/*https://docs.google.com/document/d/1-1D6ziW7nPR1UrYb0fZSiMlYhpFcL1ojeBI-dLrRvic/edit#heading=h.a6tytg6pyeuy*/
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define DEFAULT_CAPACITY 10

/*Основные функции*/
void words_and_numbers(char **, int);

void reverse_words(char *);

int delete_comma_sentences(char *);

void sentences_sorting(char **, int);

void functional_information();
/*Вспомогательные функции*/
/*Первичные функции*/
char *input(int *);

char **split_sentences(char *, int);

char **delete_repeat_sentences(char **, int *);

/*Доп функция для команды 1*/
void word_tolower(char *);

char **separate_words(char **, int , int *);

/*Доп функции для команды 4*/
int get_fifth_symbol(const char *);

int fifth_character_comparison(const void *, const void *);

/*Управление вызовами функций по командам*/
int general_manager(int);

/*Управление вызовами функций по командам для защиты*/
int manager_defense_task();

/*Функции на защиту*/
char *input_first_sentence();

int how_many_numbers(char *);


void error_output(int num_of_error) {
    if (num_of_error == 1)
        printf("Error: Wrong command\n");
    if (num_of_error == 2) {
        printf("Error: Last symbol not dot");
        exit(0);
    }
    if (num_of_error == 3) {
        printf("Error: Too many letters");
        exit(0);
    }
}

int main() {
    printf("Course work for option 4.6, created by Anastasiya Milkhert.\n");
    while (1) {
        int task_number = 0;
        scanf("%d", &task_number);
        if (task_number >= 0 && task_number <= 4) {
            general_manager(task_number);
            break;
        } else if (task_number == 8) {
            manager_defense_task();
            break;
        } else if (task_number == 5) {
            functional_information();
            break;
        } else {
            error_output(1);
            break;
        }
    }
    return 0;

}

int manager_defense_task() {
    char *first_sentence = input_first_sentence();
    int numbers_count_first = how_many_numbers(first_sentence);

    int i;
    int sentences_count = 0;
    /*Первичные преобразования текста*/
    char *full_text = input(&sentences_count);
    char **sentences_array = split_sentences(full_text, sentences_count);
    char **sentences_no_duplicat = delete_repeat_sentences(sentences_array, &sentences_count);

    int numbers_count_sent = 0;
    for (i = 0; i < sentences_count; i++) {
        numbers_count_sent = how_many_numbers(sentences_no_duplicat[i]);
        if (numbers_count_sent > numbers_count_first) {
            printf("(%d) %s.\n", numbers_count_sent - numbers_count_first, sentences_no_duplicat[i]);
        }
    }
    free(first_sentence);
    free(full_text);
    free(sentences_array);
    free(sentences_no_duplicat);
    return 0;
}

int general_manager(int task_number) {
    int i;
    int sentences_count = 0;
    /*Первичные преобразования текста*/
    char *full_text = input(&sentences_count);
    char **sentences_array = split_sentences(full_text, sentences_count);
    char **sentences_no_duplicat = delete_repeat_sentences(sentences_array, &sentences_count);

    if (task_number == 0) {
        for (i = 0; i < sentences_count; i++) {
            printf("%s.\n", sentences_no_duplicat[i]);
        }
    } else if (task_number == 1) {
        words_and_numbers(sentences_no_duplicat, sentences_count);
    } else if (task_number == 2) {
        for (i = 0; i < sentences_count; i++) {
            reverse_words(sentences_no_duplicat[i]);
            printf("%s.\n", sentences_no_duplicat[i]);
        }
    } else if (task_number == 3) {
        for (i = 0; i < sentences_count; i++) {
            if (delete_comma_sentences(sentences_no_duplicat[i]) == 0)
                printf("%s.\n", sentences_no_duplicat[i]);
        }
    } else if (task_number == 4) {
        sentences_sorting(sentences_no_duplicat, sentences_count);
    } else
        error_output(1);

    free(full_text);
    free(sentences_array);
    free(sentences_no_duplicat);
    return 0;

}

char *input(int *count_sentences) {
    int capacity, i;
    char c;

    capacity = BUFFER_SIZE;
    i = 0;
    /*Выделение памяти*/
    char *text = (char *) calloc(BUFFER_SIZE, sizeof(char));

    while ((c = getchar())) {
        if (i == 0 && c == '\n')
            continue;
        else {
            text[i] = c;
            ++i;
        }
        if (i == capacity - 1) {
            capacity += BUFFER_SIZE;
            /*
             char *more_memory = (char*)realloc(text, capacity * sizeof(char));
             */
            char *more_memory = (char *) realloc(text, capacity * sizeof(char));
            text = more_memory;
        }
        if (c == '.') {
            ++(*count_sentences);
        }
        if (i >= 2 && text[i - 2] == '\n' && text[i - 1] == '\n') {
            if (text[i - 3] == '.')
                break;
            else
                error_output(2);
        }
    }
    text[i - 2] = '\0';
    return text;
}

char **split_sentences(char *full_text, int count_sentences) {
    int capacity = DEFAULT_CAPACITY;
    int length = 0;
    char **sentences = (char **) calloc(count_sentences, sizeof(char *));
    char *sentence = strtok(full_text, ".");

    while (sentence != NULL) {
        if (length >= count_sentences) {
            capacity *= 2;
            sentences = realloc(sentences, sizeof(char *) * capacity);
        }
        if (sentence[0] == ' ' || sentence[0] == '\t' || sentence[0] == '\n')
            sentence++;
        sentences[length] = sentence;
        sentence = strtok(NULL, ".");
        ++length;

    }
    return sentences;
}

char **delete_repeat_sentences(char **sentences, int *len) {
    int deleted_sentences = 0;
    for (int i = 0; i < (*len); i++) {
        for (int j = i + 1; j < (*len); j++) {
            if (sentences[i] != NULL && sentences[j] != NULL) {
                if (strcasecmp(sentences[i], sentences[j]) == 0) {
                    sentences[j] = NULL;
                    deleted_sentences++;
                }
            }
        }
    }
    int index = 0;
    char **res_sent = (char **) calloc((*len) - deleted_sentences, sizeof(char *));
    for (int k = 0; k < (*len); k++) {
        if (sentences[k] != NULL) {
            res_sent[index++] = sentences[k];
        }
    }
    (*len) -= deleted_sentences;
    return res_sent;
}


//int words_count()

void word_tolower(char *string) {
    for (int i = 0; i < strlen(string); i++) {
        string[i] = tolower(string[i]);
    }
}

char **separate_words(char **sentenses, int words_count, int *size) {
    char **words = (char **) calloc(1000, sizeof(char *));

    for (int i = 0; i < words_count; i++) {
        char *sep = " ,";
        char *substr;

        substr = strtok(sentenses[i], sep);
        while (substr != NULL) {
            while (isspace(*substr)) {
                substr++;
            }
            words[*size] = substr;
            (*size)++;
            substr = strtok(NULL, sep);
        }
    }
    return words;
}

void words_and_numbers(char **sentenses, int words_count) {
    int size = 0;
    char **words = separate_words( sentenses, words_count, &size);

    char **words_flag = (char **) calloc(1000, sizeof(char *));
    for (int i = 0; i < size; i++) {
        int k = 0; //счётчик для слова
        char *copyi = (char *) calloc(strlen(words[i]) + 1, sizeof(char));
        strcpy(copyi, words[i]);
        word_tolower(copyi);

        for (int j = 0; j < size; j++) {
            char *copyj = (char *) calloc(strlen(words[j]) + 1, sizeof(char));
            strcpy(copyj, words[j]);
            word_tolower(copyj);


            if (strcmp(copyi, copyj) == 0) {
                k++;
            }
            free(copyj);
        }
        int flag = 1;
        for (int q = 0; q < i; q++) {
            char *copyq = (char *) calloc(strlen(words[q]) + 1, sizeof(char));
            strcpy(copyq, words_flag[q]);
            word_tolower(copyq);
            if (strcmp(copyi, copyq) == 0) flag = 0;
            free(copyq);
        }
        if (flag) {
            printf("%s %d\n", copyi, k);
        }
        //какие слова уже выведены
        words_flag[i] = copyi;
        free(copyi);
    }
    free(words);
    free(words_flag);
}


void reverse_words(char *sentence) {
    int length = strlen(sentence);
    int start = 0;
    int end = length - 1;
    char new_sentence[length + 1];

    for (int i = 0; i < length; i++) {
        new_sentence[i] = ' ';
    }
    new_sentence[length] = '\0';

    while (start <= end) {
        while (start < length && !isalpha(sentence[start])) {
            new_sentence[start] = sentence[start];
            start++;
        }
        int word_end = start;

        while (word_end < length && isalpha(sentence[word_end])) {
            word_end++;
        }

        for (int i = word_end - 1; i >= start; --i) {
            new_sentence[start + (word_end - i - 1)] = sentence[i];
        }
        start = word_end;

    }
    strcpy(sentence, new_sentence);
}


/*Возвращает 0, если запятой нет и 1, если запятая есть*/
int delete_comma_sentences(char *sentence) {
    if (strstr(sentence, ",") == NULL)
        return 0;
    return 1;
}

int get_fifth_symbol(const char *sentence) {
    if (strlen(sentence) < 5)
        return -1;
    char symbol = sentence[4];
    if (symbol == ' ' || symbol == '\t') {
        if (sentence[5] != '\0')
            return sentence[5];
        else
            return -1;
    }
    return symbol;
}

int fifth_character_comparison(const void *a, const void *b) {
    const char *sentence_a = *(const char **) a;
    const char *sentence_b = *(const char **) b;
    int value_a = get_fifth_symbol(sentence_a);
    int value_b = get_fifth_symbol(sentence_b);

    return value_a - value_b;
}

void sentences_sorting(char **sentences, int sentences_count) {
    qsort(sentences, sentences_count, sizeof(char *), fifth_character_comparison);
    for (int i = 0; i < sentences_count; i++) {
        printf("%s.\n", sentences[i]);
    }
}

void functional_information() {
    printf("The program takes as input the command number and the text to be processed according to the algorithm number\n");
    printf("Command 0 - Outputs text after initial processing (no duplicate sentences)\n");
    printf("Command 1 - Prints each word and the number of times it is repeated.\n");
    printf("Command 2 - Convert each sentence so that the characters in each word are in reverse order.\n");
    printf("Command 3 - Deletes sentences in which a comma occurs.\n");
    printf("Command 4 - Sorts sentences by decreasing the value of the 5 character code of the sentence.\n");
    printf("Command 5 - Outputs help about functions implemented in the program.\n");
}

char *input_first_sentence() {
    int i;
    char c;
    int capacity = BUFFER_SIZE;
    char *text = (char *) calloc(capacity, sizeof(char));
    if ((c = getchar()) == '\n');
    for (i = 0; (c = getchar()) != EOF && c != '\n' && i < 200; ++i) {
        if (capacity - 1 == i) {
            capacity += BUFFER_SIZE;
            text = (char *) realloc(text, sizeof(char) * capacity);
        }
        text[i] = c;
    }
    if (i >= 200) {
        error_output(3);
    }
    if (c == '\n') {
        text[i] = c;
        ++i;
    }
    text[i] = '\0';
    return text;
}

int how_many_numbers(char *sentence) {
    int numbers = 0;
    for (int i = 0; i < strlen(sentence); i++) {
        if (isdigit(sentence[i])) {
            numbers = numbers + (sentence[i] - '0');
        }
    }
    return numbers;

}