#ifndef MY_LIB_H_INCLUDED
#define MY_LIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>

#define BLOCK 8

struct Sentence{
    wchar_t* snt;
    int cnt_ch;
    int cnt_wrd;
};

struct Text{
    struct Sentence* txt;
    int cnt_sen;
};


#include "Input_Sentence.h"
#include "Input_Text.h"
#include "ERROR.h"
#include "DELL.h"
#include "find.h"
#include "Memory_Cleaning.h"
#include "Replace.h"
#include "Sort_low_cnt_wrd.h"
#include "find_no_reg.h"
typedef wchar_t ch;



#endif // MY_LIB_H_INCLUDED
