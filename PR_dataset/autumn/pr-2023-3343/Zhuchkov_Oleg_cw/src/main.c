#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


typedef struct {
	char* chars;
	int size;
	int word_count;
} Sentence;

typedef struct {
	Sentence* sentences;
	int size;
} Text;

//Input
Sentence get_sentence(int* end){
	char tmpchar = '\0';
	int allocsize = 128, size = 0;
	Sentence sentence;
	sentence.chars = malloc(sizeof(char) * allocsize);
	sentence.size = 0;
	while (tmpchar != '.'){
		tmpchar = getchar();
		if (tmpchar == '\n'){
			if (++(*end) == 2){
				break;
			}
		}
		else *end = 0;
		if (isspace(tmpchar) && size == 0) continue;
		sentence.chars[size++] = tmpchar;
		if (size == allocsize){
			allocsize *= 2;
			sentence.chars = realloc(sentence.chars, sizeof(char) * allocsize);
			if (sentence.chars == NULL){
				fprintf(stderr, "Error: not enough memory");
				exit(0);
			}
		}
	}
	sentence.size = size;
	sentence.chars[size] = '\0';
	return sentence;
}

int cmpstr_case_insesitive(char* a, char* b){
	int i = 0, result = 1;
	while (a[i] != '\0' && b[i] != '\0'){
		if (tolower(a[i]) != tolower(b[i])){
			result = 0;
			break;
		}
		i++;
	}
	if ((a[i] == '\0') ^ (b[i] == '\0')) result = 0;
	return result;
}

Text get_text(){
	int allocsize = 16, size = 0, end = 0;
	Text text;
	text.sentences = malloc(sizeof(Sentence) * allocsize);
	text.size = 0;
	while (end < 2){
		Sentence tmpsentence = get_sentence(&end);
		if (end == 2) break;
		int is_double = 0;
		for (int i = 0; i < size; i++)
			//if (strcasecmp(text.sentences[i].chars, tmpsentence.chars) == 0){
			if (cmpstr_case_insesitive(text.sentences[i].chars, tmpsentence.chars) == 1){
				is_double = 1;
				break;
			}
		if (is_double) continue;
		text.sentences[size++] = tmpsentence;
		if (size == allocsize){
			allocsize *= 2;
			text.sentences = realloc(text.sentences, sizeof(Sentence) * allocsize);
			if (text.sentences == NULL){
				fprintf(stderr, "Error: not enough memory");
				exit(0);
			}
		}
	}
	text.size = size;
	return text;
}

//Output
void print_text(Text text){
	for (int i = 0; i < text.size; i++)
		puts(text.sentences[i].chars);
}

//Task 1
void cut_sentences(Text text){
	for (int i = 0; i < text.size; i++){
		int first_ind = -1, second_ind = -1;
		Sentence sentence = text.sentences[i];
		char* chars = sentence.chars;
		for (int j = 0; j < sentence.size; j++){
			if (chars[j] == '$'){
				if (first_ind == -1) first_ind = j;
				else second_ind = j;
			}
		}
		if (first_ind == -1) continue;
		int new_size;
		char* new_sentence;
		if (second_ind == -1){
			new_size = sentence.size - 1;
			new_sentence = malloc(sizeof(char) * (new_size + 1));
			for (int j = 0; j < first_ind; j++)
				new_sentence[j] = sentence.chars[j];
			for (int j = first_ind + 1; j <= sentence.size - 1; j++)
				new_sentence[j-1] = sentence.chars[j];
		}
		else{
			new_size = second_ind - first_ind + 1;
			new_sentence = malloc(sizeof(char) * (new_size + 1));
			for (int j = first_ind; j <= second_ind; j++)
				new_sentence[j-first_ind] = sentence.chars[j];
			new_sentence[new_size] = '\0';
		}
		text.sentences[i].size = new_size;
		text.sentences[i].chars = new_sentence;
	}
	return;
}

