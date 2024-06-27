#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    char **matrix = NULL;
    int row = 0;
    int col = 0;
    int max_rows = 1;

    matrix = (char **)malloc(max_rows * sizeof(char *));

    char c;
    do {
        c = getchar();
        if (c == '\n') {
            matrix[row][col] = '\0';
            row++;
            if (row >= max_rows) {
                max_rows *= 2;
                matrix = (char **)realloc(matrix, max_rows * sizeof(char *));
            }
            matrix[row] = (char *)malloc(100 * sizeof(char));
            col = 0;
        } else {
            if (col == 0) {
                matrix[row] = (char *)malloc(100 * sizeof(char));
            }
            matrix[row][col] = c;
            col++;
        }
    } while (strcmp(matrix[row], "Fin.") != 0);

    regex_t regex;
    regmatch_t matches[8];
    char *pattern = "([a-z]+:\\/\\/)?(www\\.)?(([a-zA-Z0-9_]+\\.)+[a-zA-Z0-9_]+)(\\/)([a-zA-Z0-9_]+\\/)*([a-zA-Z0-9_]+\\.[a-zA-Z0-9_]+)";
    int status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char err[100];
        regerror(status, &regex, err, sizeof(err));
        printf("%s\n", err);
        return 1;
    }
    for (int i = 0; i < row; i++) {
        if (regexec(&regex, matrix[i], 8, matches, 0) == 0) {
            int start = matches[3].rm_so;
            int end = matches[3].rm_eo;
            printf("%.*s - ", end - start, matrix[i] + start);

            start = matches[7].rm_so;
            end = matches[7].rm_eo;
            printf("%.*s\n", end - start, matrix[i] + start);
        }
    }

    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
