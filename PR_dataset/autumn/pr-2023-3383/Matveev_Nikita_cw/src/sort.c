#include "sort.h"
int len_cmp(const void* str_one, const void* str_two){
    wchar_t* str1 = *(wchar_t**)str_one;
    wchar_t* str2 = *(wchar_t**)str_two;
    int len1 = wcslen(str1);
    int len2 = wcslen(str2);
    return len1 - len2;
}

int v_comp(const void* str_one, const void* str_two){
    int v_count_str1 =0;
    int v_count_str2 =0;
    wchar_t* str1 = *(wchar_t**)str_one;
    wchar_t* str2 = *(wchar_t**)str_two;
    for (int i =0; i<wcslen(str1); i++){
        if (wcschr(L"aeiouyAEIOUYаоуыэеёиюяАОУЫЭЕЁИЮЯ", str1[i]) != NULL){
            v_count_str1 += 1;
        }
    }
     for (int j =0; j<wcslen(str2); j++){
        if (wcschr(L"aeiouyAEIOUYаоуыэеёиюяАОУЫЭЕЁИЮЯ", str2[j]) != NULL){
            v_count_str2 += 1;
        }
    }
    return v_count_str1 - v_count_str2;
}

int cmp_mask(const void *a, const void *b){
    wchar_t* s1 = *(wchar_t**)a;
    wchar_t* s2 = *(wchar_t**)b;
    int count_alph1 = 0, count_alph2 = 0;
    for (int p = 0; p < wcslen(s1); p++){
        if (s1[p] != L'?'){
            count_alph1++;
        }
    }
    for (int p1 = 0; p1 < wcslen(s2); p1++){
        if (s2[p1] != L'?'){
            count_alph2++;
        }
    }
    if (count_alph1 > count_alph2){
        return -1;
    }
    else if(count_alph1 < count_alph2){
        return 1;
    }
    else {
        if ((wcslen(s1) - count_alph1) > (wcslen(s2) - count_alph2)){
            return 1;
        } else if ((wcslen(s1) - count_alph1) < (wcslen(s2) - count_alph2)){
            return -1;
        } else {
            return 0;
        }
    }
}
