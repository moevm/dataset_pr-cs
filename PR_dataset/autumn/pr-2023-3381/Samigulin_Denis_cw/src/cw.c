#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

typedef struct {
    char *word;
} Word;

typedef struct {
    Word *words;
    size_t numWords;
} Sentence;

typedef struct {
    Sentence *sentences;
    size_t numSentences;
} Text;

void printInfo() {
    printf("Course work for option 4.15, created by Denis Samigulin.\n");
}

void information(void) {
    printf("0 : Вывод текста после первичной обязательной обработки.\n");
    printf("1 : В каждом предложении заменить все слова “flower” на “planted”.\n");
    printf("2 : Для каждого предложения посчитать количество слов “student” и вывести количество посчитанных слов и само предложение выделив слова “student” красным цветом.\n");
    printf("3 : Удалить все предложения в которых слово “friend” встречается больше одного раза.\n");
    printf("4 : Отсортировать предложения по уменьшению максимального числа в строке. Число - слово состоящее только из цифр. Если в предложении нет числа, то для такого числа значение максимального числа равно 0.\n");
    printf("5 : Вывод справки о функциях, которые реализует программа.\n");
}

void printText(const Text *text) {
    for (size_t i = 0; i < text->numSentences; ++i) {
        for (size_t j = 0; j < text->sentences[i].numWords; ++j) {
            printf("%s", text->sentences[i].words[j].word);

            // Печатаем пробел только если не последнее слово в предложении
            if (j < text->sentences[i].numWords - 1) {
                printf(" ");
            }
        }
        printf(".\n");
    }
}

void freeTextMemory(Text *text) {
    if (text == NULL) {
        return;
    }

    for (size_t i = 0; i < text->numSentences; ++i) {
        if (text->sentences[i].words != NULL) {
            for (size_t j = 0; j < text->sentences[i].numWords; ++j) {
                free(text->sentences[i].words[j].word);
            }
            free(text->sentences[i].words);
        }
    }

    free(text->sentences);
    text->sentences = NULL;
    text->numSentences = 0;
}

void standart_conversion(Text *text) {
    char buffer[1000]; // предполагаем максимальную длину предложения 1000 символов
    int c;
    size_t sentenceIndex = 0;
    int newlineCount = 0;

    while (1) {
        c = getchar();

        if (c == '\n') {
            newlineCount++;

            if (newlineCount == 2) {
                break; // Два символа новой строки, завершаем ввод
            }
        } else {
            newlineCount = 0; // Сбрасываем счетчик новых строк

            if (c == EOF) {
                break; // Достигнут конец файла, завершаем ввод
            }

            if (c == '.') {
                buffer[sentenceIndex++] = '\0'; // завершаем строку
                sentenceIndex = 0; // сбрасываем индекс

                if (strlen(buffer) > 0) {
                    text->sentences = realloc(text->sentences, (text->numSentences + 1) * sizeof(Sentence));
                    text->sentences[text->numSentences].words = malloc(sizeof(Word)); // предполагаем максимум 1 слово
                    text->sentences[text->numSentences].numWords = 0;

                    char *token = strtok(buffer, " ,"); // разделители - пробел и запятая
                    while (token != NULL) {
                        size_t len = strlen(token) + 1;
                        text->sentences[text->numSentences].words = realloc(
                                text->sentences[text->numSentences].words,
                                (text->sentences[text->numSentences].numWords + 1) * sizeof(Word)
                        );

                        text->sentences[text->numSentences].words[text->sentences[text->numSentences].numWords].word = malloc(len);
                        if (text->sentences[text->numSentences].words[text->sentences[text->numSentences].numWords].word != NULL) {
                            strncpy(text->sentences[text->numSentences].words[text->sentences[text->numSentences].numWords].word, token, len);
                        } else {
                            // Обработка ошибки выделения памяти
                            fprintf(stderr, "Memory allocation error.\n");
                            exit(EXIT_FAILURE);
                        }

                        text->sentences[text->numSentences].numWords++;
                        token = strtok(NULL, " ,");
                    }

                    text->numSentences++;
                }
            } else {
                buffer[sentenceIndex++] = (char)c;
            }
        }

        if (sentenceIndex == sizeof(buffer) - 1) {
            fprintf(stderr, "Error: Sentence too long.\n");
            exit(EXIT_FAILURE);
        }
    }
}

