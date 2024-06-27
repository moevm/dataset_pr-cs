#include "dict.h"

size_t find_value(wchar_t key, struct Dict *dict, size_t dict_len){
    for (size_t i = 0; i < dict_len; i++)
        if (dict->keys[i] == key)
            return i;
    panic(DICT_ERROR);
}