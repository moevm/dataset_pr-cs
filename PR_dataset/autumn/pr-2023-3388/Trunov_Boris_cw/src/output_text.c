#include "output_text.h"

void output_text(Text * text){
	for(size_t i = 0; i < text->length; i++){
		wprintf(L"%ls\n", text->text[i]->sentence);
	}
}
