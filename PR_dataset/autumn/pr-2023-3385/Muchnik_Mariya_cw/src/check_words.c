#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>

#include "struct.h"

wchar_t* to_lower(wchar_t* word){
	wchar_t* nword = (wchar_t*)calloc(wcslen(word)+1, sizeof(wchar_t));
	wcscpy(nword, word);
    for (int i = 0; i < wcslen(word); i++)
        if (iswupper(word[i])) nword[i] = towlower(word[i]);
    return nword;
}

int is_ok(wchar_t* first, wchar_t* word){
	int flag = 1;
	for (int i = 0; i < wcslen(word); i++){
		if (!wcschr(first, word[i])) {
			flag = 0;
			break;
		}
	}
	return flag;
}

void check(wchar_t* first, wchar_t* sent){
	wchar_t dsent[wcslen(sent)];
    wcscpy(dsent, sent);

    wchar_t* pt; 
    wchar_t* word = wcstok(dsent, L" ,.", &pt);
	while(word){
		wchar_t* nword = to_lower(word);
		if (is_ok(first, nword)) wprintf(L"%ls\n", word);
		free(nword);
		word = wcstok(NULL, L" ,.", &pt);
	}
}

void check_words(struct Text txt){
	wchar_t dsent[txt.ptr[0]->len+1];
	wcscpy(dsent, txt.ptr[0]->ptr);	
	wchar_t* pt;
	wchar_t* word = wcstok(dsent, L"\n", &pt);
	word = to_lower(word);
	check(word, pt);

	for (int i = 1; i < txt.len; i++){
		check(word, txt.ptr[i]->ptr);
	}
	free(word);
}

