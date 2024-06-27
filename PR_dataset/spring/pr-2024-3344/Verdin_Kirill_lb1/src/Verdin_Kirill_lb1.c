#include <stdio.h>
#include <regex.h>
#include <string.h>

void print_groups_of_string(regmatch_t *group, char *s)
{
    for (size_t j = group[1].rm_so; j < group[1].rm_eo; j++)
    {
        printf("%c", s[j]);
    }
    printf(" - ");
    for (size_t j = group[2].rm_so; j < group[2].rm_eo; j++)
    {
        printf("%c", s[j]);
    }
}

int main()
{
    char *regex_string = "(\\w+)@[0-9a-zA-Z_-]+: ?~ ?# (.+\n)";
    regmatch_t group_array[3];

    regex_t regex_compiled;
    regcomp(&regex_compiled, regex_string, REG_EXTENDED);

    char s[100] = "";
    while (strcmp(s, "Fin."))
    {
        fgets(s, 100, stdin);
        if (regexec(&regex_compiled, s, 3, group_array, 0) == 0)
        {
            print_groups_of_string(group_array, s);
        }
    }
    regfree(&regex_compiled);
    return 0;
}