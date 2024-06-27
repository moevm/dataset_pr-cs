#pragma once
#include "structs.h"
#include "leave.h"

#define ALL L"Палиндромы на месте!" 
#define NO L"Кто-то потерял все палиндромы."
#define SOME  L"Чего-то не хватает."
#define NO_WORDS L"В предложении нет слов"

bool check_no_words(Sentence*);
void print_palindrome_status(Sentence*, bool, bool);
void is_palindrome(Sentence*);
void print_palindromes(Text*);