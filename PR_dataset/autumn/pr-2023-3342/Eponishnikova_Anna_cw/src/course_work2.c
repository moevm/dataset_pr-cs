#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BLOCK_SIZE 10
#define INFORMATION_ABOUT_FUNCTIONS "Help about functions:\n0 - Text output after the initial mandatory processing\n1 - Delete all the symbols at the beginning and end of the sentence so that in the end the first and last symbols of the sentence are different.\n2 - Sort all the words in a sentence in lexicographic order.\n3 - Delete all sentences in which at least one word is a palindrome.\n4 - Print all sentences that contain the word  HiddenTiger and which is not the first word.\n5 - Output help about the functions that the program implements.\n"
#define INDORMATION_ABOUT_COURSE_WORK "Course work for option 4.18, created by Anna Eponishnikova.\n"
#define STR_FOR_INPUT_TEXT &idx
#define STR_FOR_TEXT input_text,&amount_of_str,&idx
#define STR_FOR_TEXT_AFTER_CHANGE text,&amount_of_str, &amount_of_str_after
#define STR_FOR_FUNCTION text_after, &amount_of_str_after
#define STR_FOR_FREE text_after, &amount_of_str_after, text, &amount_of_str, input_text
#define SPACE_TIGER_SPACE " HiddenTiger "
#define SPACE_TIGER_POINT " HiddenTiger."
#define SPACE_TIGER_COMMA " HiddenTiger,"
#define COMMA_TIGER_COMMA ",HiddenTiger,"
#define COMMA_TIGER_POINT ",HiddenTiger."
#define COMMA_TIGER ",HiddenTiger"
#define STR_SIZE 121

char* get_text(int* idx){
    int capacity = BLOCK_SIZE;
    char symbol = getchar();
    char* input_text = (char*)malloc(capacity);
    if(input_text == NULL){
        fprintf(stderr,"Error: error reallocating memory\n");
    }
    int end_of_text = 0;
    while(1){
        if(symbol == '\n'){
            if(end_of_text == 1){
                break;
            }
            else{
                end_of_text = 0;
            }
        }
        else{
            end_of_text = 0;
        }
        if (symbol == '\n'){
            end_of_text = 1;
            symbol = getchar();
            continue;
        }
        input_text[(*idx)++] = symbol;
        if(*idx == capacity - 1){
            capacity += BLOCK_SIZE;
            input_text = (char*)realloc(input_text,capacity);
            if(input_text==NULL){
                fprintf(stderr,"Error: error reallocating memory\n");
            }

        }
        symbol = getchar();

    }
    if(input_text[(*idx)-1] != '.'){
        input_text = (char*)realloc(input_text, sizeof(char) * ((*idx) + 1));
        (*idx)++;
        input_text[*idx-1] = '.';
    }
    
    return input_text;
}

char** text_in_two_demencional_array(char* input_text, int* amount_of_str, int* idx){
    int sentences = 0;
    int amount_of_char = 0;
    int max_amount_of_char = 0;
    for(int i = 0; i<*idx; i++){
        if(input_text[i] == '.'){
           sentences++;
           amount_of_char++;
           if(amount_of_char>max_amount_of_char){
               max_amount_of_char = amount_of_char;
           }
           amount_of_char = 0;
        }
        else{
            amount_of_char++;
        }
    }
    char** text_before = (char**)malloc(sizeof(char*) * sentences);
    if(text_before == NULL){
        fprintf(stderr,"Error: error reallocating memory\n");
    }
    for(int i = 0; i<sentences; i++){
        text_before[i] = (char*)calloc(max_amount_of_char+2, sizeof(char));
        if(text_before[i] == NULL){
            fprintf(stderr,"Error: error reallocating memory\n");
        }
    }
    int  chr = 0;
    for(int i = 0; i<*idx; i++){
         if(chr == 0 && (input_text[i] == ' ' || input_text[i] == '\t' || input_text[i] == '\n' || input_text[i] == '.')){
            continue;
        }
        else{
            if(input_text[i] == '.'){
            text_before[*amount_of_str][chr] = input_text[i];
                text_before[*amount_of_str][chr+1] = '\0';
                (*amount_of_str)++;
                chr = 0;
            }
            else{
                text_before[*amount_of_str][chr] = input_text[i];
                chr++;
            }
        }
    }
    return text_before;
}

