#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_WORD_COUNT 10
#define WORD_LENGTH_INCREMENT 10
#define WORD_INCREMENT 10

char* get_text() {
    int size = 10;
    char* sentence = (char*)calloc(size, sizeof(char));
    char* p_sen = sentence;
    int count = 0, k = 1;
    int consecutive_newlines = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            consecutive_newlines++;
            if (consecutive_newlines >= 2) {
                break;
            }
        } else {
            consecutive_newlines = 0;
        }
        *p_sen = c;
        if (count == (10 * k) - 1) {
            k++;
            size = k * 10;
            sentence = realloc(sentence, size * sizeof(char));
        }

        p_sen++;
        count++;
    }

    if (c == EOF) {
        printf("Error: Invalid input\n");
        free(sentence); // Освобождаем память перед выходом из функции
        return NULL;
    }

    // Удаление переноса строки в конце
    if (count > 0 && sentence[count - 1] == '\n') {
        sentence[count - 1] = '\0'; // Заменяем перенос строки на завершающий символ
    }

    return sentence;
}
char** text_to_sentences(char* text, int* num_sen) {
    int size = 5;
    char** sentences = (char**)malloc(size * sizeof(char*));
    int count = 0;
    int sentence_start = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
            sentences[count] = (char*)malloc((i - sentence_start + 2) * sizeof(char));
            strncpy(sentences[count], &text[sentence_start], i - sentence_start + 1);
            sentences[count][i - sentence_start + 1] = '\0';

            int next_start = i + 1;

            // Пропускаем символы до начала следующего предложения
            while (text[next_start] != '\0' && !isalnum(text[next_start])) {
                next_start++;
            }

            sentence_start = next_start; // Обновляем начало для следующего предложения
            count++;

            if (count >= size) {
                size += 5;
                sentences = realloc(sentences, size * sizeof(char*));
            }
        }
    }
    sentences[count] = NULL; // Устанавливаем NULL для обозначения конца массива строк
    *num_sen = count;
    return sentences;
}

