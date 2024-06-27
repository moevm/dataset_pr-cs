#include <iostream>
#include <cstring>

#define BASE_CAPACITY 8

class CustomStack {
private:
    size_t length;
    size_t capacity;

protected:
    char** mData;

public:
    CustomStack() : length(0), capacity(0), mData(nullptr) {}

    ~CustomStack() {
        for (size_t i = 0; i < this->length; i++) {
            free(this->mData[i]);
        }
        free(this->mData);
    }

    void push(const char *str)
    {
        this->extend(1);
        this->mData[this->length - 1] = strdup(str);
    }

    void pop()
    {
        if (this->length == 0) {
            return;
        }
        this->shrink(1);
    }

    char *top()
    {
        if (this->length == 0) {
            return nullptr;
        }
        return this->mData[this->length - 1];
    }

    size_t size()
    {
        return this->length;
    }

    bool empty()
    {
        return this->length == 0;
    }

    void extend(size_t n)
    {
        this->length += n;

        if (this->length > this->capacity) {
            if (this->capacity == 0)
                this->capacity = BASE_CAPACITY;
            
            while (this->length > this->capacity)
                this->capacity *= 2;
            
            this->mData = (char**)realloc(this->mData, sizeof(char*) * this->capacity);
        }
    }

    void shrink(size_t n)
    {
        n = (n > this->length) ? this->length : n;
        this->length -= n;
        
        for (size_t i = 0; i < n; i++) {
            free(this->mData[this->length + i]);
        }

        if (this->length == 0) {
            this->capacity = 0;
            free(this->mData);
            this->mData = nullptr;
            return;
        }

        if (this->capacity / this->length >= 2) {
            while (this->capacity / this->length >= 2)
                this->capacity /= 2;

            this->mData = (char**)realloc(this->mData, sizeof(char*) * this->capacity);
        }
    }
};

bool does_require_closing_tag(const char *str)
{
    return strcmp(str, "br") != 0 && strcmp(str, "hr") != 0;
}

bool is_valid_html(char *str)
{
    CustomStack stack;

    char *ptr = str;
    while (*ptr != '\0') {
        if (*ptr == '<') {
            bool is_closing_tag = false;
            if (ptr[1] == '/') {
                ptr++;
                is_closing_tag = true;
            }

            char *begin = ptr + 1;
            char *end = strchr(begin, '>');

            if (end == nullptr)
                return false;
            
            ptr = end;
            
            size_t tag_len = end - begin;
            char *tag = (char*)malloc(sizeof(char) * (tag_len + 1));
            memcpy(tag, begin, tag_len);
            tag[tag_len] = '\0';

            if (is_closing_tag) {
                if (stack.empty() || (strcmp(stack.top(), tag) != 0)) {
                    free(tag);
                    return false;
                }
                
                stack.pop();
            }
            else if (does_require_closing_tag(tag)) {
                stack.push(tag);
            }

            free(tag);
        }
        ptr++;
    }

    return stack.empty();
}

int main()
{
    char *str = nullptr;
    size_t size = 0;

    getline(&str, &size, stdin);
    str[size - 1] = '\0';
    size--;

    if (is_valid_html(str))
        std::cout << "correct" << std::endl;
    else
        std::cout << "wrong" << std::endl;

    free(str);
    return 0;
}
