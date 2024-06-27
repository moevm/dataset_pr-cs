#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define INF_ABOUT_STaW "Course work for option 4.6, created by Kseniya Kopasova\n"
#define LEN_TEXT 100

//объявляем все функции

void file_help();
void text_print_func(char** splitted_text, int output_numb);
char* text_input_func();
char** split_text_func(char* text, char* splitter, int* output_numb, int func_value);
void text_free_func(char** splitted_text, char* text, int output_numb);
void text_deleting_repeat_func(char** splitted_text, int* output_numb);
void print_word_and_number_repetitions(char* text);
int numb_word(char** splitted_text, int i);
char* text_reverse(char* text);
void toLower(char* text);
void bubble_sort(char** splitted_text, int output_numb, int index);
void text_func_four(char** splitted_text, int output_numb);



int main() {
	
	printf(INF_ABOUT_STaW);

	///чтобы компилятор воспинимал кирилицу
	setlocale(LC_ALL, "ru_RU.UNF-8");

///
	char func_value = 0; //значение функции
	scanf("%c", &func_value);
	getchar();

	if (!isdigit(func_value)) {
		printf("Error: Некорректный ввод.\n");
	}

	int output_numb = 0;
	char** splitted_text;
	char* text;
	

	/////////////

	switch (func_value) {
	case '0'://выводим текст после первичной обработки
		//ввод и первичная обрботка
		text = text_input_func();
		splitted_text = split_text_func(text, ".", &output_numb, func_value);

		//выводим текст после первичной обработки и особождаем память
		text_print_func(splitted_text, output_numb);
		text_free_func(splitted_text, text, output_numb);

		break;

	case '1'://выводим функцию под номером 1
		//ввод и первичная обрботка
		text = text_input_func();
		splitted_text = split_text_func(text, ".", &output_numb, func_value);
		//выводим текст после первичной обработки и особождаем память
		print_word_and_number_repetitions(text);
		text_free_func(splitted_text, text, output_numb);

		break;

	case '2'://выводим функцию под номером 2

		//ввод и обработка
		text = text_input_func();
		splitted_text = split_text_func(text_reverse(text), ".", &output_numb, func_value);

		//вывод и освобождение памяти
		text_print_func(splitted_text, output_numb);
		text_free_func(splitted_text, text, output_numb);

		break;

	case '3'://выводим функцию под номером 3

		//обработка и ввод
		text = text_input_func();
		splitted_text = split_text_func(text, ".", &output_numb, func_value);

		//вывод и освобождение памяти
		text_print_func(splitted_text, output_numb);
		text_free_func(splitted_text, text, output_numb);

		break;

	case '4'://выводим функцию под номером 4
		//ввод и обработка
		text = text_input_func();
		splitted_text = split_text_func(text, ".", &output_numb, func_value);

		//вывод и освобождение памяти
		text_func_four(splitted_text, output_numb);
		text_free_func(splitted_text, text, output_numb);
		break;

	case '5'://выводим справки о всех функциях

		file_help();
		break;
	case '9': {
		char* new_str=malloc(sizeof(char)*100);
		int i = 0;
		char c;
		while ((c = getchar())) {
			if (c == '\n') {
				break;
			}
			new_str[i] = c;
			i++;
		}
		new_str[i]='\0';
		text = text_input_func();
		splitted_text = split_text_func(text, ".", &output_numb, func_value);

		//вывод и освобождение памяти
		if (output_numb%2!=0){
		    for (int i = 0; i <= (output_numb / 2); i++) {
			    for (int k = 0; k < strlen(splitted_text[i]) - 1; k++) {
			        printf("%c", splitted_text[i][k]);
			    }
			    printf(" ");
			    for (int l = 0; (l < strlen(new_str)); l++) {
				    printf("%c", new_str[l]);
			    }
			    printf(" ");
			    printf("%s\n", splitted_text[output_numb-i-1]);
		       
		        }
		}else{
		    for (int i = 0; i < (output_numb / 2); i++) {
			    for (int k = 0; k < strlen(splitted_text[i]) - 1; k++) {
			        printf("%c", splitted_text[i][k]);
			    }
			    printf(" ");
			    for (int l = 0; l < strlen(new_str); l++) {
				    printf("%c", new_str[l]);
			    }
			    printf(" %s\n", splitted_text[output_numb-i-1]);
		       
		        }
		}
		
	    free(new_str);
		text_free_func(splitted_text, text, output_numb);
		break;
	}
	default:

		printf("Error: Неправильно введена функция.\n");
		break;
	}


	return 0;
}

