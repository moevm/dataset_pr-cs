#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "sum_between_even_odd.h"

int not_main();

void _start() {
    exit(not_main());
};

int not_main() {
    int command;
    char trailing_char;
    // get command code
    scanf("%d ", &command);

    // get input numbers
    for (length = 1; length <= 100; length++) {
        scanf("%d%c", &(nums[length - 1]), &trailing_char);
        // check if input line ends
        if (trailing_char == '\n')
            break;
    }

    switch (command) {
        case 0:
            printf("%d\n", index_first_even());
            break;
        case 1:
            printf("%d\n", index_last_odd());
            break;
        case 2:
            printf("%d\n", sum_between_even_odd());
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd());
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
