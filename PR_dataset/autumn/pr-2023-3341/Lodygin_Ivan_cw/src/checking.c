#include <wchar.h>
#include <wctype.h>

int checking(wchar_t word[], wchar_t first_word[]) {
	int checkbox = 1;
	for(int i = 0; i < wcslen(word); i++){
		if(wcschr(first_word, towupper(word[i])) == NULL) checkbox = 0;
	}
	return checkbox;
}