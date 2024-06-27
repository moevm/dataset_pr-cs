#include <stdio.h>  // Стандартный ввод и вывод
#include <stdlib.h> // Для функций выделения памяти
#include <string.h> // Для работы со строками
#include <ctype.h>  // Для проверки символов
#include <strings.h> // Для верной работы какой-то там из вышеперечисленных функций

// Определение констант размера блоков для выделения памяти
#define SIZE_BLOCK 20        // Размер блока для предложений
#define SIZE_MASSIVE_BLOCK 3     // Размер блока для массива текста (массив предложений)

// Функция проверки на уникальность предложения в тексте
// ppText - указатель на массив указателей на строки (предложения)
// countTexts - количество предложений в массиве ppText
// pointerCurrentOffer - указатель на текущее предложение для сравнения
int sentEquals(char** ppText, int countTexts, char* pointerCurrentOffer) {
    // Проход по массиву предложений для проверки каждого на совпадение с pointerCurrentOffer
    for (int i = 0; i < countTexts; i++) {
        // Использование strcasecmp для сравнения строк без учёта регистра
        if (!strcasecmp(ppText[i], pointerCurrentOffer)) return 0; // Возвращает 0, если найдено совпадение
    }
    return 1; // Возвращает 1, если совпадений не найдено
}

// Функция для считывания одного предложения из стандартного ввода
char* getSentence() {
    size_t indexSymb = 0; // Индекс символа в предложении
    size_t capacity = SIZE_BLOCK; // Текущий размер выделенной памяти

    char symb = getchar(); // Считывание первого символа
    char* sentence = (char*)malloc(capacity); // Выделение памяти под предложение
    if (sentence == NULL) {
        fprintf(stderr, "Memory allocation error\n"); // Вывод сообщения об ошибке
        exit(EXIT_FAILURE); // Завершение программы в случае ошибки
    }

    // Чтение символов до конца предложения или ввода
    while (1) {
        // Пропуск начальных пробелов или обработка конца строки
        if (!((indexSymb == 0 && isblank(symb)) || (symb == '\n'))) {
            sentence[indexSymb++] = symb; // Добавление символа к предложению
        }
        // Если текущий символ точка или конец строки, завершить предложение
        if ((symb == '.') || (symb == '\n')) {
            sentence[indexSymb] = '\0'; // Добавление нуль-терминатора в конец строки
            break;
        }

        // Расширение массива, если в нём заканчивается место
        if (indexSymb >= capacity - 1) { // Проверка, достигнут ли предел выделенной памяти
            capacity += SIZE_BLOCK; // Увеличение размера выделенной памяти
            sentence = (char*)realloc(sentence, capacity); // Реаллокация памяти
            if (sentence == NULL) { // Проверка успешности реаллокации
                fprintf(stderr, "Memory allocation error\n"); // сообщение об ошибке
                exit(EXIT_FAILURE); // Завершение программы в случае ошибки
            }
        }
        symb = getchar(); // Считывание следующего символа
    }

    return sentence; // Возвращение указателя на считанное предложение
}

