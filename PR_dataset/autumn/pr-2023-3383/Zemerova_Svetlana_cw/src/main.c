#include <stdlib.h>
#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include "struct.h"
#include "input_output.h"
#include "freememory.h"
#include "functions.h"

int main(){
	setlocale(LC_ALL, "");
	wprintf(L"Course work for option 5.1, created by Svetlana Zemerova.\n");
	int number;
	Text T;
	wscanf(L"%d",&number);
	switch(number){
		case 0 ... 3:
			T=input();
			output(T, number);
			freememory(T);
			break;
		case 4:
			output(T, number);
			break;
		case 5:
			function5();
			break;
		case 9:
			output(T, number);
			break;
		default:
			wprintf(L"Error: введена несуществующая команда.\n");
			wprintf(L"Завершение работы программы.\n");
			break;
	}
	return 0;
}
