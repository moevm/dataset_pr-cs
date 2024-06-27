#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include <stdio.h>

struct Sentence{ 
    char *str; 
    int size; 
}; 
 
struct Text{ 
    struct Sentence **sents; 
    int n; 
    int size; 
};

long long int convert_date(char *date);
int get_min_date(char *sentence);
void print_earliest_latest_sentence(char *sentence);
int check_nineteen_century(char *word);
int check_word_year(char *word);
int check_sentence_year(char *sentence);
int check_sentence_nineteen(char *sentence);
int cmp_sents(char *first_sent, char *second_sent);
int check_double_n(char *sentence);
int cmp(const void *a, const void *b);
void print_earliest_latest(struct Text text);
void print_current_year(struct Text text);
void print_nineteen_century(struct Text text);
struct Sentence* read_sentence();
struct Text read_text();
int error_check(struct Text text);
void description();
void function_select();
void func9(struct Text text, char[100], char[100]);

int main(){
   description();
   function_select();
}

long long int convert_date(char *date) {
    long long int days = atoi(date);
    long long int months = atoi(date + 3);
    long long int years = atoi(date + 6);
    return days + 100*months + 10000*years;
}

int get_min_date(char *sentence) {
    char *processed_sentence = calloc(1, sizeof(char));
    processed_sentence = realloc(processed_sentence, (strlen(sentence)+1)*sizeof(char));
    strcpy(processed_sentence, sentence);
    int min;
    char *date;
    date = strtok(processed_sentence, " ");
    min = convert_date(date);
    while(1) {
        date = strtok(NULL, " ");
        if(date == NULL) break;
        if(convert_date(date) < min) min = convert_date(date);
    }
    return min;
}

void print_earliest_latest_sentence(char *sentence){
    int min;
    int max;
    char *date;
    date = strtok(sentence, " ");
    min = convert_date(date);
    max = convert_date(date);
    while(1) {
        date = strtok(NULL, " ");
        if(date == NULL) break;
        if(convert_date(date) > max) max = convert_date(date);
        if(convert_date(date) < min) min = convert_date(date);
    }
    int min_year = min/10000;
    int min_month = (min/100)%100;
    int min_day = min%100;
    int max_year = max/10000;
    int max_month = (max/100)%100;
    int max_day = max%100;
    printf("%.2d/%.2d/%.4d ", min_day, min_month, min_year);
    printf("%.2d/%.2d/%.4d.\n", max_day, max_month, max_year);
}

int check_nineteen_century(char *word){
    if((word[6] == '1')&&(word[7] == '8')) return 1;
    return 0;
}

int check_word_year(char *word) {
    if((word[3] == '1')&&(word[4] == '2')&&(word[6] == '2')&&(word[7] == '0')&&(word[8] == '2')&&(word[9] == '3')) return 1;
    return 0;
}

int check_sentence_year(char *sentence) {
    char *processed_sentence = calloc(1, sizeof(char));
    processed_sentence = realloc(processed_sentence, (strlen(sentence)+1)*sizeof(char));
    strcpy(processed_sentence, sentence);
    char *date;
    date = strtok(processed_sentence, " ");
    int checkbox = 0;
    if(check_word_year(date)) checkbox = 1;
    while(1){
        date = strtok(NULL, " ");
        if(date == NULL) break;
        if(check_word_year(date)) checkbox = 1;
    }
    return checkbox;
}

int check_sentence_nineteen(char *sentence) {
    char *processed_sentence = calloc(1, sizeof(char));
    processed_sentence = realloc(processed_sentence, (strlen(sentence)+1)*sizeof(char));
    strcpy(processed_sentence, sentence);
    char *date;
    date = strtok(processed_sentence, " ");
    int checkbox = 1;
    if(check_nineteen_century(date) == 0) checkbox = 0;
    while(1){
        date = strtok(NULL, " ");
        if(date == NULL) break;
        if(check_nineteen_century(date) == 0) checkbox = 0;
    }
    return checkbox;
}

int cmp_sents(char *first_sent, char *second_sent) { 
    int checkbox = 0; 
    if(strlen(first_sent)!=strlen(second_sent)) { 
        checkbox = 0; 
    } else{ 
        for(int i = 0; i < strlen(first_sent); i++) { 
            if(toupper(first_sent[i])!=toupper(second_sent[i])) { 
                checkbox = 0; 
                break; 
            } else checkbox = 1; 
        } 
    } 
    return checkbox; 
}

int check_double_n(char *sentence) {
    int checkbox = 0;
    for(int i = 0; i < strlen(sentence)-1; i++) {
        if((sentence[i] =='\n')&&(sentence[i+1] == '\n')) {
            checkbox = 1;
        }
    }
    return checkbox;
}

struct Sentence* read_sentence(){ 
    int size = 0; 
    char *buf = calloc(1, sizeof(char)); 
    char symbol = ' '; 
    char prev_symbol = 0; 
    int checkbox = 0; 
    while(isspace(symbol)){ 
  symbol = getchar(); 
        if((symbol == '\n')&&(prev_symbol == '\n')){ 
            checkbox = 1; 
            break; 
        } 
        prev_symbol = symbol; 
 } 
    if(checkbox == 1){ 
        buf = realloc(buf, 3*sizeof(char)); 
        buf[0] = '\n'; 
        buf[1] = '\n'; 
        buf[2] = '\0'; 
        struct Sentence *sentence = calloc(1, sizeof(struct Sentence)); 
        sentence->str = buf; 
        sentence->size = -1; 
        return sentence; 
    }  
    else{ 
        if(symbol == '.') { 
            buf = realloc(buf, 2*sizeof(char)); 
            buf[0] = '/'; 
            buf[1] = '\0'; 
            struct Sentence *sentence = calloc(1, sizeof(struct Sentence)); 
            sentence->str = buf; 
            sentence->size = -2; 
        } else { 
            while((symbol != '.')) { 
                if(size == 0) { 
           symbol = symbol; 
          } 
                else{ 
                    symbol = getchar(); 
          } 
          buf[size] = symbol; 
          size++; 
          buf = realloc(buf, (size + 1)*sizeof(char)); 
                if((symbol == '\n')&&(prev_symbol == '\n')) { 
                    break; 
                } 
          prev_symbol = symbol; 
            } 
            buf[size]= '\0'; 
            struct Sentence *sentence = calloc(1, sizeof(struct Sentence)); 
            sentence->str = buf; 
            sentence->size = size; 
            return sentence; 
            } 
        } 
	return NULL;
} 
 
