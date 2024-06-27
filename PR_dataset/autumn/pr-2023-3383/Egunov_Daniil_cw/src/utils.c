#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include "utils.h"


bool wcscaseends(const wchar_t *main, const wchar_t *sub) {
    size_t main_len = wcslen(main);
    size_t sub_len = wcslen(sub);
    if (sub_len > main_len) return false;
    return (wcscasecmp(&main[main_len - sub_len], sub) == 0);
}

bool is_separator(const wchar_t c) {
    return (iswspace(c) || c == L',' || c == L'.');
}

wchar_t *wcs_to_lower(wchar_t *wcs) {
    size_t wcs_len = wcslen(wcs);
    wchar_t* wcs_lower = (wchar_t *) malloc((wcs_len + 1) * sizeof(wchar_t));

    size_t cur_len;
    for (cur_len = 0; cur_len < wcs_len; cur_len++) {
        wcs_lower[cur_len] = (wchar_t) towlower(wcs[cur_len]);
    }
    wcs_lower[cur_len] = L'\0';

    return wcs_lower;
}
