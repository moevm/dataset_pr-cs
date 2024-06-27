#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <strings.h>

#define N 100


char** get_text(int* sentences_count);                              //ввод
void free_text(char** sentences, int len);                          //очистка
void print_text(char** text, int len);                              //0, вывод
void count_garbage(char** sentences, int len);                      //1
void replace_num_str(char** sentences, int len);                    //2
void delete_sen(char** sentences, int len, int* sentences_count);   //3
void sort_vowel(char** sentences, int len);                         //4
void help();                                                        //5
void connect_words(char** sentences, int len, char* rep);           //9


int main() {
    printf("Course work for option 4.13, created by Anastasiya Dorogushina.\n");
    int len = 0;
    int len_after = 0;
    char** sentences = NULL;
    int func_value;
    if (scanf("%d\n", &func_value) != 1)
        printf("Error: введен недопустимый символ, ожидалась цифра 0-5.\n");

    switch (func_value) {
    case 0:
        sentences = get_text(&len);
        print_text(sentences, len);
        free_text(sentences, len);
        break;
    case 1:
        sentences = get_text(&len);
        count_garbage(sentences, len);
        free_text(sentences, len);
        break;
    case 2:
        sentences = get_text(&len);
        replace_num_str(sentences, len);
        print_text(sentences, len);
        free_text(sentences, len);
        break;
    case 3:
        sentences = get_text(&len);
        delete_sen(sentences, len, &len_after);
        print_text(sentences, len_after);
        free_text(sentences, len_after);
        break;
    case 4:
        sentences = get_text(&len);
        sort_vowel(sentences, len);
        print_text(sentences, len);
        free_text(sentences, len);
        break;
    case 5:
        help();
        break;
    case 9:{
        char* rep = malloc(100 * sizeof(char));
        int i = 0;
        char c;
        while ((c = getchar())){
            if (c == '\n')
                break;
            rep[i] = c;
            i++;
        }
        rep[i] = '\0';
        sentences = get_text(&len);
        connect_words(sentences, len, rep);
        free_text(sentences, len);
        break;
    }
    default:
        printf("Error: некорректно введена функция, ожидалось значение 0-5.\n");
        break;
    }
}


//функция ввода текста, используется во всех случаях, кроме вызова справки
char** get_text(int* sentences_count) {
    int kol = 0;
    int len = 0;
    int capacity_kol = N;
    int capacity_len = N;
    char c;

    //создание динамического массива строк и ввод
    char** sentences = malloc(N * sizeof(char*));
    for (int i = 0; i < INT_MAX; i++) {
        kol++;
        if (kol >= capacity_kol) {
            capacity_kol += N;
            sentences = realloc(sentences, capacity_kol * sizeof(char*));
            if (sentences == NULL)
                exit(1);
        }
        sentences[i] = malloc(capacity_len * sizeof(char));
        for (int j = 0; j < INT_MAX; j++) {
            c = getchar();
            if ((c == '\n') & (sentences[i][j - 1] == '\n')) {
                sentences[i] = NULL;
                *sentences_count = i;
                return sentences;
            }
            sentences[i][j] = c;
            len++;
            if (len >= capacity_len) {
                capacity_len += N;
                sentences[i] = realloc(sentences[i], capacity_len * sizeof(char*));
                if (sentences[i] == NULL)
                    exit(1);
            }
            //если конец строки, добавление \0 и выход из цикла заполнения i строки
            if (c == '.') {
                sentences[i][j + 1] = '\0';
                break;
            }
        }

        //удаление табуляции, пробелов и переноса строки в начале предложения
        while (isspace(sentences[i][0]))
            for (int k = 0; k < strlen(sentences[i]); k++)
                sentences[i][k] = sentences[i][k + 1];

        //удаление предложения, если оно совпадает с одним из предыдущих без учёта регистра
        for (int j = 0; j < i; j++)
            if (!strcasecmp(sentences[i], sentences[j])) {
                i--;
                break;
            }
    }
    return sentences;
}


//вспомогательная функция, очищает выделенную память
void free_text(char** sentences, int len) {
    for (int i = 0; i < len; i++)
        free(sentences[i]);
    free(sentences);
}


//вспомогательная функция, вывод текста
void print_text(char** sentences, int len) {
    for (int i = 0; i < len; i++)
        printf("%s\n", sentences[i]);
}


//вспомогательная функция, ищет слово word в предложении sentence без учёта регистра
char* strcasestr(char* sentence, char* word) {
    while (*sentence) {
        if (!(strncasecmp(sentence, word, strlen(word))))
            return sentence;
        sentence++;
    }
    return NULL;
}


