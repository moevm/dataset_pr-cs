#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BUFFER_SIZE 1024

int main() {
    regex_t regex;
    const char *pattern = "([a-zA-Z0-9]+:)?(www.)?([a-zA-Z0-9\\.]+)\\/([a-zA-Z0_9]+\\/)*([a-zA-Z0-9]+(\\.[a-z0-9-]+))*$";
    regmatch_t matches[6];
    char input[BUFFER_SIZE];

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    while (fgets(input, BUFFER_SIZE, stdin)) {
        if (strcmp(input, "Fin.\n") == 0) {  
            break;
        }

        input[strcspn(input, "\n")] = 0;

        char *cursor = input;
        while (regexec(&regex, cursor, 6, matches, 0) == 0) {
            int domain_start = matches[3].rm_so;
            int domain_end = matches[3].rm_eo;
            int file_start = matches[5].rm_so;
            int file_end = matches[5].rm_eo;

            char domain[256] = "";
            char file[256] = "";

            if (domain_start != -1 && domain_end != -1) {
                strncpy(domain, cursor + domain_start, domain_end - domain_start);
                domain[domain_end - domain_start] = '\0';

                if (strstr(domain, ".") == NULL) {
                    cursor += matches[0].rm_eo;
                    continue;
                }
            }

            if (file_start != -1 && file_end != -1) {
                strncpy(file, cursor + file_start, file_end - file_start);
                file[file_end - file_start] = '\0';
            }

            printf("%s - %s\n", domain, file);
            cursor += matches[0].rm_eo;
        }
    }

    regfree(&regex);
    return 0;
}
