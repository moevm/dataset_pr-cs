#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  
#include <string.h> 

void info(){
    printf("Information about course work.\n");
    printf("0 - Display text.\n");
    printf("1 - Delete chosen word from the text.\n");
    printf("2 - Display all capital letters in lexicographic order for sentence.\n");
    printf("3 - Sort sentences by the arithmetic mean of the numbers in the sentence.\n");
    printf("4 - Remove all sentences that do not contain lowercase letters.\n");
    printf("5 - Display information about functions in programm.\n");
}

char* is_digit(char* text){
    char* empty = malloc(sizeof(char) * 2);
    empty[0] = '#';
    empty[1] = '\0';
    int i = 0;
    int counter = 0;
    for (i = 0; i < strlen(text); i++){
        if (isdigit(text[i])) {
            counter++;
        }
    }
    if (counter == strlen(text)){
        return text;
    }
    return empty;
}

int average_digits(char* sentence){
    int sum = 0;
    int count = 0;
    double result;
    char* word = malloc(sizeof(char));
    int j = 0;
    for (int i = 0; i < strlen(sentence); i++){
        if (isspace(sentence[i]) || ispunct(sentence[i])){
            if (isdigit(is_digit(word)[0])){
                count++;
                sum = sum + atoi(word);
            } 
            word = malloc(sizeof(char));
            j = 0;
        }
        else {
            word = realloc(word, sizeof(char) * (j + 1));
            word[j] = sentence[i];
            j++;
        }
    }
    word[j] = '\0';
    if (isdigit(is_digit(word)[0])){
        count++;
        sum = sum + atoi(word);
    };
    free(word);
        ///printf("%i|%c|\n", flag, sentence[i]);
    if (count > 0){
        result = sum / count;
    }
    else{
        result = 0;
    }
    return result;
}

