#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RED "\033[1;31m%s\033[0m"

char* remove_symbol_before(char* sentence);
int compare_sentence(char* sentence1, char* sentence2);
int compare_number_in_sentence(const void* a, const void* b);
void printRed(char* words);
void printText(char** text, int* all_text);
void freeMemory(char** text, int* all_text);
void printAuthor();
void printInfo();

void replace_flower_words(char** text, int* all_text) {
	int len_flower = strlen("flower");

	int count_flower = 0;
	for (int i = 0; i < (*all_text); i++) {
		char* sentence = text[i];
		char* word = sentence;

	while (*word) {
            if (strncmp(word, "flower", len_flower) == 0 && (word[len_flower] == '\0' || word[len_flower] == ' ' ||
                word[len_flower] == ',' || word[len_flower] == '.')) count_flower++;

            while (*word && *word != ' ' && *word != ',' && *word != '.') word++;

            while (*word && (*word == ' ' || *word == ',' || *word == '.')) word++;
        }
    }
      
    for (int i = 0; i < (*all_text); i++) {
        text[i] = realloc(text[i], strlen(text[i]) + count_flower + 1);
        if (!text[i]) {
            printf("Error: Ошибка расширения памяти в replace_flower_words.\n");
            exit(0);
        }
        char* sentence = text[i];
        char* word = sentence;

        while (*word) {
            if (strncmp(word, "flower", len_flower) == 0 && (word[len_flower] == '\0' || word[len_flower] == ' ' ||
                word[len_flower] == ',' || word[len_flower] == '.')) {

                memmove(word + strlen("planted"), word + len_flower, strlen(word + len_flower) + 1);
                memcpy(word, "planted", strlen("planted"));
                word += strlen("planted");
            }

            while (*word && *word != ' ' && *word != ',' && *word != '.') word++;

            while (*word && (*word == ' ' || *word == ',' || *word == '.')) word++;
}}}

void students_in_red(char** text, int* all_text) {
    int len_student = strlen("student");
    int student_count = 0;

    for (int i = 0; i < (*all_text); i++) {
        char* word = text[i];

        while (*word) {
            char* position = strstr(word, "student");

            if (position && (*(position + len_student) == ' ' || *(position + len_student) == ',' || *(position + len_student) == '.')) {
                while (word != position) {
                    putchar(*word);
                    word++;
                }
                printRed("student");
                student_count++;
                word += len_student;
            
            } else {
                while (*word && *word != ' ' && *word != ',' && *word != '.') {
                    putchar(*word);
                    word++;
                }
            }
            while (*word && (*word == ' ' || *word == ',' || *word == '.')) {
                putchar(*word);
                word++;
            }
        }
        printf(" %d\n", student_count);
        student_count = 0;
}}

void remove_friends(char** text, int* all_text) {
    for (int i = 0; i < (*all_text); i++) {
        char* sentence = text[i];
        char* copy = malloc(strlen(text[i]) + 1);

        if (!copy) {
            printf("Error: Ошибка выделения памяти в remove_friends\n");
            exit(0);
        }
        strncpy(copy, sentence, strlen(sentence) + 1);

        char* word = strtok(copy, " ,.");
        int friend_count = 0;

        while (word != NULL) {
            if (strcmp(word, "friend") == 0) {
                friend_count++;
                if (friend_count > 1) {
                    free(copy);
                    goto next;
                }
            }
            word = strtok(NULL, " ,.");
        }

        printf("%s\n", sentence);
        free(copy);

    next:
        continue;
}}

int max_num(char* sentence) {
    int max_num = 0;
    char* word = sentence;

    while (*word) {
        while (*word && !isdigit(*word)) word++;

        if (*word) {
            int current = atoi(word);
            if (current > max_num) max_num = current;
            while (*word && isdigit(*word)) word++;
        }
    }
    return max_num;
}

void delete_sentence(char** text, int* all_text, char* sentence_in) {
	int upper_count = 0;
	for(int i = 0; i < strlen(sentence_in); i++) {
		if (sentence_in[i] >= 65 && sentence_in[i] <= 90) upper_count++;
	}
	for (int i = 0; i < (*all_text); i++) {
		int upper = 0;
		char* sentence = text[i];
		for (int j = 0; j < strlen(sentence); j++) {
			if (sentence[j] >= 65 && sentence[j] <= 90) upper++;
		}
		if (upper <= upper_count) printf("%s\n",sentence);
	}	
}

