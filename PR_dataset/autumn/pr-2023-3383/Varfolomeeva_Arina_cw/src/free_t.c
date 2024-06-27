#include "struct.h"
#include "free_t.h"
void free_t(Text txt) {
	for (int i = 0; i < txt.length; i++) {
		free(txt.text[i]);
	}
	free(txt.text);
}
