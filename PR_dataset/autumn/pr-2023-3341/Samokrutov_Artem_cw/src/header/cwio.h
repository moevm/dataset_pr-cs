#ifndef CWIO_H
#define CWIO_H


#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "cwerror.h"
#include "cwfuncs.h"
#include "cwstructures.h"

#define CW_OPTION L"5.8"
#define FIRST_NAME L"Artem"
#define LAST_NAME L"Samokrutov"
#define TERMINATION_SEQUENCE L"\n\n"
#define SENTENCE_SEPARATORS L"."
#define WORD_SEPARATORS L" ,\n"
#define STRING_TERMINATOR L'\0'


void print_cw_info(void);

void print_Text(Text *);

void get_task(int *);

wchar_t *read(int *);

void help(void);


#endif
