#include "menu.h"



int main(){
	setlocale(LC_ALL, "");
	wprintf(FIRST_STRING);
	int task;
	if(wscanf(L"%d", &task))
		menu(task);
	else
		wprintf(L"Error: incorrect value\n");
	return 0;
}
