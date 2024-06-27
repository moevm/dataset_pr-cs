#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include "structs.h"
#include "text_processing.h"
#include "input.h"
#include "output.h"
#include "del_uppercase.h"
#include "get_time_substr.h"
#include "sort_cyrillic.h"
#include "del_sents_with_spec_symb.h"
#include "replace_if_bigger.h"

int main()
{
	setlocale(LC_ALL, "");
	wprintf(L"Course work for option 5.11, created by Petr Korshunov.\n");
	int action;
	if (wscanf(L"%d", &action) == 0)
	{
		wprintf(L"Error: incorrect action with text.\n");
		exit(0);
	}
	TEXT text;
	switch (action)
	{
	case 0:
		text = readText();
		printText(&text);
		freeText(&text);
		break;

	case 1:
		text = readText();
		getTimeSubstrings(&text);
		freeText(&text);
		break;

	case 2:
		text = readText();
		delUpperCase(&text);
		printText(&text);
		freeText(&text);
		break;

	case 3:
		text = readText();
		qsort(text.sents, text.len, sizeof(SNT *), cmp);
		printText(&text);
		freeText(&text);
		break;

	case 4:
		text = readText();
		delSentsWithSpecSymbs(&text);
		printText(&text);
		freeText(&text);
		break;

	case 5:
		wprintf(L"Info about actions with text:\n\n");
		wprintf(L"Action - 1: For each substring in the text that sets the time in the form “clock:minutes”,\nprint the number of the sentence in which it occurs and the number of minutes\nbefore the current time (the time at which this task began to run).\n\n");
		wprintf(L"Action - 2: Delete all uppercase Latin letters in each sentence.\n\n");
		wprintf(L"Action - 3: Sort sentences by reducing the number of Cyrillic letters.\n\n");
		wprintf(L"Action - 4: Delete all sentences that do not contain special characters (№*$#@).\n\n");
		break;

	case 9:
		text = readText();
		replaceIfBigger(&text);
		printText(&text);
		freeText(&text);
		break;

	default:
		wprintf(L"Error: incorrect action with text.\n");
		exit(0);
	}
	return 0;
}