//Task 2
void count_words (Text text){
	Sentence *sentences = text.sentences;
	for (int i = 0; i < text.size; i++){
		int count = 1;
		Sentence sentence = text.sentences[i];
		for (int j = 0; j < sentence.size-1; j++){
			if ((isspace(sentence.chars[j]) || sentence.chars[j] == ',') && !(isspace(sentence.chars[j+1]) || sentence.chars[j+1] == ','))
				count++;
		}
		sentences[i].word_count = count;
	}
}

int cmp_sentences(const void * a, const void * b){
	if ((*(Sentence*)(b)).word_count - (*(Sentence*)(a)).word_count)
	    return (*(Sentence*)(b)).word_count - (*(Sentence*)(a)).word_count;
	else
	    return (*(Sentence*)(b)).size - (*(Sentence*)(a)).size;
}

int cmp_sentences_rev(const void * a, const void * b){
	if ((*(Sentence*)(a)).word_count - (*(Sentence*)(b)).word_count)
	    return (*(Sentence*)(a)).word_count - (*(Sentence*)(b)).word_count;
	else
	    return (*(Sentence*)(a)).size - (*(Sentence*)(b)).size;
}


void sort_by_word_count(Text text, int reverse){
	count_words(text);
	if (reverse)
	    qsort(text.sentences, text.size, sizeof(Sentence), cmp_sentences_rev);
	else
	    qsort(text.sentences, text.size, sizeof(Sentence), cmp_sentences);
	return;
}

//Task 3
void count_chars_and_print(Text text){
	char* symbols = malloc(256 * sizeof(char));
	int* symbol_count = malloc(256 * sizeof(int));
	int count = 0;
	for (int i = 0; i < text.size; i++){
		for (int j = 0; j < text.sentences[i].size; j++){
			char symbol = text.sentences[i].chars[j];
			if (ispunct(symbol) || isspace(symbol)) continue;
			int index = -1;
			for (int k = 0; k < count; k++)
				if (symbol == symbols[k]){
					index = k;
					break;
				}
			if (index == -1) {
				symbols[count] = symbol;
				symbol_count[count] = 1;
				count++;
			}
			else symbol_count[index]++;
		}	
	}
	for (int i = 0; i < count; i++){
		printf("'%c': %d", symbols[i], symbol_count[i]);
		if (i != count - 1) printf(", ");
	}
}

//Task 4
void delete_even_sentences(Text *text){
	int new_size = (*text).size / 2;
	Sentence* new_sentences = malloc(new_size * sizeof(Sentence));
	for (int i = 0; i < new_size; i++)
		new_sentences[i] = (*text).sentences[2*i+1];
	(*text).sentences = new_sentences;
	(*text).size = new_size;
	return;
}


int main(){
	puts("Course work for option 4.19, created by Oleg Zhuchkov.");
	int mode;
	scanf("%i", &mode);
	Text text;
	switch (mode){
		case 0:
			text = get_text();
			print_text(text);
			break;
		case 1:
			text = get_text();
			cut_sentences(text);
			print_text(text);
			break;
		case 2:
			text = get_text();
			sort_by_word_count(text, 0);
			print_text(text);
			break;
		case 3:
			text = get_text();
			count_chars_and_print(text);
			break;
		case 4:
			text = get_text();
			delete_even_sentences(&text);
			print_text(text);
			break;
		case 5:
			puts("0 - Read and print text\n"
			"1 - Cut sentence before first $ and after last $ (if only one $, then only $ is deleted)\n"
			"2 - Sort sentences by word count\n"
			"3 - Count symbols in text\n"
			"4 - Delete sentences with an even index\n"
			"5 - info");
			break;
		case 9:
			text = get_text();
			sort_by_word_count(text, 1);
			print_text(text);
			break;
		default:
			fprintf(stderr, "Error: incorrect input");
			exit(0);
	}
	return 0;
}



