#include <stdio.h>
#include <regex.h>
#include <string.h>

#define WEBSITE_CAPTURING_GROUP 3
#define FILE_CAPTURING_GROUP 6
#define SIZE 100
#define REGULAR_EXPRESSION "(\\w+:\\/\\/)?(w*\\.*)?((\\w+\\.)+\\w+)\\/(\\w+\\/)*(\\w+\\.\\w+)"


int main() {
    size_t max_groups = 7;

    regex_t regex_compiled;
    regmatch_t group_array[max_groups];

    if (regcomp(&regex_compiled, REGULAR_EXPRESSION, REG_EXTENDED)) {
        printf("Can't compile regular expression\n");
        return 1;
    };

    char input[SIZE];
    while (!strstr(input, "Fin.")) {
        fgets(input, SIZE, stdin);
        if (!regexec(&regex_compiled, input, max_groups, group_array, 0)) {
            for (int i = group_array[WEBSITE_CAPTURING_GROUP].rm_so;
                 i < group_array[WEBSITE_CAPTURING_GROUP].rm_eo; i++)
                printf("%c", input[i]);
            printf(" - ");
            for (int i = group_array[FILE_CAPTURING_GROUP].rm_so; i < group_array[FILE_CAPTURING_GROUP].rm_eo; i++)
                printf("%c", input[i]);
            printf("\n");
        }
    }

    regfree(&regex_compiled);
    return 0;
}
