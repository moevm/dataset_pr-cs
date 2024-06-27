#include "text_processing.h"


struct Text split_text(wchar_t *text_buffer, int len)
{
	struct Text text;
	text.sentences = (struct Sentence *)calloc(len + 1, sizeof(struct Sentence));
	if(text.sentences == NULL){
		return text;
	}

	wchar_t *tmp, *pt;
	tmp = wcstok(text_buffer, L".", &pt);

	int i = 0;
	while (tmp != NULL)
	{
		while (*tmp == L' ' || *tmp == L'\n' || *tmp == L',')
			tmp++;

		
		if(wcslen(tmp) != 0){
			text.sentences[i].words = tmp;
			text.sentences[i].len = wcslen(tmp);
			i++;
		}

		tmp = wcstok(NULL, L".", &pt);
	}

	text.len = i;
	
	return text;
}

void delete_extra_commas(struct Text *text){
	int comma_flag, new_len;
	for(int i = 0; i < text->len; i++){
		new_len = text->sentences[i].len;
		comma_flag = 0;

		for(int j = text->sentences[i].len - 1; j > -1; j--){
			if(
			comma_flag &&
			(text->sentences[i].words[j] == L' ' ||
			text->sentences[i].words[j] == L'\n' ||
			text->sentences[i].words[j] == L',')
			){
				for(int k = j; k < text->sentences[i].len - 1; k++){
					text->sentences[i].words[k] = text->sentences[i].words[k + 1];
				}

				new_len--;
			}

			if(text->sentences[i].words[j] == L',') comma_flag = 1;

			if(text->sentences[i].words[j] != L','
			&& text->sentences[i].words[j] != L' '
			&& text->sentences[i].words[j] != L'\n'){
				comma_flag = 0;
			}
		}

		if(text->sentences[i].words[new_len - 1] != L','){
			text->sentences[i].len = new_len;
			text->sentences[i].words[new_len] = L'\0';
		}
		else{
			text->sentences[i].len = new_len - 1;
			text->sentences[i].words[new_len - 1] = L'\0';
		}
	}
}

void delete_extra_lines(struct Text *text){
	int line_flag, new_len;
	for(int i = 0; i < text->len; i++){
		new_len = text->sentences[i].len;
		line_flag = 0;

		for(int j = text->sentences[i].len - 1; j > -1; j--){
			if(line_flag && (text->sentences[i].words[j] == L' ' || text->sentences[i].words[j] == L'\n')){
				for(int k = j; k < text->sentences[i].len - 1; k++){
					text->sentences[i].words[k] = text->sentences[i].words[k + 1];
				}

				new_len--;
			}
			
			if(text->sentences[i].words[j] == L'\n') line_flag = 1;

			if(text->sentences[i].words[j] != L' ' && text->sentences[i].words[j] != L'\n'){
				line_flag = 0;
			}
		}

		if(text->sentences[i].words[new_len - 1] != L'\n'){
			text->sentences[i].len = new_len;
			text->sentences[i].words[new_len] = L'\0';
		}
		else{
			text->sentences[i].len = new_len - 1;
			text->sentences[i].words[new_len - 1] = L'\0';
		}
	}
}

void delete_extra_spaces(struct Text *text){
	int space_flag, new_len;
	for(int i = 0; i < text->len; i++){
		new_len = text->sentences[i].len;
		space_flag = 0;

		for(int j = text->sentences[i].len - 1; j > -1; j--){
			if(space_flag && text->sentences[i].words[j] == L' '){
				for(int k = j; k < text->sentences[i].len - 1; k++){
					text->sentences[i].words[k] = text->sentences[i].words[k + 1];
				}

				new_len--;
			}

			if(text->sentences[i].words[j] == L' ') space_flag = 1;

			if(text->sentences[i].words[j] != L' ' ){
				space_flag = 0;
			}
		}

		if(text->sentences[i].words[new_len - 1] != L' '){
			text->sentences[i].len = new_len;
			text->sentences[i].words[new_len] = L'\0';
		}
		else{
			text->sentences[i].len = new_len - 1;
			text->sentences[i].words[new_len - 1] = L'\0';
		}
	}
}

void delete_extra_separators(struct Text *text){
	delete_extra_commas(text);
	delete_extra_lines(text);
	delete_extra_spaces(text);
}

