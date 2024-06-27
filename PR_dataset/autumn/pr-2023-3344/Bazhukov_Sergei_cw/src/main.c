#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BLUE "\033[1m\033[34m"
#define CLEAR "\033[0m"

void hello_message();
void help();
int default_handling(int* text_len_pointer, char** text, char* sentence);
char** capital_first(int* text_len_pointer, char** text);
char** delete_even(int* text_len_pointer, char** text);
char** sort_by_vowel(int* text_len_pointer, char** text);
void only_capital(int* text_len_pointer, char** text);
char** text_input(int* text_len_pointer);
char** choose_option(int choice, int* text_len_pointer);
void text_result(int text_len, char** text);
int cmp(const void *a, const void *b);
int count_even(char* sentence);
char** delete_capital(int* text_len_pointer, char** text, int capital_count);




int main(){
    hello_message();
    char choice = getchar();
    getchar();

    char** text;
    int text_len = 0;
    int* text_len_pointer = &text_len;
    text = choose_option(choice, text_len_pointer);
    if(text != NULL){
        text_result(text_len, text);
    }
    return 0;
}

char** text_input(int* text_len_pointer){
    char** text = (char**)malloc(sizeof(char*));
    while(1){
        char* sentence = (char*)malloc(sizeof(char));
        char token = ' ';
        int chars_in_sentence_counter = 0;
        int out_flag = 0;
        int other_symbol = 0;

        while (token != '.'){
            token = getchar();
            if(token == '\n'){
                out_flag += 1;
            }else{
                out_flag=0;
            }
            if(isalnum(token)){
                other_symbol = 1;
            }
            if(out_flag==2){
                if (other_symbol) 
                    sentence[chars_in_sentence_counter-1] = '.';
                break;

            }
            sentence[chars_in_sentence_counter++] = token;
            sentence = realloc(sentence, sizeof(char)*(chars_in_sentence_counter + 1));
        }
        sentence[chars_in_sentence_counter] = '\0';

        while (isspace(sentence[0])) {
            memmove(sentence, sentence+1, strlen(sentence));
        }

        if (default_handling(text_len_pointer, text, sentence) && strlen(sentence) > 1){
            text[(*text_len_pointer)++] = sentence;
            text = realloc(text, sizeof(char*)*((*text_len_pointer) + 1));
        }

        if (out_flag==2){
            break;
        }
    }
    return text;
}

char** choose_option(int choice, int* text_len_pointer){
    char **text;
    switch (choice){
        case '0':{
            text = text_input(text_len_pointer);
            return text;
            break;
        }
        case '1':{
            text = text_input(text_len_pointer);
            capital_first(text_len_pointer, text);
            return text;
            break;
        }
        case '2':{
            text = text_input(text_len_pointer);
            delete_even(text_len_pointer, text);
            return text;
            break;
        }
        case '3':{
            text = text_input(text_len_pointer);
            text = sort_by_vowel(text_len_pointer, text);
            return text;
            break;
        }
        case '4':{
            text = text_input(text_len_pointer);
            only_capital(text_len_pointer, text);
            return NULL;
            break;
        }
        case '5':{
            help();
            return NULL;
            break;
        }
        case '8':{
            char first_row[200];
            fgets(first_row,200,stdin);
            int capital_count = 0;
            for(int i=0;i<strlen(first_row);i++){
                if(isupper(first_row[i])){
                    capital_count++;
                }
            }
            text = text_input(text_len_pointer);
            delete_capital(text_len_pointer, text, capital_count);
            return text;
            break;
        }
        default:{
            printf("Error: Вы ввели неправильный номер опции. Введите целое число от 0 до 5\n");
            printf("(Для получения справки введите 5)\n");
            return NULL;
            break;
        }
    }
}

void hello_message(){
    printf("Course work for option 4.1, created by Sergei Bazhukov.\n");
}

int default_handling(int* text_len_pointer, char** text, char* sentence){
    for (int i=0; i<(*text_len_pointer);i++){
        if (strlen(sentence) == strlen(text[i])){
            int flag = 0;
            for (int j=0; j < strlen(text[i]);j++){
                if (tolower(sentence[j]) != tolower(text[i][j])){
                    flag = 1;
                    break;
                }
            }
            if (flag == 0){
                return 0;
            }
        }
    }
    return 1;
}


char** capital_first(int* text_len_pointer, char** text){
    int len = *text_len_pointer;
    for(int i=0; i!=len;i++){
        text[i][0] = toupper(text[i][0]);
        int ch = 1;
        do{
            text[i][ch] = tolower(text[i][ch]);
            ch++;
        } while(text[i][ch]!='.');
        ch=1;
    }
    return text;
}

