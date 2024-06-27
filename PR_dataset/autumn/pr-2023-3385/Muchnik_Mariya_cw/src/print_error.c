#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#define RED "\033[0;31m"
#define NONE "\033[0m"

void print_error(wchar_t* error){
	wprintf(L"%sError: <%ls>%s\n", RED, error, NONE);
}
