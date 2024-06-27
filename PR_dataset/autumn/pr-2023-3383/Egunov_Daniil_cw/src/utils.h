#ifndef CW_UTILS_H
#define CW_UTILS_H

#include <stdbool.h>
#include <wchar.h>

bool wcscaseends(const wchar_t *main, const wchar_t *sub);

bool is_separator(wchar_t c);

wchar_t *wcs_to_lower(wchar_t *wcs);

#endif //CW_UTILS_H