//функция для вывода справки (func_value=5)
void file_help() {
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
		"Справка:",
		"0 - вывод текста после первичной обязательной обработки;",
		"1 - распечатать каждое слово и количество его повторений в тексте;",
		"2 - преобразовать каждое предложение так, что символы в каждом слове шли в обратном порядке;",
		"3 - удалить предложения, в которых встречается запятая;",
		"4 - отсортировать предложения по уменьшению значения кода 5 символа предложения;",
		"5 - вывод справки о функциях, которые реализует программа.");
}

//принимаем текст
char* text_input_func() {

	int len = 0;
	int add_memory = LEN_TEXT;
	char input_char;
	char* text = malloc(sizeof(char) * add_memory);//выделяем память на массив с указателями

	//динамическое выделение памяти под исходный текст
	while ((input_char = getchar())) {
		if ((input_char == '\n')) {
			if ((len > 0) && (text[len - 1] == '\n')) {
				break;
			}
		}

		if (text[0] == '.') {
			printf("Error: Ошибка ввода.\n");
		}
		if (len >= add_memory && text != NULL) {
			add_memory += LEN_TEXT;
			text = realloc(text, sizeof(char) * add_memory);
		}
		text[len++] = input_char;
	}

	text[len] = '\0';

	if (text[strlen(text) - 1] != '.' && isalnum(text[strlen(text) - 2]) && text[strlen(text) - 1] != ' ') {
		text[strlen(text) - 1] = '.';
	}
	return text;
}




//выводим текст
void text_print_func(char** splitted_text, int output_numb) {
	for (int i = 0; i < output_numb; i++) {
		printf("%s\n", splitted_text[i]);
	}
}

//функция освобождения динамической памяти
void text_free_func(char** splitted_text, char* text, int output_numb) {
	for (int i = 0; i < output_numb; i++) {
		free(splitted_text[i]);
	}
	free(splitted_text);
	free(text);
}

//функция удаления одинаковых предложений
void text_deleting_repeat_func(char** splitted_text, int* output_numb) {
	for (int i = 0; (i < (*output_numb)) && (splitted_text[i]); i++) {
		for (int j = i + 1; (j < (*output_numb)) && (splitted_text[j]); j++) {
			if (strcmp(splitted_text[i], splitted_text[j]) == 0) {//strcmp поправить
				free(splitted_text[j]);
				for (int k = j; k < (*output_numb); k++) {
					splitted_text[k] = splitted_text[k + 1];
				}
				(*output_numb)--;
				j--;
			}
		}
	}
}

//считаем количество слов

int numb_word(char** splitted_text, int i) {
	int word_count = 0;
	//for (int i = 0; i < output_numb; i++) {
		for (int j = 0; j < ((int)strlen(splitted_text[i])+1); j++) {
			if (((splitted_text[i][j] == ' ') || (splitted_text[i][j] == ',') || (splitted_text[i][j] == '.')) && ((splitted_text[i][j - 1] != ' ') && (splitted_text[i][j - 1] != ',') && (splitted_text[i][j - 1] != '.'))) {
				word_count++;
			}
		}
	//}
	return word_count;
}


//все для функции 1
struct WordCount {
	char* word;
	int count;
};

int compare(const void* a, const void* b) {
	struct WordCount* f = (struct WordCount*)a;
	struct WordCount* s = (struct WordCount*)b;
	return strcmp(f->word, s->word);
}

void toLower(char* text) {
	for (int i = 0; text[i]; i++) {
		text[i] = tolower(text[i]);
	}
}

void print_word_and_number_repetitions(char* text) {
	toLower(text);
	struct WordCount* word_count = malloc(100 * sizeof(struct WordCount));
	int capacity = 100;
	int count = 0;
	int len_str = strlen(text);
	if (text[len_str - 1] == '\n') {
		text[len_str - 1] = '\0';
	}
	char* temp_word = strtok(text, " ,.");
	while (temp_word != NULL) {
		int fl = 0;
		for (int i = 0; i < count; i++) {
			if (strcmp(word_count[i].word, temp_word) == 0) {
				fl = 1;
				word_count[i].count++;
				break;
			}
		}
		if (!fl) {
			if (count == capacity) {
				capacity *= 2;
				word_count = realloc(word_count, capacity * sizeof(struct WordCount));
			}
			word_count[count].word = malloc(strlen(temp_word) + 1);
			strcpy(word_count[count].word, temp_word);
			word_count[count].count = 1;
			count++;
		}
		temp_word = strtok(NULL, " ,.");
	}

	qsort(word_count, count, sizeof(struct WordCount), compare);

	for (int i = 0; i < count; i++) {
		printf("%s - %d\n", word_count[i].word, word_count[i].count);
		free(word_count[i].word);
	}
	free(word_count);
}

