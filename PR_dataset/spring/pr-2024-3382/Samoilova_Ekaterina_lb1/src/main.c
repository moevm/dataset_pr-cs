#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

int main() {
	char* mask = "(www.)?((\\w+\\.)+\\w+)(.*)(\\/(\\w+\\.\\w+))";
    size_t max_groups = 7;
    regex_t mask_comp;
    regmatch_t arr_of_group[max_groups];

    if (regcomp(&mask_comp, mask, REG_EXTENDED)){
        return 0;
    }

    char text[100];
    while (fgets(text, 100, stdin)){
        if (strstr(text, "Fin.") != NULL){
            break;
        }
        if (regexec(&mask_comp, text, max_groups, arr_of_group, 0) == 0){
            char site[100];
            char file[100];
            strncpy(site, text + arr_of_group[2].rm_so, arr_of_group[2].rm_eo - arr_of_group[2].rm_so);
            site[arr_of_group[2].rm_eo - arr_of_group[2].rm_so] = '\0';

            strncpy(file, text + arr_of_group[6].rm_so, arr_of_group[6].rm_eo - arr_of_group[6].rm_so);
            file[arr_of_group[6].rm_eo  - arr_of_group[6].rm_so] = '\0';
            printf("\n%s - %s", site, file);
        }
    }
    regfree(&mask_comp);
	return 0;
}