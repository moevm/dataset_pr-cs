#include "utils.h"


size_t calc_sum(size_t *array, size_t size) {
    size_t sum = 0;
    for (size_t i = 0; i < size; i++)
        sum += array[i];
    return sum;
}

void say_hello()
{
    puts(START_INFO);
}

void print_help() {
    puts(HELP_MSG_H);
    puts(HELP_MSG_ZERO);
    puts(HELP_MSG_ONE);
    puts(HELP_MSG_TWO);
    puts(HELP_MSG_THREE);
    puts(HELP_MSG_FOUR);
    puts(HELP_MSG_FIVE);
};

void panic(const char* message) {
    printf("%s\n", message);
    exit(0);
}

char get(char* buf) {
    *buf = getchar();
    return *buf;
}

void put(char symbol) {
    fputc(symbol, stdout);
}

unsigned int get_hours_to_end_of_year() {
    time_t now = time(0);
    struct tm buf = *localtime(&now);
    struct tm next_year = {.tm_year = buf.tm_year + 1, .tm_mday=1};
    unsigned int seconds = difftime(mktime(&next_year), now);
    return seconds / 3600;
}

