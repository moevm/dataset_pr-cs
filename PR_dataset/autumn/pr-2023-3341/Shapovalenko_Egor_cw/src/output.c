#include "output.h"

void print_text(struct Text text)
{
	for (int i = 0; i < text.len; i++)
	{
		wprintf(L"%ls.\n", text.sentences[i].words);
	}
}

void print_time_and_sentence_num_arr(int *time_and_sentence_num, int minutes){
	if(time_and_sentence_num[1] < 10) wprintf(L"%d: \x1b[32m%d:0%d\x1b[0m -- \x1b[32m%d\x1b[0m минут до текущего времени\n", time_and_sentence_num[2], time_and_sentence_num[0], time_and_sentence_num[1], minutes);
	else wprintf(L"%d: \x1b[32m%d:%d\x1b[0m -- \x1b[32m%d\x1b[0m минут до текущего времени\n", time_and_sentence_num[2], time_and_sentence_num[0], time_and_sentence_num[1], minutes);
}

void print_error(int code)
{
	if (code == 0)
		wprintf(L"\x1b[31mError: некорректная команда\n\x1b[0m");
	if(code == 1)
		wprintf(L"\x1b[31mError: не удалось выделить память\n\x1b[0m");
	if(code == 2)
		wprintf(L"\x1b[31mError: пустой ввод\n\x1b[0m");
}

void print_manual(){
	wprintf(L"\x1b[36m0 -- первичная обработка текста: запись в структуру Text, удаление повторно встречающихся предложений (вне зависимости от регистра)\n"
	L"1 -- первичная обработка текста, вывод для каждой подстроки вида \"hh:mm\" или \"h:mm\" номера предложения, в котором она встречается, самой подстроки и количества минут до текущего времени (времени начала выполнения задачи)\n"
	L"2 -- первичная обработка текста, удаление всех заглавных латинских букв\n"
	L"3 -- сортировка предложений по убыванию количества кириллических букв\n"
	L"4 -- первичная обработка текста, удаление всех предложений без специальных символов (№*$#@)\n"
	L"5 -- вызов справки о функциях\n\x1b[0m");
	return;
}