char** text_after_changes(char** text_before, int* amount_of_str, int* amount_of_str_after){
    char** text = (char**)malloc(sizeof(char*) * (*amount_of_str));
    if(text == NULL){
        fprintf(stderr,"Error: error reallocating memory\n");
    }
    for(int i = 0; i<*amount_of_str; i++){
        int same_symbol = 0;
        int same_sentences = 0;
        for(int j = 0; j<i; j++){
            if(strlen(text_before[i]) != strlen(text_before[j])){
                continue;
            }
            for(int l = 0; l<strlen(text_before[i]); l++){
                if(tolower(text_before[i][l]) != tolower(text_before[j][l])){
                    same_symbol = 1;
                }
            }
            if(same_symbol == 0){
                same_sentences = 1;
            }
        }
        if(same_sentences == 0){
            text[*amount_of_str_after] = text_before[i];

            (*amount_of_str_after)++;
        }
    }
    return text;
}
char* my_strdup(const char *src) {
    size_t len = strlen(src) + 1;
    char *dest = (char *)malloc(len);

    if (dest != NULL) {
        memcpy(dest, src, len);
    }

    return dest;
}

void first_function(char** text, int* amount_of_str_after) {
    for (int i = 0; i <*amount_of_str_after; i++) {
        int len = strlen(text[i]);

        if (len > 0 && text[i][len - 1] == '.') {
            text[i][len - 1] = '\0';
            len--;
        }

        while(len>0 && text[i][0] == text[i][len-1]){
            for(int j = 0; text[i][j]; j++){
                text[i][j] = text[i][j+1];
            }
            len-=2;
        }
        if(len>0){
            for(int k =0; k<len; k++){
                printf("%c", text[i][k]);
            }
            printf("\n");
        }

    }
}

int cmp_words(const void* first, const void* second){
    const char **first_word = (const char **)first;
    const char **second_word = (const char **)second;
    return strcmp(*first_word, *second_word);
}

void second_function(char** text, int* amount_of_str_after, int* count) {
    for (int i = 0; i < *amount_of_str_after; i++){
        int len = strlen(text[i]);
        int word_count = 1;
        for (int n = 0; n < len; n++) {
            if ((text[i][n] == ' ' || text[i][n] == ',') && (text[i][n + 1] != ' ' && text[i][n + 1] != ',')) {
                word_count++;
            }
        }
        char* words[word_count];
        char* sentence = my_strdup(text[i]);
        int length = 0;
        char sep[] = " ,.";
        char* word = strtok(sentence, sep);
        while (word != NULL) {
            words[length] = my_strdup(word);
            length++;
            word = strtok(NULL, sep);
        }
        qsort(words, length, sizeof(char*), cmp_words);
        for(int j = 0; j<length; j++){
            printf("%s ", words[j]);
        }
        printf("\n");
    }
}

int is_palindrom(const char* word){
    for(int i = 0; i<strlen(word)/2; i++){
        if (tolower(word[i]) != tolower(word[strlen(word) - 1 - i])){
            return 0;
        }
    }
    return 1;
}

void third_function(char** text, int* amount_of_str_after) {
    for(int i = 0; i<*amount_of_str_after; i++){
        int len=strlen(text[i]);
        if(len>0 && text[i][len-1] == '.'){
            text[i][len-1] = '\0';
            len--;
        }
        int flag = 0;
        char* sentence_copy = my_strdup(text[i]);
        char sep[] = " ,";
        char* word = strtok(sentence_copy, sep);
        while(word!=NULL){
            if(is_palindrom(word)){
                flag = 1;
            }
            word=strtok(NULL, sep);
        }

        if(flag == 0){
            for(int n = 0; n<len; n++){
                printf("%c", text[i][n]);
            }
            printf(".\n");
        }
        free(word);
    }
}
//Вывести на экран все предложения, в которых встречаются HiddenTiger.
void fourth_function(char** text, int* amount_of_str_after){
	for(int i = 0; i<*amount_of_str_after; i++){
		char* istr1 = strstr(text[i], SPACE_TIGER_SPACE);
		char* istr2 = strstr(text[i], SPACE_TIGER_POINT);
		char* istr3 = strstr(text[i], SPACE_TIGER_COMMA);
		char* istr4 = strstr(text[i], COMMA_TIGER_COMMA);
		char* istr5 = strstr(text[i], COMMA_TIGER_POINT);
		char* istr6 = strstr(text[i], COMMA_TIGER);
		if(istr1 != NULL || istr2 != NULL || istr3 != NULL || istr4 != NULL || istr5 != NULL || istr6 != NULL){
			puts(text[i]);
		}
	}
}

