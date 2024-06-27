#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_STRING_SIZE 8

int strCaseCmp(const char *first_sentence, const char *second_sentence) {
    const unsigned char *ptr_one = (const unsigned char *)first_sentence;
    const unsigned char *ptr_two = (const unsigned char *)second_sentence;
    int result;
    if (ptr_one == ptr_two)
        return 0;
    while ((result = tolower(*ptr_one) - tolower(*ptr_two++)) == 0)
        if (*ptr_one++ == '\0')
            break;
    return result;
}

char *strDup(const char *sentence) {
    char *dup = calloc(strlen(sentence) + 1, sizeof(char));

    if (dup != NULL)
        strcpy(dup, sentence);

    return dup;
}

void funcInfo() {
    printf("Функции программы:");
    printf("0. Вывод текста после первичной обязательной обработки\n");
    printf("1. Найти все предложения в которых есть слова вида “<число>sec>” (“23sec”) задающие количество секунд. Для каждого такого предложения посчитать количество секунд и вывести количество полученных часов, минут и секунд в виде строки “hour:min:sec”.\n");
    printf("2. В каждом предложении удалить первое слово. Если в предложении не останется слов, то его надо удалить.\n");
    printf("3. Удалить все предложения у которых длины всех слов одинаковые.\n");
    printf("4. Отсортировать предложения по уменьшению количества строчных букв в нем.\n");
    printf("5. Вывод справки о функциях.");
}

void funcRemoveDuplicats(char **sentences, int sentences_count);

void funcExtendSentences(int *sentences_allocated, int sentences_count, char ***sentences) {
    if (*sentences_allocated < (sentences_count + 1)) {
        char **temp = *sentences;
        *sentences_allocated *= 2;
        *sentences = malloc(*sentences_allocated * sizeof(char *));
        if (*sentences == NULL) {
            puts("Error: malloc error");
            exit(1);
        }
        memcpy((*sentences), temp, sizeof(char *) * *sentences_allocated);
        free(temp);
    }
}

void funcExtendString(int *current_string_allocated, int current_string_length, char ***sentences, int sentences_count) {
    if (*current_string_allocated < (current_string_length + 2) && *current_string_allocated != 0) {
        char *temp = (*sentences)[sentences_count];
        *current_string_allocated *= 2;
        (*sentences)[sentences_count] = calloc(*current_string_allocated, sizeof(char));
        if ((*sentences)[sentences_count] == NULL) {
            puts("Error: calloc error");
            exit(1);
        }
        strcpy((*sentences)[sentences_count], temp);
        free(temp);
    } else if (*current_string_allocated == 0) {
        *current_string_allocated = MIN_STRING_SIZE;
        (*sentences)[sentences_count] = calloc(*current_string_allocated, sizeof(char));
        if ((*sentences)[sentences_count] == NULL) {
            puts("Error: calloc error");
            exit(1);
        }
    }
}

int funcInput(char ***sentences) {
    int new_lines = 0;  // '\n'
    int sentences_count = 0;
    int sentences_allocated = 4;
    int current_string_length = 0;
    int current_string_allocated = 0;
    *sentences = malloc(sentences_allocated * sizeof(char *));
    char ch;
    while (new_lines < 2) {
        funcExtendSentences(&sentences_allocated, sentences_count, sentences);
        funcExtendString(&current_string_allocated, current_string_length, sentences, sentences_count);
        ch = getchar();

        if (isspace(ch) && ch != '\n') {
            if (current_string_length != 0) {
                (*sentences)[sentences_count][current_string_length++] = ch;
            }
        } else {
            switch (ch) {
                case '.':
                    (*sentences)[sentences_count++][current_string_length] = ch;
                    current_string_length = 0;
                    current_string_allocated = 0;
                    new_lines = 0;
                    break;
                case '\n':
                    new_lines++;
                    break;
                default:
                    (*sentences)[sentences_count][current_string_length++] = ch;
                    new_lines = 0;
                    break;
            }
        }
    }
    funcRemoveDuplicats(*sentences, sentences_count);
    return sentences_count;
}

void funcRemoveDuplicats(char **sentences, int sentences_count) {
    for (int i = 0; i < sentences_count - 1; i++) {
        if (sentences[i] == NULL)
            continue;
        for (int j = i + 1; j < sentences_count; j++) {
            if (sentences[j] == NULL)
                continue;
            if (strCaseCmp(sentences[i], sentences[j]) == 0) {
                sentences[i][0] = '\0';
            }
        }
    }
}

