#include "print_t.h"
#include "struct.h"

void print_t(Text txt) {
	for (int i = 0; i < txt.length; i++) {
		wprintf(L"%ls\n", txt.text[i]->string);
	}
}