void remove_duplicate_sentences(Text *text) {
    for (size_t i = 0; i < text->numSentences; ++i) {
        for (size_t j = i + 1; j < text->numSentences; ) {
            // Проверяем, что количество слов в предложениях одинаково
            if (text->sentences[i].numWords == text->sentences[j].numWords) {
                int cmp = 0;
                // Сравниваем слова поочередно в предложениях
                for (size_t k = 0; k < text->sentences[i].numWords; ++k) {
                    cmp = strcasecmp(text->sentences[i].words[k].word, text->sentences[j].words[k].word);
                    if (cmp != 0) {
                        break;  // Найдено несовпадение, выходим из цикла
                    }
                }
                if (cmp == 0) {
                    // Найдено одинаковое предложение, удаляем его
                    for (size_t k = 0; k < text->sentences[j].numWords; ++k) {
                        free(text->sentences[j].words[k].word);
                    }
                    free(text->sentences[j].words);

                    // Сдвигаем массив влево
                    for (size_t k = j; k < text->numSentences - 1; ++k) {
                        text->sentences[k] = text->sentences[k + 1];
                    }
                    text->numSentences--;
                } else {
                    ++j;
                }
            } else {
                ++j;
            }
        }
    }
}


void first_func(Text *text) {
    const char *target_word = "flower";
    char replacement[] = "planted";

    for (size_t i = 0; i < text->numSentences; ++i) {
        for (size_t j = 0; j < text->sentences[i].numWords; ++j) {
            if (strcasecmp(text->sentences[i].words[j].word, target_word) == 0) {
                // Найдено слово "flower", заменяем его на "planted"
                size_t len = strlen(replacement) + 1;
                int isCapitalized = isupper(text->sentences[i].words[j].word[0]); // Проверяем, была ли первая буква заглавной

                free(text->sentences[i].words[j].word);
                text->sentences[i].words[j].word = malloc(len);
                if (text->sentences[i].words[j].word != NULL) {
                    if (isCapitalized) {
                        replacement[0] = toupper(replacement[0]); // Если первая буква "flower" была заглавной, делаем первую букву "planted" заглавной
                    }
                    strncpy(text->sentences[i].words[j].word, replacement, len);
                } else {
                    // Обработка ошибки выделения памяти
                    fprintf(stderr, "Error: Memory allocation error.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

void second_func(Text *text) {
    const char *target_word = "student";
    const char *color_red = "\x1b[31m"; // ANSI escape code для красного цвета
    const char *color_reset = "\x1b[0m"; // ANSI escape code для сброса цвета

    for (size_t i = 0; i < text->numSentences; ++i) {
        size_t student_count = 0;

        for (size_t j = 0; j < text->sentences[i].numWords; ++j) {
            if (strcasecmp(text->sentences[i].words[j].word, target_word) == 0) {
                // Найдено слово "student", увеличиваем счетчик и выводим его красным цветом
                student_count++;
                printf("%s%s%s ", color_red, text->sentences[i].words[j].word, color_reset);
            } else {
                printf("%s ", text->sentences[i].words[j].word);
            }
        }

        // Выводим количество слов "student" в предложении
        printf("(%zu word count)\n", student_count);
    }
}

void third_func(Text *text) {
    const char *target_word = "friend";

    for (size_t i = 0; i < text->numSentences; ++i) {
        size_t friend_count = 0;

        // Count the occurrences of the word "friend" in the sentence
        for (size_t j = 0; j < text->sentences[i].numWords; ++j) {
            if (strcasecmp(text->sentences[i].words[j].word, target_word) == 0) {
                friend_count++;
            }
        }

        // If the word "friend" occurs more than once, remove the sentence
        if (friend_count > 1) {
            for (size_t j = 0; j < text->sentences[i].numWords; ++j) {
                free(text->sentences[i].words[j].word);
            }
            free(text->sentences[i].words);

            // Shift the remaining sentences to the left
            for (size_t k = i; k < text->numSentences - 1; ++k) {
                text->sentences[k] = text->sentences[k + 1];
            }
            text->numSentences--;

            // Adjust the loop counter since we removed a sentence
            i--;
        }
    }
}

int compare_sentences(const void *a, const void *b) {
    // Функция сравнения для использования в qsort
    // Сравнивает максимальные числа в двух предложениях

    const Sentence *sentence_a = (const Sentence *)a;
    const Sentence *sentence_b = (const Sentence *)b;

    // Находим максимальные числа в каждом предложении
    int max_num_a = 0;
    int max_num_b = 0;

    for (size_t i = 0; i < sentence_a->numWords; ++i) {
        char *endptr;
        int num = strtol(sentence_a->words[i].word, &endptr, 10);
        if (*endptr == '\0') {
            // Если преобразование удалось и в слове есть число
            max_num_a = (num > max_num_a) ? num : max_num_a;
        }
    }

    for (size_t i = 0; i < sentence_b->numWords; ++i) {
        char *endptr;
        int num = strtol(sentence_b->words[i].word, &endptr, 10);
        if (*endptr == '\0') {
            // Если преобразование удалось и в слове есть число
            max_num_b = (num > max_num_b) ? num : max_num_b;
        }
    }

    // Сравниваем максимальные числа
    return max_num_b - max_num_a;
}

void fourth_func(Text *text) {
    // Сортируем предложения по убыванию максимального числа
    qsort(text->sentences, text->numSentences, sizeof(Sentence), compare_sentences);
}

void add_function(Text *text) {
    int count;
    scanf("%d", &count);

    standart_conversion(text);
    remove_duplicate_sentences(text);
    for (size_t i = 0; i < text->numSentences; ++i) {
        for (size_t k=0; k<count; ++k) {
            for (size_t j = 0; j < text->sentences[i].numWords; ++j) {
                printf("%s", text->sentences[i].words[j].word);
                if(j < text->sentences[i].numWords && k==count-1 && j==text->sentences[i].numWords-1){
                    continue;
                } else {
                        printf(" ");
                }
            }
        }
        printf(".\n");
    }
}

int main() {
    printInfo();
    Text text = {NULL, 0};

    text.sentences = malloc(sizeof(Sentence));
    if (text.sentences == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        return 1;
    }
    char scan_num;
    scan_num = getchar();
    // Удаляем символ новой строки из вводного буфера
    while (getchar() != '\n');

    switch (scan_num) {
        case '0':
            standart_conversion(&text);
            remove_duplicate_sentences(&text);
            printText(&text);
            freeTextMemory(&text);
            break;

        case '1':
            standart_conversion(&text);
            remove_duplicate_sentences(&text);
            first_func(&text);
            printText(&text);
            freeTextMemory(&text);
            break;

        case '2':
            standart_conversion(&text);
            remove_duplicate_sentences(&text);
            second_func(&text);
            freeTextMemory(&text);

            break;

        case '3':
            standart_conversion(&text);
            remove_duplicate_sentences(&text);
            third_func(&text);
            printText(&text);
            freeTextMemory(&text);
            break;

        case '4':
            standart_conversion(&text);
            remove_duplicate_sentences(&text);
            fourth_func(&text);
            printText(&text);
            freeTextMemory(&text);
            break;

        case '5':
            information();
            break;

        case '9':

            add_function(&text);
            freeTextMemory(&text);
            break;

        default:
            printf("Error: invalid number.\n");
            return 1;
    }
    return 0;
}