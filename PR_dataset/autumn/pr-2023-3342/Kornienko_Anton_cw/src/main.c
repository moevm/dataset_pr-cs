#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

void greetings();
int count_of_sentences(char *str);
int input(char** str);
char** treatment(char* str, int count_sentanses, int len);
void output(char** str, int count_sentences);
void clear(char** str, int count_sentences);
char** clear_double(char** array, int size,int* new_size);
char* create_lower_case_array(int size, char* str);
void change(char** str, int size, int command);

char** delete_words(char** str, int size);
char** write_capital_letters(char** str, int size,int* new_size);
void sort_average(char** str, int size);
char** delele_without_lowercase_letters(char** str, int size,int* new_size);
char** replace_numbers_with_binary(char** str,int size);

int cmp(const void *a, const void *b);
char* remove_word_from_sentence(char* str, char* word);
int compare_sentences(const void *a, const void *b);
float calculate_average(const char *str);
char* space(char* str);
char* replacement_numbers_with_binary_of_sentence(char* str_1);
char* bin(char* num);
void command_selection(int number);

int main(){
    setlocale(LC_CTYPE, "");
    greetings();

    int command;        
    scanf("%d", &command);
    command_selection(command);
    return 0;
}
void command_selection(int number){
    if((number > 5 || number < 0) && number != 9)
        printf("error: первый символ должнен быть числом от 0 до 5");
    else if(number == 5)
        printf("1: Во всемы тексте удалить слово введенное пользователем. Если после удаления в предложении не останется слов, его необходимо удалить.\n2: Для каждого предложения вывести все заглавные буквы в лексикографическом порядке.\n3: Отсортировать предложения по среднему арифметическому чисел в предложении. Число - слово состоящее только из цифр.\n4: Удалить все предложения в которых нет строчных букв.");

    else{
        
        char* str = NULL;
        int len = input(&str);
        int count_sentences = count_of_sentences(str);
        
        
        char ** sentences = treatment(str, count_sentences,len);
        
        change(sentences, count_sentences, number);
        
        if(str != NULL){
            free(str);
        }
    
    }
}
int cmp(const void *a, const void *b){
    const char *f = (const char *)a;
    const char *s = (const char *)b;
    return strcmp(f,s);
}

