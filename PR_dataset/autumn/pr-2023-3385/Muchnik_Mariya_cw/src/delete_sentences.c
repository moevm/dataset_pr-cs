#include <wchar.h>
#include <stdlib.h>

#include "struct.h"

struct Text del_sent(struct Text txt, size_t n){
	free(txt.ptr[n]->ptr);
	free(txt.ptr[n]);
	for (size_t i = n; i < txt.len-1; i++){
		txt.ptr[i] = txt.ptr[i+1];
	}
	txt.len--;
	return txt;
}

struct Text delete_sentences(struct Text txt){
	for (size_t i = 0; i < txt.len; i++){
		wchar_t* last_word = txt.ptr[i]->ptr;
		wchar_t* last_space = wcsrchr(txt.ptr[i]->ptr, L' ');
		wchar_t* last_comma = wcsrchr(txt.ptr[i]->ptr, L',');
		if (last_space > 0 || last_comma > 0){
			if (last_space > last_comma) 
					last_word = last_space+1;
			else last_word = last_comma+1;
		}
		
		int flag = 1;
		wchar_t* vowels = L"aeiouyаоуыэяёюие";
		while (flag && (last_word < txt.ptr[i]->ptr+txt.ptr[i]->len)){
			if (wcscspn(last_word, vowels) >= 3) flag = 0;
			last_word++;
		}
		if (!flag) {
			txt = del_sent(txt, i);
			i--;
		}
	}
	return txt;
}
