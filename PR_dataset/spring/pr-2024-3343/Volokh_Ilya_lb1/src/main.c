#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_RAZ 250

struct Bigger_Info {
    char *adress;
    char *file;
};

int main() {
    regex_t regor;
    int rep;
    char gotten[MAX_RAZ];
    struct Bigger_Info *whole_data = NULL;
    int count = 0;
    regmatch_t groups[7];
    rep = regcomp(&regor, "(http://)?(www\\.)?(([A-Za-z0-9\\-]+\\.)+[A-Za-z0-9\\-]+)\\/([A-Za-z0-9\\/\\-_]+\\/)*([A-Za-z0-9_\\-]+\\.[A-Za-z0-9]+)", REG_EXTENDED);
    while (1) {
        fgets(gotten, MAX_RAZ - 1, stdin);
        if (strstr(gotten, "Fin.") != NULL) {
            break;
        }
        rep = regexec(&regor, gotten, 7, groups, 0);
        if (rep == 0) {
            whole_data = realloc(whole_data, (count + 1) * sizeof(struct Bigger_Info));
            whole_data[count].adress = strndup(gotten + groups[3].rm_so, groups[3].rm_eo - groups[3].rm_so);
            whole_data[count].file = strndup(gotten + groups[6].rm_so, groups[6].rm_eo - groups[6].rm_so);
            count++;
        }
    }
    for (int i = 0; i < count; i++) {
        printf("%s - %s\n", whole_data[i].adress,  whole_data[i].file);
        free(whole_data[i].adress);
        free(whole_data[i].file);
    }
    free(whole_data);
    regfree(&regor);
    return 0;
}
