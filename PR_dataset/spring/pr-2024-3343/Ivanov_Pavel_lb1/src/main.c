#include <stdio.h>
#include <regex.h>

void print_group(char* str, regmatch_t matched_group){
    for (int i = matched_group.rm_so; i < matched_group.rm_eo; ++i) {
        printf("%c", str[i]);
    }
}

int main(){
    char pattern[] = "([A-z]+:\\/\\/)?(www\\.)?([A-z-]+\\.[A-z-]+(\\.[A-z_-]+)*)\\/([A-z]+\\/)*([A-z]+\\.[A-z0-9]+\n?)"; //3 //6
    int capturing_groups = 7;

    regex_t regex_compiled;
    regmatch_t matched_groups[capturing_groups];

    if (regcomp(&regex_compiled, pattern, REG_EXTENDED)){
        printf("pattern error");
        return 0;
    }

    char str[100];
    while (fgets(str, 100, stdin)){
        if (regexec(&regex_compiled, str, capturing_groups, matched_groups, 0) == 0){
            print_group(str, matched_groups[3]);
            printf(" - ");
            print_group(str, matched_groups[6]);
        }
    }

    regfree(&regex_compiled);
    return 0;
}
