#include "menu.h"
#include <stdio.h>

void replace_to_big_word(Text *text, wchar_t *word){
	for(int i = 0; i < text->size; ++i)
		replace_word_in_sentense(text->sentences[i], word);
}

void replace_word_in_sentense(Sentence* sentence, wchar_t * word){
	wchar_t* duplicate = wcsdup(sentence->str);
	
	int size_word = wcslen(word);
	wchar_t* buffer = malloc(sizeof(wchar_t) * sentence->size * 100);
	buffer[0] = '\0';
	int buffer_size = sentence->size * 100;
	int *pos = malloc(sizeof(int) * sentence->size);
	int *islong = malloc(sizeof(int) * sentence->size);
	int count = 0;
	
	wchar_t* p;
	wchar_t* ptr = wcstok(duplicate, L" ", &p);
	islong[count] = (wcslen(ptr) > size_word);
	pos[count++] = ptr - duplicate;
	while(ptr = wcstok(NULL, L" ", &p)){
		islong[count] = (wcslen(ptr) > size_word);
		pos[count++] = ptr - duplicate;
		sentence->str[ptr - duplicate] = '\0';
	}
	wchar_t *sent = sentence->str;
	if (islong[0]){
			if (duplicate[pos[0] + wcslen(&duplicate[pos[0]]) - 1] == L',')
				swprintf(buffer, buffer_size, L"%ls%ls", buffer, L"(большое слово),");
			else
				swprintf(buffer, buffer_size, L"%ls%ls", buffer, L"(большое слово)");
		}
		else{
			swprintf(buffer, buffer_size, L"%ls%ls", buffer, &duplicate[pos[0]]);
		}
	for(int i = 1; i < count; ++i){
		if (islong[i]){
			if (duplicate[pos[i] + wcslen(&duplicate[pos[i]]) - 1] == L',')
				swprintf(buffer, buffer_size, L"%ls%ls", buffer, L"(большое слово),");
			else
				swprintf(buffer, buffer_size, L"%ls%ls", buffer, L"(большое слово)");
		}
		else{
			swprintf(buffer, buffer_size, L"%ls %ls", buffer, &duplicate[pos[i]]);
		}
	}
	free(sentence->str);
	sentence->str = buffer;
}



void menu(int task){
Text* text = NULL;
switch(task){
	case 0:
		text = input_text();
		print_text(text);
		free_text(text);
		break;
	case 1:
		text = input_text();
		Text* anagrams = find_anagrams(text);
		print_text(anagrams);
		free(anagrams->sentences);
		free(anagrams);
		free_text(text);
		break;
	case 2:
		text = input_text();
		sort_text(text);
		print_text(text);
		free_text(text);
		break;
	case 3:
		text = input_text();
		replace_vowel_in_text(text);
		print_text(text);
		free_text(text);
		break;
	case 4:
		text = input_text();
		if (replace_words_in_text(text))
			print_text(text);
		else
			wprintf(L"Error: incorrect value\n");
		free_text(text);
		break;
	case 5:
		wprintf(L"%ls%ls%ls%ls%ls", INTRODUCION_STR_ONE, INTRODUCION_STR_TWO, INTRODUCION_STR_THREE, INTRODUCION_STR_FOUR, INTRODUCION_STR_FIVE);
		break;
	case 9:
		getwchar();
		wchar_t *word = malloc(sizeof(wchar_t) * 200);
		fgetws(word, 200, stdin);
		word[wcslen(word) - 1] = '\0';
		text = input_text();
		replace_to_big_word(text, word);
		print_text(text);
		free_text(text);
		break;
	default:
		wprintf(L"Error: unknown value\n");
	}
	
}
