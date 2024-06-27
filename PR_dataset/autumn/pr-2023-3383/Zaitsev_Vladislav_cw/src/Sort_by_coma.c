#include "Sort_by_coma.h"

int coma_cmp(const void *s1, const void *s2){
        const char *str1 = *(const char **)s1;
        const char *str2 = *(const char **)s2;
        int com1 = 0;
        int com2 = 0;
        for (int i = 0; i < strlen(str1); i++){
                if (str1[i] == ','){
                        com1++;
                }
        }
        for (int i = 0; i < strlen(str2); i++){
                if (str2[i] == ','){
                        com2++;
                }
        }
        return com1 - com2;
}
char **Sort_by_coma(int *len, char **text){
        qsort(text, *len, sizeof(char *), coma_cmp);
        return text;
}

