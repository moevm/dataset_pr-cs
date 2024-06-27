#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define ORIGINAL_SIZE 100
#define EXTRA_SIZE 30

int text_output(char** text, int sentence){
	for (int i = 0; i < sentence; i++){
		if (strlen(text[i]) != 0){
			printf("%s\n", text[i]);
		}
		free(text[i]);
	}
	free(text);
	return 0;
}

int function9(char** text, int sentence, int N){
	for (int i = 0; i < sentence; i++){
		int helper = strlen(text[i]);
		if (N == 1 || helper == 1){
			continue;
		}
		else{
			char* new_sentence = (char*)realloc(text[i], sizeof(char) * (strlen(text[i]) + 2) * N);
        		if (new_sentence == NULL){
        			printf("Error: memory allocation\n");
        			for (int j = 0; j < sentence; j++){
        				free(text[j]);
        			}
        			free(text);
        			return 1;
        		}
        		text[i] = new_sentence;
        		for (int j = helper; j >= 0; j--){
        			if (isdigit(text[i][j]) || isalpha(text[i][j])){
        				helper = j;
        				break;
        			}
        		}
        		helper++;
        		text[i][helper] = ' ';
        		for (int k = 1; k < N; k++){
        			for (int j = 0; j <= helper; j++){
        				text[i][helper * k + k - 1 + j + 1] = text[i][j];
        			}
        		}
        		text[i][helper * N + N - 1] = '.';
        		text[i][helper * N + N] = '\0';
		}
	}
	text_output(text, sentence);
	return 0;
}

int repeating_letters(char** text, int sentence){
	for (int i = 0; i < sentence; i++){
		int ind, flag = 1;
		char symbol = text[i][0];
		for (int j = 1; j < strlen(text[i]); j++){
			if (isalpha(symbol) && isalpha(text[i][j])){
				if (toupper(text[i][j]) != toupper(symbol)){
					if (flag == 0){
						char str[strlen(text[i])];
						sprintf(str, "%d", j - ind);
						for (int k = ind; k < ind + strlen(str) + 2; k++){
							if (k < ind + strlen(str)){
								text[i][k] = str[k - ind];
							}
							if (k == ind + strlen(str)){
								text[i][k] = toupper(symbol);
							} 
							if (k > ind + strlen(str)){
								memmove(&text[i][k], &text[i][k + j - ind - strlen(str) - 1], strlen(text[i]) - k - j + ind + strlen(str) + 2);
							}
						}
						j = ind + strlen(str);
						ind = -1;
						flag = 1;
					}
					symbol = text[i][j];
				}
				else{
					if (flag == 1){
						ind = j - 1;
						flag = 0;
					}
				}
			}
			else{
				if (flag == 0){
					char str[strlen(text[i])];
					sprintf(str, "%d", j - ind);
					for (int k = ind; k < ind + strlen(str) + 2; k++){
						if (k < ind + strlen(str)){
							text[i][k] = str[k - ind];
						}
						if (k == ind + strlen(str)){
							text[i][k] = toupper(symbol);
						} 
						if (k > ind + strlen(str)){
							memmove(&text[i][k], &text[i][k + j - ind - strlen(str) - 1], strlen(text[i]) - k - j + ind + strlen(str) + 2);
						}
					}
					j = ind + strlen(str);
					ind = -1;
					flag = 1;
				}
				symbol = text[i][j];
			}
		}
	}
	text_output(text, sentence);
	return 0;
}

int words_counter(const char** the_sentence){
	char* now_sentence = (char*)calloc(strlen(*the_sentence) + 2, sizeof(char));
	strcpy (now_sentence, *the_sentence);
	char* word = strtok(now_sentence, " ,.\t\n");
	int counter_words = 0;
	char** new_sentence = (char**)calloc(strlen(*the_sentence) + 2, sizeof(char*));
	while (word != NULL){
		new_sentence[counter_words] = word;
		word = strtok(NULL, " ,.\t\n");
		counter_words++;
	}
	int len_sentence;
	if (counter_words == 0){
		len_sentence = 0;
	}
	if (counter_words == 1){
		len_sentence = strlen(new_sentence[0]);
	}
	if (counter_words > 1){
		len_sentence = strlen(new_sentence[0]) + strlen(new_sentence[counter_words - 1]);
	}
	free(new_sentence);
	free(now_sentence);
	return len_sentence;
}

