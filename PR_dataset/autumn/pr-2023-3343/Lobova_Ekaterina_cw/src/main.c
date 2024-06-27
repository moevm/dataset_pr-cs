#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#define RED "\033[0;31m"
#define NONE "\033[0;0m"
#define TEXT_SIZE 100
#define BLOCK 10
#define START_SENTENCE "Course work for option 4.5, created by Ekaterina Lobova."

void InputText(char **text){
    int size = TEXT_SIZE;
    char *buf = (char*)malloc(size*sizeof(char));
    int NotEnd = 1;
    int length = 0;
    char temp;
    do{
        if(length >= size-2){
            char *t = (char*)realloc(buf, size+TEXT_SIZE);
            size+=TEXT_SIZE;
            buf = t;
        }
        temp = getchar();
        if (temp == '\n' && length>0 && buf[length-1]=='\n')
            NotEnd = 0;
        buf[length]= temp;
        length++;
    }while(NotEnd);
    buf[length]= '\0';
    *text = buf;
}

int compareStrings(char* sentence_1, char* sentence_2) {
    for (int j = 0; j < strlen(sentence_1); j++){
	if (strlen(sentence_1) != strlen(sentence_2) || tolower(sentence_1[j]) != tolower(sentence_2[j])) {
	    return 1;
	}
    }
    return 0;
}

char** SplitSentences(char* text, int* count_sentence) {
    int len_text = strlen(text);
    int capacity = BLOCK;
    char** new_text = (char**)malloc(capacity * sizeof(char*));
    int sentence_start = 0;
    for (int i = 0; i < len_text; i++) {
        if (text[i] == '.' || (i==len_text-2 && text[i-1]!='.')) {
            text[i] = '.';
            while (text[sentence_start]==' ' || text[sentence_start]=='\n') sentence_start++;
            int len_sentence = i - sentence_start + 2;
            char* sentence = (char*)malloc((len_sentence) * sizeof(char));
            strncpy(sentence, text + sentence_start, len_sentence - 1);
            sentence[len_sentence-1] = '\0';
            int not_repeating = 1;
            for (int i = 0; i<(*count_sentence);i++){
                if (compareStrings(sentence,new_text[i])==0){
                    not_repeating = 0;
                    break;
                }
            }
            if (not_repeating) {
                if (*count_sentence >= capacity) {
                    capacity+=BLOCK;
                    new_text = (char**)realloc(new_text, capacity * sizeof(char*));
                }
                new_text[*count_sentence] = sentence;
                (*count_sentence)++;
            } else {
                free(sentence);
            }
            sentence_start = i + 1;
        }
    }
    return new_text;
}

void OutputText(char** splitted_text, int* number_sentences){
    for (int i = 0; i<(*number_sentences);i++){
        printf("%s\n",splitted_text[i]);
    }
}

void FreeMemory(char** splitted_text, char** text,int* number_sentences){
    for (int i = 0; i<(*number_sentences);i++){
        free(splitted_text[i]);
    }
    free(text);
    free(splitted_text);
}

int IsValidDate(const char *date_str) {
    int year, month, day;
    if (sscanf(date_str, "%d/%d/%d", &day, &month, &year) != 3) {
        return 0; 
    }
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return 0; 
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return 0; 
        }
    } else if (month == 2) {
        int is_leap_year = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
        if ((is_leap_year && day > 29) || (!is_leap_year && day > 28)) {
            return 0; 
        }
    }
    return 1; 
}

