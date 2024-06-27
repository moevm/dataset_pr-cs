#pragma once

// malloc(), but complain and exit instead of null
void * s_malloc(size_t size);
// realloc(), but complain and exit instead of null
void * s_realloc(void * oldptr, size_t size);
// The function for advanced complaining
void printerr(char type);
