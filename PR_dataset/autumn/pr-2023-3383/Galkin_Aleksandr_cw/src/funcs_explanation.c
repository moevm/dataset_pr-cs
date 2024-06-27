#include "funcs_explanation.h"

void explain_functions(){
    wprintf(L"\x1b[1;4mВ данной курсовой работе реализованы следующие функции:\x1b[0m\n");
    wprintf(L"\x1b[1;5mФункции для осуществления ввода-вывода текста и очищения памяти (описаны в файлах <get_text.c> и <text_treatment.c>):\x1b[0m\n");
    wprintf(L"1. \x1b[1;31mstruct Sentence *get_str()\x1b[0m: используется для считывания каждого предложения (до символа точки или переноса строки), возвращает указатель на считанное предложение.\n");
    wprintf(L"2. \x1b[1;31mstruct Sentence delete_trash(struct Sentence str*)\x1b[0m: функция получает на вход указатель на предложение, после чего удаляет все табуляции и иные неотображаемые графически символы в начале полученного предложения. Возвращает обработанное предложение.\n");
    wprintf(L"3. \x1b[1;31mstruct Text get_text()\x1b[0m: используется для получения текста, в своем теле вызывая функцию get_str() и заполняя полученными предложениями текст. Возвращает считанный текст (до двух символов переноса строки).\n");
    wprintf(L"4. \x1b[1;31mvoid withdraw_text(struct Text txt)\x1b[0m: получает на вход текст и выводит его на экран. В случае пустого текста выводит строку 'Текст пустой'\n");
    wprintf(L"5. \x1b[1;31mvoid release_text(struct Text txt)\x1b[0m: получает на вход структуру текста и высвобождает выделенную под его хранение память.\n");
    wprintf(L"\x1b[1;5mФункция для первой задачи из условия:\x1b[0m\n");
    wprintf(L"1. \x1b[1;33mvoid translate_func(struct Sentence *str)\x1b[0m: получает на вход указатель на предложение и заменяет все подстроки 'high noon' и 'полночь' на 'полдень' и 'midnight' соответственно.\n");
    wprintf(L"\x1b[1;5mФункции для второй задачи из условия (описаны в файле <time.c>):\x1b[0m\n");
    wprintf(L"1. \x1b[1;34mvoid check_time(struct Text text)\x1b[0m\x1b[0m: получает на вход текст и определяет в нем все подстроки, обозначающие даты в формате DD/MM/YYYY или DD-MM-YYYY и в случае их валидности выводит их на экран в порядке возрастания (функция сортировки и проверки на возможность существования подобной даты описаны далее в п.2 и п.3).\n");
    wprintf(L"2. \x1b[1;34mint cmp(const void *aa, const void *bb)\x1b[0m: компаратор, необходимый для осуществления сортировки функцией qsort().\n");
    wprintf(L"3. \x1b[1;34mint error_data_check(struct Date date)\x1b[0m: проверяет, возможна ли такая дата (например на то, что 29 февраля только в високосный год). В зависимости от возвращенного значения функция из п.1 может выдать ошибку о невалидности даты в тексте.\n");
    wprintf(L"\x1b[1;5mФункция для третьей задачи из условия (описаны в файле <text_treatment.c>):\x1b[0m\n");
    wprintf(L"3. \x1b[1;32mvoid delete_sentences(struct Text txt)\x1b[0m: получает на вход текст и осуществляет удаление тех предложений, у которых совпадают первое и последнее слово (в том числе, если предложение состоит из одного слова)\n");
    wprintf(L"\x1b[1;5mФункции для четвертой задачи из условия (описаны в файле <time.h>):\x1b[0m\n");
    wprintf(L"1. \x1b[1;35mvoid get_and_check_dates(struct Text txt)\x1b[0m: получает на вход текст и разбивает каждое предложение на токены. Определяет подстроки вида <day> <month> <year>, передает их в функцию, описанную в п.2 и сравнивает с текущим временем. Выводит дату и строку 'Happened', если дата уже произошла, 'Not happened', если нет и 'It's today', если дата сегодняшняя.\n");
    wprintf(L"2. \x1b[1;35mstruct tm* check_for_date(wchar_t *day, wchar_t* month, wchar_t* year)\x1b[0m: получает на вход обнаруженные в предыдущей функции подстроки дня, месяца и года, проверяет верность данной даты и возвращает указатель на структуру struct *tm.\n");
    wprintf(L"3. \x1b[1;35mint check_if_happened(struct tm *time1, struct tm *time2)\x1b[0m: получает на вход дату из текста и дату сегодняшнего дня, сравнивает и определяет, произошло ли событие.\n");
}