int DateNotArrived(char* date){
    time_t current_time;
    struct tm* timeinfo;
    time(&current_time);
    timeinfo = localtime(&current_time);
    int current_day = timeinfo->tm_mday;
    int current_month = timeinfo->tm_mon + 1;
    int current_year = timeinfo->tm_year + 1900;
    int year, month, day;
    sscanf(date, "%d/%d/%d", &day, &month, &year);
    if (current_year < year) return 1;
    if (current_year == year){
        if (current_month < month) return 1;
        if (current_month == month){
            if (current_day < day) return 1;
            return 0;
        }
        return 0;
    }
    return 0;    
}
void FindDate(char** text, int* number_sentences){
    int date_index;
    int index_cur;
    int length_sentence;
    for (int i = 0; i<(*number_sentences); i++){
    	date_index = -1;
    	index_cur = 0;
    	length_sentence = strlen(text[i]);
    	if (length_sentence <= 10) continue;
    	while (index_cur<strlen(text[i])-10){
    	    if (isdigit(text[i][index_cur])){
    	        char date[11];
    	        date[0] = text[i][index_cur];
    	        for (int k = 1; k<10; k++) date[k] = text[i][index_cur+k];
    	        date[10]='\0';
    	    	if (IsValidDate(date)){
    	    	    if (date_index == -1){
    	    	        for (int k = 0 ; k<index_cur; k++) printf("%c",text[i][k]);
    	    	    }
    	    	    if (DateNotArrived(date)){
    	    	        printf(RED);	
    	    	        printf("%s",date);
    	    	        printf(NONE);
    	    	    } else printf("%s",date);
    	    	    date_index = index_cur;
    	    	    index_cur+=10;
    	        } else{
    	            if (date_index != -1) printf("%c", text[i][index_cur++]);
    	            else index_cur++;
    	        } 
    	    } else {
    	        if (date_index != -1) printf("%c", text[i][index_cur++]);
    	        else index_cur++;
    	    } 	        
    	}
    	if (date_index != -1){
    	    while (text[i][index_cur]!='\0') printf("%c", text[i][index_cur++]);
    	    printf("\n");
    	}
    }
}

int OddNumberLetters(char* word){
    int number_letters = 0;
    for (int i = 0; i<strlen(word); i++){
        if (isalpha(word[i])) number_letters++;
    }
    return number_letters % 2;
}

void Deleting_Sentences_With_Odd_Number_Letters(char** text, int* number_sentences){
    int starting_number_sentences = *number_sentences;
    int index = 0;
    for (int i = 0; i<(starting_number_sentences); i++){
        int all_words_correct = 1;
        size_t len_sentence = strlen(text[i-index]);
        char* sentence = (char*)malloc((len_sentence) * sizeof(char));
        strncpy(sentence, text[i-index], len_sentence);
        char* word = strtok(sentence," ,.");
        while (word!= NULL){
            if (!OddNumberLetters(word)) {
                all_words_correct = 0;
                break;
            }
            word = strtok(NULL, " ,.");
        }
        if (all_words_correct){
            free(text[i-index]);
            for (int j = i-index; j<(*number_sentences) - 1; j++){
                text[j]=text[j+1];
            }
            index++;
            (*number_sentences)--;
        }
    }
}


int CounterLetters(char* word){
    int counter = 0;
    for (int i = 0; i<strlen(word); i++){
        if (isalpha(word[i])) counter++;
    }
    return counter;
}

void ModifySentence(char** text, int* number_sentences){
    for (int i = 0; i<(*number_sentences); i++){
        char* sentence = (char*)malloc(strlen(text[i])+1);
        memcpy(sentence, text[i], strlen(text[i])+1);
        char* word;
        int was_first_word = 0;
        int index_cur = 0;
        while (text[i][index_cur]!='\0'){
            if (strchr(" .,",text[i][index_cur]) == NULL){
                if (was_first_word) word = strtok(NULL," ,.");
                else{
                    word = strtok(sentence," ,.");
                    was_first_word = 1;
                }
                index_cur+=strlen(word);
                int counter_letters = CounterLetters(word);
                if (counter_letters>0){
                    printf("%d%s", counter_letters, word);
                } else {
                    printf("%s", word);
                }
            } else{
                printf("%c", text[i][index_cur]);
                index_cur++;
            }    
        }
        printf("\n");
        free(sentence);
    }
}

char* LastWord(char* sentence){
    char* word = strtok(sentence," ,.");
    char* last_word = NULL;
    while (word!= NULL){
        last_word = word;
        word = strtok(NULL, " ,.");
    }
    return last_word;
}