int cmp(const void *the_sentence1, const void *the_sentence2){
	const char **f = (const char**)the_sentence1;
	const char **s = (const char**)the_sentence2;
	int len1 = words_counter(f);
	int len2 = words_counter(s);
	return len2 - len1;
}

int sort_by_length(char** text, int sentence){
	qsort(text, sentence, sizeof(char*), cmp);
	text_output(text, sentence);
	return 0;
}

int delete_if_three(char** text, int sentence){
	for (int i = 0; i < sentence; i++){
		char* now_sentence = (char*)calloc(strlen(text[i]) + 2, sizeof(char));
		if (now_sentence == NULL){
			for (int j = 0; j < sentence; j++){
				free(text[j]);
			}
			free(text);
			printf("Error: memory allocation\n");
			return 1;
		}
		strcpy (now_sentence, text[i]);
		char* word = strtok(now_sentence, " ,.\t\n");
        	int counter_words = 0;
        	while (word != NULL){
                	word = strtok(NULL, " ,.\t\n");
                	counter_words++;
        	}
		if (counter_words % 3 == 0){
			text[i][0] = '\0';
		}
		free(now_sentence);
	}
	text_output(text, sentence);
	return 0;
}

int recolour_in_cyan(char** text, int sentence){
	char need_sentence[] = "define BLUE";
	char* flag;
	for (int i = 0; i < sentence; i++){
		flag = NULL;
		char* the_first_symbol = strstr(text[i], need_sentence);
		while (the_first_symbol != NULL){
			if (the_first_symbol != NULL){
				if (the_first_symbol != &text[i][0] && (isdigit(*(the_first_symbol - sizeof(char))) || isalpha(*(the_first_symbol - sizeof(char))))){
					flag = the_first_symbol;
					the_first_symbol = NULL;
				}
				else{
					if (isdigit(*(the_first_symbol + strlen(need_sentence) * sizeof(char))) || isalpha(*(the_first_symbol + strlen(need_sentence) * sizeof(char)))){
						flag = the_first_symbol;
						the_first_symbol = NULL;
					}
				}
			}
			if (the_first_symbol != NULL){
				break;
			}
			if (the_first_symbol == NULL){
				the_first_symbol = strstr(flag + sizeof(char) * 2, need_sentence);
			}
		}
		if (the_first_symbol != NULL){
			the_first_symbol += strlen(need_sentence) * sizeof(char);
		}
		for (int j = 0; j < strlen(text[i]); j++){
			if (&text[i][j] == the_first_symbol){
				printf("\033[34m%s\033[0m", the_first_symbol);
				break;
			}
			putchar(text[i][j]);
		}
		printf("\n");
		free(text[i]);
	}
	free(text);
	return 0;
}

int similar_sentence(char** text, int sentence){
	int flag = 1;
	if (sentence == 0){
		return 0;
	}
	for (int i = 0; i < sentence; i++){
		flag = 1;
		if (strlen(text[i]) != strlen(text[sentence])){
			continue;
		}
		for (int j = 0; j < strlen(text[i]); j++){
			if (isalpha(text[i][j]) && isalpha(text[sentence][j])){
				if (toupper(text[sentence][j]) != toupper(text[i][j])){
					flag = 0;
					break;
				}
			}
			else{
				if (text[i][j] != text[sentence][j]){
					flag = 0;
					break;
				}
			}
		}
		if (flag == 1){
			 return 1;
		}
	}
	return 0;
}

