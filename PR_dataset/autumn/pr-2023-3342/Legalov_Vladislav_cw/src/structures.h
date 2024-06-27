#pragma once
#include<wchar.h>

struct Sentence {
wchar_t* str;
size_t size, count_upper;
};

typedef struct Sentence Sentence;


struct Text {
Sentence** sentences;
size_t size, capacity;
};

typedef struct Text Text;

struct BreaksData {
int *breaks_pos;
int size, size_breaks;
};

typedef struct BreaksData BreaksData;