int compar(const void *a, const void *b){
    char* sentence1 = *((char**) a);
    char* first = (char*)malloc(strlen(sentence1)+1);
    memcpy(first, sentence1, strlen(sentence1)+1);
    char* sentence2 = *((char**) b);
    char* second = (char*)malloc(strlen(sentence1)+1);
    memcpy(second, sentence2, strlen(sentence2)+1);
    char* last_word1 = LastWord(first);
    char* last_word2 = LastWord(second);
    size_t length1 = strlen(last_word1);
    size_t length2 = strlen(last_word2);
    return length1 - length2;
}

void Sort(char** text, int* number_sentences){
    qsort(text, *number_sentences, sizeof(char*), compar);
}

void decimalToBinary(int decimal) {
if(decimal == 0) {
    printf("0");
    return; 
}

int binary[32], i = 0;

while(decimal > 0) {
    binary[i] = decimal % 2;
    decimal = decimal / 2;
    i++;
}
for(int j = i - 1; j >= 0; j--) {
    printf("%d", binary[j]);
}
}

void Bin(char** text, int* number_sentences){
    int index = 0;
    long dec;
    for (int i = 0; i<(*number_sentences); i++){
        char* digits = (char*)malloc(sizeof(char)*strlen(text[i]));
        for (int j = 0; j<strlen(text[i]); j++){
            if (isdigit(text[i][j])){
                digits[index++] = text[i][j];
            } else {
                if (index>0){
                    digits[index] = '\0';
                    dec = strtol(digits, NULL, 10);
                    printf("0b");
                    decimalToBinary(dec);
                    index = 0;
                    printf("%c", text[i][j]);
                } else {
                    printf("%c", text[i][j]);
                }
            }
        }
        free(digits);
        printf("\n");
    }
}
int main()
{ 
    printf("%s\n",START_SENTENCE);
    char command;
    scanf("%c", &command);
    
    char **text = (char**)malloc(sizeof(char*));
    int number_sentences = 0;
    char **splitted_text;

    switch (command) {
        case '0':
            InputText(text);
            splitted_text = SplitSentences(*text, &number_sentences);
            OutputText(splitted_text, &number_sentences);
            FreeMemory(splitted_text, text, &number_sentences);
            break;
        case '1':
            InputText(text);
            splitted_text = SplitSentences(*text, &number_sentences);
            FindDate(splitted_text, &number_sentences);
            FreeMemory(splitted_text, text, &number_sentences);
            break;   
        case '2':
            InputText(text);
            splitted_text = SplitSentences(*text, &number_sentences);
            Deleting_Sentences_With_Odd_Number_Letters(splitted_text,&number_sentences);
            OutputText(splitted_text, &number_sentences);
            FreeMemory(splitted_text, text, &number_sentences);
            break;
        case '3':
            InputText(text);
            splitted_text = SplitSentences(*text, &number_sentences);
            ModifySentence(splitted_text, &number_sentences);
            FreeMemory(splitted_text, text, &number_sentences);
            break; 
        case '4':
            InputText(text);
            splitted_text = SplitSentences(*text, &number_sentences);
            Sort(splitted_text, &number_sentences);
            OutputText(splitted_text, &number_sentences);
            FreeMemory(splitted_text, text, &number_sentences);
            break;
        case '9':
            InputText(text);
            splitted_text = SplitSentences(*text, &number_sentences);
            Bin(splitted_text, &number_sentences);
            FreeMemory(splitted_text, text, &number_sentences);
            break;
        case '5':
            printf("%s\n%s\n%s\n%s\n%s\n%s\n",
		"0 – Вывод текста после первичной обязательной обработки",
		"1 – Вывести все предложения в которых есть даты в формате “DD/MM/YYYY”, даты которые еще не наступили надо выделить красным цветом.",
		"2 – Удалить все предложения в которых каждое слово содержит нечетное количество букв.",
		"3 – Преобразовать предложения так, чтобы перед каждым словом стояло количество букв в нем.",
		"4 – Отсортировать предложения по возрастанию длины последнего слова",
		"5 – Вывод справки о функциях, которые реализует программа.");
		break;
	default:
	    printf("Error: incorrect command input\n");
	    break;
    }
    return 0;
}