void change(char** str, int size, int command){
    int new_size = 0;
    if(command == 0){

            char** result = clear_double(str,size,&new_size);
            output(result,new_size);
            clear(result,new_size);
            clear(str,size);
        }
    if(command == 1){

            char** text = clear_double(str,size,&new_size);
            char** result = delete_words(text, new_size);
            output(result,new_size);
            clear(result ,new_size);
            clear(text,new_size);
            clear(str,size);
        }
    if(command == 2){
            int size_after_t_2 = 0;
            char** text = clear_double(str,size,&new_size);
            char** result = write_capital_letters(text, new_size,&size_after_t_2);
            
            output(result,size_after_t_2);
            clear(result,size_after_t_2);
            clear(text,new_size);
            clear(str,size);
        }
    if(command == 3){
            sort_average(str, size);
        }
    if(command == 4){
        int size_after_t_4 = 0;
        char** text = clear_double(str,size,&new_size);
        char** result = delele_without_lowercase_letters(text, new_size, &size_after_t_4);
        output(result,size_after_t_4);
        clear(result,size_after_t_4);
        clear(text,new_size);
        clear(str, size);
    }
    if(command == 9){
        char** text = clear_double(str,size,&new_size);
        char** result = replace_numbers_with_binary(text,new_size);
        output(result,new_size);
        clear(result ,new_size);
        clear(text,new_size);
        clear(str,size);
    }

}
void output(char** str, int count_sentences){
    if(str != NULL){
        for(int i = 0; i < count_sentences; i++){
            printf("%s\n", str[i]);
        }
    }
}
char** replace_numbers_with_binary(char** str,int size){
    char** result = malloc(sizeof(char*) * size);
    
    for(int i = 0; i< size; i++){
        result[i] = replacement_numbers_with_binary_of_sentence(str[i]);
    }
    return result;
}
char* replacement_numbers_with_binary_of_sentence(char* str_1)
{
    int capacity = 50;
    int len = 0;
    char* res = malloc(sizeof(char) * capacity);
    
    int len_num = 0;
    int capacity_num = 10;
    char* number = malloc(sizeof(char) * capacity_num);
    
    for(int i = 0; i < strlen(str_1); i ++){
        if(isdigit(str_1[i])){

            len_num++;
            if(len_num >= capacity_num){
                capacity_num = capacity_num * 1.5;
                number = realloc(number, capacity_num);
            }
            number[len_num - 1] = str_1[i];
            
        }
        else{
            if(strlen(number) > 0 && atoi(number) > 0){
                number[len_num] = '\0';
                
                char* n = bin(number);
                
                if(strcmp(n,"0b") != 0){
                for(int j = 0; j < strlen(n); j++){

                    len++;
                    if(len >= capacity){
                        capacity = capacity * 1.5;
                        res = realloc(res, capacity);
                    }
                    res[len - 1] = n[j];
                    }
                }
                free(number);
                
                len_num = 0;
                capacity_num = 10;
                number = malloc(sizeof(char) * capacity_num);
                len++;
                    if(len >= capacity){
                        capacity = capacity * 1.5;
                        res = realloc(res, capacity);
                    }
                res[len - 1] = str_1[i];
            }
        
            else{
                len++;
                if(len >= capacity){
                        capacity = capacity * 1.5;
                        res = realloc(res, capacity);
                    }
                
                res[len - 1] = str_1[i];
            }
            
        }
    }
    res[len] = '\0';
    return res;


    
}
char* bin(char* num){
    int capacity = 10;
    char* res = malloc(sizeof(char) * 3);
    res[0] = '0';
    res[1] = 'b';

    int number = atoi(num);
    int c = 0;
    int idx = 0;
    char* text = malloc(sizeof(char) * capacity);
    while(number > 0){
        c = number % 2;
        idx ++;
        text[idx - 1] = c + '0';
        if(idx >= capacity){
            capacity = capacity * 1.5;
            text = realloc(text,capacity);
        }
        number = number / 2; 
    }
    text[idx] = '\0';
    res = realloc(res, sizeof(char) * (strlen(text) + 4));
    int index = 2;
    for(int i = strlen(text) - 1;i >= 0;i--){
        index ++;
        res[index - 1] = text[i];
    }
    res[index] = '\0';
    return res;
}
char** delete_words(char** str, int size){
    char* word = NULL;
    int idx = 0;
    for(int i = 0; i < strlen(str[0]) && str[0][i] != ' ' && str[0][i] != '.'; i++){
        word = realloc(word, sizeof(char) * ++idx);
        word[idx - 1] = str[0][i];
        
    }
    word[idx] = '\0';
    int len = 0;
    char** result = NULL;
    for(int i = 0;i < size;i++){
        char* sentence = remove_word_from_sentence(str[i], word);
        result = realloc(result, sizeof(char*) * ++len);
        result[len - 1] = malloc(strlen(sentence) + 1);
        for(int j = 0;j < strlen(sentence); j++){
            result[len - 1][j] = *(sentence + j);
        }
        
        result[len - 1][strlen(sentence)] = '\0';
        if(sentence != NULL){
            free(sentence);
        }
    }
    if(word != NULL){
        free(word);
    }
    return result;
}   
char** write_capital_letters(char** str, int size,int* new_size){
    int count = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0;j < strlen(str[i]); j++){
            if(isupper(str[i][j])){
                count++;
                break;
            }
        
        }
    }
    *new_size = count;
    
    char** arr = malloc(sizeof(char*) * count);
    int len = 0;
    for(int i = 0; i < size; i++){
        char* word = NULL;
        int idx = 0;
        int flag = 0;
        for(int j = 0; j < strlen(str[i]); j++){
            if(isupper(str[i][j])){
                word = realloc(word, sizeof(char) * ++idx);
                word[idx - 1] = str[i][j];
                flag = 1;
            }
        }
        if(idx)
            word[idx] = '\0';
        
        if(flag){
            
            
            arr[len] = malloc(strlen(word) + 1);
            for(int i = 0; i < strlen(word);i++){
                arr[len][i] = word[i];
            }
            arr[len][strlen(word)] = '\0';
            len++;
            if(word != NULL){
                free(word);
            }
        }
    }

    for(int i = 0; i < count; i++){
        qsort(arr[i], strlen(arr[i]), sizeof(char), cmp);
    }
    return arr;
}
void sort_average(char** str, int size){
    int new_size = 0;
    char** text = clear_double(str,size,&new_size);
    qsort(text, new_size, sizeof(char *), compare_sentences);
    
    
    output(text,new_size);
    clear(text,new_size);
    clear(str,size);
}

char** delele_without_lowercase_letters(char** str, int size,int* new_size){
    char** res = NULL;
    int idx = 0;
    for(int i = 0; i < size; i++){
        int flag = 1;
        for(int j = 0; j < strlen(str[i]); j++){
            if(islower(str[i][j])){
                flag = 0;
                break;
            }
        }
        if(flag == 0){

            res = realloc(res, sizeof(char*) * ++idx);
            res[idx - 1] = malloc(sizeof(char) * (strlen(str[i]) + 1));
            for(int k = 0; k < strlen(str[i]); k ++){
                res[idx - 1][k] = str[i][k];
            }
        res[idx - 1][strlen(str[i])] = '\0';
        }
        

    }
    
    *new_size = idx;
    return res;

}


void greetings(){

    printf("Course work for option 4.20, created by Anton Kornienko\n");

}


int input(char** str)
{
    int iter = 0;
    char c;
    int count_n = 0;
    while (1) {
            c = getchar();

            if(c == '\n'){
                count_n ++;
                if(count_n == 2){
                    break;
                }
                else{
                    iter++;
                    *str = (char *)realloc(*str, (iter) * sizeof(char));
                    *(*str + iter - 1) = c;
                }
            }
            else{
                count_n = 0;
                iter++;
                *str = (char *)realloc(*str, (iter) * sizeof(char));
                *(*str + iter - 1) = c;
            }

    }
    iter ++;
    *str = (char *)realloc(*str, (iter) * sizeof(char));
    *(*str + iter - 1) = '\0';
    return iter;
}

