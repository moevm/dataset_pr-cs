#include "string.h"
#include <ctype.h> // tolower
#include <stdio.h> // for sscanf

#include "fatal_error.h"

#define STRING_BLOCKSIZE 8

void string_init(string_t *str, size_t len)
{
    str->len = len;
    str->capacity = len;
    str->data = (char*)malloc(len);
    
    if (str->len != 0 && str->data == NULL)
        fatal_error("failed to allocate %ld bytes.", len);

    str->hash = 5381;
    str->word_count = 0;
}

void string_deinit(string_t *str)
{
    free(str->data);
}

void string_grow_memory(string_t *str)
{
    if (str->capacity == 0)
        str->capacity = STRING_BLOCKSIZE;
    else
        str->capacity *= 2;

    str->data = (char*)realloc(str->data, str->capacity);
    if (str->len != 0 && str->data == NULL)
        fatal_error("failed to reallocate %ld bytes.", str->capacity);
}

void string_push_back(string_t *str, char c)
{
    if (str->len == str->capacity)
        string_grow_memory(str);

    str->data[str->len++] = c;
}

void string_update_hash(string_t *str)
{
    char *str_ptr = str->data;
    unsigned long hash = 5381;
    char c;

    for (size_t i = 0; i < str->len; i++) {
        c = tolower(*str_ptr++);
        if (c == '\0')
            break;

        hash = hash * 33 + c;
    }

    str->hash = hash;
}

int is_separator(char c)
{
    return isspace(c) || c == ',' || c == '.' || c == '\0';
}

void string_update_word_count(string_t *str)
{
    unsigned int cnt = 0;

    for (size_t i = 1; i < str->len; i++) {
        char prev = str->data[i - 1];
        char cur  = str->data[i];
        
        if (!is_separator(prev) && is_separator(cur))
            cnt++;
        if (prev == '\0' || cur == '\0')
            break;    
    }

    if (!is_separator(str->data[str->len - 1]))
        cnt++;

    str->word_count = cnt;
}

int string_eq(string_t *str1, string_t *str2)
{
    if (str1->hash != str2->hash)
        return 0;

    if (str1->len != str2->len)
        return 0;

    char *p1 = str1->data, *p2 = str2->data;
    char *end = str1->data + str1->len;
    while(p1 != end && (tolower(*p1) == tolower(*p2))) {
        p1++;
        p2++;
    }
    return p1 == end;
}

void string_shrink(string_t *str)
{
    str->capacity = str->len;
    str->data = (char*)realloc(str->data, str->capacity);

    if (str->len != 0 && str->data == NULL)
        fatal_error("failed to reallocate %ld bytes.", str->capacity);
}

char *get_word_start(char *text, char *end)
{
    while (text != end && is_separator(*text)) text++;
    return text;
}

char *get_word_end(char *text, char *end)
{
    while (text != end && !is_separator(*text)) text++;
    return text;
}

void string_update_timesum(string_t *str)
{
    size_t timesum = 0;
    char *str_end = str->data + str->len;

    char *start = get_word_start(str->data, str_end);
    char *end   = get_word_end(start, str_end);

    while (start != end) {
        int hour, min, sec;
        
        if ((sscanf(start, "%02d-%02d-%02d", &hour, &min, &sec) == 3) && (end - start == 8))
            timesum += sec + min*60 + hour*3600;

        start = get_word_start(end, str_end);
        end = get_word_end(start, str_end);
    }

    str->timesum = timesum;
}