wchar_t* make_lowercase_copy(struct Sentence sentence){
	wchar_t *copy = (wchar_t *)calloc(sentence.len + 1, sizeof(wchar_t));
	if(copy == NULL) return copy;

	for(int k = 0; k < sentence.len; k++){
		copy[k] = towlower(sentence.words[k]);
	}

	return copy;
}

struct Text delete_repeating_sentences(struct Text *text){
	struct Text new_text;
	new_text.sentences = (struct Sentence *)calloc(text->len, sizeof(struct Sentence));
	if(new_text.sentences == NULL){
		return new_text;
	}

	new_text.len = 1;
	new_text.sentences[0] = text->sentences[0];

	wchar_t *sentence_copy, *new_sentence_copy;
	int flag = 0;
	for(int i = 1; i < text->len; i++){
		sentence_copy = make_lowercase_copy(text->sentences[i]);
		if(sentence_copy == NULL){
			free(new_text.sentences);
			new_text.sentences = NULL;
			return new_text;
		}

		for(int j = 0; j < new_text.len; j++){
			new_sentence_copy = make_lowercase_copy(new_text.sentences[j]);
			if(new_sentence_copy == NULL){
				free(new_text.sentences);
				new_text.sentences = NULL;
				return new_text;
			}

			if(!wcscmp(sentence_copy, new_sentence_copy)){
				flag = 1;
				free(new_sentence_copy);
				break;
			}
			free(new_sentence_copy);
		}
		if(!flag){
			new_text.sentences[new_text.len] = text->sentences[i];
			new_text.len++;
		}
		flag = 0;
		free(sentence_copy);
	}
	free(text->sentences);
	return new_text;
}

int check_format(struct Sentence sentence, int index, int minute_flag){
	wchar_t test_buffer[2];
	int test_number;
	if(!minute_flag){
		if(index > 0){
			if(iswdigit(sentence.words[index - 1])) test_buffer[0] = sentence.words[index - 1];
			else test_buffer[0] = L'0';
		}
		else test_buffer[0] = L'0';

		test_buffer[1] = sentence.words[index];

		test_number = (int)wcstol(test_buffer, NULL, 10);

		if(0 <= test_number && test_number <= 23) return test_number;
		else return -1;
	}
	else{
		test_buffer[0] = sentence.words[index + 2];
		test_buffer[1] = sentence.words[index + 3];
		test_number = (int)wcstol(test_buffer, NULL, 10);

		if(0 <= test_number && test_number <= 59) return test_number;
		else return -1;
	}
}

int **make_time_and_sentence_num_arr(struct Text *text, int *size){
	int **time_and_sentence_num_arr, allocated_memory = 1;

	time_and_sentence_num_arr = (int **)calloc(1, sizeof(int *));
	if(time_and_sentence_num_arr == NULL) return NULL;

	time_and_sentence_num_arr[0] = (int *)calloc(3, sizeof(int));
	if(time_and_sentence_num_arr[0] == NULL) return NULL;

	int test_number, value_flag;
	for(int i = 0; i < text->len; i++){
		for(int j = 0; j < text->sentences[i].len - 3; j++){
			if(
			iswdigit(text->sentences[i].words[j]) &&
			text->sentences[i].words[j + 1] == L':' &&
			iswdigit(text->sentences[i].words[j + 2]) &&
			iswdigit(text->sentences[i].words[j + 3])
			){
				test_number = check_format(text->sentences[i], j, 0);
				if(test_number == -1) continue;
				time_and_sentence_num_arr[(*size)][0] = test_number;

				test_number = check_format(text->sentences[i], j, 1);
				if(test_number == -1) continue;
				time_and_sentence_num_arr[(*size)][1] = test_number;

				time_and_sentence_num_arr[(*size)][2] = i + 1;

				(*size)++;

				if((*size) >= allocated_memory){
					allocated_memory *= 2;
					time_and_sentence_num_arr = (int **)realloc(time_and_sentence_num_arr, allocated_memory * sizeof(int *));
					if(time_and_sentence_num_arr == NULL) return NULL;
				}

				time_and_sentence_num_arr[(*size)] = (int *)calloc(3, sizeof(int));
				if(time_and_sentence_num_arr[(*size)] == NULL) return NULL;
			}
		}
	}

	return time_and_sentence_num_arr;
}

