#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

#include "struct.h"

int to_int(wchar_t* word){
	int result = 0;
	int d = 1;
	for(int i = wcslen(word)-1; i >= 0; i--){
		result += ((int)word[i]-48) * d;
		d *= 10;
	}
	return result;
}

void get_minutes(struct Text txt){
	float secs = 0;
	for (size_t i = 0; i < txt.len; i++){
		if (wcsstr(txt.ptr[i]->ptr, L"sec") > 0){
			wchar_t sent_cp[txt.ptr[i]->len+1];
			wcscpy(sent_cp, txt.ptr[i]->ptr);
			wchar_t* pt;
			wchar_t* ptr = wcstok(sent_cp, L" ,.", &pt);
			wchar_t* word;
			while (ptr != NULL){
				if (!wcscmp(ptr, L"sec"))
					secs += to_int(word);
				word = ptr;
				ptr = wcstok(NULL, L" ,.", &pt);
			}
		}
	}
	wprintf(L"%f\n", secs/60);
}

