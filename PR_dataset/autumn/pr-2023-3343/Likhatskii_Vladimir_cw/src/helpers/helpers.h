#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <string.h>

#pragma once
#include "../config/config.h"
int contains(wchar_t *, wchar_t *);
int endswith(wchar_t *, wchar_t *);
int startswith(wchar_t *, wchar_t *);
int icmp(wchar_t *, wchar_t *);
int isempty(wchar_t *);
wchar_t * trim(wchar_t *, wchar_t *);
wchar_t * trimstart(wchar_t *, wchar_t *);
wchar_t * trimend(wchar_t *, wchar_t *);
wchar_t *replace(wchar_t *s, const wchar_t *s1, const wchar_t *s2);
wchar_t *replaceall(wchar_t *s, const wchar_t *s1, const wchar_t *s2);