int funcCountLowersChars(char *sentence) {
    if (sentence == NULL)
        return 0;
    int sum = 0;
    for (int i = 0; i < strlen(sentence); i++) {
        if (islower(sentence[i])) {
            sum++;
        }
    }
    return sum;
}

int summary(char *sentence) {
    if (sentence == NULL)
        return 0;
    int sum = 0;
    for (int i = 0; i < strlen(sentence); i++) {
        if (isdigit(sentence[i])) {
            sum += (int)sentence[i];
        }
    }
    return sum;
}

int funcSortComparator(const void *a, const void *b) {
    return (summary(*(char **)a) - summary(*(char **)b));
}

int funcComparator(const void *a, const void *b) {
    return (funcCountLowersChars(*(char **)b) - funcCountLowersChars(*(char **)a));
}

void funcRemoveSameLen(char **sentences, int sentences_count) {
    for (int i = 0; i < sentences_count; i++) {
        if (sentences[i] != NULL) {
            int all_same = 1;
            char *temp_copy = strDup(sentences[i]);
            char *word = strtok(temp_copy, " .");
            int word_len = strlen(word);
            while (word != NULL) {
                if (word_len != strlen(word)) {
                    all_same = 0;
                    break;
                }
                word = strtok(NULL, " .");
            }

            free(temp_copy);

            if (all_same) {
                sentences[i][0] = '\0';
            }
        }
    }
}

void funcRemoveFirstWords(char **sentences, int sentences_count) {
    for (int i = 0; i < sentences_count; i++) {
        char *sentence = sentences[i];
        char *first_word = strchr(sentence, ' ');
        if (first_word != NULL) {
            memmove(sentence, first_word + 1, strlen(first_word + 1) + 1);
        } else {
            sentences[i][0] = '\0';
        }
    }
}

void funcOutput(char **sentences, int sentences_count) {
    for (int i = 0; i < sentences_count; i++) {
        if (sentences[i][0] != '\0') {
            puts(sentences[i]);
        }
    }
}

void funcTime(char **sentences, int sentences_count) {
    int total_seconds = 0;
    for (int i = 0; i < sentences_count; i++) {
        char *secPtr = sentences[i];
        while ((secPtr = strstr(secPtr, "sec")) != NULL) {
            int seconds = 0;
            char *numberPtr = secPtr - 1;
            while (numberPtr > sentences[i] && isdigit(*numberPtr)) {
                numberPtr--;
            }
            sscanf(numberPtr, "%dsec", &seconds);
            total_seconds += seconds;
            secPtr++;
        }
    }
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    total_seconds = total_seconds % 60;
    printf("%02d:%02d:%02d\n", hours, minutes, total_seconds);
}

int main() {
    puts("Course work for option 4.11, created by Che Maksim.");
    char **sentences = NULL;
    int sentences_count = 0;
    int token;
    if (scanf("%d", &token) != 1) {
        printf("Error: Wrong input format");
        return 0;
    }
    switch (token) {
        case 0:
            sentences_count = funcInput(&sentences);
            funcOutput(sentences, sentences_count);
            break;
        case 1:
            sentences_count = funcInput(&sentences);
            funcTime(sentences, sentences_count);
            break;
        case 2:
            sentences_count = funcInput(&sentences);
            funcRemoveFirstWords(sentences, sentences_count);
            funcOutput(sentences, sentences_count);
            break;
        case 3:
            sentences_count = funcInput(&sentences);
            funcRemoveSameLen(sentences, sentences_count);
            funcOutput(sentences, sentences_count);
            break;
        case 4:
            sentences_count = funcInput(&sentences);
            qsort(sentences, sentences_count, sizeof(char *), funcComparator);
            funcOutput(sentences, sentences_count);
            break;
        case 5:
            funcInfo();
            return 0;
        case 9:
            sentences_count = funcInput(&sentences);
            qsort(sentences, sentences_count, sizeof(char *), funcSortComparator);
            funcOutput(sentences, sentences_count);
            break;
        default:
            puts("Error: Invalid command number");
            return 0;
    }

    for (int i = 0; i < sentences_count; i++) {
        free(sentences[i]);
    }
    free(sentences);

    return 0;
}
