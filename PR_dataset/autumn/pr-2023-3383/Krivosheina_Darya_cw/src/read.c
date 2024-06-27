#include "read.h"
#include "struct.h"
#define TEXT 15
#define SENT 30

struct Text read(){
    setlocale(LC_CTYPE, ""); // подключение кириллицы
    wchar_t **text = malloc(TEXT * sizeof(wchar_t*)); 
    wchar_t *sent = malloc(SENT * sizeof(wchar_t));
    int len_text = 0, len_sent = 0;
    int cap_sent = SENT, cap_text = TEXT; // переменные для расширения памяти блоками
    wchar_t g; // считываемый символ
    int flag = 0, flag1 = 1; // flag: для проверки на два подряд идущих символа переноса строки, flag1: для проверки на неповторимость предложения
    
    while(1){
        g = getwchar();
        if (g == '.'){
            flag = 0;
            if (len_sent == 0){ // удаление незначащих точек 
            	continue;
            }
            if (len_sent % (SENT - 1) == 0){  // проверка на наличие места для добавления точки в массив, расширение памяти при необходимости 
                cap_sent += SENT;
                sent = realloc(sent, cap_sent * sizeof(wchar_t));
            }
            sent[len_sent] = g;
            len_sent++;
            // проверка на неповторимость 
            for (int k = 0; k < len_text; k++){
                if (wcslen(text[k]) == len_sent){
                    flag1 = 0;
                    for (int k1 = 0; k1 < len_sent; k1++){
                        if (towlower(text[k][k1]) != towlower(sent[k1])){  // посимвольное сравнение предложений с одинаковыми длинами
                            flag1 = 1;
                            break;
                        }
                    }
                    if (flag1 == 0){
                        break;
                    }
                }
            }
            if (flag1 == 1){  // добавление предложения в текст только в случае прохождения проверки на неповторимость 
                if (len_text % (TEXT - 1) == 0){  // расширение текста в случае необходимости 
                    cap_text += TEXT;
                    text = realloc(text, cap_text * sizeof(wchar_t*));
                }
                text[len_text] = malloc((len_sent + 1) * sizeof(wchar_t));  // выделение памяти для считанного предложения
                for (int i = 0; i < len_sent; i++){  // добавление предложения в текст
                    text[len_text][i] = sent[i];
                }
                text[len_text][len_sent] = '\0';  // добавление символа окончания строки
                len_text++;
            }
            memset(sent, 0, sizeof(sent));  // обнуление предложения для считывания нового
            flag1 = 1; 
            len_sent = 0;
        } else if (g == '\n'){  
            if (flag == 1){  // проверка на два подряд идущих символа переноса строки
                if (len_sent != 0){
                    if (len_text % (TEXT - 1) == 0){
                        cap_text += TEXT;
                        text = realloc(text, cap_text * sizeof(wchar_t*));
                    }
                    text[len_text] = malloc((len_sent + 1) * sizeof(wchar_t));
                    for (int i1 = 0; i1 < len_sent - 1; i1++){
                        text[len_text][i1] = sent[i1];
                    }
                    text[len_text][len_sent - 1] = '.';
                    text[len_text][len_sent] = '\0';
                    len_text++;
                }
                break;
            } else {
                flag++;
                if (len_sent == 0){ // игнорирование переносов строки между пердложениями 
                    continue;
                }
		        if (len_sent % (SENT - 1) == 0){  // расширение памяти для предложения в случае необходимости и добавление нового символа в него 
		            cap_sent += SENT;
		            sent = realloc(sent, cap_sent * sizeof(wchar_t));
				}
				sent[len_sent] = g;
				len_sent++;
		    }
        } else {
            flag = 0;
            if (g == ' ' && len_sent == 0){  // удаление пробелов между точкой и началом нового предложения
                continue;
            }
            if (len_sent % (SENT - 1) == 0){  // расширение памяти для предложения в случае необходимости и добавление нового символа в него 
                cap_sent += SENT;
                sent = realloc(sent, cap_sent * sizeof(wchar_t));
            }
            sent[len_sent] = g;
            len_sent++;
        }
    }
    struct Text input_text = {text, len_text};  // создание структуры и добавление в нее считанного текста и его длины
    return input_text;
}