// Функция для считывания всего текста, состоящего из предложений
// pointerLenText - указатель на переменную, в которую будет записана длина текста
char** getText(int* pointerLenText) {
    size_t size = SIZE_MASSIVE_BLOCK; // Текущий размер массива текста
    int indexText = 0; // Индекс для заполнения массива текста
    int emptyLines = 0; // Счётчик пустых строк
    char** ppText = (char**)malloc(size * sizeof(char*)); // Выделение памяти под массив текста
    if (ppText == NULL) {// Проверка успешности выделения памяти
        fprintf(stderr, "Memory allocation error\n"); // сообщение об ошибке
        exit(EXIT_FAILURE); // Завершение программы в случае ошибки
    }
    char* sentence = getSentence(); // Получение первого предложения

    // Чтение предложений до тех пор, пока не встретятся две пустые строки подряд
    while (1) {
        // Обработка пустых строк и вставка точек, если они отсутствуют в конце предложений
        if (strlen(sentence) < 1) {
            emptyLines++; // Увеличение счетчика пустых строк
            // Добавление точки в предыдущее предложение, если оно без точки
            if ((indexText > 0) && (ppText[indexText - 1][strlen(ppText[indexText - 1]) - 1] != '.')) {
                int sent_len = strlen(ppText[indexText - 1]);
                ppText[indexText - 1][sent_len] = '.';
                ppText[indexText - 1][sent_len + 1] = '\0';
            }
            // Остановка считывания, если две пустые строки подряд
            if (emptyLines == 2) break;
        }
        else {
            emptyLines = 0; // Сброс счетчика пустых строк, если текущая строка не пуста
        }

        // Добавление нового предложения в массив, если оно уникально
        if (sentEquals(ppText, indexText, sentence) && emptyLines == 0) {
            ppText[indexText++] = sentence;
        }
        else {
            free(sentence); // Освобождение памяти для недобавленного (дублирующего) предложения
        }

        // Если достигнут текущий размер массива - расширение массива
        if (indexText >= size - 1) {
            size += SIZE_MASSIVE_BLOCK; // Увеличение размера выделенной памяти
            ppText = (char**)realloc(ppText, size * sizeof(char*)); // Реаллокация памяти
            if (ppText == NULL) { // Проверка успешности реаллокации
                fprintf(stderr, "Memory allocation error\n"); // сообщение об ошибке
                exit(EXIT_FAILURE); // Завершение программы в случае ошибки
            }

            // Инициализация новых элементов массива текста
            for (int x = indexText; x < size; x++) {
                ppText[x] = NULL; // Элементы инициализируются как NULL
            }
        }

        // Получение следующего предложения
        sentence = getSentence();
    }

    *pointerLenText = indexText; // Возвращение размера массива текста через указатель
    return ppText; // Возвращение указателя на массив текста
}

// Функция для печати текста и освобождения выделенной памяти
// ppText - указатель на массив указателей на строки
// pointerLenText - указатель на переменную с длиной текста
void printText(char** ppText, int* pointerLenText) {
    for (int i = 0; i < *pointerLenText; i++) {
        printf("%s\n", ppText[i]); // Вывод предложения
        free(ppText[i]); // Освобождение памяти для предложения
    }

    free(ppText); // Освобождение памяти для всего массива текста
    exit(EXIT_SUCCESS); // Завершение программы с успешным кодом
}

// Функция удаления предложения из текста по его индексу
// ppText - указатель на массив указателей на строки
// lengthText - длина текста
// id - индекс удаляемого предложения
char** deleteSugg(char** ppText, int lengthText, int id) {
    free(ppText[id]); // Освобождение памяти удаляемого предложения
    // Сдвиг всех последующих предложений на место удаляемого
    for (int i = id; i < lengthText - 1; i++) {
        ppText[i] = ppText[i + 1];
    }
    ppText[lengthText - 1] = NULL; // Обнуление последнего элемента, т.к. предложение удалено
    return ppText; // Возвращение обновленного массива текста
}

// Функция удаляет первое слово каждого предложения в тексте
// ppText - указатель на массив указателей на строки
// pointerLenText - указатель на переменную с длиной текста
char** deleteFirstWord(char** ppText, int* pointerLenText) {
    // Длина текста (количество строк) сохраняется в новую переменную
    int newLen = *pointerLenText;

    // Перебор всех строк текста
    for (int i = 0; i < *pointerLenText; i++) {
        // Счетчик пробелов (для определения наличия слова)
        int space_count = 0;

        // Поиск первого слова, перебирая символы строки
        for (int j = 1; j < strlen(ppText[i]); j++) {
            // Условие, определяющее конец первого слова (пробел перед не-пробельным символом)
            if ((ppText[i][j] == ' ') && (!isspace(ppText[i][j + 1]))) {
                // Увеличение счетчика пробелов и смещение строки, чтобы удалить первое слово
                space_count += 1;
                memmove(ppText[i], ppText[i] + j + 1, strlen(ppText[i]) * sizeof(char));
                break;
            }
            // Условие для обработки запятой в качестве разделителя
            else if (ppText[i][j] == ',') {
                // Увеличение счетчика и смещение строки так, чтобы запятая осталась
                space_count += 1;
                memmove(ppText[i], ppText[i] + j, strlen(ppText[i]) * sizeof(char));
                break;
            }
        }
        // Если предложение состояло из одного слова или не содержало пробелов, удаляем его
        if ((space_count == 0) || (strlen(ppText[i]) == 1)) {
            ppText = deleteSugg(ppText, newLen, i); // deleteSugg - функция не представлена в коде, предположительно удаляет предложение
            i--; // Поскольку строка удалена, уменьшаем индекс
            newLen--; // Уменьшаем новую длину текста
            *pointerLenText = newLen; // Обновляем значение длины текста через указатель
        }
    }
    return ppText; // Возвращаем измененный текст
}

