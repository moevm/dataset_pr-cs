#include "../include/set.h"

Set *set_new()
{
    Set *res = (Set *) malloc(sizeof(Set));
    if(res == NULL) return NULL;

    res->arr = (int64_t *) malloc(sizeof(int64_t) * BLOCK_SIZE);
    if(res->arr == NULL)
    {
        free(res);
        return NULL;
    }
    
    res->len = 0;
    res->allocated = BLOCK_SIZE;
    return res;
}

void set_add(Set *set, int64_t value, int *status_code)
{
    // If already exists
    if(set_check(set, value))
    {
        *status_code = RETCODE_OK;
        return;
    }

    // Reallocate if not enough space
    if(set->allocated == set->len)
    {
        int64_t *new_arr = (int64_t *) realloc(set->arr,
            sizeof(int64_t) * (set->allocated + BLOCK_SIZE));
        if(new_arr == NULL)
        {
            *status_code = RETCODE_MEMORY_ERROR;
            return;
        }
        set->arr = new_arr;
    }
    
    set->arr[set->len++] = value;
    *status_code = RETCODE_OK;
}

int set_check(Set *set, int64_t value)
{
    uint8_t exists = 0;
    for(size_t i = 0; i < set->len; i++)
    {
        if(set->arr[i] == value)
        {
            exists = 1;
            break;
        }
    }
    return exists;
}

void set_listall(Set *set, int64_t **arr, size_t *arr_len, int *status_code)
{
    *arr = (int64_t *) malloc(sizeof(int64_t) * set->len);
    if(*arr == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }

    memcpy(*arr, set->arr, sizeof(int64_t) * set->len);
    *arr_len = set->len;
    *status_code = RETCODE_OK;
}

void set_destroy(Set *set)
{
    free(set->arr);
    free(set);
}