int count_of_sentences(char *str)
{
    int count = 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '.'){
            count ++;
        }

    }
    return count;
}
char** treatment(char* str, int count_sentanses, int len){
    char ** result = malloc(sizeof(char*) * count_sentanses);
    int number = 0;
    int idx = 0;
    
    char* sentence = NULL;



    for(int i = 0; i < len;i++){
        
        if(str[i] != '.'){
            sentence = realloc(sentence, sizeof(char) * (++idx));
            sentence[idx - 1] = str[i];
            
        }

        if(str[i] == '.' && i > 0){
            sentence = realloc(sentence, sizeof(char) * ((++idx) + 1));
            sentence[idx - 1] = str[i];
            sentence[idx] = '\0';

            if (sentence[0] == ' '){
                int start = 0;
                while(sentence[start] == ' '){
                    start ++;
                }
                memmove(sentence, sentence + start, strlen(sentence));
            }

            result[number] = malloc((strlen(sentence) + 1) * sizeof(char*));
            for(int k = 0; k < strlen(sentence); k++){
                result[number][k] = sentence[k];
            }   
             result[number][strlen(sentence)] = '\0';
             number++;
             
             
             idx = 0;           
        }
    }
    return result;
}




void clear(char** str, int count_sentences){
    if(str != NULL){
        for (int i = 0; i < count_sentences; i++) {
            if(str[i] != NULL){
                free(str[i]);
            }
        }
        free(str);
    }
}
char** clear_double(char** array, int size,int* new_size){
    char** text_res = malloc(0);
    int idx = 0;
    for(int i = 0; i < size;i++){
        char* str = array[i];
        char* str_low = create_lower_case_array(strlen(str), str);
        int flag = 1;
        for(int j = 0; j < idx;j++){
            char* str_0 = array[j];
            char* str_0_low = create_lower_case_array(strlen(str_0), str_0);
            if(strcmp(str_low, str_0_low) == 0){
                flag = 0;
                break;
            }
        }
        if(flag){
            text_res = realloc(text_res, sizeof(char*) * ++idx);
            text_res[idx - 1] = space(str);
        }
    }
    *new_size = idx;
    return text_res;
}

char* create_lower_case_array(int size, char* str){
    char* arr = malloc((sizeof(char) + 1) * size);
    int i = 0;
    for(;i < size; ++i){
        arr[i] = tolower(str[i]);
    }

    arr[i] = '\0';
    return space(arr);

}



    
char* remove_word_from_sentence(char* str, char* word) {
    char arr[strlen(str)];
    for(int i = 0;i < strlen(str);i++){
        if(str[i] != '.')
            arr[i] = *(str + i);
    }
    char sep[10] = " ";
    char* result = malloc(sizeof(char) * strlen(str) + 1);
    int idx = 0;
    arr[strlen(str) - 1] = '\0';
    char *token = strtok(arr, sep);
    while(token != NULL){
            if(strcmp(token, word) != 0){
                for(int i = 0; i < strlen(token); i++){
                        result[idx++] = token[i];    
                }
                result[idx++] = ' ';

            }
            token = strtok(NULL, sep);

    }
 
    if(idx){
        result[idx - 1] = '.';
        result[idx] = '\0';
    }
    else{
        result[idx] = '.';
        result[idx + 1] = '\0';
    }
    return result;
}



float calculate_average(const char *str) {
    char arr[strlen(str)];
    for(int i = 0; i < strlen(str) && str[i] != '.'; i++){
        arr[i] = *(str + i);
    }
    int count = 0;
    float sum = 0.0;
    arr[strlen(str) - 1] = '\0';
    char *token = strtok(arr, " ");
    while (token != NULL) {
        int flag = 1;
        for(int i = 0; i < strlen(token); i++){
            if(isdigit(token[i]) == 0){
                flag = 0;
                break;
            }
        }
        if(flag){
            sum += atoi(token);
            count++;
        }
        token = strtok(NULL, " ");
    }
    return count > 0 ? (sum / count) : 0;
}



int compare_sentences(const void *a, const void *b) {
    const char **sentenceA = (const char **)a;
    const char **sentenceB = (const char **)b;
    float averageA = calculate_average(*sentenceA);
    float averageB = calculate_average(*sentenceB);

    if (averageA < averageB) {
        return -1;
    } else if (averageA > averageB) {
        return 1;
    } else {
        return 0;
    }
}



char* space(char* str){
    char* res = calloc(strlen(str) + 1, sizeof(char));
    int start = 0;
    while (str[start] == '\t' || str[start] == ' ' || str[start] == '\n'){
        start++;
    }
    for (int i = 0; i < strlen(str) - start; i++){
        res[i] = str[start + i];
    }
    res[strlen(str) - start] = '\0';
    return res;
}