char** into_words(char* sentence) {
    char** words = (char**)malloc(INITIAL_WORD_COUNT * sizeof(char*));
    int word_count = 0;
    int word_capacity = INITIAL_WORD_COUNT;

    char* p_start = sentence;
    char* p_end;

    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '?' || sentence[i] == '!') {
            words[word_count] = (char*)calloc(WORD_LENGTH_INCREMENT, sizeof(char));
            int word_length = 0;
            int word_length_capacity = WORD_LENGTH_INCREMENT;

            p_end = sentence + i;

            while (p_start < p_end) {
                words[word_count][word_length] = *p_start;
                p_start++;
                word_length++;

                if (word_length == word_length_capacity) {
                    word_length_capacity += WORD_LENGTH_INCREMENT;
                    words[word_count] = realloc(words[word_count], word_length_capacity * sizeof(char));
                }
            }

            words[word_count][word_length] = '\0'; // Добавляем завершающий символ

            word_count++;
            p_start = sentence + i + 1; // Обновляем указатель на начало следующего слова

            if (word_count == word_capacity) {
                word_capacity += WORD_INCREMENT;
                words = realloc(words, word_capacity * sizeof(char*));
            }
        }
    }

    words[word_count] = NULL; // Устанавливаем NULL для обозначения конца массива слов

    return words;
}
int count_words(char* sen, char* word){
    int count = 0, i = 0;
    char word_1[BUFSIZ]; // Выделение памяти для строк word_1 и word_2
    sprintf(word_1, "%s.", word);
    char word_2[BUFSIZ];
    sprintf(word_2, "%s,", word);

    char** words = into_words(sen);
    while (words[i] != NULL){
        if (strcmp(words[i], word) == 0 || strcmp(words[i], word_1) == 0 || strcmp(words[i], word_2) == 0){
            count++;
        }
        i++;
    }
    return count;
}
void word_change(char** sentences) {
    int i = 0;
    while (sentences[i] != NULL) {
        char* sen = sentences[i];
        int count = 0;
        char* index = sen;
        while ((index = strstr(index, "flower")) != NULL) {
            if (*(index + strlen("flower")) != 's') {
                char buffer[BUFSIZ];
                strncpy(buffer, sen, index - sen);
                buffer[index - sen] = '\0';

                strcat(buffer, "planted");

                strcat(buffer, index + strlen("flower"));

                free(sentences[i]); // Освобождаем предыдущую память
                sentences[i] = (char*)malloc(strlen(buffer) + 1); // Выделяем новую память
                strcpy(sentences[i], buffer); // Копируем данные

                index = sentences[i] + (index - sen) + strlen("planted"); // Обновляем индекс
                count++;
            } else {
                index += strlen("flower") + 1;
            }
        }
        i++;
    }
}
void to_lower_str(char* str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}
void dups_delete(char** sentences, int* num_sen) {
    int i = 0;
    while (sentences[i] != NULL) {
        int j = i + 1;
        char* sen_copy = malloc(strlen(sentences[i]) + 1); // Выделяем память для копии
        strcpy(sen_copy, sentences[i]);
        to_lower_str(sen_copy); // Применяем to_lower_str к текущей строке

        while (sentences[j] != NULL) {
            char* sen_copy_1 = malloc(strlen(sentences[j]) + 1); // Выделяем память для копии
            strcpy(sen_copy_1, sentences[j]);
            to_lower_str(sen_copy_1); // Применяем to_lower_str к сравниваемой строке

            if (strcmp(sen_copy, sen_copy_1) == 0) {
                free(sentences[j]);
                free(sen_copy_1);
                (*num_sen)--;

                // Сдвигаем последующие предложения влево
                int k = j;
                while (sentences[k] != NULL) {
                    sentences[k] = sentences[k + 1];
                    k++;
                }
            } else {
                j++;
            }
        }
        i++;
        free(sen_copy);
    }
}
void print_info() {
    printf("Course work for option 4.15, created by Andreev Makar.\n");
}
void task_0(char** sentences){
    int i=0;
    while (sentences[i]!=NULL){
        printf("%s\n",sentences[i]);
        free(sentences[i]);
        i++;
    }
    free(sentences);
}
void task_1(char** sentences, int num_sen) {
    char** sen_copy = malloc(sizeof(char*) * (num_sen + 1));
    if (sen_copy == NULL) {
        printf("Error: Memory allocation error\n");
        return;
    }

    int i = 0;
    while (sentences[i] != NULL) {
        sen_copy[i] = malloc(strlen(sentences[i]) + 1);
        if (sen_copy[i] == NULL) {
            printf("Error: Memory allocation error\n");
            // Освобождаем уже выделенную память
            while (i > 0) {
                free(sen_copy[--i]);
            }
            free(sen_copy);
            return;
        }
        strcpy(sen_copy[i], sentences[i]);
        i++;
    }
    sen_copy[i] = NULL;

    word_change(sen_copy);

    i=0;
    while (sen_copy[i]!=NULL){
        printf("%s\n",sen_copy[i]);
        i++;
    }

    // Освобождение памяти sen_copy
    i = 0;
    while (sen_copy[i] != NULL) {
        free(sen_copy[i]);
        i++;
    }
    free(sen_copy); // Освобождение массива указателей
}
void task_2(char **sentences, int numSentences) {
    for (int i = 0; i < numSentences; i++) {
        int count = count_words(sentences[i], "student");
        printf("%d ", count);

        char **words = into_words(sentences[i]);
        int j = 0;
        while (words[j] != NULL) {
            if (strcmp(words[j], "student") == 0) {
                printf("\033[0;31mstudent\033[0m");
            } else if (strcmp(words[j], "student,") == 0 ) {
                printf("\033[0;31mstudent\033[0m,");
            } else if (strcmp(words[j], "student.") == 0 ) {
                printf("\033[0;31mstudent\033[0m");
            }else{
                printf("%s",words[j]);
            }
            if (words[j + 1] != NULL) {
                printf(" ");
            }
            j++;
        }
        printf(".");
        for (int k = 0; k < j; k++) {
            free(words[k]);
        }
        free(words);

        printf("\n");
    }
}
void task_3(char** sentences) {
    int i = 0;
    while (sentences[i] != NULL) {
        int count = count_words(sentences[i], "friend");
        if (count > 1) {
            free(sentences[i]); // Освобождаем память текущего предложения
            int j = i + 1;
            while (sentences[j] != NULL) {
                sentences[j - 1] = sentences[j]; // Сдвигаем последующие предложения влево
                j++;
            }
            sentences[j - 1] = NULL; // Устанавливаем конец списка предложений
        } else {
            i++;
        }
    }

    i = 0;
    while (sentences[i] != NULL) {
        printf("%s\n", sentences[i]);
        free(sentences[i]);
        i++;
    }
    free(sentences);
}

