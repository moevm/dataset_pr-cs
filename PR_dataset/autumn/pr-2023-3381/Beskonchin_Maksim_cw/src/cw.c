#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define BLOCK_SIZE 100
#define BLOCK_SIZE_WORD 30
#define BLOCK_SIZE_STR 10
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"


typedef struct{
    char *word;
    char service_symbol; // Служебный символ после слова
    int count_symbol;
    int title_word;
}Word;

typedef struct{
    Word *string;
    int count_word;
    int number_of_vowels; //количество гласных букв в каждом втором слове
    int words_capital;
}Sentence;

int isAllUppercase(char* word) {
    for (size_t i = 0; word[i] != '\0'; i++) {
        if (!isupper(word[i])) {
            return 0; // Найден символ, не являющийся прописной буквой
        }
    }
    return 1; // Все символы - прописные буквы
}


void print_povtor(Sentence* text, size_t* number_string, int* povtor){
    for(size_t j = 0; j < *number_string; j++) {
        for (int z = 0; z < *povtor; z++) {
            for (size_t i = 0; i < text[j].count_word; i++) {
                if (text[j].string[i].word != NULL){
                    if (z + 1 == *povtor && i + 1 == text[j].count_word){
                        printf("%s", text[j].string[i].word);}
                    else{
                        printf("%s ", text[j].string[i].word);}}
            }
        }
        if (text[j].count_word != 0) {
            printf(".");
            puts("");
        }
    }}


void print(Sentence* text, size_t* number_string){
for(size_t j = 0; j < *number_string; j++){
    for(size_t i = 0; i < text[j].count_word; i++){
        if(text[j].string[i].word != NULL)
        printf("%s%c", text[j].string[i].word, text[j].string[i].service_symbol);
    }
    if (text[j].count_word != 0)
    puts("");}
}

void print_even(Sentence* text, size_t* number_string){
    for(size_t j = 0; j < *number_string; j++){
        if(text[j].count_word % 2 != 0){
        for(size_t i = 0; i < text[j].count_word; i++){
            printf("%s%c", text[j].string[i].word, text[j].string[i].service_symbol);
        }}
        if (text[j].count_word != 0 && text[j].count_word % 2 != 0)
        puts("");}
}


int countVowelsInSecondWord(Word* words, int count_words) {
    int vowels_count = 0;

    // Первое слово считаем как нечетное, поэтому начинаем с 1
    for (int i = 1; i < count_words; i += 2) {
        for (int j = 0; words[i].word[j] != '\0'; j++) {
            char current_char = tolower(words[i].word[j]);
            if (current_char == 'a' || current_char == 'e' || current_char == 'i' || current_char == 'o' || current_char == 'u') {
                vowels_count++;
            }
        }
    }

    return vowels_count;
}



void capitalizeFirstWord(Sentence* text, size_t* number_string) {
    for (size_t j = 0; j < *number_string; j++) {
        if (text[j].count_word > 0) {
            // Преобразовать первую букву в верхний регистр
            if (text[j].string[0].word != NULL && text[j].string[0].word[0] != '\0') {
                text[j].string[0].word[0] = toupper(text[j].string[0].word[0]);
                for (size_t k = 1; text[j].string[0].word[k]; k++) {
                    text[j].string[0].word[k] = tolower(text[j].string[0].word[k]);
                }
            }

            for (size_t i = 1; i < text[j].count_word; i++) {
                if (text[j].string[i].word != NULL && text[j].string[i].word[0] != '\0') {
                    text[j].string[i].word[0] = tolower(text[j].string[i].word[0]);
                    for (size_t k = 1; text[j].string[i].word[k]; k++) {
                        text[j].string[i].word[k] = tolower(text[j].string[i].word[k]);
                    }
                }
            }
        }
    }
}

void clearing_the_buffer(Word* buffer, size_t number_buffer_word) {
    for (size_t i = 0; i < number_buffer_word; i++) {
        if (buffer[i].word != NULL) {
            free(buffer[i].word);
        }
    }
    if (buffer != NULL)
    free(buffer);
}

