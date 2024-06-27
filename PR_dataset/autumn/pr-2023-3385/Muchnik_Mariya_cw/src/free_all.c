#include <stdlib.h>
#include <wchar.h>

#include "struct.h"

void free_all(struct Text txt){
	for(size_t i = 0; i < txt.len; i++){
		free(txt.ptr[i]->ptr); 
		free(txt.ptr[i]);
	}
	free(txt.ptr);
}
