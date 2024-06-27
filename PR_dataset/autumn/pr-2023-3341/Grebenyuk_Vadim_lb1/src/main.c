#include <stdio.h>
#include <stdlib.h>

int nums[100];
int command;
char trailing_char;
int length;

int index_first_even() {
    for (int i = 0; i < length; i++)
        if ((nums[i] & 1) == 0)
            return i;
}

int index_last_odd() {
    for (int i = length - 1; i > 0; i--)
        if (nums[i] & 1)
            return i;
}

int sum(int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++)
        sum += abs(nums[i]);
    return sum;
}

int main() {
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
            printf("%d\n", sum(index_first_even(), index_last_odd()));
            break;
        case 3:
            printf("%d\n", sum(0, index_first_even()) + sum(index_last_odd(), length));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
