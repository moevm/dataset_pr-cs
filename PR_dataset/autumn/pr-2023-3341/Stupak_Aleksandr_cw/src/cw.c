#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>


#define AUTHOR "Course work for option 4.10, created by Aleksandr Stupak."
void replaceVowels(char** sep_text, int* sentence_num);
void deleteOffers(char** sep_text, int* sentence_num);
void findOffers(char** sep_text, int* sentence_num);
void sortSentences(char **sentences, int numSentences);
void defence(char** sep_text, int* sentence_num, char*keystr);

//Input


//ввод номера функции
void get_mode(char* mode) {
    *mode = getchar();
}


//Ввод текста без разделения
char* get_text(int* sentence_num) {
    char* text = malloc(sizeof(char));
    int line_block_sum = 0; //счетчик переноса строки
    int capacity = 1; //вместимость масива
    char get_input = getchar(); //первый символ в массиве
    int length_of_text = 0; //длина всего текста
    while (line_block_sum < 2) {
        if (get_input == '.') {
            (*sentence_num)++;
        }

        text[length_of_text] = get_input;
        length_of_text++;
        if (length_of_text + 1 >= capacity) {
            capacity *= 2;
            text = realloc(text, sizeof(char) * capacity);
        }
        get_input = getchar();
        if (get_input == '\n') {
            line_block_sum++;
        } else {
            line_block_sum = 0;
        }
    }
    text[length_of_text - 1] = '\0';
    return text;
}


//Разделение функции
char** separation(int* sentence_num, char* text) {
    char** sep_text = (char**) malloc(sizeof(char*) * (*sentence_num)); //двумерный массив с разделенным текстом
    char* sentence = strtok(text, "."); //отдельно взятое предложение по разделителю точка
    int i = 0; //индекс элемента массива
    while (sentence != NULL) {
        while(isspace(*sentence)) {
            sentence++;
        }
        sep_text[i] = malloc(sizeof(char) * (strlen(sentence) + 1));
        sep_text[i] = sentence;
        sentence = strtok(NULL, ".");
        i++;
    }
    return sep_text;
}


//Удаление дубликатов
void delete_duplicate(char** text, int* sentence_num) {
    int number_sent_items = 0;
    for(int i = 0; i < *sentence_num; ++i) {
        if(text[i] == NULL) {
            continue;
        }
        for (int j = 0; j < *sentence_num; ++j) {
            if(text[j] == NULL) {
                continue;
            }
            if(strcasecmp(text[i], text[j]) == 0 && i != j) {
                text[j] = NULL;
                number_sent_items++;
            }
        }
    }
}

//Output


//вывод автора курсовой
void print_author() {
    puts(AUTHOR);
}


//Func 5
void info() {
    puts("0 - Читает и выводит текст");
    puts("1 - Заменяет в тексте все гласные буквы на следующую в алфавитe\n");
    puts("2 - Находит все предложения вида То <подстрока 1> or not to <подстрока 2> и для каждого такого пердложения вывести подстроку у которой длина больше.\n");
    puts("3 - Удаляет все предложения у которых длина первого слова равняется 4");
    puts("4 - Сортирует предложения по увеличению кода последнего символа не являющегося разделителем предложений или слов");
    puts("5 - Информация о функциях");
}


//вывод текста
void text_output(int* sentence_num, char** sep_text) {
    for(int i = 0; i < *sentence_num; ++i) {
        if(sep_text[i] != NULL) {
            printf("%s.\n", sep_text[i]);
        }
    }
}



void output(char* mode, int* sentence_num, char** sep_text, char * keystr) {
    int mode_num = *mode - '0';
    switch (mode_num) {
        case 0:
            text_output(sentence_num, sep_text);
            break;
        case 1:
            replaceVowels(sep_text, sentence_num);
            text_output(sentence_num, sep_text);
            break;
        case 2:
            findOffers(sep_text, sentence_num);
            break;
        case 3:
            deleteOffers(sep_text, sentence_num);
            text_output(sentence_num, sep_text);
            break;
        case 4:
            sortSentences(sep_text, *sentence_num);
            text_output(sentence_num, sep_text);
            break;
        case 8:
            defence(sep_text,sentence_num, keystr);
            break;
    }
}


//Func 1
void replaceVowels(char** sep_text, int* sentence_num) {
    for(int i = 0; i < *sentence_num; ++i) {
        for(int j = 0; j < strlen(sep_text[i]); ++j) {
            char currentChar = sep_text[i][j];
            if(currentChar == 'a' || currentChar == 'e' || currentChar == 'i' || currentChar == 'o' || currentChar == 'u' || currentChar == 'y' || currentChar == 'A' || currentChar == 'E' || currentChar == 'I' || currentChar == 'O' || currentChar == 'U' || currentChar == 'Y') {
                sep_text[i][j]++;
            }
        }
    }
}


