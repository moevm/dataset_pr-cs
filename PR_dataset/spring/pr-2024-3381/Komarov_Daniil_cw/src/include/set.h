#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "errors.h"

#define BLOCK_SIZE 5

typedef struct Set_struct
{
    int64_t *arr;
    size_t len;
    size_t allocated;
} Set;

Set *set_new();

void set_add(Set *set, int64_t value, int *status_code);

int set_check(Set *set, int64_t value);

void set_listall(Set *set, int64_t **arr, size_t *arr_len, int *status_code);

void set_destroy(Set *set);

#endif