void clearing_the_text(Sentence* text, size_t number_string) {
    for (size_t i = 0; i < number_string; i++) {
        for (size_t j = 0; j < text[i].count_word; j++) {
            if (text[i].string[j].word != NULL) {
                free(text[i].string[j].word);
            }
        }

        free(text[i].string);
    }
    free(text);
}

Sentence* reading_the_text(size_t* number_string){
    int capacity_struc_text = BLOCK_SIZE_STR;
    Sentence *text = (Sentence *) malloc(capacity_struc_text * sizeof(Sentence));

    while(1){
        int capacity_struc_word = BLOCK_SIZE_STR;
        size_t capacity_word = BLOCK_SIZE_WORD;
        size_t number_buffer_word = 0;
        size_t number_buffer_symbol = 0;
        Word *buffer = (Word *) malloc(capacity_struc_word  * sizeof(Word));//Массив слов

        if (buffer == NULL) {
            printf("Error: ошибка выделения памяти\n");
            clearing_the_buffer(buffer, number_buffer_word);
            clearing_the_text(text, (*number_string));
            exit(EXIT_FAILURE);
        }
        buffer[number_buffer_word].word = (char *) malloc(capacity_word * sizeof(char)); // Слово
        if (buffer[number_buffer_word].word == NULL) {
            printf("Error: ошибка выделения памяти\n");
            clearing_the_text(text, (*number_string));
            clearing_the_buffer(buffer, number_buffer_word);
            exit(EXIT_FAILURE);
        }
        int flag_all = 0;
        int replay_flag = 0;
        int flag_word = 0;
    //Считывание предложения
        char ch = getchar();
    while(1){
        if (ch == '\n')
            if ((ch = getchar()) == '\n'){
                flag_all = 1;
                break;
            }
        if (isalpha(ch) || isdigit(ch)){
            flag_word = 1;
            if(number_buffer_symbol < capacity_word - 1*sizeof(size_t)){
                capacity_word += BLOCK_SIZE_WORD;
                buffer[number_buffer_word].word = (char *) realloc( buffer[number_buffer_word].word, capacity_word * sizeof(char));
                if (buffer[number_buffer_word].word == NULL){
                    printf("Error: ошибка выделения памяти\n");
                    clearing_the_text(text,(*number_string));
                    clearing_the_buffer(buffer, number_buffer_word);
                    exit(EXIT_SUCCESS);
                }
                }
            buffer[number_buffer_word].word[number_buffer_symbol++] = ch;
        }
        else if (flag_word == 1) {
            buffer[number_buffer_word].word[number_buffer_symbol] = '\0';
            buffer[number_buffer_word].count_symbol = number_buffer_symbol+1;
            buffer[number_buffer_word].service_symbol = ch;
            if((capacity_struc_word -1)<= number_buffer_word){
                capacity_struc_word += BLOCK_SIZE_STR;
                buffer = (Word *) realloc(buffer, capacity_struc_word  * sizeof(Word));
                if (buffer == NULL){
                    printf("Error: ошибка выделения памяти\n");
                    clearing_the_text(text,(*number_string));
                    clearing_the_buffer(buffer, number_buffer_word);
                    exit(EXIT_SUCCESS);
                }
            }
            number_buffer_word++;
            buffer[number_buffer_word].word = (char *) malloc(capacity_word * sizeof(char));
            if (buffer[number_buffer_word].word == NULL) {
                printf("Error: ошибка выделения памяти\n");
                clearing_the_text(text, (*number_string));
                clearing_the_buffer(buffer, number_buffer_word);
                exit(EXIT_SUCCESS);
            }
            number_buffer_symbol = 0;
            flag_word = 0;
        }
        if (ch == '.'){
            break;}
        ch = getchar();
    }

    free(buffer[number_buffer_word].word);
        // Проверка на повторы
        for (int j = 0; j < *number_string; j++) {
            int isIdentical = 1;  // Предполагаем, что предложения идентичны
            if (text[j].count_word != number_buffer_word && number_buffer_word != 0) {
                isIdentical = 0;  // Если количество слов различно, предложения не могут быть идентичными
            }
            else {
                for (size_t i = 0; i < number_buffer_word; i++) {
                    if (strstr(buffer[i].word, text[j].string[i].word) == 0) {
                        isIdentical = 0;  // Если хоть одно слово не совпадает, предложения не могут быть идентичными
                        break;
                    }
                }
            }
            if (isIdentical) {
                replay_flag = 1;
                break;  // Если найдено идентичное предложение, выходим из цикла
            }
        }


        //Запись - копия предложения
    if (replay_flag == 0){
        text[*number_string].string = (Word *)malloc(number_buffer_word * sizeof(Word));
        if (text[*number_string].string == NULL) {
            printf("Error: ошибка выделения памяти\n");
            clearing_the_text(text, *number_string);
            clearing_the_buffer(buffer, number_buffer_word);
            exit(EXIT_FAILURE);
        }
        for(size_t i = 0; i < number_buffer_word; i++){
            text[*number_string].string[i].word = (char *) malloc(buffer[i].count_symbol * sizeof(char));
            if (text[*number_string].string[i].word == NULL) {
                printf("Error: ошибка выделения памяти\n");
                clearing_the_text(text, (*number_string));
                clearing_the_buffer(buffer, number_buffer_word);
                exit(EXIT_SUCCESS);
            }
            strcpy(text[*number_string].string[i].word,buffer[i].word);
            text[*number_string].string[i].service_symbol = buffer[i].service_symbol;
        }
        text[*number_string].count_word = number_buffer_word;

    }
        clearing_the_buffer(buffer, number_buffer_word);

    if(*number_string >= capacity_struc_text-2){
        capacity_struc_text += BLOCK_SIZE_STR;
        text = (Sentence *)realloc(text, capacity_struc_text * sizeof(Sentence));
        if (text == NULL){
            printf("Error: ошибка выделения памяти\n");
            clearing_the_text(text,(*number_string));
            clearing_the_buffer(buffer, number_buffer_word);
            exit(EXIT_SUCCESS);
        }
    }
    if(flag_word == 0 && replay_flag == 0){
        (*number_string)++;}
    if (flag_all == 1){
        break;}
}

    return text;
}

