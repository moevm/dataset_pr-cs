#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define SIZE 2
#define ROOT_PATH "root"
#define Array(type)                                                                     \
    typedef struct array_##type {                                                       \
        type *arr;                                                                      \
        size_t size, capacity;                                                          \
        void (*deleter)(type *p);                                                       \
    } Array_##type;                                                                     \
                                                                                        \
    Array_##type create_##type##_array(void (*deleter)(type *)) {                       \
        Array_##type arr = { calloc(SIZE, sizeof(type)), 0, SIZE, deleter };            \
        if(arr.arr)                                                                     \
            return arr;                                                                 \
        else {                                                                          \
            printf("[create_" #type "_array()]: memory allocation error!\n");           \
            exit(1);                                                                    \
        }                                                                               \
    }                                                                                   \
                                                                                        \
    void clear_##type##_array(Array_##type *arr) {                                      \
        if (arr->deleter) {                                                             \
            for (size_t i = 0; i < arr->size; ++i)                                      \
                arr->deleter(&arr->arr[i]);                                             \
        }                                                                               \
        free(arr->arr);                                                                 \
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
            exit(1);                                                                    \
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

Array(char)

typedef struct {
    long value_int;
    Array_char string;
} FileValue;

Array(FileValue)

void add_name_to_path(Array_char *path, char *name) {
    if (path->arr[path->size - 1] != '/')
        add_char_element(path, '/');

    if((strlen(name) + path->size + 1) >= path->capacity)
        resize_char_array(path);

    for(size_t i = 0; i < strlen(name); i++) {
        path->arr[path->size++] = name[i];
    }

    path->arr[path->size] = '\0';
}

void remove_name_from_path(Array_char *path) {
    char *slash_ptr = strrchr(path->arr, '/');
    if(slash_ptr) {
        *slash_ptr = '\0';
        path->size = strlen(path->arr);
    }
}

int compare(const void *a, const void *b) {
    const FileValue *f_v1 = (const FileValue*)a;
    const FileValue *f_v2 = (const FileValue*)b;

    if(f_v1->value_int > f_v2->value_int)
        return 1;
    else if(f_v1->value_int < f_v2->value_int)
        return -1;
    else
        return 0;
}

char* get_file_extension(char* filename) {
    char *period = strrchr(filename, '.');
    if(period && period + 1)
        return period + 1;
    else
        return "";
}

long extract_integer(char *str) {
    char *endptr;
    return strtol(str, &endptr, 10);
}

char read_next_char(Array_char *str, FILE *f) {
    char c = (char)getc(f);
    if(c != EOF && c != '\n') {
        if(str->size + 1 == str->capacity)
            resize_char_array(str);
        str->arr[str->size++] = c;
        str->arr[str->size] = '\0';
        return c;
    }
    else
        return 0;
}

void read_line(Array_char *s, FILE *f) {
    while(read_next_char(s, f));
}

void read_txt(Array_char *path, struct dirent *entity, Array_FileValue *fileValues) {
    add_name_to_path(path, entity->d_name);
    FILE  *f = fopen(path->arr, "r");

    FileValue f_v;
    f_v.string = create_char_array(NULL);
    read_line(&f_v.string, f);
    f_v.value_int = extract_integer(f_v.string.arr);
    add_FileValue_element(fileValues, f_v);

    fclose(f);
    remove_name_from_path(path);
}

void directory_lookup(Array_FileValue *fileValues, Array_char *path) {
    DIR *directory = opendir(path->arr);
    if (!directory)
        return (void)printf("[directory_lookup()]: directory in {%s} is NULL\n", path->arr);

    for(struct dirent *entity = readdir(directory); entity; entity = readdir(directory)) {
        if(entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {

            add_name_to_path(path, entity->d_name);
            directory_lookup(fileValues, path);
            remove_name_from_path(path);

        } else if (entity->d_type == DT_REG && strcmp(get_file_extension(entity->d_name), "txt") == 0) {
            read_txt(path, entity, fileValues);
        }
    }
}

void write_file(Array_FileValue *fileValues) {
    FILE *f = fopen("result.txt", "w");

    for(int i = 0; i < fileValues->size; i++) {
        if(fileValues->arr[i].string.arr)
            fprintf(f, "%s\n", fileValues->arr[i].string.arr);
    }
    fclose(f);
}

void file_value_deleter(FileValue *p) {
    clear_char_array(&p->string);
}

int main() {
    Array_char path = create_char_array(NULL);
    append_char_array(&path, ROOT_PATH, strlen(ROOT_PATH));

    Array_FileValue f_v = create_FileValue_array(file_value_deleter);

    directory_lookup(&f_v, &path);
    qsort(f_v.arr, f_v.size, sizeof(FileValue), compare);
    write_file(&f_v);

    clear_FileValue_array(&f_v);
    clear_char_array(&path);
    return 0;
}

