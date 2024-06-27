#include <stdio.h>
#include <regex.h>
#include <string.h>

#define BUFFER_SIZE 500
#define MAX_MATCHES 4

int main() {
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    int regex_status;
    char buffer[BUFFER_SIZE];
    regex_status = regcomp(&regex, "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+):[ ]*~[ ]*# (.+)\n", REG_EXTENDED);
    if (regex_status != 0) {
        return 1;
    }
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        if (strstr(buffer, "Fin.") != NULL) {
            break;
        }
        if (regexec(&regex, buffer, MAX_MATCHES, matches, 0) == 0) {
            for (int i = matches[1].rm_so; i < matches[1].rm_eo; i++) {
                printf("%c", buffer[i]);
            }
            printf(" - ");
            for (int i = matches[3].rm_so; i < matches[3].rm_eo; i++) {
                printf("%c", buffer[i]);
            }
            printf("\n");
        }
    }
    regfree(&regex);
    return 0;
}