struct Text read_text(){ 
    int size = 0; 
    struct Sentence** text= calloc(1, sizeof(struct Sentence*)); 
    int n=0; 
    struct Sentence* sentence; 
    int checkbox = 0; 
    int flag; 
    int Dublicate; 
    while(checkbox != 1){ 
        flag = 0; 
        sentence = read_sentence(); 
        if(check_double_n(sentence->str)){ 
            if(n == 0) printf("The text is entered incorrectly.\n"); 
            checkbox = 1; 
        } 
        else{ 
                for(int i = 0; i < n; i++){ 
                    Dublicate = cmp_sents(sentence->str, text[i]->str); 
                    if(Dublicate == 1) { 
                        Dublicate = 0; 
                        flag = 1; 
                        break; 
                    } 
                } 
                if(flag != 1){ 
                    text = (struct Sentence**) realloc(text, (n + 1)*sizeof(struct Sentence*)); 
                    size += sentence->size; 
                    text[n] = sentence; 
                    n++; 
                } 
        } 
    } 
    struct Text txt; 
    txt.size = size; 
    txt.sents = text; 
    txt.n = n; 
    return txt; 
}

int cmp(const void *a, const void *b) {
    struct Sentence *sentenceA = *(struct Sentence **)a;
    struct Sentence *sentenceB = *(struct Sentence **)b;
    int minA = get_min_date(sentenceA->str);
    int minB = get_min_date(sentenceB->str);
    if (minA < minB) {
        return -1;
    } else if (minA > minB) {
        return 1;
    } else {
        return 0;
    }
}

void print_earliest_latest(struct Text text) {
    for(int i = 0; i<text.n; i++) {
        print_earliest_latest_sentence(text.sents[i]->str);
    }
}

void print_current_year(struct Text text){
    for(int i = 0; i < text.n; i++) {
        if(check_sentence_year(text.sents[i]->str)) printf("%s\n", text.sents[i]->str);
    }
}

void print_nineteen_century(struct Text text){
    for(int i = 0; i < text.n; i++) {
        if(check_nineteen_century(text.sents[i]->str) == 0) printf("%s\n", text.sents[i]->str);
    }
}

int error_check(struct Text text){
    int checkbox = 0;
    for(int i = 0; i < text.n; i++){
        if(text.sents[i]->size == -2) checkbox = 1;
    }
    if(checkbox == 1) printf("Text entered incorrectly.\n");
    return checkbox;
}

void description() {
	printf("Course work for option 4.8, created by Perevalov Pasha.\n");
}

void function_select() {
    char num;
    char enter;
    scanf("%c%c", &num, &enter);
    switch(num){
        case('0'):{
            struct Text text = read_text();
            if(error_check(text) != 1){
                for(int i = 0; i < text.n; i++){
                    printf("%s\n", text.sents[i]->str);
                }
            }
            break;
        }
        case('1'):{
            struct Text text = read_text();
            if(error_check(text) != 1) print_current_year(text);
            break;
        }
        case('2'):{
            struct Text text = read_text();
            if(error_check(text) != 1){
                qsort(text.sents, text.n, sizeof(struct Sentence *), cmp);
                for(int i = 0; i < text.n; i++) {
                    printf("%s\n", text.sents[i]->str);
                }
            }
            break;
        }
        case('3'):{
            struct Text text = read_text();
            if(error_check(text) != 1) print_nineteen_century(text);
            break;
        }
        case('4'):{
            struct Text text = read_text();
            if(error_check(text) != 1) print_earliest_latest(text);
            break;
        }
        case('5'):{
            printf("Function number 0 displays the text after initial processing.\nFunction number 1 displays all sentences that contain a date with the current year and month.\nFunction number 2 sorts all sentences by increasing the minimum date in them.\nFunction number 3 removes all sentences in which all dates belong to the 19th century.\nFunction number 4 displays the earliest and latest date for each sentence.\n");
            break;
        }
        case('9'):{
            char X[100], Y[100];
            scanf("%s%s", X, Y);

            for(int i=0; i<strlen(X); i++){
                X[i] = tolower(X[i]);
            }

            struct Text text = read_text();
            func9(text, X, Y);
            break;
        }
        default:{
            printf("Error: the function number was entered incorrectly.\n");
        }
    }
}

void func9(struct Text text, char X[100], char Y[100]) {
    for (int i=0; i<text.n; i++) {
        char* sep = " .";
        char* token = strtok(text.sents[i]->str, sep);
        while (token != NULL) {
            
            char* copy = (char*) calloc(100, sizeof(char));
            strcpy(copy, token);
            for (int i=0; i<strlen(copy); i++) {
                copy[i] = tolower(copy[i]);
            }

            if (strcmp(copy, X) == 0) {
                printf("%s", Y);
            } else {
                printf("%s", token);
            }
            token = strtok(NULL, sep);
            if (token != NULL) {
                printf(" ");
            }
        }
        printf(".\n");
    }
}
