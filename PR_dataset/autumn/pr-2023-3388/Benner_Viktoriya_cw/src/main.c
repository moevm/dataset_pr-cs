#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define INFORMATION_ABOUT_CW "Course work for option 4.7, created by Viktoriya Benner."
#define ERROR_MESSAGE "Error: ircorrect function value.\n"
#define HELP_ABOUT_FUNCTIONS "0 - Вывод текста после первичной обработки(удаление повторяющихся предложений).\n1 - Вывести список всех цифр встречаемых во всем тексте и частоту их упоминания. \n2 - Преобразовать предложение так, чтобы символы кроме разделительных шли в обратном порядке. Например, для строки “abc defg.” результатом будет “gfe dcba.”.\n3 - Удалить все предложения в которых встречается слово “physics”.\n4 - Отсортировать предложения по уменьшению количества слов, длина которых равняется 3.\n"
#define END_SYMBOL '\0'
#define ARRAY_SIZE 10
#define BUFER_SIZE 10
#define WORD_TO_DELITE "physics"

void first_sentence(){
    printf("%s\n", INFORMATION_ABOUT_CW);
}

int get_commamd(){
    int command_number;
    scanf("%d", &command_number);
    getchar();
    if (command_number == 5){
        printf("%s\n", HELP_ABOUT_FUNCTIONS);
        exit(0);
    }
    return command_number;
}
char* input_function(){
    char* text = malloc(BUFER_SIZE*sizeof(char));
    size_t len = 0;
    char current = END_SYMBOL;
    char before_current = END_SYMBOL;
    while (current != '\n' || before_current != '\n'){
            if (current == EOF){
                printf("Error: Incorrect end of input\n");
                exit(0);
            }
            before_current = current;
            current = getchar();
            if (len % BUFER_SIZE == 0){
                text = realloc(text, (len + BUFER_SIZE)*sizeof(char));
            }
            text[len++] = current;
    }
    text[len-2] = END_SYMBOL;
    len-= 2;

    return text;   
}

char* make_sentence(char* text, int* start){
    char* sentence = malloc(BUFER_SIZE*sizeof(char));
    size_t len = 0;
    bool flag = false;
    size_t i = *start;
    while (text[i] != '.' && text[i] != END_SYMBOL){
        if (isspace(text[i]) && !flag){
            i++;
            continue;
        }
        if (len % BUFER_SIZE == 0){
            sentence = realloc(sentence, (len + BUFER_SIZE)*sizeof(char));
        } 
        sentence[len++] = text[i];
        flag = true;
        i++;
    }
    if (text[i] == END_SYMBOL){
        *start = -1;
    }
    else{
        *start = i+1;
    }
    sentence = realloc(sentence, (len + 2)*sizeof(char));
    sentence[len++] = '.';
    sentence[len++] = END_SYMBOL;

    return sentence;
}

char** split_sentences(char* text, size_t *len){
    char** sens = NULL;
    int start = 0;
    char* sentence = make_sentence(text, &start);
    while(start != -1){
        sens = realloc(sens, ((*len)+1)*sizeof(char*));
        sens[*len] = malloc((strlen(sentence)+1)*sizeof(char));
        strcpy(sens[*len], sentence);
        (*len)++;
        free(sentence);
        sentence = make_sentence(text, &start);
    }
    return sens;
}

char** find_duplicate_sentences(char** sentences_with_duplicates, size_t sentences_quantity, size_t *new_len) {
    char **new_sentences = malloc(sentences_quantity*sizeof(char*));
    size_t current_len = 0;
    bool flag;
    for (size_t i = 0; i < sentences_quantity; i++){
        flag = true;
        for (size_t j = 0; j < current_len; j++){
            if (!strcasecmp(sentences_with_duplicates[i], new_sentences[j])){
               flag = false;
               break; 
            }
        }
        if (flag){
            new_sentences[current_len++] = strdup(sentences_with_duplicates[i]);
        }
    }
    *new_len = current_len;
    return new_sentences; 
}

void print_sentences(char** sentences, int new_len) {
    for (int i = 0; i < new_len; i++) {
        printf("%s\n", sentences[i]);
    }
}

