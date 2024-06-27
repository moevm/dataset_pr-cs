#pragma once


#include "struct.h"


// wctype-styled latin character check
char iswlatin(wchar_t c);
// wctype-styled cyrillic character check
char iswcyrillic(wchar_t c);
// Comparator function for f3_sort()
int st_sort_cmp(const void * a, const void * b);

// CourseWork tasks
void f1_palindromes(struct Text * text_p);
void f2_spec_char(struct Text * text_p);
void f3_sort(struct Text * text_p);
void f4_filter(struct Text * text_p);
void f5_info();
void f9_whitelist(struct Text * text_p, wchar_t ** whitelist);
