#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "compare_multiply.h"
#include "structs.h"


int compare_multiply(const void *a, const void *b)
{
    setlocale(LC_ALL, "");

    const struct Sentence s1 = *(const struct Sentence *)a;
    const struct Sentence s2 = *(const struct Sentence *)b;
    
    int m1 = 1, m2 = 1, len = 0;
    int i = 0;
    
    while (s1.sentence[i] != '\0') {
        if (wcschr(L" ,.", s1.sentence[i]) == NULL) {
            len++;
        } else {
            m1 *= len > 0 ? len : 1;
            len = 0;
        }
        i++;
    }
    
    i = 0, len = 0;
    
    while (s2.sentence[i] != '\0') {
        if (wcschr(L" ,.", s2.sentence[i]) == NULL) {
            len++;
        } else {
            m2 *= len > 0 ? len : 1;
            len = 0;
        }
        i++;
    }
    
    return m1 - m2;
}