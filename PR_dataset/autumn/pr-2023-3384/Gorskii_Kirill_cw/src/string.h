#ifndef CW_STRING_H
#define CW_STRING_H

#include <stdlib.h> // size_t

typedef struct {
    size_t len;
    size_t capacity;
    char *data;
    size_t timesum;
    unsigned long hash;
    unsigned int word_count;
} string_t;

void string_init(string_t *str, size_t len);
void string_deinit(string_t *str);
void string_push_back(string_t *str, char c);
void string_update_hash(string_t *str);
void string_update_timesum(string_t *str);
void string_update_word_count(string_t *str);
int  string_eq(string_t *str1, string_t *str2);
void string_shrink(string_t *str);

char *get_word_start(char *text, char *end);
char *get_word_end(char *text, char *end);

#endif