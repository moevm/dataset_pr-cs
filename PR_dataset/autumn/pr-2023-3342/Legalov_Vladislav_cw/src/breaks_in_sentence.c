#include "breaks_in_sentence.h"


void insert_breaks(Sentence* sentence, BreaksData* breaks){
	size_t size = sentence->size + breaks->size * breaks->size_breaks;
	wchar_t* str = calloc((size + 1), sizeof(wchar_t));
	wchar_t* source_ptr_left = sentence->str;
	wchar_t* source_ptr_right;
	wchar_t* current_ptr = str;
	if (breaks->size_breaks >= 0)
	for (int i = 0; i <= breaks->size; ++i){
		source_ptr_right = sentence->str + 1 + (i < breaks->size? breaks->breaks_pos[i]: sentence->size);
		memcpy(current_ptr, source_ptr_left, (source_ptr_right - source_ptr_left) * sizeof(wchar_t));
		current_ptr += source_ptr_right - source_ptr_left + breaks->size_breaks;
		source_ptr_left = source_ptr_right;
	}
	else
	for (int i = 0; i <= breaks->size; ++i){
		source_ptr_right = sentence->str + 1 + (i < breaks->size? breaks->breaks_pos[i]: sentence->size);
		memcpy(current_ptr, source_ptr_left, (source_ptr_right - source_ptr_left) * sizeof(wchar_t));
		current_ptr += source_ptr_right - source_ptr_left;
		source_ptr_left = source_ptr_right - breaks->size_breaks;
	}
	for (int i = 0; i < size; ++i)
		if (str[i] == '\0') str[i] = ' ';
	str[size] = '\0';
	free(sentence->str);
	sentence->str = str;
	sentence->size = size;
}

BreaksData* create_breaks_data(int *array, int size, int size_breaks){
	BreaksData* res = malloc(sizeof(BreaksData));
	res->breaks_pos = array;
	res->size = size;
	res->size_breaks = size_breaks;
	return res;
}

void free_breaks_data(BreaksData* breaks){
	if(breaks->breaks_pos)
		free(breaks->breaks_pos);
	free(breaks);
}
