#include <locale.h>
#include <stdio.h>

#include "exec_command.h"
#include "util/config.h"
#include "util/error.h"

int main(void) {
    if (setlocale(LC_ALL, LOCALE) == NULL) {
        printf("Current locale: %s\n", setlocale(LC_ALL, NULL));
        ERROR("No " LOCALE " encoding", 1);
    }
    puts("Course work for option 5.2, created by Vadim Grebenyuk.");
    exec_command();
    return 0;
}
