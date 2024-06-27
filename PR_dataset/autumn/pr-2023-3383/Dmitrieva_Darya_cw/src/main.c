#include "structs.h"
#include "first_function.h"
#include "second_function.h"
#include "third_function.h"
#include "fourth_function.h"
#include "Free.h"
#include "Print.h"
#include "Preprocessing.h"
#include "ninth_function.h"
int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wprintf(L"Course work for option 5.10, created by Dmitrieva Darya.\n");
    int chosenFunction;
    if ((wscanf(L"%d", &chosenFunction)) == 1){
        if (chosenFunction == 5){
            wprintf(L"Справка о функциях:\n- Функция 0 - Вывод текста с первичной обработкой.\n- Функция 1 - Для каждого предложения вывести \"Палиндромы на месте!\", если все слова являются палиндромами, \"Кто-то потерял все палиндромы.\", если ни одно слово не является палиндромом, в остальных случаях \"Чего-то не хватает.\".\n- Функция 2 - Заменить все специальные символы (включая .;,) в тексте на подстроку \">special simbol<\".\n- Функция 3 - Отсортировать предложения по уменьшению количества латинских букв.\n- Функция 4 - Удалить все предложения, в которых в одном слове встречаются латинские и кириллические буквы.\n- Функция 5 - Справка о функциях.\n");
        }
        else if (chosenFunction == 0 || chosenFunction == 1 || chosenFunction == 2 || chosenFunction == 3 || chosenFunction == 4 || chosenFunction ==9){
            struct Text text = readText();
            struct Text obr_text = func_obr_text(text);
            struct Text new_text;
            if (obr_text.n == 0){
                wprintf(L"Error: No text\n");
            }
            switch (chosenFunction)
            {
                case 0:
                    printText(obr_text);
                    break;
                case 1:
                    pallindrom_analys(&obr_text);
                    wprintf(L"\n");
                    break;
                case 2:
                    replace_special_symbol_analys(&obr_text);
                    break;
                case 3:
                    latin_sort(&obr_text);
                    printText(obr_text);
                    break;
                case 4:
                    new_text = kirill_latin(obr_text);
                    printText(new_text);
                    freeText(&new_text);
                    break;
		case 9:
		    pals_analys(&obr_text);
                    wprintf(L"\n");
                    break;
			
            }
        freeText(&text);
        freeText(&obr_text);
        }
        else {
            wprintf(L"Error: Неверная команда\n");
        }
    }
    else if ((wscanf(L"%d", &chosenFunction)) != 1){
        wprintf(L"Error: Неверная команда\n");
    }
    return 0;
}
