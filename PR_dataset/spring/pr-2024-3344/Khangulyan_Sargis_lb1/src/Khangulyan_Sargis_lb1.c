#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(){
    char input_text[1000];
    char* pattern = "(http|https|ftp)?(:\\/\\/)?(www\\.)?([A-Za-z0-9]+(\\.[a-zA-Z0-9]+)+)(\\/.+)*\\/([A-Za-z0-9]+\\.[A-Za-z0-9]+)";
    size_t max_groups = 8;
    regex_t compiled_pattern;
    regmatch_t group_array[max_groups];
    regcomp(&compiled_pattern, pattern, REG_EXTENDED);

    while (1){
        fgets(input_text, 1000, stdin);
        
        if (regexec(&compiled_pattern, input_text, max_groups, group_array, 0) == 0){
            for (int i = group_array[4].rm_so; i < group_array[4].rm_eo; i++)
                printf("%c", input_text[i]);
            printf(" - ");
            for (int j = group_array[7].rm_so; j < group_array[7].rm_eo; j++)
                printf("%c", input_text[j]);
            printf("\n");
        }

        if (strstr(input_text, "Fin."))
            break;
    }

    regfree(&compiled_pattern);
    return 0;
}