//вспомогательная функция, нахождение количества слов word в предложении sentence 
int found_word(char* sentence, char* word) {
    int count = 0;
    char* p = sentence;
    while ((p = strcasestr(p, word)) != NULL) {
        if ((p == sentence || !isalnum(*(p - 1))) && !isalnum(*(p + strlen(word))))
            count++;
        p += strlen(word);
    }
    return count;
}


//функция 1, подсчёт количества слов garbage
void count_garbage(char** sentences, int len) {
    for (int i = 0; i < len; i++) {
        int count = found_word(sentences[i], "garbage");
        if (count == 0)
            printf("Clean\n");
        else if (count > 5)
            printf("It is a dumb\n");
        else
            printf("Must be washed\n");
    }
}


//вспомогательная функция, замена цифр в предложении на строку
char* replace(char* sentence, char* rep) {
    char* result = malloc(strlen(sentence) * strlen(rep) + 1);
    sentence = realloc(sentence, (strlen(sentence) * strlen(rep) + 1) * sizeof(char*));
    if (sentence == NULL)
        exit(1);
    int index = 0;
    for (int i = 0; i < strlen(sentence); i++) {
        if (isdigit(sentence[i]))
            //добавить в новую строку символы из rep
            for (int j = 0; j < strlen(rep); j++)
                result[index++] = rep[j];
        else
            //добавить в новую строку текущий символ
            result[index++] = sentence[i];
    }
    result[index] = '\0';
    strcpy(sentence, result);
    free(result);
    return sentence;
}



//функция 2, замена всех цифр на первую строку
void replace_num_str(char** sentences, int len) {
    int len_s = strlen(sentences[0]);
    char* rep = malloc(len_s + 1);
    strcpy(rep, sentences[0]);
    rep[len_s - 1] = '\0';
    for (int i = 0; i < len; i++)
        sentences[i] = replace(sentences[i], rep);
    free(rep);
}


//вспомогательная функция, проверяет, есть ли в предложении три идущие подряд буквы в верхнем регистре
int check_reg(char* sentence) {
    int count = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (isupper(sentence[i])) {
            count++;
            if (count == 3)
                return 1;
        }
        else
            count = 0;
    }
    return 0;
}


//функция 3, удаление предложений с тремя идущими подряд буквами в верхнем регистре
void delete_sen(char** sentences, int len, int* sentences_count) {
    for (int i = 0; i < len; i++)
        if (check_reg(sentences[i])){
            len--;
            for (int j = i; j < len; j++)
                sentences[j] = sentences[j + 1];
        }
    *sentences_count = len;
}


//вспомогательная функция, возвращает количество слов, начинающихся с гласной буквы
int vowels(char* sentence) {
    int vow = 0;
    for (int i = 0; i < strlen(sentence); i++)
        if (sentence[i] == 'a' || sentence[i] == 'e' || sentence[i] == 'i' || sentence[i] == 'o' || sentence[i] == 'u' ||
            sentence[i] == 'A' || sentence[i] == 'E' || sentence[i] == 'I' || sentence[i] == 'O' || sentence[i] == 'U')
            if (i == 0 || !isalnum(sentence[i - 1]))
                vow++;
    return vow;
}


//функция 4, сортировка по уменьшению слов с гласной буквы
void sort_vowel(char** sentences, int len) {
    for (int i = 0; i < len; i++)
        for (int j = i + 1; j < len; j++)
            if (vowels(sentences[i]) < vowels(sentences[j])) {
                char* temp = sentences[i];
                sentences[i] = sentences[j];
                sentences[j] = temp;
            }
}


//функция 5, вызов справки
void help() {
    printf("Справка:\n\
0 - вывод текста после первичной обязательной обработки;\n\
1 - в зависимости от количества слов garbage вывести строки Clean(0), Must be washed(1-5) или It is a dump(>5);\n\
2 - заменить все цифры в предложениях на введенную строку;\n\
3 - удалить все предложения, в которых есть три подряд идущие буквы в верхнем регистре;\n\
4 - отсортировать по уменьшению количества слов начинающихся с гласной буквы;\n\
5 - вывод справки о функциях, которые реализует программа.\n");
}


//функция 9, соединение предложений
void connect_words(char** sentences, int len, char* rep){
    for (int i = 0; i < ((len+1)/2); i++){
        sentences[i][strlen(sentences[i]) - 1] = '\0';
        printf("%s %s %s", sentences[i], rep, sentences[len - i - 1]);
        if (sentences[i] == sentences[len-i-1])
            printf(".");
        else
            printf("\n");
    }
}