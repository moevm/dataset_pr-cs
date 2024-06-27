#ifndef CW_ARRAY_MACROS_H
#define CW_ARRAY_MACROS_H
#define SIZE 2
#define ArrayDecl(type)                                                                 \
    typedef struct array_##type {                                                       \
        type *arr;                                                                      \
        size_t size, capacity;                                                          \
        void (*deleter)(type *p);                                                       \
    } Array_##type;                                                                     \
                                                                                        \
    Array_##type create_##type##_array(void (*deleter)(type *));                        \
                                                                                        \
    void clear_##type##_array(Array_##type *arr);                                       \
                                                                                        \
    void resize_##type##_array(Array_##type *arr);                                      \
                                                                                        \
    void add_##type##_element(Array_##type *arr, type element);                         \
                                                                                        \
    void append_##type##_array(Array_##type *base, type *src, size_t src_size );        \

#define ArrayDef(type)                                                                  \
    Array_##type create_##type##_array(void (*deleter)(type *)) {                       \
        Array_##type arr = { calloc(SIZE, sizeof(type)), 0, SIZE, deleter };            \
        if(arr.arr)                                                                     \
            return arr;                                                                 \
        else {                                                                          \
            printf("[create_" #type "_array()]: memory allocation error!\n");           \
            exit(40);                                                                   \
        }                                                                               \
    }                                                                                   \
                                                                                        \
    void clear_##type##_array(Array_##type *arr) {                                      \
        if (arr->deleter) {                                                             \
            for (size_t i = 0; i < arr->size; ++i)                                      \
                arr->deleter(&arr->arr[i]);                                             \
        }                                                                               \
        if (arr->size)                                                                  \
            free(arr->arr);                                                             \
        arr->size = 0, arr->capacity = 0;                                               \
    }                                                                                   \
                                                                                        \
    void resize_##type##_array(Array_##type *arr){                                      \
        arr->capacity *= 2;                                                             \
        type *temp = realloc(arr->arr, arr->capacity * sizeof(type));                   \
        if(temp)                                                                        \
            arr->arr = temp;                                                            \
        else {                                                                          \
            printf("[resize_" #type "_array()]: memory allocation error!\n");           \
            clear_##type##_array(arr);                                                  \
            exit(40);                                                                   \
        }                                                                               \
    }                                                                                   \
                                                                                        \
    void add_##type##_element(Array_##type *arr, type element) {                        \
        if(arr->capacity == (arr->size + 1)) {                                          \
            resize_##type##_array(arr);                                                 \
        }                                                                               \
        arr->arr[arr->size++] = element;                                                \
    }                                                                                   \
                                                                                        \
    void append_##type##_array(Array_##type *base, type *src, size_t src_size ) {       \
        while(base->capacity < base->size + src_size)                                   \
            resize_##type##_array(base);                                                \
        memcpy(&base->arr[base->size], src, src_size * sizeof(type));                   \
        base->size += src_size;                                                         \
    }                                                                                   \
                                                                                        \
//    void remove_##type##_element(Array_##type *arr, type *element, _Bool(*f)(const type*, const type*)) {\
//        for (int i = 0; i < arr->size; ++i)                                             \
//            if(f(&arr->arr[i], element)) {\
//                memmove(&arr->arr[i], &arr->arr[i + 1], (arr->size-- - 1 - i) * sizeof (type));\
//                break;\
//            } else {                                                                    \
//                exit(40);                                                               \
//                }                                                                           \
//    }                                                                                   \

#endif
