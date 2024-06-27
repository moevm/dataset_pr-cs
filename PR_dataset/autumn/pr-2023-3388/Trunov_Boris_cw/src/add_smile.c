#include "add_smile.h"

void add_smile(Text * text){
	for (size_t i = 0; i < text->length; i++){
		wchar_t * context = NULL;
		wchar_t * current_word = wcstok(text->text[i]->sentence, L" ", &context);
		while(current_word != NULL){
			int flag = 0;
			if (!wcscmp(current_word, L"smile")){
				wprintf(L"%ls :=) ",current_word);	
				flag = 1;			
			}
			if (!wcscmp(current_word, L"smile,")){
				wprintf(L"smile :=), ");
				flag = 1;
			}
			if (!wcscmp(current_word, L"smile.")){
				wprintf(L"smile :=).");
				flag = 1;
			}
			if (!wcscmp(current_word, L"smile:")){
				wprintf(L"smile :=): ");
				flag = 1;
			}
			if (flag == 0){
				if (current_word[wcslen(current_word)-1] == L'.'){
					wprintf(L"%ls", current_word);
				}else{
					wprintf(L"%ls ", current_word);		
				}
			}
			flag = 0;
			current_word = wcstok(NULL, L" ", &context);
		}
		wprintf(L"\n");
	}
}
