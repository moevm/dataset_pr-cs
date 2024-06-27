#include <wchar.h>
#define SEP L" ,.\n\t"

wchar_t* getSecondWord(wchar_t* sentence) {
    wchar_t new_sentence[wcslen(sentence)+1];
    wcscpy(new_sentence, sentence);
    wchar_t *word;
    wchar_t *ptr;
    word = wcstok(new_sentence, SEP, &ptr);
    word = wcstok(NULL, SEP, &ptr);
    if (word == NULL) {
			word = L"";
	}
    return word;
}