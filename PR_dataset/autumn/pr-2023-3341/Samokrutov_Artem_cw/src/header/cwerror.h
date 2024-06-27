#ifndef CWERROR_H
#define CWERROR_H


#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define TASK_ERR_MSG L"incorrect task number. Type '5' for help"
#define MEMORY_ERR_MSG L"memory could not be allocated succesfully"
#define NO_TERMINATION_SEQUENCE_ERR_MSG L"text ended without a correct termination sequence"
#define NO_INPUT_ERR_MSG L"no text"
#define NO_WORDS_ERR_MSG L"text has 0 words"
#define FORMAT_ERR_MSG L"incorrect text format"


void throw_error(const wchar_t *);

#endif
