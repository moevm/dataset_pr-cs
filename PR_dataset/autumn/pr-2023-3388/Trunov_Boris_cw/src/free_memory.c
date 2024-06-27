#include "free_memory.h"

void free_memory(Text* text){
	for (size_t i = 0; i < text->length; i++){
		free(text->text[i]->sentence);
		free(text->text[i]);
	}
	free(text);
}