Sentence* reading_the_text_9(size_t* number_string, int* povtor){
    int capacity_struc_text = BLOCK_SIZE_STR;
    Sentence *text = (Sentence *) malloc(capacity_struc_text * sizeof(Sentence));
    scanf("%d", povtor);
    while(1){
        int capacity_struc_word = BLOCK_SIZE_STR;
        size_t capacity_word = BLOCK_SIZE_WORD;
        size_t number_buffer_word = 0;
        size_t number_buffer_symbol = 0;
        Word *buffer = (Word *) malloc(capacity_struc_word  * sizeof(Word));//Массив слов

        if (buffer == NULL) {
            printf("Error: ошибка выделения памяти\n");
            clearing_the_buffer(buffer, number_buffer_word);
            clearing_the_text(text, (*number_string));
            exit(EXIT_FAILURE);
        }
        buffer[number_buffer_word].word = (char *) malloc(capacity_word * sizeof(char)); // Слово
        if (buffer[number_buffer_word].word == NULL) {
            printf("Error: ошибка выделения памяти\n");
            clearing_the_text(text, (*number_string));
            clearing_the_buffer(buffer, number_buffer_word);
            exit(EXIT_FAILURE);
        }
        int flag_all = 0;
        int replay_flag = 0;
        int flag_word = 0;

        //Считывание предложения
        char ch = getchar();
        while(1){
            if (ch == '\n')
                if ((ch = getchar()) == '\n'){
                    flag_all = 1;
                    break;
                }
            if (isalpha(ch) || isdigit(ch)){
                flag_word = 1;
                if(number_buffer_symbol < capacity_word - 1*sizeof(size_t)){
                    capacity_word += BLOCK_SIZE_WORD;
                    buffer[number_buffer_word].word = (char *) realloc( buffer[number_buffer_word].word, capacity_word * sizeof(char));
                    if (buffer[number_buffer_word].word == NULL){
                        printf("Error: ошибка выделения памяти\n");
                        clearing_the_text(text,(*number_string));
                        clearing_the_buffer(buffer, number_buffer_word);
                        exit(EXIT_SUCCESS);
                    }
                }
                buffer[number_buffer_word].word[number_buffer_symbol++] = ch;
            }
            else if (flag_word == 1) {
                buffer[number_buffer_word].word[number_buffer_symbol] = '\0';
                buffer[number_buffer_word].count_symbol = number_buffer_symbol+1;
                buffer[number_buffer_word].service_symbol = ch;
                if((capacity_struc_word -1)<= number_buffer_word){
                    capacity_struc_word += BLOCK_SIZE_STR;
                    buffer = (Word *) realloc(buffer, capacity_struc_word  * sizeof(Word));
                    if (buffer == NULL){
                        printf("Error: ошибка выделения памяти\n");
                        clearing_the_text(text,(*number_string));
                        clearing_the_buffer(buffer, number_buffer_word);
                        exit(EXIT_SUCCESS);
                    }
                }
                number_buffer_word++;
                buffer[number_buffer_word].word = (char *) malloc(capacity_word * sizeof(char));
                if (buffer[number_buffer_word].word == NULL) {
                    printf("Error: ошибка выделения памяти\n");
                    clearing_the_text(text, (*number_string));
                    clearing_the_buffer(buffer, number_buffer_word);
                    exit(EXIT_SUCCESS);
                }
                number_buffer_symbol = 0;
                flag_word = 0;
            }
            if (ch == '.'){
                break;}
            ch = getchar();
        }

        free(buffer[number_buffer_word].word);
        // Проверка на повторы
        for (int j = 0; j < *number_string; j++) {
            int isIdentical = 1;  // Предполагаем, что предложения идентичны
            if (text[j].count_word != number_buffer_word && number_buffer_word != 0) {
                isIdentical = 0;  // Если количество слов различно, предложения не могут быть идентичными
            }
            else {
                for (size_t i = 0; i < number_buffer_word; i++) {
                    if (strstr(buffer[i].word, text[j].string[i].word) == 0) {
                        isIdentical = 0;  // Если хоть одно слово не совпадает, предложения не могут быть идентичными
                        break;
                    }
                }
            }
            if (isIdentical) {
                replay_flag = 1;
                break;  // Если найдено идентичное предложение, выходим из цикла
            }
        }


        //Запись - копия предложения
        if (replay_flag == 0){
            text[*number_string].string = (Word *)malloc(number_buffer_word * sizeof(Word));
            if (text[*number_string].string == NULL) {
                printf("Error: ошибка выделения памяти\n");
                clearing_the_text(text, *number_string);
                clearing_the_buffer(buffer, number_buffer_word);
                exit(EXIT_FAILURE);
            }
            for(size_t i = 0; i < number_buffer_word; i++){
                text[*number_string].string[i].word = (char *) malloc(buffer[i].count_symbol * sizeof(char));
                if (text[*number_string].string[i].word == NULL) {
                    printf("Error: ошибка выделения памяти\n");
                    clearing_the_text(text, (*number_string));
                    clearing_the_buffer(buffer, number_buffer_word);
                    exit(EXIT_SUCCESS);
                }
                strcpy(text[*number_string].string[i].word,buffer[i].word);
                text[*number_string].string[i].service_symbol = buffer[i].service_symbol;
            }
            text[*number_string].count_word = number_buffer_word;

        }
        clearing_the_buffer(buffer, number_buffer_word);

        if(*number_string >= capacity_struc_text-2){
            capacity_struc_text += BLOCK_SIZE_STR;
            text = (Sentence *)realloc(text, capacity_struc_text * sizeof(Sentence));
            if (text == NULL){
                printf("Error: ошибка выделения памяти\n");
                clearing_the_text(text,(*number_string));
                clearing_the_buffer(buffer, number_buffer_word);
                exit(EXIT_SUCCESS);
            }
        }
        if(flag_word == 0 && replay_flag == 0){
            (*number_string)++;}
        if (flag_all == 1){
            break;}
    }

    return text;
}



