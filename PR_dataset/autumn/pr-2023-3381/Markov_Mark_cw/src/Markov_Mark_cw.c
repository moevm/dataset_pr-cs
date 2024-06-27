#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

void help() {
    printf("0 – вывод текста после первичной обязательной обработки.\n");
    printf("1 – Необходимо во всем тексте найти все вхождения слова “dopsa” и для каждого вхождения вывести номер предложения, позицию слова в предложении, и слова которые идут перед ним и после него.\n");
    printf("2 – В каждом предложении необходимо удалить каждый третий разделитель слов.\n");
    printf("3 – Удалить все предложения в которых у каждого слова совпадают первые 3 символа.\n");
    printf("4 – Отсортировать все предложения по уменьшению длины максимально  повторяющейся последовательности символов в нем.\n");
    printf("5 – Вывести информацию о функциях\n");
}

void error_message(char *error) {
    printf("%s", error);
    exit(1);
}

void null_deleter(char **sentences, int *size) {
    int num_deleted = 0;
    for (int i = 0; i < *size; i++) {
        if (sentences[i] == NULL) {
            free(sentences[i]);
            sentences[i] = NULL;
            num_deleted++;
        }
    }
    int not_null = 0;
    for (int i = 0; i < *size; i++) {
        if (sentences[i] != NULL) {
            sentences[not_null] = sentences[i];
            not_null++;
        }
    }
    *size = *size - num_deleted;
}

void dup_remover(char **sentences, int size) {
    for (int i = 0; i < size; i++) {
        if (sentences[i] != NULL)
            for (int j = i + 1; j < size; j++)
                if (sentences[j] != NULL)
                    if (!strcasecmp(sentences[i], sentences[j])) {
                        free(sentences[j]);
                        sentences[j] = NULL;
                    }
    }
}

int input(char ***sentences, int *index_sentences) {
    int line_break = 0, sentences_buffer = 4, sentence_buffer = 8, index_chars = 0;
    char *sentence = malloc(sentence_buffer * sizeof(char));
    if (sentence == NULL)
        error_message("Error: memory allocation error");
    while (1) {
        char c = getchar();
        if (c == '\n') {
            line_break++;
            if (line_break == 2) {
                if (index_chars != 0) {
                    (*sentences)[*index_sentences] = malloc((index_chars + 1) * sizeof(char));
                    sentence[index_chars] = '\0';
                    strcpy((*sentences)[*index_sentences], sentence);
                    (*index_sentences)++;
                    if ((*index_sentences) == sentences_buffer) {
                        sentences_buffer *= 2;
                        (*sentences) = realloc((*sentences), sentences_buffer * sizeof(char *));
                        if (*sentences == NULL)
                            error_message("Error: memory reallocation error");
                    }
                    if (sentence != NULL) {
                        free(sentence);
                        sentence = NULL;
                    }
                    sentence_buffer = 8;
                    index_chars = 0;
                    sentence = malloc(sentence_buffer * sizeof(char));
                }
                break;
            }
        } else {
            if (index_chars == 0 && (c == ' ' || c == '\t'))
                continue;
            line_break = 0;
            sentence[index_chars] = c;
            index_chars++;
            if (index_chars == sentence_buffer) {
                sentence_buffer *= 2;
                sentence = realloc(sentence, sentence_buffer * sizeof(char));
                if (sentence == NULL)
                    error_message("Error: memory reallocation error");
            }
        }
        if (c == '.') {
            if (index_chars == 1) {
                index_chars = 0;
                continue;
            }
            (*sentences)[*index_sentences] = malloc((index_chars + 1) * sizeof(char));
            sentence[index_chars] = '\0';
            strcpy((*sentences)[*index_sentences], sentence);
            (*index_sentences)++;
            if ((*index_sentences) == sentences_buffer) {
                sentences_buffer *= 2;
                (*sentences) = realloc((*sentences), sentences_buffer * sizeof(char *));
                if (*sentences == NULL)
                    error_message("Error: memory reallocation error");
            }
            if (sentence != NULL) {
                free(sentence);
                sentence = NULL;
            }
            sentence_buffer = 8;
            index_chars = 0;
            sentence = malloc(sentence_buffer * sizeof(char));
        }
    }
    free(sentence);
    sentence = NULL;
    dup_remover(*sentences, *index_sentences);
    null_deleter(*sentences, index_sentences);
    return *index_sentences;
}

void output(char **sentences, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", sentences[i]);
    }
}

char **split_sentence(char *sentence, int *words_size) {
    int count = 0;
    char *separator = " ,\n\t.";
    char *copy = malloc(strlen(sentence) * sizeof(char *));
    strcpy(copy, sentence);
    char *token = strtok(copy, separator);
    while (token != NULL) {
        count++;
        token = strtok(NULL, separator);
    }
    free(copy);
    copy = NULL;
    char **words = malloc(count * sizeof(char *));
    copy = malloc(strlen(sentence) * sizeof(char *));
    strcpy(copy, sentence);
    token = strtok(copy, separator);
    int i = 0;
    while (token != NULL) {
        char *word = malloc((strlen(token) + 1) * sizeof(char));
        strcpy(word, token);
        words[i] = word;
        i++;
        token = strtok(NULL, separator);
    }
    free(copy);
    copy = NULL;
    *words_size = count;
    return words;
}

