#include "errors.h"
#include <locale.h>

void ThrowError(int code, void* p)
{
	setlocale(LC_ALL, "");
	fwprintf(stderr, L"Error: ");
	if (code == 0) fwprintf(stderr, L"Недостаточно памяти для выполнения операции\n");
	if (code == 1) fwprintf(stderr, L"Функции не существует\n");
	free(p);
	exit(0);
}