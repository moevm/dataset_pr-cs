#include "func.h"
#include "getprint.h"
#include <stdio.h>

int main() {
	setlocale(LC_CTYPE,"");
	wprintf(L"Course work for option 5.3, created by Vitalii Traksel\n");
	int key;
	wscanf(L"%d", &key);
	switch(key) {
	    case 0: {
	        struct Text * my_text = get_text();
	        print_text(my_text);
	        free_text(my_text);
			break;
		}
		case 1: {
	        struct Text * my_text = get_text();
	        sample(my_text);
	        free_text(my_text);
			break;
		}
	    case 2:{
			struct Text * my_text = get_text();
	        first_upper(my_text);
	        print_text(my_text);
	        free_text(my_text);
			break;
			}
		case 3:{
			struct Text * my_text = get_text();
	        vowel_sort(my_text);
	        free_text(my_text);
			break;
			}
		case 4:{
			struct Text * my_text = get_text();
	        num_repeat(my_text);
	        free_text(my_text);
			break;
			}
		case 8:{
			struct Text * my_text = get_text();
			func8(my_text);
			free_text(my_text);
			break;
		}	
		
		case 5:
			wprintf(L"0 – Вывод текста после первичной обязательной обработки\n");
			wprintf(L"1 – Для каждого предложения вывести строку образец, удовлетворяющую каждому слову в предложении\n");
			wprintf(L"2 – Удалить все предложения, в которых нет заглавных букв в начале слова\n");
			wprintf(L"3 – Отсортировать слова в предложении по количеству гласных букв в слове\n");
			wprintf(L"4 – Для каждого предложения вывести количество одинаковых слов в строке\n");
			wprintf(L"5 – Вывод справки о функциях, которые реализует программа\n");
			break;
		default:
			wprintf(L"Error: Неверная команда\n");
	}
	return 0;
}

