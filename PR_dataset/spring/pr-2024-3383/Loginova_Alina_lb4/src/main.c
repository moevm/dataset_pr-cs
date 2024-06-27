#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include "string"

#define SIZE 2
#define Array(type)                                                                     \
    typedef struct array_##type {                                                       \
        type *arr;                                                                      \
        size_t size, capacity;                                                          \
        void (*deleter)(type *p);                                                       \
    } Array_##type;                                                                     \
                                                                                        \
    Array_##type create_##type##_array(void (*deleter)(type *)) {                       \
        Array_##type arr = { static_cast<type*>(calloc(SIZE, sizeof(type))), 0, SIZE, deleter };            \
        if(arr.arr)                                                                     \
            return arr;                                                                 \
        else {                                                                          \
            printf("[create_" #type "_array()]: memory allocation error!\n");           \
            exit(1);                                                                    \
        }                                                                               \
    }                                                                                   \
                                                                                        \
    void delete_##type##_array(Array_##type *arr) {                                      \
        if (arr->deleter) {                                                             \
            for (size_t i = 0; i < arr->size; ++i)                                      \
                arr->deleter(&arr->arr[i]);                                             \
        }                                                                               \
        free(arr->arr);                                                                 \
    }                                                                                   \
                                                                                        \
    void clear_##type##_array(Array_##type *arr) {                                      \
        if (arr->deleter) {                                                             \
            for (size_t i = 0; i < arr->size; ++i)                                      \
                arr->deleter(&arr->arr[i]);                                             \
        }                                                                               \
        arr->size = 0;                                                                 \
    }                                                                                   \
    \
    void resize_##type##_array(Array_##type *arr){                                      \
        arr->capacity *= 2;                                                             \
        type *temp = static_cast<type*>(realloc(arr->arr, arr->capacity * sizeof(type)));                   \
        if(temp)                                                                        \
            arr->arr = temp;                                                            \
        else {                                                                          \
            printf("[resize_" #type "_array()]: memory allocation error!\n");           \
            delete_##type##_array(arr);                                                  \
            exit(1);                                                                    \
        }                                                                               \
    }                                                                                   \
    \


Array(char)
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

class CustomStack {

public:

    CustomStack() {
    }

    ~CustomStack() {
        free(mData);
    }

    void push(int obj) {
        if(stack_capacity == 0)
            mData = static_cast<int*>(malloc(++stack_capacity * sizeof(int)));
        else if (stack_size == stack_capacity){
            resize();
        }
        mData[stack_size++] = obj;
        std::cout << "ok\n";
    }

    void pop() {
        if(stack_size == 0) {
            std::cout << "error";
            exit(0);
        }
        std::cout << mData[--stack_size] << '\n';
    }

    size_t size() {
        std::cout << stack_size << '\n';
        return stack_size;
    }

    bool empty() {
        return stack_size == 0;
    }

    int top() {
        if(stack_size == 0) {
            std::cout << "error";
            exit(0);
        }
        std::cout << mData[stack_size - 1] << '\n';
        return mData[stack_size - 1];
    }

    void extend(int n) {
        if(n > 0)
            mData = static_cast<int*>(realloc(mData, (stack_capacity + n) * sizeof(int)));
    }

private:
    size_t stack_size = 0, stack_capacity = 0;

    void resize() {
        extend(stack_capacity);
    }

protected:  // в этом блоке должен быть указатель на массив данных

    int* mData = nullptr;
};


const char cmd_push[] = "cmd_push";
const char cmd_pop[] = "cmd_pop";
const char cmd_top[] = "cmd_top";
const char cmd_size[] = "cmd_size";
const char cmd_exit[] = "cmd_exit";

int main() {
    CustomStack s;

    Array_char cmd = create_char_array(NULL);
    long n;
    char *endptr;
    while(true) {
        clear_char_array(&cmd);
        read_line(&cmd, stdin);

        if(strncmp(cmd.arr, cmd_push, sizeof(cmd_push) - 1) == 0) {
            n = std::strtol(&cmd.arr[sizeof(cmd_push) - 1], &endptr, 10);
            s.push(n);
        }

        else if(strcmp(cmd.arr, cmd_top) == 0)
            s.top();
        else if(strcmp(cmd.arr, cmd_pop) == 0)
            s.pop();
        else if(strcmp(cmd.arr, cmd_size) == 0)
            s.size();
        else if(strcmp(cmd.arr, cmd_exit) == 0) {
            std::cout << "bye";
            exit(0);
        }
    }
}
