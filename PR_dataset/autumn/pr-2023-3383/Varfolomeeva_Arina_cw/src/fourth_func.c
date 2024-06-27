#include "fourth_func.h"
#include "struct.h"

Text fourth_func(Text txt) {
	Sentence **new_txt = (Sentence **)malloc(txt.length * sizeof(Sentence *));
	int length = 0;
	wchar_t *digits = L"0123456789";
	for (int i = 0; i < txt.length; i++) {
		if (wcschr(txt.text[i]->string, L'#') || wcschr(txt.text[i]->string, L'%')) {
			if (wcspbrk(txt.text[i]->string, digits)) {
				new_txt[length] = txt.text[i];
				length++;
			}
		}
		else {
			new_txt[length] = txt.text[i];
			length++;
		}
	}	
	Text new_text = {new_txt, length};
	return new_text;
}
