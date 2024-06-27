#include "helpers.h"

int endswith(wchar_t *needle, wchar_t *haystack) {
    // if(wcslen(needle) > wcslen(haystack)) return 0;

    // for(int i = 0; i < wcslen(needle); i++) {
    //     if(towlower(needle[wcslen(needle) - i - 1]) != towlower(haystack[wcslen(haystack) - i - 1])) {
    //         return 0;
    //     }
    // }

    // return 1;
    return wcsstr(haystack, needle) != NULL;
}

int icmp(wchar_t *a, wchar_t *b) {
    if(wcslen(a) != wcslen(b)) return 1; 

    for(int i = 0; i < wcslen(a); i++) {
        if(towlower(a[i]) != towlower(b[i])) {
            return 1;
        }
    }

    return 0;
}

int isempty(wchar_t *str) {
    if(wcslen(str) < 1) return 1;
    if(str[0] == L'.') return 1;

    for(int i = 0; i < wcslen(str); i++) {
        if(wcschr(TEXT_DELIMITERS, str[i]) == NULL  && wcschr(SENTENCE_END, str[i]) == NULL){
            return 0;
        };
    }
    return 1;
}

wchar_t *trimstart(wchar_t *str, wchar_t *trimmers) {
    int offset = 0; 

    while(wcschr(trimmers, *(str + offset)) != NULL) { offset ++; }

    return (str + offset);
}

wchar_t * trimend(wchar_t *str, wchar_t *trimmers) {
    int length = wcslen(str); 

    while(wcschr(trimmers, str[length - 1]) != NULL) {
        length--;
    }

    if(length == wcslen(str)) return str;

    wchar_t *result = malloc((length + 1) * sizeof(wchar_t));
    result[0] = L'\0';
    wcscat(result, str);
    result[length] = L'\0'; 

    return result;
}

wchar_t *trim(wchar_t *str, wchar_t *trimmers) {
    return trimstart(trimend(str, trimmers), trimmers);
    // return trimstart(str, trimmers);
}

wchar_t *replace(wchar_t *s, const wchar_t *s1, const wchar_t *s2) {
    wchar_t *p = wcsstr(s, s1);
    if (p != NULL) {
        size_t len1 = wcslen(s1);
        size_t len2 = wcslen(s2);
        if (len1 != len2)
            memmove(p + len2, p + len1, (wcslen(p + len1) + 1) * sizeof(wchar_t));
        memcpy(p, s2, len2 * sizeof(wchar_t));
    }
    return s;
}

wchar_t *replaceall(wchar_t *s, const wchar_t *s1, const wchar_t *s2) {
    wchar_t *p;
    while ((p = wcsstr(s, s1)) != NULL) {
        size_t len1 = wcslen(s1);
        size_t len2 = wcslen(s2);
        if (len1 != len2)
            memmove(p + len2, p + len1, (wcslen(p + len1) + 1) * sizeof(wchar_t));
        memcpy(p, s2, len2 * sizeof(wchar_t));
    }
    return s;
}