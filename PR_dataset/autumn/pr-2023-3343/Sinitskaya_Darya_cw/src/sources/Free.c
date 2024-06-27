#include"../include/Free.h"

//метод освобождения памяти
void Free(Text *text) {
    //освобождение памяти для каждого предложения в массиве
    for (int i = 0; i < text->size; i++) {
        free(text->sentences[i].sentence);
    }
    
    //освобождение памяти для массива предложений
    free(text->sentences);
    
    //сброс значения размера массива предложений
    text->size = 0;
}
