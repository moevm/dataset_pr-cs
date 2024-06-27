#include "Libraries.h"

#define STRING_SIZE 1202


int input(int array[], int* size) {
    char string[STRING_SIZE];

    fgets(string, STRING_SIZE, stdin);

    if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = 0;

    char *current_str;

    current_str = strtok(string, " ");
    int func_type = atoi(current_str);

    current_str = strtok(NULL, " ");

    while (current_str != NULL) {
        array[(*size)++] = atoi(current_str);
        current_str = strtok(NULL, " ");
    }

    return func_type;
}