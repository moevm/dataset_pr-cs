#ifndef TIME_FUNCS
#define TIME_FUNCS
#include "structures_define.h"

void check_time(struct Text text);
int error_data_check(struct Date date);
void get_and_check_dates(struct Text txt);
struct tm* check_for_date(wchar_t *day, wchar_t* month, wchar_t* year);
int check_if_happened(struct tm *time1, struct tm *time2);
int cmp(const void *aa, const void *bb);
#endif