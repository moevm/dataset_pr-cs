#pragma once

#define __USE_XOPEN
#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))

size_t calc_sum(size_t* array, size_t size);

#define START_INFO "Course work for option 4.17, created by Igor Rautio."
void say_hello();

#define HELP_MSG_H "Справка о командах программе:"
#define HELP_MSG_ZERO "0 — вывод текста после первичной обработки;"
#define HELP_MSG_ONE "1 — найти в предложениях все даты, записанные в виде “<год> <месяц> <день>” (“1886 Jun 03”), и заменить их на строку, показывающую сколько осталось часов до конца года;"
#define HELP_MSG_TWO "2 — вывести все строки, выделив слова на четных позициях красным цветом, а на нечетных зеленым;"
#define HELP_MSG_THREE "3 — удалить все предложения, которые начинаются и заканчиваются на одно и то же слово;"
#define HELP_MSG_FOUR "4 — отсортировать предложения по увеличению сумме кодов символов первого слова в предложении;"
#define HELP_MSG_FIVE "5 — вывести эту справку."
void print_help();

void panic(const char* message);

char get(char* buf);

void put(char symbol);

unsigned int get_hours_to_end_of_year();
