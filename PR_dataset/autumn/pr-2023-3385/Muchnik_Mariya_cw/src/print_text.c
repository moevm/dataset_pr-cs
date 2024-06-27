#include <stdio.h>
#include <wchar.h>

#include "struct.h"

void print_text(struct Text text){
	for (size_t i = 0; i < text.len; i++)
		wprintf(L"%ls\n", text.ptr[i]->ptr);
}
