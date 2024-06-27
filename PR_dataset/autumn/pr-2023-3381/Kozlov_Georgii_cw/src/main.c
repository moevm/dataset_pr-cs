#include <stdio.h>
#include "struct_define.h"
#include "headers.h"


void print_text(struct Text text){
    for (int i = 0; i < text.len; i++){
        wprintf(L"%ls\n", text.text[i]->str);
    }
}          


int main()
{
	setlocale(LC_ALL, "");
	wprintf(L"Course work for option 5.15, created by Kozlov Georgii.\n");
	struct Text text;
	int a;
	wchar_t c;
	int len_w = 0;
	wchar_t* first_word = malloc(100 * sizeof(wchar_t));
    wscanf(L"%d\n", &a);
    if (a == 5){
        wprintf(L" 0)Вывод текста после первичной обработки, которая удаляет все одинаковые предложения.\n 1)Заменяет все подстроки high noon на полдень и полночь на midnight.\n 2)Находит и выводит все даты в тексте заданные в виде DD/MM/YYYY или YYYY-MM-DD в порядке возрастания этих дат.\n 3)Удаляет все предложения, которые начинаются и заканчиваются на одно и то же слово.\n 4)Для всех вхождений дат в тексте вида <day> <month> <year>, \nвыводит эти даты в виде DD.MM.YYYY и строку Happened, если эта дата была до текущей и Not Happened в противном случае.\n Например, для даты 03 Jan 1666 вывести 03.01.1666 Happened.");
        return 0;
    }
	switch (a)
	{
		case (0):
			text = get_text();
			text = delete_same_sentance(text);
			print_text(text);
			break;
		case (1):
			text = get_text();
			text = delete_same_sentance(text);
			text = replace_words(text);
			print_text(text);
			break;
		case (2):
			text = get_text();
			text = delete_same_sentance(text);
			print_sorted_dates(text);
			break;
		case (3):
			text = get_text();
			text = delete_same_sentance(text);
			text = delete_same_start_end(text);
			print_text(text);
			break;
		case (4):
			text = get_text();
			text = delete_same_sentance(text);
			happened_dates(text);
			break;
        case (9):
			do{
				c = getwchar();
				if (c == '\n'){break;}
				first_word[len_w] = c;
				len_w++;
			}
			while(c != '\n');
			first_word[len_w + 1] = '\0';
			text = get_text();
			text = delete_same_sentance(text);
            additional_task(text, first_word);
            break;
		default:
			wprintf(L"Ошбика ввода!\n");
			break;
	}

	return 0;
}