int compare_chars(const void* a, const void* b){
    int arg1 = average_digits(*(char**)a);
    int arg2 = average_digits(*(char**)b);
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
 
    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

char** sorted_by_average(char** text, int size){
    qsort(text, size, sizeof(text[0]), compare_chars);
    return text;
}


int isDelimiter(char c) {
    return !(isalnum(c) || c == '_');
}

int compare (const void * a, const void * b)
{
  return ( *(char*)a - *(char*)b );
}


char* uppercase_sort(char* sentence){
    int i;
    int ptr = 0;
    char* text = malloc(sizeof(char));
    for (i = 0; i < strlen(sentence); i++){
        if (isupper(sentence[i])){
            text = realloc(text, sizeof(char) * (ptr + 1));
            text[ptr] = sentence[i];
            ptr++;
        }
    }
    text[ptr] = '\0';
    qsort(text, ptr, sizeof(char), compare);
    return text;
}

int words_in_sentence(char* sentence){
    int flag = 0;
    for (int i = 0; i < strlen(sentence); i++){
        if (isalnum(sentence[i])){
            flag = 1;
        }
    }
    return flag;
}


char* delete_word(char *sentence, char *word) {
    int len = strlen(word);
    int wordLen = strlen(sentence);
    for (int i = 0; i <= wordLen - len; i++) {
        if ((i == 0 || isDelimiter(sentence[i - 1])) && (i + len == wordLen || isDelimiter(sentence[i + len]))) {
            if (strncmp(&sentence[i], word, len) == 0) {
                memmove(&sentence[i], &sentence[i + len], wordLen - i - len + 1);
                wordLen = wordLen - len;
                i--; // перепроверяем данную позицию
            }
        }
    }
    
    if (words_in_sentence(sentence) == 1){
        return sentence;
    }
    return "\0";
}


int compare_sentences(char* first, char* second){
    int i, flag = 0;
    int length = strlen(first);
    int equal = 1;
    if (strlen(first) == strlen(second)){
        for (i = 0; i < length - 1; i++){
            if (toupper(first[i]) != toupper(second[i])){
                equal = 0;
            }
        }
        if (equal == 1){
            flag = 1;
        }
    }
    if (flag == 1){
        return 1;
    }
    return 0;
    
}

///отсюда я убрал || (symbol == '\n')
char** input(){
    int num = 0, len = 0;
    int upd_len = 50;
    char** text = (char**) malloc(sizeof(char*) * 1);
    char *sentence = malloc(sizeof(char) * 50);
    char symbol;    
    char previous;
    int flag = 1;
    
    while (flag == 1) {
        symbol = getchar();

        if ((symbol == '\n') && (previous == '\n'))
            flag = 0; 
        previous = symbol;

        if (((symbol == '\t') && (len == 0)) || ((symbol == '\n') && (len == 0)) || ((symbol == ' ') && (len == 0)))
            continue;

        len++;
        if (len == upd_len){
            upd_len = len + 50;
            sentence = realloc(sentence, sizeof(char) * upd_len);
        }
        
        sentence[len - 1] = symbol;
        
        if (symbol == '.'){
            num ++;
            text = realloc(text, sizeof(char*) * (num + 2));
            text[num - 1] = malloc(sizeof(char) * (len + 1));
            for (int i = 0; i < len; i++)
                text[num - 1][i] = sentence[i];
            text[num - 1][len] = '\0';
            free(sentence); 
            sentence = malloc(sizeof(char) * 50);
            len = 0;
            upd_len = 50;
        }
    }
    
    text[num] = malloc(sizeof(char) * 2);
    text[num][0] = '^';
    text[num][1] = '\0';
    free(sentence);
    return text;
}

///вспомогательная функция для функции format_text
int contain(int digit, int* array, int size){
    int i;
    int flag = 0;
    for(i = 0; i < size; i++){
        if (array[i] == digit){
            flag = 1;
        }
    }
    if (flag == 1){
        return 1;
    }
    return 0;
}

/// функция удаления дубликатов предложений. Предобработка текста
char** format_text(char** text){
    int* sentences = malloc(sizeof(int) * 2);
    int counter = 0;
    int i = 0, j = 0;
    int new_size = 0;
    char** new_text = malloc(sizeof(char*));
    while (text[i][0] != '^'){
        j = i+1;
        while (text[j][0] != '^'){
            if ((compare_sentences(text[i], text[j]) == 1 ) && (i != j)){
                sentences = realloc(sentences, sizeof(int) * (counter + 2));
                sentences[counter] = i;
                sentences[counter + 1] = j;
                counter += 2;
                
                /// выводит пары дубликатов предложений, если такие есть
                /// printf("%d %d\n",i, j);
            }
            j++;
        }
        i++;
    }
        
    /* проверка программы подсчёта дубликатов
    for (int p = 0; p < counter; p++){
        printf("%d ", sentences[p]);
    */
    i = 0;
    while (text[i][0] != '^'){
        if (contain(i, sentences, counter) == 0) {
            new_text = realloc(new_text, sizeof(char*) * (new_size + 2));
            new_text[new_size] = malloc(sizeof(char) * (strlen(text[i]) + 1));
            for (j = 0; j < strlen(text[i]); j++){
                new_text[new_size][j] = text[i][j];
            }
            //new
            new_text[new_size][strlen(text[i])] = '\0';
            //str
            new_size++;
        }
        i++;
    }
    new_text[new_size] = malloc(sizeof(char) * 2);
    new_text[new_size][0] = '^';
    free(sentences);
    free(text);
    return new_text;
}


char* input_word(){
    char* word = malloc(sizeof(char)*10);
    char c = 'w';
    int ptr = 0;
    while (c != '.'){
        c = getchar();
        if (ptr == 0 && c == '\n'){
            continue;  
        } 
        
        word[ptr] = c;
        word = realloc(word, sizeof(char) * (ptr + 1));
        ptr++;
    }
    word[ptr - 1] = '\0';
    return word;
}
int sentence_without_lowercase(char* sentence){
    int flag = 0;
    int i = 0;
    for (i = 0; i < strlen(sentence); i++){
        if (islower(sentence[i])) flag = 1;
    }
    return flag;
}


void return_text(char** text){
    int i = 0;
    if (text[0][0] == '^'){
        printf("%s\n", "text is empty");
    }
    else{
        while (text[i][0] != '^'){
            printf("%s\n", text[i]);
            i++;
        }
    }
}

char** case_0(){
    char** text;
    text = input();
    text = format_text(text);
    return text;
}

char** delete_el(char** text, int el){
    int i = el;
    while (text[i][0] != '^'){
        text[i] = text[i+1];
        i++;
    }
    return text;
}

char** case_1(){
    int i = 0;
    char* word = malloc(100);
    char** text;
    word = input_word();
    text = input();
    text = format_text(text);
    while (text[i][0] != '^') {
        if (delete_word(text[i], word)[0] == '\0'){
            text = delete_el(text, i);
            
        }
        else{
            text[i] = delete_word(text[i], word);
        }
        i++;
    }
    free(word);
    
    return text;
}

char** case_2(){
    char** text;
    int i = 0;
    text = input();
    text = format_text(text);
    while (text[i][0] != '^') {
        text[i] = uppercase_sort(text[i]);
        i++;
    }
    return text;
}

char** case_3(){
    int i = 0;
    char** text;
    text = input();
    text = format_text(text);
    while (text[i][0] != '^') {
        i++;
    }
    text = sorted_by_average(text,i);
    return text;
}

char** case_4(){
    int i = 0;
    char** text;
    text = input();
    text = format_text(text);
    while (text[i][0] != '^'){
        if (sentence_without_lowercase(text[i]) == 0){
            text = delete_el(text,i);
        }
        i++;
    }
    return text;
}


void case_9(){
    int i = 0;
    int dub_count;
    scanf("%d", &dub_count);
    char** text = input();
    char* new_text;
    
    while (text[i][0] != '^'){
        new_text = malloc((strlen(text[i])*(dub_count+1))*sizeof(char));
        

        strcpy(new_text, text[i]);
        new_text[strlen(new_text)-1] = '\0';
        for (int j = 0; j < dub_count-1; j++){
            strncat(new_text, " ", 1);
            strncat(new_text, text[i], strlen(text[i]));
            new_text[strlen(new_text)-1] = '\0';
        }
        new_text[strlen(new_text)] = '.';
        printf("%s\n",new_text);
        i++;
        free(new_text);
    }

}

int main() {
    printf("Course work for option 4.20, created by Andrei Dubinin. \n");
    char** inputted;
    int choice;
    int check_error;
    check_error = scanf("%d", &choice)-1;

    if (check_error){
        printf("Error: Wrong input format.\n");
    }
    else if (choice < 0 || choice > 9){
        printf("Error: Wrong task number.\n");
    }
    
    if (choice == 5){ 
        info();
        return 0;
    }
    
    
    switch(choice){
        case 0:
            inputted = case_0();
            return_text(inputted);
            break;
        case 1:
            inputted = case_1();
            return_text(inputted);
            break;
        case 2:
            inputted = case_2();
            return_text(inputted);
            break;
        case 3:
            inputted = case_3();
            return_text(inputted);
            break;
        
        case 4:
            inputted = case_4();
            return_text(inputted);
            break;
        case 9:
            case_9();
            break;
        
    }
    
    return 0;
} 
