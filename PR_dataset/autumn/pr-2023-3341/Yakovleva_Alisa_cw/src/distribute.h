#pragma once
#include "structures.h"
#include "output.h"
#include "transliteration.h"
#include "output_special_wchar.h"
#include "replace_numbers.h"
#include "delete_sentences.h"
#include "double_word.h"
#include "help.h"
#define NUMBER_OF_FUNCTIONS 5
#define NUMBER_OF_ADDED_FUNCTION 9

int check_function_number(int* number_function);
void distribute(int function_number, struct Text* text);
