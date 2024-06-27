#include "del_extra.h"
#include "struct.h"

Sentence *del_extra(Sentence *sentence) {
	for (int i = 0; i < sentence->length; i++) {
		if (sentence->string[i] == L'\t' || sentence->string[i] == L' ') {
			sentence->string = sentence->string + 1;
			sentence->length--;
		} else break;
	}
	return sentence;
}
