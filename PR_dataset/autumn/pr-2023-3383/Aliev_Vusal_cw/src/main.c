#include "Common.h"
#include "Function1.h"
#include "Function8.h"
#include "Function2.h"
#include "Function3.h"
#include "Function4.h"
#include "FunctionText.h"
#include "FunctionObrText.h"
#include "FreeMemory.h"
#include "FreeMemory1.h"
#include "OutText.h"
#include "OutFunc1.h"

int main(void) {
	puts("Course work for option 4.6, created by Vusal Aliev.");
	int command;
	scanf("%d", &command);

	/*if (command > 5 || command < 0){
		puts("Error: введена несущетсвующая команда");
		return 0;
	}*/
	int count_sent;
	
	if (command  == 5){
		printf("Cправка о функциях:\n 0 – вывод текста после первичной обязательной обработки (если предусмотрена заданием данного уровня сложности)\n 1 – вызов функции под номером 1 из списка задания\n 2 – вызов функции под номером 2 из списка задания\n 3 – вызов функции под номером 3 из списка задания\n 4 – вызов функции под номером 4 из списка задания\n 5 – вывод справки о функциях, которые реализует программа.\n");
		return 0;
	}

	char** text = FunctionText(&count_sent);
	FunctionObrText(text, &count_sent);
	CountWord* result; 
	int res;

	if (count_sent == 0){
		puts("Eror: отстуствует текст");
	}

	switch (command) {
	case 0:
		OutText(text);
		FreeMemory(text);
		break;
	case 1:
		result = Function1(text,&res);
		OutFunc1(result, &res);
		FreeMemory1(result, &res);
		break;
	case 2:
		Function2(text);
		OutText(text);
		FreeMemory(text);
		break;
	case 3:
		Function3(text);
		OutText(text);
		FreeMemory(text);
		break;
	case 4:
		Function4(text, &count_sent);
		OutText(text);
		FreeMemory(text);
		break;
	case 8:
		Function8(text, &count_sent);
		FreeMemory(text);
		break;
	}
	return 0;
}
