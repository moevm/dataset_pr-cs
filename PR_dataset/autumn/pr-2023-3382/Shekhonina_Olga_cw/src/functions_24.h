#include "structs.h"

int comp(const void* a, const void* b);
int is_number(wchar_t* num, int len);
int wchar_to_int(wchar_t* num, int len);
void ExpandDates(DateArray* dates);
int validate(wchar_t* day, wchar_t* month, wchar_t* year);
void find_dates(Text* text);
void sort_dates(Text* text);
void output_sorted_dates(Text* text);
int did_date_happen(Date* date);
void did_dates_happen(Text* text);