int text_input(char operationValue, int N){
	int size = ORIGINAL_SIZE, sizeText = ORIGINAL_SIZE;
	char** text = (char**)calloc(sizeText, sizeof(char*));
	if (text == NULL){
		printf("Error: memory allocation\n");
		return 1;
	}
	char symbol;
	int index = 0, sentence = 0, helperSymbol = -1, flag = 1, emptiness = 0;
        while (flag == 1){
        	size = ORIGINAL_SIZE;
        	index = 0;
        	if ((sentence + 2) >= sizeText){
        		sizeText += EXTRA_SIZE;
        		char** new_text = (char**)realloc(text, sizeText * sizeof(char*));
			if (new_text == NULL){
				printf("Error: memory allocation\n");
				for (int i = 0; i < sentence; i++){
					free(text[sentence]);
				}
				free(text);
				return 1;
			}
			free(text);
			text = new_text;
        	}
        	while ((symbol = getchar()) != '.'){
        		if (symbol == '\n' && helperSymbol == -1){
        			helperSymbol = index;
        			continue;
        		}
        		if (index == helperSymbol && symbol == '\n'){
        			flag = 0;
        			if (index == 0 && sentence == 0){
        				emptiness = 1;
        				printf("Error: empty input\n");
        			}
        			helperSymbol = -1;
        			break;
        		}
        		if (index == helperSymbol && symbol != '\n'){
        			helperSymbol = -1;
        			if (index != 0){
        				text[sentence][index] = '\n';
        				index++;
        			}
        		}
        		if (index == 0 && (symbol == ' ' || symbol == '\t')){
        			continue;
        		}
        		if (index == 0){
        			char* new_sentence = (char*)calloc(size, sizeof(char));
        			if (new_sentence == NULL){
        				printf("Error: memory allocation\n");
        				if (sentence == 0){
        					free(text);
        				}
        				else{
        					for (int i = 0; i < sentence; i++){
        						free(text[sentence]);
        					}
        					free(text);
        				}
        				return 1;
        			}
        			text[sentence] = new_sentence;
        		}
        		if ((index + 8) >= size){
        			size += EXTRA_SIZE;
        			char* new_sentence = (char*)realloc(text[sentence], size * sizeof(char));
        			if (new_sentence == NULL){
        				printf("Error: memory allocation\n");
        				for (int i = 0; i <= sentence; i++){
        					free(text[sentence]);
        				}
        				free(text);
        				return 1;
        			}
        			text[sentence] = new_sentence;
        		}
        		text[sentence][index] = symbol;
        		index++;
        	}
        	if (index == 0 && symbol == '.'){
        		text[sentence] = (char*)calloc(4, sizeof(char));
        	}
        	if (index == 0 && flag == 0){
        		break;
        	}
        	if (index == helperSymbol){
        		text[sentence][index] = '\n';
        		index++;
        	}
        	text[sentence][index] = '.';
        	text[sentence][index + 1] = '\0';
        	if (similar_sentence(text, sentence)){
        		free(text[sentence]);
        		helperSymbol = -1;
        		continue;
        	}
        	sentence++;
        	helperSymbol = -1;
        	if (emptiness == 1){
        		return 1;
        	}
        	if (flag == 0){
        		break;
        	}
        }
        if (operationValue == '1'){
        	recolour_in_cyan(text, sentence);
        }
        if (operationValue == '0'){
		text_output(text, sentence);
	}
	if (operationValue == '3'){
		delete_if_three(text, sentence);
	}
	if (operationValue == '4'){
		sort_by_length(text, sentence);
	}
	if (operationValue == '2'){
		repeating_letters(text, sentence);
	}
	if (operationValue == '9'){
		function9(text, sentence, N);
	}
	return 0;
}

int text_input9(int operationValue){
	int N;
	scanf("%d", &N);
	getchar();
	text_input(operationValue, N);
	return 0;
}

int operation_5(char operationValue){
	printf("• 0 – вывод текста после первичной обязательной обработки\n");
	printf("• 1 – вывод каждого предложения, и если в нем есть словосочетание “define BLUE”, то все слова после этого словосочетания выводятся голубым цветом\n");
	printf("• 2 – замена во всем тексте последовательностей подряд идущих букв без учета регистра подстрокой вида “<кол-во подряд идущих букв><буква в верхнем регистре>”\n");
	printf("• 3 – удаление всех предложений в которых количество слов кратно трем\n");
	printf("• 4 – сортировка предложений по уменьшению суммарной длины первого и последнего слова\n");
	printf("• 5 – вывод справки о функциях, которые реализует программа\n");
	return 0;
}

int operation_selection(char operationValue){
	if (operationValue != '0' && operationValue != '1' && operationValue != '2' && operationValue != '3' && operationValue != '4' && operationValue != '5' && operationValue != '9'){
                printf("Error: invalid command\n");
		return 1;
        }
        if (operationValue == '5'){
		operation_5(operationValue);
		return 0;
        }
        if (operationValue == '9'){
        	text_input9(operationValue);
        	return 0;
        }
        int N = 1;
        text_input(operationValue, N);
	return 0;
}

int main(){
	printf("Course work for option 4.16, created by Aleksandra Derevyagina.\n");
	char operationValue;
	operationValue = getchar();
	operation_selection(operationValue);
	return 0;
}

