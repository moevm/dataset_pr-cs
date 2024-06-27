#include<locale.h>
#include<wctype.h>
#include<wchar.h>
#include"../headers/textfuncs.h"

int main()
{
	setlocale(LC_CTYPE, "");
	wprintf(L"Course work for option 5.1, created by Vladislav Boitsov.\n");
	menu();
	return 0;
}
