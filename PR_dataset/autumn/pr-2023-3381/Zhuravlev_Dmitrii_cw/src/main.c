#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> //strcasecmp
#include <ctype.h>
#include <stdbool.h> 

#define HELP_MSG "После вывода информацию о варианте курсовой работе программа ожидает ввода пользователем числа – номера команды:\n0 – вывод текста после первичной обязательной обработки,\n1 – вызов функции под номером 1 из списка задания,\n2 – вызов функции под номером 2 из списка задания,\n3 – вызов функции под номером 3 из списка задания,\n4 – вызов функции под номером 4 из списка задания,\n5 – вывод справки о функциях, которые реализует программа.\n"
#define ERR_ALLOC "Error: error re/allocating memory"
#define ERR_COMMAND_DOES_NOT_EXIST "Error: Введенной команды не существует. (5 - вызов справки)\n"
#define FORBIDDEN_WORD "physics"

void print_error(char* err) {
	printf("%s", err);
	exit(1);
}

void print_help() {
	printf("%s", HELP_MSG);
}

// Comparison function for qsort
int compare ( const void *pa, const void *pb ) {
    const int *a = *(const int **)pa;
    const int *b = *(const int **)pb;
    if(a[1] == b[1])
        return a[0] - b[0];
    else
        return b[1] - a[1];
}

void reverse_sentence(char* str) {
    // Initialize left and right pointers
    int r = strlen(str) - 1, l = 0;
 
    // Traverse string from both ends until 'l' and 'r'
    while (l < r) {
        // Ignore special characters
        if (str[l] == ' ' || str[l] == '.'  || str[l] == ',' )
            l++;
        else if (str[r] == ' ' || str[r] == '.' || str[r] == ',')
            r--;
        // Both str[l] and str[r] are not special
        else {
            char temp = str[l];
            str[l] = str[r];
            str[r] = temp;
            // swap(str[l], str[r]);
            l++;
            r--;
        }
    }
}

void reverse_text(char** text, int len) {
	for (int i = 0; i < len; i++) {
		reverse_sentence(text[i]);
	}
}

int** count_3(char** text, int sent_count) {
	int** arr = (int**) malloc(sent_count * sizeof(int*)); // arr[номер предл][кол-во слов из 3 симв]
		if (arr == NULL) print_error(ERR_ALLOC);
		for (int i = 0; i < sent_count; i++)  {
			arr[i] = (int*) calloc(2, sizeof(int));
			if (arr[i] == NULL) print_error(ERR_ALLOC);
			arr[i][0] = i;
		}

	for (int i = 0; i < sent_count; i++) {
		int len = strlen(text[i]);
		int letters = 0;
		for (int j = 0; j < len; j++){
			if (isalpha(text[i][j]) || isdigit(text[i][j])) {
				letters += 1;
			} else {
				if (letters == 3) arr[i][1] += 1;
				letters = 0;
			}
		}
	}
	return arr;
}

void print_text(char** text, int len) {
	for (int i = 0; i < len; i++) {
		printf("%s\n", text[i]);
	}
}

void print_num_count(int* arr) {
	bool flag = false;
	for (int i = 0; i < 10; i++) {
		if (arr[i] > 0) {
			flag = true;
			printf("%d: %d\n", i, arr[i]);
		}
	}
	if (!flag)  printf("Текст не содержит цифр!\n");
}

void print_wo_word(char** text, int sent_count, char* word) {
	for (int i = 0; i < sent_count; i++) {
		if (!strstr(text[i], word)) printf("%s\n", text[i]);
	}
}

void print_sorted_text(char** text, int** sort_arr, int len) {
	for (int i = 0; i < len; i++) {
         printf("%s - %d\n", text[sort_arr[i][0]], sort_arr[i][1]);
    }
}

int* count_nums(char** text, int sent_count) {
	int* nums = (int*) calloc(10, sizeof(int));
	char ch;
	for (int i = 0; i < sent_count; i++) {
        for (int j = 0; j < strlen(text[i]); j++) {
        	ch = text[i][j];
        	if ( (ch-'0')>=0 && (ch-'0')<10 ) nums[(ch-'0')] += 1;
        }
    }
    return nums;
}

