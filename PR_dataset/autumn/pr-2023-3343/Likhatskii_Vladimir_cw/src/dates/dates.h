#include <wchar.h>
#include <stdlib.h>
#define __USE_XOPEN
#include <time.h>
#include <string.h>
#include <wctype.h>
#include <stdio.h>

#include "../config/config.h"
#include "../helpers/helpers.h"

typedef struct {
    wchar_t *string; 
    struct tm *raw;
} Date;

int datecomp(const void *, const void *);
Date ** findshortdates(wchar_t *);
wchar_t * replacelongdates(wchar_t *);

int parsenum(wchar_t *);