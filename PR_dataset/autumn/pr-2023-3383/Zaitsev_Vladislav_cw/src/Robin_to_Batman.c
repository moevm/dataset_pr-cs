#include "Robin_to_Batman.h"

char *Robin_to_Batman_str(char *str, char *find, char *replace){
    int str_len = strlen(str);
    int find_len = strlen(find);
    int replace_len = strlen(replace);
    int count = 0;
    const char* tmp = str;
    while ((tmp = strstr(tmp, find)) != NULL) {
        count++;
        tmp += find_len;
    }
    if (count == 0){
        return NULL;
    }
    int new_len = str_len + count * (replace_len - find_len);
    char* new_str = (char*)malloc((new_len + 1) * sizeof(char));

    char* ptr = new_str;
    tmp = str;
    while (count > 0) {
        const char* substr = strstr(tmp, find);
        if (substr != NULL) {
            strncpy(ptr, tmp, substr - tmp);
            ptr += substr - tmp;
            strncpy(ptr, replace, replace_len);
            ptr += replace_len;
            tmp = substr + find_len;
            count--;
        }
        else {
            strcpy(ptr, tmp);
            break;
        }
    }
    strcpy(ptr, tmp);
    new_str[new_len] = '\0';
    return new_str;
}

