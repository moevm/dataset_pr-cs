#include <stdlib.h>

#include <locale.h> 

#include <stdio.h>

#include <ctype.h>

#include <string.h>

typedef struct {

	char* chars;

	int digit_sum;

	int size;

} Sentence;

typedef struct {

	Sentence* sentences;

	int size;

} Text;

Sentence get_sentence(int* end) {
	;

	int allocsize = 128, size = 0;

	char tmpchar = '\0';

	Sentence sentence;

	sentence.digit_sum = 0; sentence.size = 0;

	sentence.chars = malloc(sizeof(char) * allocsize);

	while (tmpchar != '.') {

		tmpchar = getchar();

		if (tmpchar == '\n') {

			if (++(*end) == 2) {

				break;
			}
		}
		else *end = 0;

		if (isspace(tmpchar) && size == 0) continue;

		sentence.chars[size++] = tmpchar;

		if (isdigit(tmpchar)) {

			sentence.digit_sum += tmpchar - '0';

		}

		if (size == allocsize) {

			allocsize *= 2;

			sentence.chars = realloc(sentence.chars, sizeof(char) * allocsize);

			if (sentence.chars == NULL) {

				fprintf(stderr, "Error: not enough memory");

				exit(0);
			}

		}

	}
	sentence.size = size;

	sentence.chars[size] = '\0';

	return sentence;
}

void swap(Sentence* a, Sentence* b) {

	Sentence temp = *a;

	*a = *b; *b = temp;
}

int cmpstr_case_insesitive(char* a, char* b) {

	int i = 0, result = 1;

	while (a[i] != '\0' && b[i] != '\0') {

		if (tolower(a[i]) != tolower(b[i])) {

			result = 0;

			break;
		}
		i++;
	}
	if ((a[i] == '\0') ^ (b[i] == '\0')) result = 0;

	return result;
}

Text get_text() {

	int allocsize = 16, size = 0, end = 0;

	Text text;

	text.sentences = malloc(sizeof(Sentence) * allocsize);

	text.size = 0;

	while (end < 2) {

		Sentence tmpsentence = get_sentence(&end);

		if (end == 2) break;

		int is_double = 0;

		for (int i = 0; i < size; i++)

			if (strcmp(text.sentences[i].chars, tmpsentence.chars) == 0) {

				is_double = 1;

				break;
			}
		if (is_double) continue;

		text.sentences[size++] = tmpsentence;

		if (size == allocsize) {

			allocsize *= 2;

			text.sentences = realloc(text.sentences, sizeof(Sentence) * allocsize);

			if (text.sentences == NULL) {

				fprintf(stderr, "Error: not enough memory");

				exit(0);
			}

		}

	}
	text.size = size;

	return text;
}

void print_text(Text text) {

	for (int i = 0; i < text.size; i++)

		puts(text.sentences[i].chars);
}

//1

Text capitalize_word() {

	Text text = get_text();

	for (int i = 0; i < text.size; i++) {

		for (int j = 0; j < text.sentences[i].size; j++) {

			if (j == 0 || isspace(text.sentences[i].chars[j - 1])) {

				text.sentences[i].chars[j] = toupper(text.sentences[i].chars[j]);


			}

			else {

				text.sentences[i].chars[j] = tolower(text.sentences[i].chars[j]);

			}

		}

	}

	return text;

}

//2

Text remove_sentences_with_2018(Text text) {

	int num_sentences_with_2018 = 0;

	Sentence* sentences_with_2018 = malloc(sizeof(Sentence) * text.size);

	for (int i = 0; i < text.size; i++) {

		Sentence sentence = text.sentences[i];


		if (strstr(sentence.chars, "2018") != NULL) {

			sentences_with_2018[num_sentences_with_2018++] = sentence;
		}

	}

	for (int i = 0; i < num_sentences_with_2018; i++) {

		for (int j = 0; j < text.size; j++) {

			if (cmpstr_case_insesitive(text.sentences[j].chars, sentences_with_2018[i].chars)) {

				swap(&text.sentences[j], &text.sentences[text.size - 1]);

				text.size--;

				break;
			}

		}

	}

	return text;

}

//3

int get_digit_sum(char* string) {

	long int sum = 0;

	while (*string) {

		if (isdigit(*string)) {

			sum += *string - '0';

		}

		string++;
	}
	if (sum == 0) {

		sum = 9999999999999999;

	}

	return sum;
}

void sort_sentences(Text* text) {

	for (int i = 0; i < text->size - 1; i++) {

		for (int j = 0; j < text->size - i - 1; j++) {

			int sum1 = get_digit_sum(text->sentences[j].chars);

			int sum2 = get_digit_sum(text->sentences[j + 1].chars);

			if (sum1 > sum2) {

				swap(&text->sentences[j], &text->sentences[j + 1]);

			}
		}
	}
}


//4

void find_sentences_with_digits(Text text) {

	Text result_text;

	result_text.sentences = malloc(sizeof(Sentence) * text.size);

	result_text.size = 0;

	for (int i = 0; i < text.size; i++) {

		int digits[10] = { 0 };

		int all_digits_present = 1;


		for (int j = 0; j < text.sentences[i].size; j++) {

			char c = text.sentences[i].chars[j];

			if (isdigit(c)) {

				digits[c - '0'] = 1;

			}
		}

		for (int k = 0; k < 10; k++) {

			if (digits[k] == 0) {

				all_digits_present = 0;

				break;
			}
		}

		if (all_digits_present) {

			result_text.sentences[result_text.size++] = text.sentences[i];

		}
	}

	if (result_text.size > 0) {

		print_text(result_text);

	}
	else {

		printf("No sentences found.\n");
	}
}

int main() {

	setlocale(LC_CTYPE, "ru_RU.utf8");

	puts("Course work for option 4.2, created by Daniil Kerbel.");

	int option;

	scanf("%i", &option);

	Text text;

	switch (option) {

	case 0:

		text = get_text();

		print_text(text);

		break;

	case 1:

		text = capitalize_word();

		print_text(text);

		break;

	case 2:

		text = get_text();

		text = remove_sentences_with_2018(text);

		print_text(text);

		break;

	case 3:

		text = get_text();

		sort_sentences(&text);

		print_text(text);

		break;

	case 4:

		text = get_text();

		find_sentences_with_digits(text);

		break;

	case 5:

		printf("0 - Вывод текста после первичной обязательной обработки\n\
                \r1 - Преобразовать предложения так, чтобы каждое слово в нем начиналось с заглавной буквы, а остальные символы слова были строчными.\n\
                \r2 - Удалить все предложения, в которых есть число 2018 (даже если оно  внутри какого-то слова).\n \
                \r3 - Отсортировать предложения по увеличению суммы цифр встречаемых в предложении. Если в предложении нет цифр, то сумма цифр данного предложения равняется ∞.\n \
                \r4 - Вывести на экран все предложения, в которых встречаются все цифры хотя бы один раз.\n \
                \r5 - Вывод справки о функциях, которые реализует программа.\n");
		break;

	default:

		fprintf(stderr, "Error: incorrect code for command\n");

	}
	return 0;

}