void fifth_function(){
	printf("%s",INFORMATION_ABOUT_FUNCTIONS);
}

char* read_sentence(){
    int capacity_of_str = STR_SIZE;
    char* input_sentence = (char*)malloc(sizeof(char) * capacity_of_str);
    fgets(input_sentence, STR_SIZE+1, stdin);
    return input_sentence;
}

void ninth_function(char** text, int* amount_of_str_after, char* input_sentence){
    int len_input_str = strlen(input_sentence); 
    input_sentence[len_input_str - 1] = '\0';
    int count_upper_symbols = 0;
    for(int i = 0; i<len_input_str; i++){
        if(isupper(input_sentence[i])){
            count_upper_symbols++;
        }
    }
    for(int x = 0; x<*amount_of_str_after; x++){
        int count_upper_symbols_in_str = 0;
        for(int y = 0; text[x][y]; y++){
            if(isupper(text[x][y])){
                count_upper_symbols_in_str++;
            }
        }
        if(count_upper_symbols_in_str<= count_upper_symbols){
            printf("%s\n", text[x]);
        }
    }
}

void free_memory(char** text, int* amount_of_str_after, char** text_before,int* amount_of_str, char* input_text){
    for(int i = 0; i<*amount_of_str_after; i++){
        text[i] = NULL;
        free(text[i]);
    }
    text = NULL;
    free(text);
    for(int j = 0; j<*amount_of_str; j++){
        text_before[j] = NULL;
        free(text_before[j]);
    }
    text_before = NULL;
    free(text_before);
}

void switch_case(int number){
    int amount_of_str = 0;
    int amount_of_str_after= 0;
    int idx = 0;
    int count = 0;
    char* input_text = NULL;
    char** text = NULL;
    char** text_after = NULL;
    char* input_sentence = NULL;
    switch(number){
        case 0:
            input_text = get_text(STR_FOR_INPUT_TEXT);
            text = text_in_two_demencional_array(STR_FOR_TEXT);
            text_after = text_after_changes(STR_FOR_TEXT_AFTER_CHANGE);
            for(int i = 0; i<amount_of_str_after; i++){
                printf("%s\n",text_after[i]);
            }
            free_memory(STR_FOR_FREE);
            break;
        case 1:
            input_text = get_text(STR_FOR_INPUT_TEXT);
            text = text_in_two_demencional_array(STR_FOR_TEXT);
            text_after = text_after_changes(STR_FOR_TEXT_AFTER_CHANGE);
            first_function(STR_FOR_FUNCTION);
            free_memory(STR_FOR_FREE);
            break;
        case 2:
            input_text = get_text(STR_FOR_INPUT_TEXT);
            text = text_in_two_demencional_array(STR_FOR_TEXT);
            text_after = text_after_changes(STR_FOR_TEXT_AFTER_CHANGE);
            second_function(STR_FOR_FUNCTION, &count);
            free_memory(STR_FOR_FREE);
            break;
        case 3:
            input_text = get_text(STR_FOR_INPUT_TEXT);
            text = text_in_two_demencional_array(STR_FOR_TEXT);
            text_after = text_after_changes(STR_FOR_TEXT_AFTER_CHANGE);
            third_function(STR_FOR_FUNCTION);
            free_memory(STR_FOR_FREE);
            break;
        case 4:
            input_text = get_text(STR_FOR_INPUT_TEXT);
            text = text_in_two_demencional_array(STR_FOR_TEXT);
            text_after = text_after_changes(STR_FOR_TEXT_AFTER_CHANGE);
            fourth_function(STR_FOR_FUNCTION);
            free_memory(STR_FOR_FREE);
            break;
        case 5:
            fifth_function();
            break;
	case 9:
            input_sentence = read_sentence();
            input_text = get_text(STR_FOR_INPUT_TEXT);
            text = text_in_two_demencional_array(STR_FOR_TEXT);
            text_after = text_after_changes(STR_FOR_TEXT_AFTER_CHANGE);
            ninth_function(STR_FOR_FUNCTION, input_sentence);
            free_memory(STR_FOR_FREE);
            break;
        default:
            printf("%s\n", "The entered data is incorrect");
    }
}

int main(){
    printf("%s",INDORMATION_ABOUT_COURSE_WORK);
    int number;
    scanf("%d\n", &number);
    switch_case(number);
    return 0;
}
