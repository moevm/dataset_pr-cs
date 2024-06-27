#include <regex.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 1000
#define SITE_GROUP 3
#define FILE_GROUP 7
#define REGEX_STRING                                                           \
    "([a-z]+:\\/\\/)?(www\\.)?(([a-z0-9]+\\.)+[a-z]+)\\/((\\w+\\/"             \
    ")+)?(\\w+\\.\\w+)"

int main()
{
    size_t maxGroups = 8;

    regex_t regex;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regex, REGEX_STRING, REG_EXTENDED))
    {
        printf("Error while compiling regular expression\n");
        return 1;
    };

    char input_string[BUF_SIZE];
    while (!strstr(input_string, "Fin."))
    {
        (fgets(input_string, BUF_SIZE, stdin));

        if (!regexec(&regex, input_string, maxGroups, groupArray, 0))
        {
            for (int i = groupArray[SITE_GROUP].rm_so;
                 i < groupArray[SITE_GROUP].rm_eo; i++)
                printf("%c", input_string[i]);

            printf(" - ");

            for (int i = groupArray[FILE_GROUP].rm_so;
                 i < groupArray[FILE_GROUP].rm_eo; i++)
                printf("%c", input_string[i]);

            printf("\n");
        }
    }

    regfree(&regex);
    return 0;
}