void choice_option(char** text, int option, int* all_text, char* sentence_in) {
    switch (option) {
        case 0:
            printText(text, all_text);
            freeMemory(text, all_text);
            break;
        case 1:
            replace_flower_words(text, all_text);
            printText(text, all_text);
            freeMemory(text, all_text);
            break;
        case 2:
            students_in_red(text, all_text);
            freeMemory(text, all_text);
            break;
        case 3:
            remove_friends(text, all_text);
            freeMemory(text, all_text);
            break;
        case 4:
            qsort(text, *all_text, sizeof(char*), compare_number_in_sentence);
            printText(text, all_text);
            freeMemory(text, all_text);
            break;
        case 9:
			delete_sentence(text, all_text, sentence_in);
			free(sentence_in);
			freeMemory(text, all_text);
			break;
		default:
			printf("Error: Некорректная опция. Введите целое число от 0 до 5.\n");
        	printf("Введите 5 для вызова справки.\n");
        	exit(0);	    
}}

char** readText(int* all_text) {
    char** text = (char**)malloc(sizeof(char*));

    if (!text) {
        printf("Error: Ошибка выделения памяти в readText для текста.\n");
        exit(0);
    }
    
    int endText = 0;
    while (1) {
        char* sentence = (char*)malloc(sizeof(char));
        char symbol = ' ';
        int count_symbol = 0;

        while (symbol != '.') {
            symbol = getchar();

            if (symbol == '\n') endText++;
            else endText = 0;
            if (endText == 2) break;

            sentence[count_symbol++] = symbol;
            sentence = (char*)realloc(sentence, sizeof(char) * (count_symbol + 1));
        	if (!sentence) {
            printf("Error: Ошибка расширения памяти в readText для предложения.\n");
            exit(0);
        	}
        }
		if (sentence[count_symbol - 1] != '.') sentence[count_symbol - 1] = '.';
        
        sentence[count_symbol] = '\0';
        remove_symbol_before(sentence);
		
        int duplicate = 0;
        for (int i = 0; i < *all_text; i++) {
            if (compare_sentence(sentence, text[i])) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate && (*sentence) != '.') {
            text[(*all_text)++] = sentence;
            text = (char**)realloc(text, sizeof(char*) * ((*all_text) + 1));
        	if(!text) {
				printf("Error: Ошибка расширения памяти в readText для предложения.\n");
				exit(0);
			}
        }
        if (endText == 2) break;
    }
    return text;
}

int main() {
    printAuthor();
	
	char* sentence_in = (char*)malloc(121);
    
    int option;
    scanf("%d\n", &option);
    if (option == 5) printInfo();
	if (option == 9) fgets(sentence_in, 121, stdin);
	
    int all_text = 0;
    char** text = readText(&all_text);

    /*if (all_text == 0 || all_text == 1) {
        printf("Error: Нет текста для обработки.\n");
        exit(0);
    }*/
    choice_option(text, option, &all_text, sentence_in);

    return 0;
}

char* remove_symbol_before(char* sentence) {
    int count = 0;

    while (sentence[count] == ' ' || sentence[count] == '\t' || sentence[count] == '\n') count++;
    if (count > 0) memmove(sentence, sentence + count, strlen(sentence) - count + 1);

    return sentence;
}

int compare_sentence(char* sentence1, char* sentence2) {
    int i = 0;

    while (sentence1[i] && sentence2[i]) {
        if (tolower(sentence1[i]) != tolower(sentence2[i])) return 0;
        i++;
    }
    return sentence1[i] == '\0' && sentence2[i] == '\0';
}

int compare_number_in_sentence(const void* a, const void* b) {
    char* str_a = *(char**)a;
    char* str_b = *(char**)b;

    int num_a = max_num(str_a);
    int num_b = max_num(str_b);

    return num_b - num_a;
}

void printRed(char* words) {
    printf(RED, words);
}

void printText(char** text, int* all_text) {
    for (int i = 0; i < (*all_text); i++) printf("%s\n", text[i]);
}

void freeMemory(char** text, int* all_text) {
    for (int i = 0; i < (*all_text); i++) free(text[i]);
    free(text);
}

void printAuthor() {
    printf("Course work for option 4.15, created by Roman Kuznetsov.\n");
}

void printInfo() {
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("Опции программы:\n");
    printf("\t0 - Вывод текста после первичной обработки\n");
    printf("\t1 - В каждом предложении заменить все слова “flower” на “planted”.\n");
    printf("\t2 - Для каждого предложения посчитать количество слов “student” \n");
    printf("\tи вывести количество посчитанных слов и само предложение выделив слова “student” ");
    printRed("красным цветом.");
    printf(".\n");
    printf("\t3 - Удалить все предложения в которых слово “friend” встречается больше одного раза.\n");
    printf("\t4 - Отсортировать предложения по уменьшению максимального числа в строке. Число - слово состоящее только из цифр.\n");
    printf("\tЕсли в предложении нет числа, то для такого числа значение максимального числа равно 0.\n");
    printf("\t5 - Справка о возможностях программы\n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    exit(0);
}