//функция 2 преворачиваем слова
char* text_reverse(char* text) {
	int len_str = strlen(text);
	int start = 0;
	int fl = 0;
	for (int i = 0; i <= (len_str); i++) {
		if ((fl == 0) && (isalnum(text[i]))) {
			start = i;
			fl = 1;
		}
		if (((text[i] == ',') || (text[i] == ' ') || (text[i] == '.')) && (isalnum(text[i - 1]))) {
			int stop = i - 1;
			for (int j = start, k = stop; j < k; j++, k--) {
				char temp = text[j];
				text[j] = text[k];
				text[k] = temp;
			}
			fl = 0;
		}
	}
	return text;
}

//bubble sort для 4 функици
void bubble_sort(char** splitted_text, int output_numb, int index) {
	char temp;

	for (int k = 0; k < output_numb; k++) {
		int len_sent = strlen(splitted_text[k]);
		for (int i = index; i < len_sent + (index - 1); i++) {
			for (int j = index; j < len_sent - i + (index - 1); j++) {
				if ((splitted_text[k][j] < splitted_text[k][j + 1])) {
					temp = splitted_text[k][j];
					splitted_text[k][j] = splitted_text[k][j + 1];
					splitted_text[k][j + 1] = temp;
				}
			}
		}
	}
}

//функция 4
void text_func_four(char** splitted_text, int output_numb) {
	for (int i = 0; i < output_numb; i++) {
		int len_sent = strlen(splitted_text[i]);
		int index = 4;
		if (isalnum(splitted_text[i][4]) && ((len_sent - 1) >= 5)) {
			index = 4;
			bubble_sort(splitted_text, output_numb, index);
			break;
		}
		else {

			for (int l = 0; l < len_sent-4; l++) {
				if (isalnum(splitted_text[i][index+l])) {
					bubble_sort(splitted_text, output_numb, index+l);
					break;
				}
			}
		}

	}

	for (int i = 0; i < output_numb; i++) {
		if (strlen(splitted_text[i]) - 1 < 5) {
			printf("-1\n");
		}
		else {
			printf("%s\n", splitted_text[i]);
		}
	}
}
/*
//поиск максимального слова в предложении
int max_word(char** splitted_text, int i) {
	int len_word = 0, ma_len_word =0;
	for (int j = 0; j < strlen(splitted_text[i]); j++) {
		if (isalnum(splitted_text[i][j])) {
			len_word++;
			if (ma_len_word < len_word) {
				ma_len_word = len_word;
			}
		}
		else {
			len_word = 0;
		}
	}
	return ma_len_word;
}
*/



//функция разделения предложений и удаления предложений с запятыми
char** split_text_func(char* text, char* splitter, int* output_numb, int  func_value) {
	char** splitted_text = malloc(sizeof(char*));

	int count_sent = 0; //счетчик предложений
	int last_ind = 0;
	int deleting_sent = 0; //флаг удаления предложения
	int was_letter_printed = 0;

	for (int i = 0; i < (int)strlen(text); i++) {
		//если вызвана функция 3, то удаляем предложение с запятой
		if ((func_value == '3') && (text[i] == ',')) {
			deleting_sent = 1;
		}

		// считаем предложения и разделяем текст на предложения
		if (strchr(splitter, text[i])) {

			if (deleting_sent == 1) {
				deleting_sent = 0;
				last_ind = 0;
				continue;
			}

			count_sent++;

			splitted_text = realloc(splitted_text, count_sent * sizeof(char*));
			splitted_text[count_sent - 1] = malloc((last_ind + 2) * sizeof(char));

			int chr_temp = 0;
			for (int j = last_ind; j >= 0; j--) {
				/////////////пропуск запятой и точки в начале предложения

				if ((!isspace(text[i - j])) && (text[i - j] != ',')) {
					was_letter_printed = 1;
				}
				if ((!was_letter_printed) && ((isspace(text[i - j])) || (text[i - j] == ','))) {
					continue;
				}
				splitted_text[count_sent - 1][chr_temp++] = text[i - j];
			}

			while (isspace(splitted_text[count_sent - 1][chr_temp - 1])) {
				chr_temp--;
			}

			splitted_text[count_sent - 1][chr_temp] = '\0';
			last_ind = 0;
			continue;
		}
		last_ind++;
		was_letter_printed = 0;
	}
	*output_numb = count_sent;
	text_deleting_repeat_func(splitted_text, output_numb);
	return splitted_text;
}
