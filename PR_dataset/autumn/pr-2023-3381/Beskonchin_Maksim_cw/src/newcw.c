#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define BLOCK_SIZE 100
#define BLOCK_SIZE_WORD 30
#define BLOCK_SIZE_STR 10
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"


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

void print(Sentence* text, size_t* number_string){
for(size_t j = 0; j < *number_string; j++){
    for(size_t i = 0; i < text[j].count_word; i++){
        printf("%s%c", text[j].string[i].word, text[j].string[i].service_symbol);
    }
    puts("");}
}

void print_even(Sentence* text, size_t* number_string){
    for(size_t j = 0; j < *number_string; j++){
        if(text[j].count_word % 2 != 0){
        for(size_t i = 0; i < text[j].count_word; i++){
            printf("%s%c", text[j].string[i].word, text[j].string[i].service_symbol);
        }}
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
            text[j].string[0].word[0] = toupper(text[j].string[0].word[0]);

            // Преобразовать остальные буквы в нижний регистр
            for (size_t k = 1; text[j].string[0].word[k]; k++) {
                text[j].string[0].word[k] = tolower(text[j].string[0].word[k]);
            }
        }
    }
}


Sentence* reading_the_text(size_t* number_string){
    int capacity_struc_text = BLOCK_SIZE_STR;
    int capacity_struc_word = BLOCK_SIZE_STR;
    size_t capacity_word = BLOCK_SIZE_WORD;

    Sentence *text = (Sentence *) malloc(capacity_struc_text * sizeof(Sentence));
   // text[number_string].string = (Word *) malloc(capacity_struc_word * sizeof(Word));
    int count_sentense =0;

    while(1){

        size_t number_buffer_word = 0;
        size_t number_buffer_symbol = 0;
        Word *buffer = (Word *) malloc(capacity_struc_word  * sizeof(Word));//Массив слов
        buffer[number_buffer_word].word = (char *) malloc(capacity_word * sizeof(char)); // Слово
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
            if(number_buffer_symbol < capacity_word - 1){
                capacity_word += BLOCK_SIZE_WORD;
                buffer[number_buffer_word].word = (char *) realloc( buffer[number_buffer_word].word, capacity_word * sizeof(char));
                }
            buffer[number_buffer_word].word[number_buffer_symbol++] = ch;
        }
        else if (flag_word == 1) {
            buffer[number_buffer_word].word[number_buffer_symbol] = '\0';
            buffer[number_buffer_word].count_symbol = number_buffer_symbol;
            buffer[number_buffer_word].service_symbol = ch;
            if(capacity_struc_word <= number_buffer_word-1){
                capacity_struc_word += BLOCK_SIZE_STR;
                buffer = (Word *) realloc(buffer, capacity_struc_word  * sizeof(Word));
            }
            number_buffer_word++;
            buffer[number_buffer_word].word = (char *) malloc(capacity_word * sizeof(char));
            number_buffer_symbol = 0;
            flag_word = 0;
        }
        if (ch == '.'){
            break;}
        ch = getchar();
    }

    //Служебный вывод
    /*for(size_t i = 0; i < number_buffer_word; i++){
        printf("%s%c", buffer[i].word,buffer[i].service_symbol );
    }*/


        // Проверка на повторы
        for (int j = 0; j < count_sentense; j++) {
            int isIdentical = 1;  // Предполагаем, что предложения идентичны
            if (text[j].count_word != number_buffer_word) {
                isIdentical = 0;  // Если количество слов различно, предложения не могут быть идентичными
            } else {
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
        for(size_t i = 0; i < number_buffer_word; i++){
            text[*number_string].string[i].word = (char *) malloc(buffer[i].count_symbol * sizeof(char));
            strcpy(text[*number_string].string[i].word,buffer[i].word);
            text[*number_string].string[i].service_symbol = buffer[i].service_symbol;
            text[*number_string].count_word = number_buffer_word;
            //printf("%s%c", text[*number_string].string[i].word, text[*number_string].string[i].service_symbol);
        }
        //puts("");
    }
    if(*number_string > capacity_struc_text-2){
        capacity_struc_text += BLOCK_SIZE_STR;
        text = (Sentence *) realloc(text, capacity_struc_text * sizeof(Sentence));
    }
        (*number_string)++;
        count_sentense++;
    for(size_t i = 0; i < number_buffer_word; i++){
       free(buffer[i].word);
        }
    free(buffer);

        if (flag_all == 1){
            break;
        }
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
    else if (number_func != 0 && number_func != 1 && number_func != 2 && number_func != 3 && number_func != 4){
        puts("Error: выбрана несуществующая функция");
        exit(EXIT_SUCCESS);
    }
    else return number_func;
}

// Сравниваем двух людей по возрасту для использования в функции qsort
int compare_people(const void *a, const void *b) {
    return ((Sentence*)a)->number_of_vowels - ((Sentence*)b)->number_of_vowels;
}

void printSentenceIfCapitalWordsExist(Sentence* sentence) {
    for (int i = 0; i < sentence->count_word; i++) {
        if (sentence->string[i].title_word) {
            for (int j = 0; j < sentence->count_word; j++) {
                if (sentence->string[j].title_word) {
                    printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, sentence->string[j].word);
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
    size_t number_string = 0;
    Sentence* text = reading_the_text(&number_string);
    number_string--;
    size_t len = 0;



    //Sentence* text = reading_the_text(number_func, &number_string);

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
            qsort(text, len, sizeof(Sentence), compare_people);
            print(text, &number_string);
            break;
        case 4:
            for(size_t i = 0; i < number_string; i++) {
                for (size_t j = 0; j < text[i].count_word; j++) {
                    text[i].string[j].title_word = isAllUppercase(text[i].string[j].word);
                }
                printSentenceIfCapitalWordsExist(&text[i]);
            }
            break;
    }
    for(size_t i = 0; i < number_string; i++) {
        for (size_t j = 0; j < text[i].count_word; j++) {
            free(text[i].string[j].word);
        }
        free(text[i].string);
    }
    free(text);
    return 0;
}