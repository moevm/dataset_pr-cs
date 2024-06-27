#include "tools/char_struct.h"

Char_struct *
init_char_struct()
{
    Char_struct *_char_struct = (Char_struct *)malloc(sizeof(Char_struct));

    _char_struct->data = NULL;
    _char_struct->len = DEFAULT_LEN;
    _char_struct->capacity = DEFAULT_CAPACITY;
    _char_struct->end = DEFAULT_END;

    return _char_struct;
}

void free_char_struct(Char_struct *_char_struct)
{
    free(_char_struct->data);
    free(_char_struct);
}

void _increase_capacity_char_struct(Char_struct *_char_struct, size_t single_size)
{
    _char_struct->capacity = _ceil(
        _char_struct->capacity *
        DEFAULT_CAPACITY_INCREASE_COEFFICIENT);

    _char_struct->data = realloc(
        _char_struct->data,
        _char_struct->capacity * single_size);
}
