#include "../include/Removal.h"

//функция определения наличия латинских и кириллических букв в слове
int Mix_Alphabets(wchar_t* word) {
    int has_latin = 0;  //флаг наличия латинских букв
    int has_cyrillic = 0;  //флаг наличия кириллических букв

    while (*word) {
        //проверка на латинскую букву
        if (iswalpha(*word) && (tolower(*word) >= 'a' && tolower(*word) <= 'z')) {
            has_latin = 1;
        } else {
            //проверка на кириллическую букву
            if (iswalpha(*word) && (tolower(*word) >= L'а' && tolower(*word) <= L'я')) {
                has_cyrillic = 1;
            }
        }

        if (has_latin && has_cyrillic) {  
            return 1; //найдены и латинские, и кириллические буквы
        }
        word++;
    }

    return 0;  //не найдены и латинские, и кириллические буквы
}

//метод удаления предложений, содержащих слова со смешанными буквами
void Removal(Text *text) {
    //выделение памяти для нового массива предложений
    Sentence *filtered_sentences = malloc(text->size * sizeof(Sentence));

    //обработка ошибки выделения памяти для нового массива предложений
    if(filtered_sentences == NULL){
        wprintf(L"Error: Memory allocation\n");
        free(filtered_sentences);
    }
    
    int filtered_size = 0; //количество обработанных предложений
    int flag = 0;  //флаг наличия смешанных слов

    for (int i = 0; i < text->size; i++) {
        wchar_t *word = text->sentences[i].sentence; //указатель на предложение
        
        //разделение предложения на слова по пробелам
        wchar_t *wcs;
        wchar_t *token = wcstok(word, L" ,", &wcs);

        //перебор каждого слова в предложении
        while (token != NULL) {
            if(Mix_Alphabets(token)) { //проверка слова
                flag = 1;
                break;
            } 
            token = wcstok(NULL, L" ,", &wcs);
        }
        
        //проверка на наличие смешанных слов
        if (flag == 0) {
            filtered_sentences[filtered_size] = text->sentences[i]; //добавление предложения из исходного массива в новый массив предложений
            filtered_size++; //увелечение количества обработанных предложений
        }
        
    }

    //освобождение памяти от предыдущего массива предложений
    free(text->sentences);

    //обновление указателя и размера массива предложений
    text->sentences = filtered_sentences;
    text->size = filtered_size;
}