//Шапка программы
int heading(){
    int number_func = 0;
    puts("Course work for option 4.1, created by Maksim Beskonchin.");
    scanf("%d", &number_func);
    getchar(); // Очистка буфера

    if (number_func == 5){
        puts("\n\nСправка о функиях:");
        puts("_______________________________________________________________________________________________________________________________________________________________");
        puts("0 - Вывод текста после первичной обязательной обработки.");
        puts("1 - Преобразовать предложения так, чтобы каждое первое слово в нем начиналось с заглавной буквы, а остальные символы были прописными.");
        puts("2 - Удалить все предложения, состоящие из четного количества слов.");
        puts("3 - Отсортировать предложения по сумме количеств гласных букв в каждом втором слове. Сумма для предложения “abc qwe defgh prq ijklmno” будет такой: abc = 1, defgh=1, ijklmno=2, итоговая сумма = 4.");
        puts("4 - Вывести на экран все предложения, в которых в середине предложения встречаются слова, состоящие из прописных букв. Данные слова нужно выделить синим цветом.");
        puts("_______________________________________________________________________________________________________________________________________________________________");
        exit(EXIT_SUCCESS);
    }
    else if (number_func != 0 && number_func != 1 && number_func != 2 && number_func != 3 && number_func != 4 && number_func != 9){
        puts("Error: выбрана несуществующая функция");
        exit(EXIT_SUCCESS);
    }
    else return number_func;
}

