#include<locale.h>
#include "input_output.h"
#include "actions.h"

int main(){
    Text text;
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.1, created by Ekaterina Maksimova\n");
    wchar_t command = ' ';
    command = getwchar();
    getwchar();
    Sentence find;
    Word replaceTo;
    Word replaceFrom;
    switch(command){
        case '0':
            text = readText();
            removeEmptySentences(&text);
            removeCopies(&text);
            printText(text);
            freeText(&text);
            break;
        case '1':
            text = readText();
            removeEmptySentences(&text);
            removeCopies(&text);
            printAnagrams(text);
            freeText(&text);
            break;
        case '2':
            text = readText();
            removeEmptySentences(&text);
            removeCopies(&text);
            sortSentences(&text);
            printText(text);
            freeText(&text);
            break;
        case '3':
            text = readText();
            removeEmptySentences(&text);
            removeCopies(&text);
            changeVowels(&text);
            printText(text);
            freeText(&text);
            break;
        case '4':
            replaceTo = readWord();
            replaceFrom = readWord();
            text = readText();
            removeEmptySentences(&text);
            removeCopies(&text);
            changeWords(&text, replaceFrom, replaceTo);
            printText(text);
            freeText(&text);
            break;
        case '5':
            wprintf(L"0 - Вывести текст после первичной обработки.\n");
            wprintf(L"1 - Вывести все предложения, которые являются анаграммами друг для друга.\n");
            wprintf(L"2 - Отсортировать предложения по количеству заглавных букв в предложении.\n");
            wprintf(L"3 - Заменить каждую гласную буквы двумя другими буквами идущими следующими по алфавиту.\n");
            wprintf(L"4 - Заменить все вхождения одного слова на другое слово\n");
            wprintf(L"5 - Справка\n");
            break;
		case '9':
			text = readText();
			removeEmptySentences(&text);
            removeCopies(&text);
            countSymbols(&text);
            printText(text);
			freeText(&text);
			break;
        default:;
    }
    return 0;
}
