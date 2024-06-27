#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#define BLOCK 20

//добавление строки
char** addLine(char** text, int* capacity, int* lastIndex, char* sentence) {
    if (*lastIndex >= *capacity) {
        *capacity += 1;
        char** check = (char**)realloc(text, *capacity * sizeof(char*));
        if (!check){
            printf("Error: ошибка выделения памяти");
            exit(1);
        }
        text = check;
    }
    text[*lastIndex] = malloc((strlen(sentence) + 1) * sizeof(char));
    strcpy(text[*lastIndex], sentence);
    (*lastIndex)++;
    return text;
}

//добавление символа
char* addChar(char* line, int* capacity, int* lastIndex, char c) {
    if (*lastIndex >= *capacity){
        *capacity += BLOCK;
        char* check = realloc(line, *capacity * sizeof(char));
        if (!check){
            printf("Error: ошибка выделения памяти");
            exit(1);
        }
        line = check;
    }
    line[*lastIndex] = c;
    (*lastIndex)++;
    return line;
}

char** get_text(int* index){
    char** text = (char**)malloc(1 * sizeof(char*));
    int capacity = 0;
    int lastIndex = 0;
    char* currentLine = (char*)malloc(1 * sizeof(char));
    int currentCapacity = 0;
    int currentLastIndex = 0;
    char b = ' ';
    char c = ' ';

    while (1){
        c = getchar();
        if (c=='\n' && b=='\n'){
            free(currentLine);
            break;
        }
        b = c;
        if (currentLastIndex == 0 && isspace(c)){
            continue;
        }
        if (c=='\n'){
            free(currentLine);
            currentLine = malloc(1 * sizeof(char));
            continue;
        }
        currentLine = addChar(currentLine, &currentCapacity, &currentLastIndex, c);
        if (c == '.') {
            currentLine = addChar(currentLine, &currentCapacity, &currentLastIndex, '\0');
            text = addLine(text, &capacity, &lastIndex, currentLine);
            free(currentLine);
            currentLine = malloc(1 * sizeof(char));
            currentCapacity = 1;
            currentLastIndex = 0;
            }
    }
    
    char **textNew = (char**)malloc((capacity) * sizeof(char*));
    
    *index = 0;
    int flag = 1;

    for (int i = lastIndex - 1; i >= 0; i--) {
        if (i == 0) {
            textNew[*index] = (char*)malloc(strlen(text[i]) + 1);
            strcpy(textNew[*index], text[i]);
        }
        else for (int j = i - 1; j >= 0; j--) {
            if (strcasecmp(text[i], text[j]) == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            textNew[*index] = (char*)malloc(strlen(text[i]) + 1);
            strcpy(textNew[*index], text[i]);
            (*index)++;
        }
        flag = 1;
    }
 
    for (int i = 0; i < capacity; i++) { 
        free(text[i]); 
    } 
    free(text);
    
    for (int i = (*index); i < capacity; i++) { 
        free(textNew[i]);
    } 
    int start = 0;
    int end = (*index-1);
    while (start < end) { //разворот массива
        char *temp = textNew[start];
        textNew[start] = textNew[end];
        textNew[end] = temp;
        start++;
        end--;
    }
    return textNew;
}

//вывести и освободить память
void print_and_free_memory(char *sentence){
    printf("%s\n", sentence);
    free(sentence);
}

//счётчик кол-ва слов
int words_count(char* sentence){
	int counter = 1;
	for (int i = 1; sentence[i] != '\0'; i++){
	    if ((isspace(sentence[i-1])&&(!isspace(sentence[i])&&sentence[i]!=','&&sentence[i]!='.')) || (sentence[i-1]==',' && !isspace(sentence[i]))){
                counter++;
        }
	}
	return counter;
}

//удалить чётные предложения с чётными словами
void even_even(char** text, int index){ 
    for(int i=0;i<index;i++){
        int counter = words_count(text[i]);
        if ((i%2)==0 || (counter%2)!=0){
            puts(text[i]);
        }
        free(text[i]);
    }
    free (text);
}

//сравнение двух слов для функции qsort
int compare_upper(const void *a, const void *b){
    char *word1 = *(char**)a;
    char *word2 = *(char**)b;
    int upper1 = 0, upper2 = 0;
    
    for (int i = 0; i < strlen(word1); i++) {
        if (isupper(word1[i])) {
            upper1++;
        }
    }

    for (int i = 0; i < strlen(word2); i++) {
        if (isupper(word2[i])) {
            upper2++;
        }
    }
    return upper1 - upper2;
}

//сортировка по кол-ву заглавных букв
void upper_sort(char** text, int index) {
	for (int i = 0; i < index; i++){
		int num_words = words_count(text[i]);
		char** splitters = calloc(num_words, sizeof(char*));
		splitters[0] = calloc(BLOCK, sizeof(char));
		int current_splitter = 0;
		int splitter_capacity = BLOCK;
		for (int j = 0; j < strlen(text[i]); j++){
			int counter = 0;
			if (isspace(text[i][j]) || text[i][j] == ',') {
				while (isspace(text[i][j]) || text[i][j] == ','){
					splitters[current_splitter] = addChar(splitters[current_splitter], &splitter_capacity, &counter, text[i][j]);
					j++;
				}
				splitter_capacity = BLOCK;
				splitters[current_splitter][counter] = '\0';
				if (current_splitter < num_words - 1) {
					current_splitter++;
					splitters[current_splitter] = calloc(BLOCK, sizeof(char));
				}
			}
		}
		char** words = malloc(num_words * sizeof(char*));
		char* word =  calloc(2, sizeof(char));
		int word_counter = 0;
		int word_capacity = 1;
		int word_index = 0;

		for (int j = 0; j< strlen(text[i]); j++){
		    if(!isspace(text[i][j])&&text[i][j]!=','&&text[i][j]!='.'){
			    word = addChar(word, &word_capacity, &word_index, text[i][j]);
		    }
			else if (word[0]!='\0'){
			    word = addChar(word, &word_capacity, &word_index, '\0');
			    words[word_counter] = malloc((strlen(word)+1) * sizeof(char));
			    strcpy(words[word_counter], word);
			    free(word);
			    word =  calloc(2,sizeof(char));
			    word_capacity = 1;
        		word_index = 0;
        		word_counter++;
			}
		}
		qsort(words, num_words, sizeof(char*), compare_upper);
		for (int k = 0; k < num_words; k++) {
			printf("%s", words[k]);
			if (splitters[k]!=NULL)
				printf("%s", splitters[k]);
		}
		printf(".\n");
		for (int i = 0; i < current_splitter + 1; i++){
            free(splitters[i]);
        }
		free(splitters);
		for (int i = 0; i < num_words; i++){
			free(words[i]);
		}
		free(words);
	}
	for (int i = 0; i < index; i++){
			free(text[i]);
	}
	free(text);
}

//меньше трёх букв в слове
void less_then_3(char** text, int index){
    for(int i=0;i<index;i++){
        int str_capacity = strlen(text[i]) + words_count(text[i])*11;
        int str_last_index = 0;
        int counter = 0;
        char* cur_line = malloc((strlen(text[i]) + words_count(text[i])*11) * sizeof(char));
        for(int k=0;text[i][k]!='\0';k++){
            if (k!=0){
                if ((isspace(text[i][k-1])&&isspace(text[i][k]))){
                    continue;
                }
                if (isspace(text[i][k])&&text[i][k-1]==','){
                cur_line = addChar(cur_line, &str_capacity, &str_last_index, text[i][k]);
                continue;
                }
            }
            if (isspace(text[i][k]) || text[i][k]=='.' || text[i][k]==','){
                if (counter<3){
                    int str_rewrite = str_last_index - counter;
                    cur_line[str_rewrite] = '\0';
                    strcat(cur_line, "Less Then 3");
                    str_last_index+=(11-counter);
                }
                cur_line = addChar(cur_line, &str_capacity, &str_last_index, text[i][k]);
                counter=0;
            }
            else{
                counter++;
                cur_line = addChar(cur_line, &str_capacity, &str_last_index, text[i][k]);
            }
        }
        cur_line = addChar(cur_line, &str_capacity, &str_last_index, '\0');
        print_and_free_memory(cur_line);
    }
    for (int i = 0; i < index; i++){
		free(text[i]);
	}
	free(text);
}

//сравнение двух строк по длине
int compare_str(const void *a, const void *b){
    char *str1 = *(char**)a;
    char *str2 = *(char**)b;
    return strlen(str2) - strlen(str1);
}

//подстроки с цифрами
void digits_str(char** text, int index){
    char** result = malloc(index * sizeof(char*));
    int result_index = 0;
    int result_capacity = index;
    
    for(int k = 0; k<index;k++){
        int str_capacity = strlen(text[k]);
        int str_lastIndex = 0;
        char* cur_line = malloc((strlen(text[k])+1) * sizeof(char));
        int memory[2];
        int counter = 0;
        for(int i = 0; text[k][i]!='\0';i++){
            if (isdigit(text[k][i])){
                counter++;
            }
        }
        if (counter<=1){
            continue;
        }
        int new_counter = 0;
        for(int i = 0; text[k][i]!='\0';i++){
            if (isdigit(text[k][i])){
                new_counter++;
                if (new_counter==1){
                    memory[0] = i;
                }
                if (new_counter==counter){
                    memory[1] = i;
                    break;
                }
            }
        }
        for(int i = memory[0]; i<memory[1] + 1;i++){
            cur_line = addChar(cur_line, &str_capacity, &str_lastIndex, text[k][i]);
        }
        cur_line = addChar(cur_line, &str_capacity, &str_lastIndex, '\0');
        result = addLine(result, &result_capacity, &result_index, cur_line);
        free(cur_line);
    }
    qsort(result, result_index, sizeof(char*), compare_str);
    for(int j=0;j<result_index;j++){
        print_and_free_memory(result[j]);
    }
    for(int i=0;i<index;i++){
        free(text[i]);
    }
    free(text);
}

void more_one(char** text, int index, char* rstr){
    for(int i=0;;i++){
            if(rstr[i]=='\n'){
                rstr[i]='\0';
                break;}        
    }
    for(int n=0; n<((index+1)/2); n++){
        text[n][strlen(text[n])-1] = '\0';
        printf("%s %s %s", text[n], rstr, text[index-n-1]);
        if (text[n]==text[index-n-1]){
            printf(".");
        }
        else
            printf("\n");
    }
}

//основная функция
int main() {
    printf("Course work for option 4.23, created by Sofiya Skryabina\n");
    int value;
    int index = 0;
    scanf("%d", &value);
    getchar();

    switch(value){
    case 0:{
        char** text = get_text(&index);
        for (int i = 0; i < index; i++) {
            print_and_free_memory(text[i]);
        }
        free(text);
		break;
	}
	case 1:{
		char** text = get_text(&index);
        even_even(text, index);
		break;
	}
	case 2:{
	    char** text = get_text(&index);
		upper_sort(text, index);
	   	break;
	}
	case 3:{
		char** text = get_text(&index);
		less_then_3(text, index);
		break;
	}
	case 4:{
		char** text = get_text(&index);
		digits_str(text, index);
		break;
	}
	case 5:{
	    printf("0 – Вывод текста после первичной обязательной обработки.\n1 – Удалить все четные по счету предложения в которых четное количество слов.\n2 – Отсортировать все слова в предложениях по возрастанию количества букв в верхнем регистре в слове.\n3 – Заменить все слова в тексте длина которых не более 3 символов на подстроку “Less Then 3”.\n4 – Найти в каждом предложении строку максимальной длины, которая начинается и заканчивается цифрой. Вывести найденные подстроки по убыванию длины подстроки.\n");
	    break;
	}
	case 9:{
	    char buff[101];
            char* new_str = fgets(buff, 100, stdin);
	    char** text = get_text(&index);
	    more_one(text, index, new_str);
	    break;
	}
	default:{
		printf("Error: неизвестная команда\n");
	}
    }
    return 0;
}
