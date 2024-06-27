#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *end_sentence = "Dragon flew away!";

typedef struct {
    size_t len, capacity;
    char *data;
} str_t;

void str_grow(str_t *str)
{
    if (str->capacity == 0) {
        str->capacity = 2;
        str->data = malloc(2);
        return;
    }

    str->capacity = (str->capacity * 3) / 2;
    str->data = realloc(str->data, str->capacity);
    return;
}

void str_push_back(str_t *str, char c)
{
    if (str->len == str->capacity)
        str_grow(str);

    str->data[str->len++] = c;
}

void str_init(str_t *str)
{
    str->len = str->capacity = 0;
    str->data = NULL;
}

void str_deinit(str_t *str)
{
    free(str->data);
}

int is_end_of_sentence(char c)
{
    return (c == '.') || (c == ';') || (c == '?') || (c == '!');
}

int str_init_from_sentence(str_t *str, FILE *fptr)
{
    char c;
    str_init(str);

    while (isspace(c = fgetc(fptr))); /* empty thile loop. BAAAAD((( */
    if (c == EOF) return 0;

    str_push_back(str, c);

    while (!is_end_of_sentence(c = fgetc(fptr))) {
        if (c == '\n')
            c = ' ';
        str_push_back(str, c);
    }

    str_push_back(str, c);
    str_push_back(str, '\0');
    return 1;
}

int main()
{
    int cnt_before = 0;
    int cnt_after  = 0;
    str_t str;

    while (str_init_from_sentence(&str, stdin)) {
        if (strcmp(end_sentence, str.data) == 0) {
            puts(str.data);
            break;
        }

        cnt_before++;
        
        if (strchr(str.data, '7') == NULL) {
            puts(str.data);
            cnt_after++;
        }

        str_deinit(&str);
    }

    str_deinit(&str);
    printf("Количество предложений до %d и количество предложений после %d\n",
        cnt_before, cnt_after
    );
}