char** delete_even(int* text_len_pointer, char** text){
    int len = *text_len_pointer;
    int space_counter = 0;
    char even_token='c';
    for(int i=0;i!=len;i++){
        int ch = 0;
        do{
            even_token=text[i][ch];
            if(even_token==' '){
                space_counter++;
            }
            ch++;
        }while(text[i][ch]!='.');
        if(space_counter%2!=0){
            text[i]=NULL;
        }
        space_counter=0;
    }
    return text;
}

char **sort_by_vowel(int *text_len_pointer, char **text){
    qsort(text, (*text_len_pointer), sizeof(char *), cmp);
    return text;
}

void only_capital(int *text_len_pointer, char **text){
    int len = *text_len_pointer;
    for (int i = 0; i != len; i++){
        char *sentence = text[i];
        int num_of_words = 1;
        for (int j = 0; j < strlen(sentence); j++){
            if (sentence[j] == ' ')
                num_of_words++;
        }
        int do_print = 0;
        int lbd = 0;
        int rbd = 0;
        for (int j = 0; j < strlen(sentence); j++){
            if (sentence[j] == ' '){
                lbd = j;
                break;
            }
        }
        for (int j = strlen(sentence) - 1; j >= 0; j--){
            if (sentence[j] == ' '){
                rbd = j;
                break;
            }
        }
        for (int j = lbd; j < rbd; j++){
            if (isupper(sentence[j]))
                do_print = 1;
        }

        if (!do_print){
            continue;
        }
        char sep[10] = " ";
        char *istr;
        istr = strtok(sentence, sep);
        int printed_words = 0;
        while (istr != NULL){
            int flag_capital = 0;
            for (int j = 0; j < strlen(istr); j++){
                if (isupper(istr[j])){
                    flag_capital++;
                }
                else{
                    flag_capital = 0;
                    break;
                }
            }
            if (flag_capital != 0 && printed_words > 0 && printed_words < num_of_words - 1){
                printf(BLUE);
                printf("%s ", istr);
                printed_words++;
                printf(CLEAR);
            }
            else{
                printf("%s ", istr);
                printed_words++;
            }
            istr = strtok(NULL, sep);
        }
        printf("\n");
    }
}



void text_result(int text_len, char** text){
    for (int i = 0; i < text_len; i++){
        if (text[i] != NULL){
            printf("%s\n", text[i]);
        }
        free(text[i]);
    }
    free(text);
}

int count_even(char *sentence)
{
    int even_counter = 0;
    int i = 0;
    char let;
    int do_count = 1;
    do{
        let = sentence[i];
        if (let == 'a' || let == 'i' || let == 'e' || let == 'u' || let == 'o' || let == 'y' || let == 'A' || let == 'I' || let == 'E' || let == 'U' || let == 'O' || let == 'Y'){
            if (do_count)
                even_counter++;
        }
        if (let == ','){
            i++;
        }
        if (let == ' '){
            do_count = !do_count;
        }
        i++;
    } while (sentence[i] != '.');
    return even_counter;
}

int cmp(const void *a, const void *b){
    int even_1 = count_even(*(char **)a);
    int even_2 = count_even(*(char **)b);
    if (even_1 == even_2)
        return 1;
    else
        return even_1 - even_2;
}

char** delete_capital(int* text_len_pointer, char** text, int capital_count){
    int len = *text_len_pointer;
    for(int i=0;i!=len;i++){
        int ch_cap_counter = 0;
        char* sentence = text[i];
        for(int j=0;j<strlen(sentence);j++){
            if(isupper(sentence[j])){
                ch_cap_counter++;
            }
        }
        if(ch_cap_counter>capital_count){
            free(sentence);
            text[i]=NULL;
        }
    }
    return text;
}

void help(){
    printf("///////////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("0 - Вывод текста после первичной обязательной обработки \n");
    printf("1 - Преобразовать предложения так, чтобы каждое первое слово в нем начиналось\n    с заглавной буквы, а остальные символы были прописными. \n");
    printf("2 - Удалить все предложения, состоящие из четного количества слов. \n");
    printf("3 - Отсортировать предложения по сумме количеств гласных букв в каждом втором слове. \n");
    printf("4 - Вывести на экран все предложения, в которых в середине предложения \n    встречаются слова, состоящие из прописных букв. Данные слова нужно выделить синим цветом. \n");
    printf("8 - Удалить все предложения, в которых заглавных букв больше, чем в первой строке. \n");
    printf("///////////////////////////////////////////////////////////////////////////////////////////////////\n");
}