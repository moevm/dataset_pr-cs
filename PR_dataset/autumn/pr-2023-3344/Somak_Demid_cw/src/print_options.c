#include "print_options.h"


void print_options(void)
{
    wprintf(L"Команда - 0: Функция выводит на экран текст после первичной обязательной обработки.\nКоманда - 1: Функция заменяет первое слово каждого предложения на второе слово из предыдещго предложения. Если второго слова нет, функция заменяет первое слово на пустую строку. Для первого предложения, второе слово функция берёт из последнего.\nКоманда - 2: Функция сортирует предложения в тексте по длинне третьего слова. Если в предложении меньше трех слов, то длина третьего слова этого предложения равняется нулю.\nКоманда - 3: Функция выводит на экран предложения, в которых в середине слова (например, вав4вав или ва5ва) встречаются цифры, выделяя такие слова зеленым цветом.\nКоманда - 4: Функция заменяет все символы, которые встречаются несколько раз подряд, одним таким символом в каждом слове каждого предложения.\n");
}