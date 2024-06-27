#include "Structs.h"
#include "TextRead.h"
#include "DelRepStr.h"
#include "PaintWords.h"
#include "RemoveNumText.h"
#include "SortLenLast.h"
#include "PrintText.h"
#include "PrintUpper.h"
#include "CountSum.h"


int main(){
setlocale(LC_ALL, ""); 
wprintf(L"Course work for option 5.7, created by Anton Usikov.\n");
int opt=-1;
int c;
struct Text T;
wscanf(L"%d%c", &opt, &c);
switch (opt) {
case 0:
	T = TextRead();
	DelRepStr(&T);
	PrintText(&T);
	break;
case 1:
	T = TextRead();
	DelRepStr(&T);
	PaintWords(&T);
	break;
case 2: 
	T = TextRead();
	DelRepStr(&T);
	PrintText(&T);
	PrintUpper(&T);
	break;
case 3:
	T = TextRead();
	DelRepStr(&T);
	SortLenLast(&T);
	PrintText(&T);
	break;
case 4:
	T = TextRead();
	DelRepStr(&T); 
	RemoveNumText(&T);
	PrintText(&T);
	break;
case 5:
	wprintf(L"1) “Раскрасить” каждое слово в зависимости от остатка от деления его длины на 4. Если остаток равен 0 - красный цвет, 1 - синий, 2 - зеленый, 3 - желтый.\n2) Распечатать каждое слово, которое начинается и заканчивается на заглавную букву, и номера предложений, в которых оно встречается .\n3) Отсортировать предложения по длине последнего слова в предложении.\n4) Удалить все числа из предложений. Число - набор подряд идущих цифр, перед и после которого стоят пробелы.\n8)Вывести для каждого предложения сумму всех чисел в нем.\n"); 
	break;
case 8:
	T = TextRead();
	DelRepStr(&T); 
	CountSum(&T);
	break;
default:   
	wprintf(L"Error: Неверный номер команды\n");  
	break;
}
 return 0;   
}  