void delete_uppercase_letters(struct Text *text){
	int new_len;

	for(int i = 0; i < text->len; i++){
		new_len = text->sentences[i].len;

		for(int j = text->sentences[i].len - 1; j > -1; j--){
			if(iswupper(text->sentences[i].words[j]) &&
			!(1040 <= text->sentences[i].words[j] &&
			text->sentences[i].words[j] <= 1071)
			){
				for(int k = j; k < text->sentences[i].len - 1; k++){
					text->sentences[i].words[k] = text->sentences[i].words[k + 1];
				}

				new_len--;
			}
		}
		text->sentences[i].len = new_len;
		text->sentences[i].words[new_len] = L'\0';
	}
}

int compare(const void * first_sentence, const void * second_sentence)
{
  return ((struct Sentence *)second_sentence)->cyrillic_symbol_count - ((struct Sentence *)first_sentence)->cyrillic_symbol_count;
}

void sort_by_cyrillic_symbol_count(struct Text *text){
	for(int i = 0; i < text->len; i++){
		text->sentences[i].cyrillic_symbol_count = 0;
		for(int j = 0; j < text->sentences[i].len; j++){
			if(1040 <= text->sentences[i].words[j] && text->sentences[i].words[j] <= 1103){
				text->sentences[i].cyrillic_symbol_count++;
			}
		}
	}

	qsort(text->sentences, text->len, sizeof(struct Sentence), compare);
}

struct Text delete_sentences_without_special_symbols(struct Text *text){
	struct Text new_text;
	new_text.sentences = (struct Sentence *)calloc(text->len, sizeof(struct Sentence));
	if(new_text.sentences == NULL){
		return new_text;
	}
	new_text.len = 0;

	wchar_t *special_cymbols = L"№*$#@";

	for(int i = 0; i < text->len; i++){
		if(wcspbrk(text->sentences[i].words, special_cymbols) != NULL){
			new_text.sentences[new_text.len] = text->sentences[i];
			new_text.len++;
		}
	}

	free(text->sentences);
	return new_text;
}

int add_word(struct Sentence *new_sentence, struct Sentence sentence, int tmp_word_len, int word_len, int *allocated_memory, int *new_len, int tmp_word_index){
	wchar_t *long_word = L"(большое слово)";

	if(tmp_word_len > word_len){
		*allocated_memory += wcslen(long_word) - tmp_word_len;
		new_sentence->words = (wchar_t *)realloc(new_sentence->words, *allocated_memory * sizeof(wchar_t));
		if(new_sentence->words == NULL) return 0;
		
		wcscat(new_sentence->words, long_word);
		(*new_len) += wcslen(long_word);
	}
	else{
		if(tmp_word_len > 0){
			wcsncat (new_sentence->words, sentence.words + tmp_word_index, tmp_word_len);
			(*new_len) += tmp_word_len;
		}
	}
	return 1;
}

struct Text replace_long_words(struct Text *text){
	int word_len = text->sentences[0].len;
	struct Text new_text;
	new_text.len = text->len - 1;
	new_text.sentences = (struct Sentence *)calloc(new_text.len + 1, sizeof(struct Sentence));
	if(new_text.sentences == NULL){
		return new_text;
	}
	
	int word_flag, new_len, tmp_word_len, tmp_word_index, allocated_memory;
	for(int i = 1; i < text->len; i++){
		word_flag = 0;
		new_len = 0;
		tmp_word_len = 0;
		tmp_word_index = 0;
		allocated_memory = text->sentences[i].len + 1;

		new_text.sentences[i - 1].words = (wchar_t *)calloc(allocated_memory, sizeof(wchar_t));
		if(new_text.sentences[i - 1].words == NULL){
			free(new_text.sentences);
			new_text.sentences = NULL;
			return new_text;
		}
		
		for(int j = 0; j < text->sentences[i].len; j++){
			if(text->sentences[i].words[j] != L' ' && text->sentences[i].words[j] != L','){
				if(!word_flag){
					word_flag = 1;
					tmp_word_index = j;
				}

				tmp_word_len++;
			}
			
			if(text->sentences[i].words[j] == L' ' || text->sentences[i].words[j] == L',' || j == text->sentences[i].len - 1){
				word_flag = 0;

				int result = add_word(&(new_text.sentences[i - 1]), text->sentences[i], tmp_word_len, word_len, &allocated_memory, &new_len, tmp_word_index);
				if(!result){
					free(new_text.sentences);
					new_text.sentences = NULL;
					return new_text;
				}

				if(j != text->sentences[i].len - 1){
					new_text.sentences[i - 1].words[new_len] = text->sentences[i].words[j];
					new_len++;
				}

				tmp_word_len = 0;
			}
		}
	
		new_text.sentences[i - 1].len = new_len;
	}

	return new_text;
}