void dopsa_output(int sentence_number, int word_number, char *word_before, char *word_after) {
    printf("Sentence number:%d Word number: %d Word before: %s Word after: %s\n", sentence_number, word_number,
           word_before, word_after);
}

void dopsa_finder(char **sentences, char **words, int sentences_size, int *words_size) {
    for (int i = 0; i < sentences_size; i++) {
        words = split_sentence(sentences[i], words_size);
        for (int j = 0; j < *words_size; j++) {
            if (!strcasecmp("dopsa", words[j])) {
                if (j == 0 && *words_size == 1) {
                    dopsa_output(i + 1, j + 1, "", "");
                } else if (j == 0 && *words_size > 1)
                    dopsa_output(i + 1, j + 1, "", words[j + 1]);
                else if (j == (*words_size - 1)) {
                    dopsa_output(i + 1, j + 1, words[j - 1], "");
                } else {
                    dopsa_output(i + 1, j + 1, words[j - 1], words[j + 1]);
                }
            }
        }
        for (int j = 0; j < *words_size; j++) {
            free(words[j]);
            words[j] = NULL;
        }
        free(words);
        words = NULL;
    }
}

char **sep_deleter(char **sentences, int size) {
    int sep_counter = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < strlen(sentences[i]) - 1; j++) {
            if (sentences[i][j] == ' ' || sentences[i][j] == '\t' || sentences[i][j] == ',') {
                sep_counter++;
            }
            if (sep_counter == 3) {
                memmove(&sentences[i][j], &sentences[i][j + 1], strlen(sentences[i]) - j);
                sep_counter = 0;
                j--;
            }
        }
    }
    return sentences;
}

void match_deleter(char **sentences, char **words, int sentences_size, int *words_size) {
    for (int i = 0; i < sentences_size; i++) {
        int flag = 0;
        words = split_sentence(sentences[i], words_size);
        if ((*words_size == 1) && (strlen(words[0]) >= 3)) {
            free(sentences[i]);
            sentences[i] = NULL;
        } else if (*words_size > 1) {
            for (int j = 1; j < *words_size; j++) {
                if (!(strncasecmp(words[j], words[0], 3)))
                    flag++;
            }
        }
        if (flag == *words_size - 1) {
            free(sentences[i]);
            sentences[i] = NULL;
        }
        for (int j = 0; j < *words_size; j++) {
            free(words[j]);
            words[j] = NULL;
        }
        free(words);
        words = NULL;
    }
}

int lcs(char *sentence) {
    int sentence_size = strlen(sentence);
    int lcs = 0;
    for (int i = 0; i < sentence_size; i++) {
        for (int j = i + 1; j < sentence_size; j++) {
            int k = i, l = j, cs = 0;
            while (k < sentence_size && l < sentence_size && sentence[k] == sentence[l]) {
                cs++;
                k++;
                l++;
            }
            if (cs > lcs) {
                lcs = cs;
            }
        }
    }
    return lcs;
}

int comparator(const void *a, const void *b) {
    int lcs_a = lcs(*((char **) a)), lcs_b = lcs(*((char **) b));
    return lcs_b - lcs_a;
}

void output_words(char **words, int words_size, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < words_size; j++) {
            if (i == N - 1 && j == words_size - 1) {
                printf("%s.\n", words[j]);
            } else
                printf("%s ", words[j]);
        }
    }
}

void func_9(char **sentences, char **words, int sentences_size, int *words_size, int N) {
    for (int i = 0; i < sentences_size; i++) {
        words = split_sentence(sentences[i], words_size);
        output_words(words, *words_size, N);
        for (int i = 0; i < *words_size; i++) {
            free(words[i]);
            words[i] = NULL;
        }
        free(words);
    }
}

void action(int a) {
    int N = 0;
    char **sentences = malloc(4 * sizeof(char *));
    int sentences_size = 0;
    char **words = malloc(4 * sizeof(char *));
    int words_size = 0;
    if (a != '5' && a != '9')
        sentences_size = input(&sentences, &sentences_size);
    else if (a == '9') {
        scanf("%d\n", &N);
        sentences_size = input(&sentences, &sentences_size);
    }
    switch (a) {
        case '0':
            output(sentences, sentences_size);
            break;
        case '1':
            dopsa_finder(sentences, words, sentences_size, &words_size);
            break;
        case '2':
            sep_deleter(sentences, sentences_size);
            output(sentences, sentences_size);
            break;
        case '3':
            match_deleter(sentences, words, sentences_size, &words_size);
            null_deleter(sentences, &sentences_size);
            output(sentences, sentences_size);
            break;
        case '4':
            qsort(sentences, sentences_size, sizeof(char *), comparator);
            output(sentences, sentences_size);
            break;
        case '5':
            help();
            break;
        case '9':
            func_9(sentences, words, sentences_size, &words_size, N);
            break;
        default:
            error_message("Error: invalid action\n");
    }
    if (sentences != NULL) {
        for (int i = 0; i < sentences_size; i++) {
            if (sentences[i] != NULL) {
                free(sentences[i]);
                sentences[i] = NULL;
            }
        }
        free(sentences);
        sentences = NULL;
    }
    free(words);
    words = NULL;
}

int main() {
    printf("Course work for option 4.22, created by Mark Markov.\n");
    action(getchar());
    return 0;
}