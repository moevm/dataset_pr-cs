#ifndef CWPROCESSING_H
#define CWPROCESSING_H


#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>

#include "cwerror.h"
#include "cwfuncs.h"
#include "cwio.h"
#include "cwstructures.h"

#define CHUNK 2048


int Text_nduplicate(Text *, wchar_t *, int);

void trim_start(wchar_t **);

void string_to_proper_Text(Text *, wchar_t *);


#endif