void find_and_count_digits(char **sentences, int new_len) {
    int count[ARRAY_SIZE] = {0}; // массив для подсчета встреченных цифр от 0 до 9
    
    for (int i = 0; i < new_len; i++) {
        char *text = sentences[i]; // Получаем текущее предложение
        
        for (char *current = text; *current; ++current) {
            if (isdigit(*current)) {
                count[*current - '0']++; // Увеличиваем счетчик для соответствующей цифры
            }
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (count[i] > 0) {
            printf("%d: %d\n", i, count[i]); // Выводим цифру и количество ее вхождений
        }
    }
}
void reverse_words(char* sentence) {
    int length = strlen(sentence);
    int start = 0, end = length - 1;
    
    // Меняем порядок символов внутри каждого слова
    while (start <= end) {
        if (sentence[start] == ' ' || sentence[start] == '.'  || sentence[start] == ',') {
            start++;
            continue;
        }
        if (sentence[end] == ' ' || sentence[end] == '.' || sentence[end] == ',') {
            end--;
            continue;
        }

        char temp = sentence[start];
        sentence[start] = sentence[end];
        sentence[end] = temp;
        
        start++;
        end--;
    }
}

int contains_word(char* sentence_for_processing, char* word) {
    char* sentence = malloc(sizeof(char)*(strlen(sentence_for_processing)+1));
    strcpy(sentence, sentence_for_processing); // fix the variable name here
    char* token = strtok(sentence, " ,.");
    while (token != NULL) {
        if (strcmp(token, word) == 0) {
            return 1; // слово найдено
        }
        token = strtok(NULL, " ,.");
    }
    return 0; // слово не найдено
}
char** remove_sentences_with_word(char** sentences, size_t* new_len, char* word) {
    int sentence_number, length_sentences_without_word;
    char** sentences_without_word = NULL;
    for (sentence_number = 0, length_sentences_without_word = 0; sentence_number < *new_len; sentence_number++) {
        if (!contains_word(sentences[sentence_number], word)){
            sentences_without_word = realloc(sentences_without_word, (length_sentences_without_word+1)*sizeof(char*));
            sentences_without_word[length_sentences_without_word++] = sentences[sentence_number];
        }
        else{
            free(sentences[sentence_number]);
        }
    }
    *new_len = length_sentences_without_word;
    return sentences_without_word;
}

void swap(char** sentences, int what_replace, int with_what_replace) {
    char* temp = sentences[what_replace];
    sentences[what_replace] = sentences[with_what_replace];
    sentences[with_what_replace] = temp;
}

int count_words_of_length(char* str, int len) {
    int count = 0;
    char* temp = malloc(strlen(str) + 1); // выделяем память для временного буфера
    strcpy(temp, str); // копируем строку во временный буфер
    char* token = strtok(temp, " ,.");
    while (token != NULL) {
        if (strlen(token) == len) {
            count++;
        }
        token = strtok(NULL, " ,.");
    }
    free(temp); // освобождаем память для временного буфера
    return count;
}

void sort_by_word_length_count(char** sentences, int new_len) {
    for (int i = 0; i < new_len - 1; i++) {
        for (int j = 0; j < new_len - i - 1; j++) {
            if (count_words_of_length(sentences[j], 3) > count_words_of_length(sentences[j + 1], 3)) {
                swap(sentences, j, j + 1);
            }
        }
    }
}

void free_sen(char** sentence, size_t len){
    for (size_t i = 0; i < len; i++){
        free(sentence[i]);
    }
    free(sentence);
}

char* connect_sentences(char* text){
    int text_len = strlen(text);

    int start_index;
    int num_sentences = 1;
    for (int i = 0; i < text_len; i++){
        if (text[i] == '\n'){
            start_index = i + 1;
            break;
        }
    }
    for (int i = start_index; i < text_len; i++){
        if (text[i] == '\n'){
            num_sentences ++;
        }
    }
    int dest_index;
    if (num_sentences % 2 == 0){
        dest_index = num_sentences /2;
    }
    else{
        dest_index = num_sentences/2 + 1;
    }
    char* connect_text = (char*)malloc(100*sizeof(char));
    int current_index = 0;

    for (int i = start_index; i < text_len; i++){
        if (text[i] == '\n'){
            continue;
        }
    
        if (current_index >= dest_index){
            connect_text = (char*)realloc(connect_text, (current_index - dest_index + 2)*100*sizeof(char));
            if (connect_text == NULL){
                printf("Ошибка выделения памяти.\n");
                free(connect_text);
                return NULL;
            }
            strncat(connect_text, &text[i], 1);
            if (text[i] == '.'){
                strcat(connect_text, " ");
            }
        }
        if (text[i] == '.'){
            current_index++;
        }
    }
    connect_text[current_index - dest_index + 1] = '\0';

    return connect_text;
}

void new_func(int n, char** sentences, size_t len){
    size_t sen_len;
    for (size_t i = 0; i < len; i++ ){
        sen_len = strlen(sentences[i]);
        sentences[i][sen_len-1] = END_SYMBOL;
        for (size_t j = 0; j < n-1; j++)
            printf("%s ", sentences[i]);
        printf("%s.\n", sentences[i]);
    }

}

void switch_function(){
    int command = get_commamd();
    int n;
    //printf("%d", command);
    if (command == 8){
        scanf("%d", &n);
        getchar();
    }
    size_t new_len;
    char *text = input_function();

    int count = 0;
    size_t len = 0;
    char** sentences_with_duplicates = split_sentences(text, &len);
    free(text);
    char **sentences = find_duplicate_sentences(sentences_with_duplicates, len, &new_len);
    free_sen(sentences_with_duplicates, len);

    switch (command){
    case 0:{
        print_sentences(sentences, new_len);  
        free_sen(sentences, new_len);
        break;
    }
    case 1:{
        find_and_count_digits(sentences, new_len);
        free_sen(sentences, new_len);
        break;
    }
    case 2:{
        for (int i = 0; i < new_len; i++) {
            reverse_words(sentences[i]);
            printf("%s\n", sentences[i]);
        }
        free_sen(sentences, new_len);
        break;
    }
    case 3:{
        size_t old_len = new_len;
        char** sentences_without_word = remove_sentences_with_word(sentences, &new_len, WORD_TO_DELITE);
        print_sentences(sentences_without_word, new_len);
        free_sen(sentences_without_word, new_len);
        break;
    }
    case 4:{
        sort_by_word_length_count(sentences, new_len);
        print_sentences(sentences, new_len);
        free_sen(sentences, new_len);
        break;
    }
    case 5:{
        printf(HELP_ABOUT_FUNCTIONS);
        break;
    }
    case 8:{
        //printf("123%d", n);
        new_func(n, sentences, new_len);
        break;
    }
    default:{
        printf("ERROR: number or function");
        exit(0);
    }
    }
}

int main(){
    first_sentence();
    switch_function();
    return 0;
}
