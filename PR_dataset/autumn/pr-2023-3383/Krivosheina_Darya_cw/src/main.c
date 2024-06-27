#include "read.h"
#include "date.h"
#include "reverse.h"
#include "struct.h"
#include "delete.h"
#include "sort.h"
#include "search_word.h"
#include "free_all.h"

int main(){
    setlocale(LC_CTYPE, "");
    wprintf(L"Course work for option 5.8, created by Darya Krivosheina.\n");
    int n;
    wscanf(L"%d\n", &n);
    if (n == 5){
        wprintf(L"Функция 0: вывод текста после первичной обработки.\nФункция 1: вывод строки-даты предложения, где день — количество слов в предложении, месяц — наибольшая длина слова в предложении, год — общее количество символов в предложении +1900.\nФункция 2: вывод предложений таким образом, чтобы слова шли в обратном порядке.\nФункция 3: сортировка предложений по длине первого слова.\nФункция 4: удаление предложений, у которых длина всех слов не больше 3 символов.\n");
        return 0;
    } 
    if (n == 9){
    	wchar_t word[100];
	fgetws(word, 100, stdin);
	word[wcslen(word) - 1] = '\0';
	struct Text full_text;
	full_text = read();
	search_word(full_text, word);
	return 0;
    }
    struct Text full_text;
    full_text = read();
    if (full_text.len == 0){
    	wprintf(L"Error: ничего не введено.\n");
    	return 0;
    }
    if (n == 0){
    	for (int t = 0; t < full_text.len; t++){
    		if (t != 0){
        		wprintf(L"\n");
        	}
        	for (int t1 = 0; t1 < wcslen(full_text.text[t]); t1++){
            	wprintf(L"%lc", full_text.text[t][t1]);
        	}
    	}
    	wprintf(L"\n");
    } else if (n == 1){
        date(full_text);
    } else if (n == 2){
        for (int f = 0; f < full_text.len; f++){
        	reverse(full_text.text[f]);
        }
    } else if (n == 3){
        sort(&full_text);
        for (int f1 = 0; f1 < full_text.len; f1++){
        	wprintf(L"%ls\n", full_text.text[f1]);
		}
    } else if (n == 4){
    	wchar_t **text2 = malloc(full_text.len * sizeof(wchar_t**));  // создание массива для нового текста без неподходящих предложений
    	int len_text2 = 0;
	    for (int w = 0; w < full_text.len; w++){
			if (wcscmp(delete(full_text.text[w]), L"0") != 0){  // сравнение возвращенной строки с 0 
		    		text2[len_text2] = full_text.text[w];  // добавление предложения в массив только в случае прохождения проверки
		    		len_text2++;
			}
	    }
	    full_text.text = text2;  // замена текста в структуре на новый
	    full_text.len = len_text2;  // замена длины в структуре на новую 
		for (int w1 = 0; w1 < full_text.len; w1++){  // вывод 
		    wprintf(L"%ls\n", full_text.text[w1]);
		}
    } else {
        wprintf(L"Error: нет функции с таким номером.\n");
    }
    free_all(&full_text);
    return 0;
}
