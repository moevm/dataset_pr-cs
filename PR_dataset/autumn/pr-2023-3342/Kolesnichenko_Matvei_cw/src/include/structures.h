#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <wchar.h>

typedef struct{
    int len; //длина слова
    wchar_t* chars; //символы слова
    int followingLen; //длина символов пробелов и пунктуации после слова
    wchar_t* followingChars; //символы пробелов и пунктуации после слова
}Word;

typedef struct{
    int len; //длина предложения
    int wordsCounter; //счётчик слов
    Word* words; //массив слов
    wchar_t* chars; //предложение посимвольно
}Sentence;

typedef struct{
    int sentenceCounter; //счетчик предложений
    Sentence* sentences; //массив предложений
}Text;

#endif