// Сравниваем предложения по количеству гласных букв для использования в функции qsort
int compare(const void *a, const void *b) {
    return ((Sentence*)a)->number_of_vowels - ((Sentence*)b)->number_of_vowels;
}

void print_blue_capital_letters(Sentence* sentence) {
    for (int i = 0; i < sentence->count_word; i++) {
        if (sentence->string[i].title_word && i != 0 && i != sentence->count_word-1) {
            for (int j = 0; j < sentence->count_word; j++) {
                if (sentence->string[j].title_word && j != 0 && j != sentence->count_word-1) {
                    printf(COLOR_BLUE "%s" COLOR_RESET, sentence->string[j].word);
                } else {
                    printf("%s", sentence->string[j].word);
                }
                printf("%c", sentence->string[j].service_symbol);
            }
            printf("\n");
            return; // Печать только один раз, если найдено хотя бы одно слово с title_word = 1
        }
    }
}


int main(){
    int number_func = heading();
    int povtor = 0;
    size_t number_string = 0;
    Sentence* text;
    if(number_func != 9){
    text = reading_the_text(&number_string);}
    else {text = reading_the_text_9(&number_string, &povtor);}
    size_t len = 0;

    switch (number_func) {
        case 0:
            print(text, &number_string);
            break;
        case 1:
            capitalizeFirstWord(text, &number_string);
            print(text, &number_string);
            break;
        case 2:
            print_even(text, &number_string);
            break;
        case 3:
            for (size_t i = 0; i < number_string; i++) {
                text[i].number_of_vowels = countVowelsInSecondWord(text[i].string, text[i].count_word);
                len++;
            }
            qsort(text, len, sizeof(Sentence), compare);
            print(text, &number_string);
            break;
        case 4:
            for(size_t i = 0; i < number_string; i++) {
                for (size_t j = 0; j < text[i].count_word; j++) {
                    text[i].string[j].title_word = isAllUppercase(text[i].string[j].word);
                }
                print_blue_capital_letters(&text[i]);
            }
            break;
        case 9:
            print_povtor(text, &number_string, &povtor);
            break;
    }
    clearing_the_text(text,number_string);
    return 0;
}