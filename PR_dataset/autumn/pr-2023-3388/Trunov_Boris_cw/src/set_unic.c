#include "set_unic.h"

void set_unic(Text * text){
	size_t length_unic_array = 0;
	wchar_t * unic_array = malloc(sizeof(wchar_t));
	size_t flag_is_unic = 0;
	for (size_t i = 0; i < text->length; i++){
		for (size_t x = 0;x < wcslen(text->text[i]->sentence); x++){
			flag_is_unic = 1;
			for (size_t f = 0;f < length_unic_array;f++){
				if(text->text[i]->sentence[x] == unic_array[f]){
					flag_is_unic = 0;
					break;
				}
			}
			if(flag_is_unic == 1 && text->text[i]->sentence[x] != SYMBOL_SPACE){
				unic_array = realloc(unic_array, sizeof(wchar_t)*(++length_unic_array + 1));
				unic_array[length_unic_array - 1] = text->text[i]->sentence[x];
			}
		}
	}
	for (size_t x = 0; x < length_unic_array;x++){
		wprintf(L"%lc ", unic_array[x]);
	}
	free(unic_array);
	wprintf(L"\n");
}
