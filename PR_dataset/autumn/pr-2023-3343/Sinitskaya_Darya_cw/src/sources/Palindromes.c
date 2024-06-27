#include"../include/Palindromes.h"

//функция проверки, является ли данное слово палиндромом
int Is_Palindrome(wchar_t *word, int size) {
    wchar_t *start = word; //указатель на начало слова
    wchar_t *end = word + size - 1; //указатель на конец слова
    
    while (start < end) {
        if (towlower(*start) != towlower(*end)) {
            return 0; //не палиндром
        }
        
        start++;
        end--;
    }
    
    return 1; //палиндром
}

//функция подсчета слов-палиндромов в предложении
int Check_Sentence(Sentence *sentence) {
    wchar_t *word = sentence->sentence; //указатель на предложение
    int kol_palindrome = 0; //счетчик палиндромов
    
    //разделение предложения на слова по пробелам
    wchar_t *wcs;
    wchar_t *token = wcstok(word, L" ,", &wcs);
    
    //перебор каждого слова в предложении
    while (token != NULL) {
        if (Is_Palindrome(token, wcslen(token))) { //проверка на палиндром
            kol_palindrome++;
        }
        token = wcstok(NULL, L" ,", &wcs);
    }
    
    return kol_palindrome; //количество палиндромов в предложении
}

//функция подсчета слов в предложении
int Num_Words(Sentence *sentence) {
    wchar_t *word = sentence->sentence; //указатель на предложение
    int kol_words = 0; //счетчик слов
    
    //разделение предложения на слова по пробелам
    wchar_t *wcs;
    wchar_t *token = wcstok(word, L" ,", &wcs);
    
    //перебор каждого слова в предложении
    while (token != NULL) {
        kol_words++;
        token = wcstok(NULL, L" ,", &wcs);
    }
    
    return kol_words; //количество слов в предложении
}

//метод определения наполнения предложений палиндромами
void Palindromes(Text *text) {

    for (int i = 0; i < text->size; i++) {

        Sentence sentence = text->sentences[i]; //предложение
        int count_palindrome = Check_Sentence(&(text->sentences[i])); //количество палиндромов в предложении
        
        if (count_palindrome == 0) {
            wprintf(L"%ls ", text->sentences[i].sentence);
            wprintf(L"Кто-то потерял все палиндромы.\n");
        } else { 

            if (count_palindrome == Num_Words(&(text->sentences[i]))) {
                wprintf(L"%ls ", text->sentences[i].sentence);
                wprintf(L"Палиндромы на месте!\n");
            } else {
                wprintf(L"%ls ", text->sentences[i].sentence);
                wprintf(L"Чего-то не хватает.\n");
            }
        }
    }
}
