#include <stdlib.h>
#include <wchar.h>

#include "safety.h"



void * s_malloc(size_t size)
{
	void * ptr = malloc(size);
	if (ptr == NULL)
	{
		printerr(11);
		exit(11);
	}
	return (ptr);
}



void * s_realloc(void * oldptr, size_t size)
{
	void * ptr = realloc(oldptr, size);
	if (ptr == NULL)
	{
		printerr(12);
		exit(12);
	}
	return (ptr);
}



void printerr(char type)
{
	switch (type)
	{
		case (11):
		case (12):
			wprintf(L"Error: превышен лимит памяти программы");
			break;
		default:
			wprintf(L"Error: неизвестная ошибка");
			break;
	}
}