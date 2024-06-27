#include "../include/Replacing_Special_Characters.h"

//метод замены специальных символов в тексте
void Replacing_Special_Characters(Text* text) {
    wchar_t* special_symbols = L"№*$#@.;,\0"; //строка со специальными символами, которые нужно заменить
    wchar_t* replacement = L">special symbol<"; //строка для замены специальных символов
    wchar_t* temp; //временный указатель на строку
    size_t original_length, replacement_length = wcslen(replacement), new_length; //переменные для хранения длин строк
 
    for (int i = 0; i < text->size; i++) {
        wchar_t* sentence = text->sentences[i].sentence; //получение текущего предложения
        
        for (int j = 0; special_symbols[j] != L'\0'; j++) {
            wchar_t* symbol = wcschr(sentence, (wchar_t)special_symbols[j]); //поиск специального символа в предложении
            
            while (symbol != NULL) {
                int position = symbol - sentence; //определение позиции специального символа в предложении
                
                original_length = wcslen(sentence); //длина исходной строки
                new_length = original_length + replacement_length; //новая длина строки после замены
                
                temp = (wchar_t*)malloc((new_length + 1) * sizeof(wchar_t)); //выделение памяти под временный буфер
                
                //обработка ошибки выделения памяти под временный буфер
                if (temp == NULL) {
                    wprintf(L"Error: Memory allocation\n");
                    return;
                }
                
                wmemcpy(temp, sentence, position); //копирование части исходной строки до специального символа
                wmemcpy(temp + position, replacement, replacement_length); //копирование строки замены
                wmemcpy(temp + position + replacement_length, sentence + position + 1, original_length - position); //копирование оставшейся части исходной строки
                
                temp[new_length] = L'\0'; //установка завершающего нулевого символа
                
                free(sentence); //освобождение памяти, занимаемой исходным предложением
                sentence = temp; //обновление указателя на предложение
                
                symbol = wcschr(sentence + position + replacement_length, special_symbols[j]); //поиск следующего вхождения специального символа в предложении
            }
        }
        
        text->sentences[i].sentence = sentence; //обновление указателя на предложение в структуре Text
    }
}
