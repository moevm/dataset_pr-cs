#include "del_duplicates.h"
#include "struct.h"

Text del_duplicates(Text txt) {
	Sentence **new_txt = (Sentence **)malloc(txt.length * sizeof(Sentence *));
	int length = 0;
	for (int i = 0; i < txt.length; i++) {
		Text new_text = {new_txt, length};
		int flag = 0;
		for (int j = 0; j < length; j++) {
			if (!wcscasecmp(txt.text[i]->string, new_text.text[j]->string)) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			new_txt[length] = txt.text[i];
			length++;
		}
	}	
	Text new_text = {new_txt, length};
	return new_text;
}
