#include <stdio.h>
#include <regex.h>
#include <string.h>

int main() {
    char* reg_str = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: ?~ ?# (.+\n)";
    regex_t reg_compiled;
    regcomp(&reg_compiled, reg_str, REG_EXTENDED);
    size_t max_groups = 3;
    regmatch_t match_groups[max_groups];

    char cur_str[1000];
    fgets(cur_str, 1000, stdin);
    while(strstr(cur_str, "Fin.") == 0) {
        if (regexec(&reg_compiled, cur_str, max_groups, match_groups, 0) == 0) {
            for (int i = 1; i < max_groups; i++) {
                for (int j = match_groups[i].rm_so; j < match_groups[i].rm_eo; j++) {
                    printf("%c", cur_str[j]);
                }
                if (i == 1)
                    printf(" - "); 
            }
        }
        fgets(cur_str, 1000, stdin);
    }
    return 0;
}