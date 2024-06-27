#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

char** read_string(int* arr_s_len) {
    char* s = (char*)malloc(100 * sizeof(char));
    char** arr_s = (char**)malloc(100 * sizeof(char*));

    int s_maxlen = 100;
    int arr_s_maxlen = 100;
    int s_len = 0;
    *arr_s_len = 0;

    while (1) {
        if (s_len == s_maxlen - 1) {
            s = realloc(s, s_maxlen + 100);
            s_maxlen += 100;
        }

        if (*arr_s_len == arr_s_maxlen - 1) {
            arr_s = realloc(arr_s, (arr_s_maxlen + 100) * sizeof(char*));
            arr_s_maxlen += 100;
        }

        char input_c = getchar();
        if (input_c == '\n' || input_c == EOF) {
            s[s_len] = '\0';
            if (strcmp(s, "Fin.") == 0) {
                break;
            }
            arr_s[(*arr_s_len)++] = strdup(s);

            s_len = 0;
            continue;
        }
        s[s_len++] = input_c;
    }
    free(s);
    return arr_s;
}

int main()
{
    char* regexp = "([a-zA-Z0-9_]+)\\@[a-z0-9A-Z_-]+\\: ?\\~ ?\\# (.+)";
    int max_groups = 3;
    int arr_ex_len;

    regex_t regex;
    regmatch_t arr_group[max_groups];
    if (regcomp(&regex, regexp, REG_EXTENDED)) {
        return 0;
    }
    char** arr_ex = read_string(&arr_ex_len);

    for (int i = 0; i < arr_ex_len  ; i++) {
        if (regexec(&regex, arr_ex[i], max_groups, arr_group, 0) == 0) {
            arr_ex[i][arr_group[1].rm_eo] = '\0';
            arr_ex[i][arr_group[2].rm_eo] = '\0';
            printf("%s - %s\n", arr_ex[i] + arr_group[1].rm_so, arr_ex[i] + arr_group[2].rm_so);
        }
    }

    for (int i = 0; i < arr_ex_len ; ++i)
    {
        free(arr_ex[i]);
    }
    free(arr_ex);

    return 0;
}