//Func 2
void findOffers(char** sep_text, int* sentence_num) {
    for (int i = 0; i < *sentence_num; ++i) {
        char *ptr = sep_text[i];

        // Поиск подстрок в предложении
        while ((ptr = strstr(ptr, "To ")) != NULL) {
            ptr += 3;  // Пропускаем "To "
            char *start1 = ptr;

            ptr = strstr(ptr, " or not to ");
            if (ptr == NULL) {
                break;  // Если не найдено "or not to ", выходим из цикла
            }

            char *end1 = ptr;  // Конец первой подстроки
            ptr += 10;  // Пропускаем " or not to "
            char *start2 = 1 + ptr;  // Начало второй подстроки

            // Находим конец второй подстроки
            while (*ptr != '\0') {
                ptr++;
            }
            char *end2 = ptr;  // Конец второй подстроки

            // Определяем длины подстрок
            int len1 = end1 - start1;
            int len2 = end2 - start2;

            // Выводим наиболее длинную подстроку
            if (len1 > len2) {
                printf("%.*s\n", len1, start1);
            } else {
                printf("%.*s\n", len2, start2);
            }
        }

    }
}

//Func 3
void deleteOffers(char** sep_text, int* sentence_num) {
    int sumChat = 0;
    for(int i = 0; i < *sentence_num; ++i) {
        for(int j = 0; j < strlen(sep_text[i]); ++j){
            while(sep_text[i][j] != 32 && sep_text[i][j] != 44) {
                sumChat++;
                j++;
            }
            break;
        }
        if(sumChat == 4) {
            sep_text[i] = NULL;
        }
        sumChat = 0;
    }
}

//Func 4
int getLastCharCode(const char *sentence) {
    int len = strlen(sentence);
    for(int i = len - 1; i >= 0; i--) {
        if(!isspace(sentence[i]) && !ispunct(sentence[i])) {
            return (int)sentence[i];
        }
    }
    return -1; // Возвращаем -1, если не найдено подходящего символа
}

// Функция сравнения для qsort
int compareLastChar(const void *a, const void *b) {
    const char *sentenceA = *(const char **)a;
    const char *sentenceB = *(const char **)b;
    int codeA = getLastCharCode(sentenceA);
    int codeB = getLastCharCode(sentenceB);
    return codeA - codeB;
}


// Функция для сортировки предложений
void sortSentences(char **sentences, int numSentences) {
    qsort(sentences, numSentences, sizeof(char *), compareLastChar);
}



//Errors
void modeError(char *mode){
    if (*mode==10){
        puts("Error: Function number not entered");
        exit(0);
    }
    if ((*mode>=32&&*mode<=47)||(*mode>=58)){
        puts("Error: Entered symbol");
        exit(0);
    }
    if (*mode>53 && *mode!=56){ //new
        puts("Error: Wrong function number");
        exit(0);
    }
}


void errorText(char* text_without_sep){
    if (strlen(text_without_sep)==1){
        printf("Error: Text not entered\n");
        exit(0);
    }
}

char* getKeyStr(){
    char* word = NULL, c;
    int len=0;
    word= malloc(sizeof(char ));
    c=getchar();
    while ((c=getchar())!='\n'){
        word[len]=c;
        len++;
        word= realloc(word, len+1);
    }
    word[len]='\0';
    return word;
}

void defence(char** sep_text, int* sentence_num, char* keystr){
    int keystr_count=0;
    for (int i = 0; i < strlen(keystr); ++i) {
        if (isdigit(keystr[i])!=0){
            keystr_count+=keystr[i]-'0';
        }
    }
    for (int i = 0; i < *sentence_num; ++i) {
        int sentence_count=0;
        for (int j = 0; j < strlen(sep_text[i]); ++j) {
            if (isdigit((sep_text[i][j]))!=0) {
                sentence_count+=sep_text[i][j]-'0';
            }
        }
        if (sentence_count>keystr_count) {
            printf("(%d) %s.\n", sentence_count-keystr_count, sep_text[i]);
        }
    }
}

int main() {
    print_author();
    char mode = 0;
    get_mode(&mode);
    modeError(&mode);
    if(mode == 53) {
        info();
        return 0;
    }
    char* keystr = "";
    if (mode == 56){
        keystr = getKeyStr();
    }
    int sentence_number = 0; //счетчик предложений
    char* text_without_sep = get_text(&sentence_number); //текст без разделения
    errorText(text_without_sep);
    char** sep_text = separation(&sentence_number, text_without_sep); //раздленный текст
    delete_duplicate(sep_text, &sentence_number);
    output(&mode, &sentence_number, sep_text, keystr);

    return 0;
}