int get_max_number(const char* sentence) {
    int max_number = -1000000000;
    char* sen_copy = malloc(strlen(sentence) + 1);
    if (sen_copy == NULL) {
        return max_number;
    }
    strcpy(sen_copy, sentence);
    char** words = into_words(sen_copy);
    int i = 0;

    while (words[i] != NULL) {
        int is_number = 1;
        int number; // Инициализируем ноль для числа
        char buf[BUFSIZ] = ""; // Используем массив символов для буфера

        for (int j = 0; words[i][j] != '\0'; j++) {
            if (isdigit(words[i][j])) {
                buf[j] = words[i][j]; // Добавляем символ к строке
            } else {
                is_number = 0;
                break;
            }
        }

        if (is_number) {
            number = atoi(buf); // Преобразуем строку в число
            if (number > max_number) {
                max_number = number;
            }
        }
        i++;
    }
    free(sen_copy);
    return max_number;
}
int compare_sentences(const void *a, const void *b) {
    const char **sentence_a = (const char **)a;
    const char **sentence_b = (const char **)b;

    int max_number_a = get_max_number(*sentence_a);
    int max_number_b = get_max_number(*sentence_b);

    return max_number_b - max_number_a; // Сортировка по убыванию
}

void task_4(char** sentences, int num_sentences){
    // Сортировка предложений
    qsort(sentences, num_sentences, sizeof(char *), compare_sentences);

    // Вывод отсортированных предложений
    int i=0;
    while (sentences[i]!=NULL){
        printf("%s\n", sentences[i]);
        free(sentences[i]);
        i++;
    }
    free(sentences);
}
void task_9(char** sentences, char* sep){
    int num_sen=-1;
    while (sentences[num_sen]!=NULL){num_sen++;}
    int count=0;
    if  (num_sen%2!=0){
        count=num_sen/2+1;
    } else{
        count=num_sen/2;
    }
    for (int i = 0; i < count; i++) {
        char* sen1= calloc(strlen(sentences[i]), sizeof(char));
        char* sen2= calloc(strlen(sentences[num_sen-i-1]), sizeof(char));
        strncpy(sen1,sentences[i], strlen(sentences[i])-1);
        strncpy(sen2,sentences[num_sen-i-1], strlen(sentences[num_sen-i-1])-1);
        printf("%s %s %s.\n",sen1,sep,sen2);
        free(sen1);
        free(sen2);
    }
}
void process_input() {
    int option;
    char input[10];
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &option) != 1) {
        printf("Error: Invalid input\n");
        return;
    }

    if  (option==5){
        printf("Option 0: Remove duplicate sentences.\n");
        printf("Option 1: Replace the word 'flower' with 'planted'.\n");
        printf("Option 2: Count occurrences of 'student'.\n");
        printf("Option 3: Remove sentences with more than one 'friend'.\n");
        printf("Option 4: Sort sentences by the max number in the string.\n");
        printf("Option 5: Display help on functions.\n");
    } else if(option==9){
        int num_sentences = 0;
        char sep[100];
        fgets(sep,100,stdin);
        int i=0;
        while (sep[i]!='\n'){
            i++;
        }
        sep[i]='\0';
        char* text = get_text();
        if (text == NULL) {
            printf("Error: Invalid option.\n");
            return;
        }
        char **sentences = text_to_sentences(text, &num_sentences);
        if (sentences == NULL) {
            printf("Error: Invalid option.\n");
            free(text);
            return;
        }
        dups_delete(sentences, &num_sentences);
        task_9(sentences,sep);
        }
    else{
        int num_sentences = 0;
        char* text = get_text();
        if (text == NULL) {
            printf("Error: Invalid option.\n");
            return;
        }
        char **sentences = text_to_sentences(text, &num_sentences);
        if (sentences == NULL) {
            printf("Error: Invalid option.\n");
            free(text);
            return;
        }
        dups_delete(sentences, &num_sentences);


        switch (option) {
            case 0:
                task_0(sentences);
                break;
            case 1:
                task_1(sentences, num_sentences);
                break;
            case 2:
                task_2(sentences, num_sentences);
                break;
            case 3:
                task_3(sentences);
                break;
            case 4:
                task_4(sentences, num_sentences);
                break;
            default:
                printf("Error: Invalid option.\n");
                break;
        }
    }
}


int main() {
    print_info();
    process_input();

    return 0;
}