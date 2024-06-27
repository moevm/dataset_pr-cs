#include "struct.h"
#include "free_all.h"

void free_all(struct Text *full_text){
	for (int e = 0; e < full_text->len; e++){
		free(full_text->text[e]);
	}
	free(full_text->text);
}
