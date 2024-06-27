#include "processFunc.h"
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

// Функция для сортировки массива в алфавитном порядке без учёта регистра
int compareSortByAlphabet(const void *a, const void *b) 
{
    return towlower(*(wchar_t *)a) - towlower(*(wchar_t *)b);
}

// Функция для проверки, являются ли 2 предложения анаграммами
int areAnagrams(wchar_t *str1, wchar_t *str2)
{
    int str1_len = wcslen(str1);
    int str2_len = wcslen(str2);
    // 2 строки должны быть обязательно равны
    if (str1_len != str2_len) {
        return 0;
    }

    // Выделение памяти для временных строк
    wchar_t *tmp1 = (wchar_t *)malloc(sizeof(wchar_t) * (str1_len + 1));
    wchar_t *tmp2 = (wchar_t *)malloc(sizeof(wchar_t) * (str2_len + 1));

    // Заполнение первой строки в нижнем регистре
    int index = 0;
    for (int i = 0; i < str1_len; i++) {
        if (iswalnum(str1[i])) {
            tmp1[index++] = towlower(str1[i]);
        }
    }
    tmp1[index] = L'\0';

    // Заполнение второй строки в нижнем регистре
    index = 0;
    for (int i = 0; i < str2_len; i++) {
        if (iswalnum(str2[i])) {
            tmp2[index++] = towlower(str2[i]);
        }
    }
    tmp2[index] = L'\0';

    // Сортировка временных строк
    qsort(tmp1, wcslen(tmp1), sizeof(wchar_t), compareSortByAlphabet);
    qsort(tmp2, wcslen(tmp2), sizeof(wchar_t), compareSortByAlphabet);

    // Сравнение строк
    int res = wcscmp(tmp1, tmp2);
    free(tmp1);
    free(tmp2);
    if (res == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Функция для поиска и печати анаграмм для каждого предложения
void sentenceAnagrams(struct Text *text)
{
    // Выделение памяти для массива флагов
    int *proces = (int *)calloc(text->count, sizeof(int));
    int count = 0;
    for (int i = 0; i < text->count; i++) {
        int flag = 1;
        // Если предложение было обработано, то пропускаем его
        if (proces[i] == 1)
            continue;
        // Проход по предложениям, следующим за текущим
        for (int j = i + 1; j < text->count; j++) {
            if (areAnagrams(text->text[i].sentence, text->text[j].sentence)) {
                count++;
                // Вывод первого анаграммного предложения
                if (flag == 1) {
                    wprintf(L"%ls", text->text[i].sentence);
                    flag = 0;
                }
                // Вывод следующих анаграмм
                wprintf(L", %ls", text->text[j].sentence);
                proces[j] = 1;
            }
        }
        // Помечаем, что предложение было обработано
        proces[i] = 1;
        // Если для текущего предложения были найдены анаграммы, то завершаем строку
        if (flag == 0)
            wprintf(L".\n");
    }
    // Если не было найдено анаграмм, выводим соответствующее сообщение
    if (count == 0)
        wprintf(L"Предложений анаграмм не найдено.\n");
    free(proces);
}

// Функция сравнения для сортировки предложений по количеству заглавных букв
int compareSortUpper(const void *a, const void *b)
{
    // Преобразование указателей к нужному типу
    struct Sentence *sentence_first = (struct Sentence *)a;
    struct Sentence *sentence_second = (struct Sentence *)b;

    int count_first = 0;
    int count_second = 0;

    // Подсчёт заглавных букв в первом предложении
    for (int i = 0; i < sentence_first->len; i++) {
        if (iswupper(sentence_first->sentence[i]))
            count_first++;
    }

    // Подсчёт заглавных букв во втором предложении
    for (int i = 0; i < sentence_second->len; i++) {
        if (iswupper(sentence_second->sentence[i]))
            count_second++;
    }

    return count_second - count_first;
}

// Функция для сортировки предложений по количеству загланых букв
void sortSentencesByUpper(struct Text *text)
{
    qsort(text->text, text->count, sizeof(struct Sentence), compareSortUpper);
}

// Функция для замены гласных букв
int replaceVowels(struct Text *text) {
    wchar_t *vowels = L"aeiouyаеёиоуыэюяAEIOUYАЕЁИОУЫЭЮЯ";
    for (int i = 0; i < text->count; i++) {
        // Получение предложения и его длины
        wchar_t *sentence = text->text[i].sentence;
        int len = text->text[i].len;

        for (int j = 0; j < len; j++) {
            // Проверка на то, является ли символ гласной
            if (wcschr(vowels, sentence[j])) {
                // Увеличение размера предложения на 3
                wchar_t *tmp = (wchar_t *)realloc(sentence, (len + 3) * sizeof(wchar_t));
                if (tmp == NULL) {
                    return 0;
                }
                sentence = tmp;
                // Сдвиг символов вправо на 2 поздиции
                for (int k = len - 1; k >= j; k--) {
                    sentence[k + 2] = sentence[k + 1];
                }
                // Проверка крайних позиций
                int p;
                switch(sentence[j]) {
                    case L'я':
                        sentence[j] = L'а';
                        sentence[j+1] = L'б';
                        break;
                    case L'Я':
                        sentence[j] = L'А';
                        sentence[j+1] = L'Б';
                        break;
                    case L'ю':
                        sentence[j] = L'я';
                        sentence[j+1] = L'а';
                        break;
                    case L'Ю':
                        sentence[j] = L'А';
                        sentence[j+1] = L'А';
                        break;
                    case L'y':
                        sentence[j] = L'z';
                        sentence[j+1] = L'a';
                        break;  
                    case L'Y':
                        sentence[j] = L'Z';
                        sentence[j+1] = L'A';
                        break; 
                    default:
                        p = (int)sentence[j];
                        sentence[j] = (wchar_t)(p+1);
                        sentence[j+1] = (wchar_t)(p+2);
                        break;
                }
                // Увеличение длины и индекса на 1
                j += 1;
                len += 1;
            }
        }
    // Обновление предложения и длины
    text->text[i].sentence = sentence;
    text->text[i].len = len;
    }
    return 1;
}


// Функция для замены слова в предложении
int replaceWordInSentence(wchar_t **sentence, int *len, int *capacity, const wchar_t *oldWord, const wchar_t *newWord) {
    int oldWordLen = wcslen(oldWord);
    int newWordLen = wcslen(newWord);
    int diff = newWordLen - oldWordLen;
    int i = 0;
    int flag = 0;

    while (i < *len) {
        // Сравнение части предложения и старого слова
        if (wcsncasecmp(*sentence + i, oldWord, oldWordLen) == 0) {
            // Проверка, что слово не является подстрокой
            if ((i > 0 && iswalpha((*sentence)[i - 1])) || (i + oldWordLen < *len && iswalpha((*sentence)[i + oldWordLen]))) {
                i++;
                continue;
            }
            flag = 1;
            // Изменяем длину предложения на разницу между длиной слов
            *len += diff;

            // Увеличиваем буфер, если длина больше текущей ёмкости
            if (*len > *capacity - 1) {
                wchar_t *tmp = (wchar_t *)realloc(*sentence, (*len + 1) * sizeof(wchar_t));
                if (tmp == NULL)
                    return -1;

                *sentence = tmp;
                *capacity = *len + 1;
            }

            // Сдвигаем символы вправо на разницу в длине
            wmemmove(*sentence + i + newWordLen, *sentence + i + oldWordLen, *len - i - newWordLen + 1);

            // Заменяем старое слово на новое
            for (int j = 0; j < newWordLen; j++)
                (*sentence)[i + j] = newWord[j];

            // Сдвиг индекса на длину нового слова
            i += newWordLen;
        } else {
            // Если символы не совпдают, сдвигаем индекс на 1
            i++;
        }
    }

    return flag;
}

// Функция для замены слова в тексте
int replaceWordInText(struct Text *text, const wchar_t *oldWord, const wchar_t *newWord) {
    int flag = 0;
    for (int i = 0; i < text->count; i++) {
        int current_len = text->text[i].len;
        int exist_buffer = text->text[i].capacity;
        wchar_t *str = text->text[i].sentence;
        int j = 0;

        // Проходим по всем символам предожения
        while (j < current_len) {
            // Сравниваем часть предложения и старое слово
            int res = wcsncasecmp(str + j, oldWord, wcslen(oldWord));
            if (res == 0) {
                flag = 1;
                // Заменяем старое слово на новое
                if (replaceWordInSentence(&str, &current_len, &exist_buffer, oldWord, newWord) == -1) {
                    return -1;
                }

                // Обновляем индекс, чтобы продолжить поиск после замененного слова
                j += wcslen(newWord);
            } else {
                // Продолжаем поиск, если старое слово не было найдено
                j++;
            }
        }

        // Обновляем информацию о предложении
        text->text[i].sentence = str;
        text->text[i].len = current_len;
        text->text[i].capacity = exist_buffer;
    }

    return flag;
}


// Функция для чтения слова
wchar_t *readWord(int *flag) {
    wchar_t *word = NULL;
    wchar_t c;
    int len = 0;
    *flag = -2;

    do {
        c = getwchar();
    } while (c == L' ' || c == L'\n');

    if (c == WEOF || c == L'\n') {
        *flag = 0;
        return NULL;
    }

    do {
        wchar_t *tmp = realloc(word, (len + 2) * sizeof(wchar_t));
        if (tmp == NULL) {
            wprintf(L"Error: не удалось выделить память\n");
            *flag = -1;
            free(word);
            return NULL;
        }
        word = tmp;

        if (c == L' ') {
            *flag = 1; 
        }
        word[len++] = c;
        c = getwchar();
    } while (c != L' ' && c != L'\n' && c != WEOF);

    if (len == 0) {
        free(word);
        *flag = 0;
    }

    word[len] = L'\0';
    return word;
}


int palindromSentence(wchar_t *str) {
    wchar_t *tmp1 = (wchar_t *)malloc(sizeof(wchar_t) * (wcslen(str) + 1) );
    wchar_t *tmp2 = (wchar_t *)malloc(sizeof(wchar_t) * (wcslen(str) + 1));

    // Заполнение первой строки в нижнем регистре
    int index = 0;
    for (int i = 0; i < wcslen(str); i++) {
        if (iswalnum(str[i])) {
            tmp1[index++] = towlower(str[i]);
        }
    }
    tmp1[index] = L'\0';

    index = 0;
    for (int i = wcslen(str) - 1; i >= 0; i--) {
        if (iswalnum(str[i])) {
            tmp2[index++] = towlower(str[i]);
        }
    }
    tmp2[index] = L'\0';

    int res = wcscmp(tmp1, tmp2);
    if (res == 0) {
        return 1;
    } else {
        return 0;
    }
    
    free(tmp1);
    free(tmp2);
}

void palindromInText(struct Text *text){
    for (int i = 0; i < text->count; i++) {
        int res = palindromSentence(text->text[i].sentence);
        if (res == 1)
            wprintf(L"%ls.\n", text->text[i].sentence);
    }
}