// Функция для трансформации времени в секундах в формат чч:мм:сс
// ppText - указатель на массив указателей на строки
// pointerLenText - указатель на переменную с длиной текста
char** transformTime(char** ppText, int* pointerLenText) {
    int newLen = *pointerLenText;
    // Перебор всех строк в тексте
    for (int i = 0; i < newLen; i++) {
        // Создаем временный строковый буфер и копируем туда текущую строку
        char strBuf[strlen(ppText[i]) + 1];
        strcpy(strBuf, ppText[i]);
        // Разделяем строку на токены по пробелам и запятым
        char* k = strtok(strBuf, " ,");
        // Перебор всех токенов в строке
        while (k != NULL) {
            int num = 0;
            // Проверка, что токен содержит "sec" и его длина больше трех
            if ((strlen(k) > 3) && (strstr(k, "sec") != NULL)) {
                num = atoi(k); // Преобразование к целому числу
                // Вывод времени в формате чч:мм:сс
                printf("%d:%d:%d\n", num / 3600, (num % 3600) / 60, (num % 3600) % 60);
            }
            // Переход к следующему токену (отделяем также точки)
            k = strtok(NULL, " ,.");
        }
    }
    // Освобождение памяти, выделенной под строки
    for (int i = 0; i < *pointerLenText; i++) {
        free(ppText[i]);
    }
    // Освобождение памяти, выделенной под массив строк
    free(ppText);
    // Возврат нулевого указателя в качестве сигнала об освобождении ресурсов
    return 0;
}

// Функция удаляет все предложения, где все слова имеют одинаковую длину
// ppText - указатель на массив указателей на строки
// pointerLenText - указатель на переменную с длиной текста
char** deleteSentencesWithSameLen(char** ppText, int* pointerLenText) {
    int newLen = *pointerLenText;
    // Перебор всех предложений в тексте
    for (int i = 0; i < newLen; i++) {
        // Создаем буфер для копии строки и копируем туда предложение
        char strBuf[strlen(ppText[i]) + 1];
        strcpy(strBuf, ppText[i]);
        // Разделение строки на слова (токены)
        char* tmp = strtok(strBuf, " ,.");
        // Получение длины первого слова
        int a = strlen(tmp);
        // Получение следующего слова
        tmp = strtok(NULL, " ,.");
        int flag = 1; // Флаг, указывающий на одинаковую длину всех слов
        // Если следующего слова нет, флаг остается равным 1
        if (tmp == NULL) flag = 1;

        // Перебор слов в предложении
        while (tmp != NULL) {
            // Если длины слов различаются, выставляем флаг в 0 и прерываем цикл
            if (!(a == strlen(tmp))) {
                flag = 0;
                break;
            }
            // Получение следующего слова
            tmp = strtok(NULL, " ,.");
        }
        // Если флаг остался равен 1, удаляем текущее предложение
        if (flag) {
            ppText = deleteSugg(ppText, newLen, i);
            i--; // Коррекция индекса после удаления
            newLen--; // Уменьшение длины текста
            *pointerLenText = newLen; // Обновление длины через указатель.
        }
    }
    return ppText; // Возврат текста с удаленными предложениями.
}

// Вспомогательная функция подсчета строчных букв в строке.
// str - указатель на строку
// pointerLenText - указатель на переменную с длиной текста
int lowerLen(char* str) {
    int count = 0; // Счетчик строчных букв
    // Перебор всех символов в строке
    for (int i = 0; i < strlen(str); i++) {
        // Подсчет строчных букв
        if (islower(str[i])) {
            count += 1;
        }
    }
    // Возврат количества строчных букв
    return count;
}

