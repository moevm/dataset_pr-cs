#ifndef STRUCT_H
#define STRUCT_H

#include <wchar.h>

//структура предложение
typedef struct {
    wchar_t *sentence;  //указатель на строку
}Sentence;

//структура текст
typedef struct {
    Sentence *sentences; //массив предложений
    int size; //текущий размер массива предложений
}Text;

#endif