void print_doubled_text(char** text, int sent_count) {
	//char sent_end;
	for (int i = 0; i < sent_count; i++){
		text[i][strlen(text[i])-1] = 0;
		printf("%s %s.\n", text[i], text[i]);
	}
}

char** get_text(int* sent_count_addr) {
	int N = 10, M = 10;

	char** sentences = (char**) malloc(M * sizeof(char*));
	if (sentences == NULL) print_error(ERR_ALLOC);
	char* sentence = (char*) malloc(N * sizeof(char));
	if (sentence == NULL) print_error(ERR_ALLOC);

	char ch;
	int sent_count = *sent_count_addr;
	int chars = 0;
	char last_2[2] = { 0 };
	sentences[sent_count] = sentence;

	while (1) {
		ch = getchar();
		last_2[0] = last_2[1];
		last_2[1] = ch;
		if (last_2[0] =='\n' && last_2[1] =='\n') {
			sentences[sent_count][chars-1] = 0;
			if (chars-2>=0) sent_count+=1;
			*sent_count_addr = sent_count;

			return sentences;   //выход 
		}
		//Удаление пробельных символов и точек в начале строки
		if (chars == 0 && ch == '\t') continue;
		if (chars == 0 && ch == '\n') continue;
		if (chars == 0 && ch == ' ') continue;
		if (chars == 0 && ch == '.') continue;
		//if (ch == '\n') ch = ' ';                    //?????

		if (chars > N-2) {
			N += 10;
			sentence = (char*) realloc(sentence, sizeof(char)*N);
			if (sentence == NULL) print_error(ERR_ALLOC);
			sentences[sent_count] = sentence;
		}
		
		sentences[sent_count][chars] = ch;
		chars += 1;

		if (ch == '.') {
			sentences[sent_count][chars] = 0;
			bool flag = true;
			for (int i = 0; i < sent_count; i++) {
				if (!strcasecmp(sentences[i], sentences[sent_count])) {
					flag = false;
					break;
				}
			}
			if (flag) sent_count += 1; 
			else free(sentences[sent_count]);

			if (sent_count > M-2) {
				M += 10;
				sentences = (char**) realloc(sentences, sizeof(char*)*M);
				if (sentences == NULL) print_error(ERR_ALLOC);
			}

			N = 10;
			sentence = (char*) malloc(N * sizeof(char));
			if (sentence == NULL) print_error(ERR_ALLOC);
			sentences[sent_count] = sentence;
			chars = 0;
		}
	}
}

int main() {
	printf("Course work for option 4.7, created by Dmitrii Zhuravlev.\n");
	
	int input = -1;
	int sent_count = 0;
	char** text;
	scanf("%d", &input);

	switch(input){
	case 0:
		text = get_text(&sent_count);
		print_text(text, sent_count);
		break;
	case 1:
		text = get_text(&sent_count);
		int* nums = count_nums(text, sent_count);
		print_num_count(nums);
		break;
	case 2:
		text = get_text(&sent_count);
		reverse_text(text, sent_count);
		print_text(text, sent_count);
		break;	
	case 3:
		text = get_text(&sent_count);
		print_wo_word(text, sent_count, FORBIDDEN_WORD);
		break;
	case 4:
		text = get_text(&sent_count);
		int** arr_3 = count_3(text, sent_count); // arr[номер предл][кол-во слов из 3 симв]
        qsort(arr_3, sent_count, sizeof(arr_3[0]), compare); //сортировка по второму эл-ту
    	print_sorted_text(text, arr_3, sent_count);
		break;
	case 5:
		print_help();
		break;
	case 9:
		text = get_text(&sent_count);
		print_doubled_text(text, sent_count);
		break;
	default:
		print_error(ERR_COMMAND_DOES_NOT_EXIST);
	}

	return 0;
}