// Функция-компаратор для сортировки строк по количеству строчных букв
int comparator(void const* a, void const* b) {
    // Подсчет строчных букв для первой строки
    int l_x = lowerLen(*(char**)a);
    // Подсчет строчных букв для второй строки
    int l_y = lowerLen(*(char**)b);
    // Возвращение результата сравнения
    if (l_x < l_y) {
        return 1; // Первая строка должна следовать после второй
    }
    if (l_x > l_y) {
        return -1; // Первая строка должна предшествовать второй
    }
    // Если строки равны по количеству строчных букв, возвращаем 0
    return 0;
}

int SumOfDigits(char *sent){
    int sum = 0;
    for (int i = 0; i < strlen(sent); i++){
        if (isdigit(sent[i])){
            sum += sent[i] - '0';
        }
    }
    return sum;
}

void CountBetweenSents(char** text, int len){
    int FirstSum = SumOfDigits(text[0]);
    int SumSent;
    //printf("%d", FirstSum);
    for (int i = 1; i < len; i++){
        SumSent = SumOfDigits(text[i]);
        if (SumSent > FirstSum){
            printf("(%d) %s\n", (SumSent - FirstSum), text[i]);
        }
    }
}

// Функция getInfo отвечает за вывод информации о доступных операциях
void getInfo() {
    // Выводит на экран инструкции для пользователя. Каждый номер от 0 до 4 соответствует различной функции
    printf("0: Output the text after the initial mandatory processing.\n1: Count the number of seconds.\n2: Delete the first words in the sentence.\n");
    printf("3: Remove all sentences with the same length of all words.\n4: comparator sentences in descending order of the number of lowercase letters.\n");
    printf("5: Output help about the functions implemented by the program.\n");
}

// Главная функция main – точка входа в программу
int main() {
    // Объявляется переменная length, которая будет использоваться для хранения длины текста
    int length = 0;
    // Вывод информации о курсовом проекте и имени автора
    printf("Course work for option 4.11, created by Mariya Lazebnikova\n");
    // Чтение одного символа от пользователя.
    char symb = getchar();
    // Объявление переменной s и инициализация её значением 8 (по умолчанию)
    int s = 8;
    // Проверка, является ли введённый символ цифрой
    if (isdigit(symb)) {
        // Преобразование символа цифры в соответствующее ей числовое значение
        s = (int)(symb - 48);
    }

    // Объявление указателя на указатель, который будет использоваться для хранения текста
    char** ppText;
    // Конструкция switch, которая контролирует, какая функция будет выполнена в зависимости от значения s
    switch (s) {
        // Кейс для вывода обработанного текста
    case 0:
        ppText = getText(&length);
        printText(ppText, &length);
        break;
        // Кейс для подсчёта количества секунд
    case 1:
        ppText = getText(&length);
        transformTime(ppText, &length);
        break;
        // Кейс для удаления первого слова в каждом предложении
    case 2:
        ppText = getText(&length);
        deleteFirstWord(ppText, &length);
        printText(ppText, &length);
        break;
        // Кейс для удаления предложений с одинаковой длиной всех слов
    case 3:
        ppText = getText(&length);
        deleteSentencesWithSameLen(ppText, &length);
        printText(ppText, &length);
        break;
        // Кейс для сортировки предложений
    case 4:
        ppText = getText(&length);
        // Сортирует массив предложений с помощью функции qsort
        qsort(ppText, length, sizeof(char*), comparator);
        printText(ppText, &length);
        break;
        // Кейс для вывода информации о командах
    case 5:
        getInfo();
        break;
    case 8:
        ppText = getText(&length);
        CountBetweenSents(ppText, length);
        break;
        // Вывод сообщения об ошибке, если введена незнакомая команда
    default:
        printf("There is no such command! Enter a number between 0 and 5.");
        break;
    }
    // Завершение функции main с возвратом 0, указывающим на успешное выполнение
    return 0;
}
