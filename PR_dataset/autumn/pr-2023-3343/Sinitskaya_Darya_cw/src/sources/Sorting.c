#include"../include/Sorting.h"

//функция подсчета количества латинских букв в предложении
int Count_Latin_Letters(wchar_t *sentence) {
    int count = 0; //количество латинских букв
    int length = wcslen(sentence); //длина предложения
    
    for (int i = 0; i < length; i++) {
        if ((sentence[i] >= L'A' && sentence[i] <= L'Z') || (sentence[i] >= L'a' && sentence[i] <= L'z')) {
            count++;
        }
    }
    
    return count;
}

//функция сравнения двух предложений на основе количества латинских букв в них
int Compare_Sentences(const void *a, const void *b) {
    Sentence *sentence_A = (Sentence *)a; //предложение 1
    Sentence *sentence_B = (Sentence *)b; //предложение 2
    
    int count_A = Count_Latin_Letters(sentence_A->sentence); //количество латинских букв в предложении 1
    int count_B = Count_Latin_Letters(sentence_B->sentence); //количество латинских букв в предложении 2
    
    return count_B - count_A; //упорядочивание по убыванию количества латинских букв
}

//метод сортировки предложений в тексте
void Sorting(Text *text) {
    qsort(text->sentences, text->size, sizeof(Sentence), Compare_Sentences);
}
