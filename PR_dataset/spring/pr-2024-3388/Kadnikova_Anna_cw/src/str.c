#include "str.h"


string* create_empty() {
    string* str = malloc(sizeof(string));

    str->size = 0;
    str->capacity = 1;
    str->data = malloc(1 * sizeof(char));
    memset(str->data, sizeof(char), 0x00);

    return str;
}


string* resize(string* str) {
    str->data = realloc(str->data, (str->capacity * 2) * sizeof(char));
    memset(str->data + str->capacity * sizeof(char), str->capacity * sizeof(char), 0x00);
    str->capacity *= 2;

    return str;
}


string* push(string* str, const char symbol) {
    if (str->size + 1 >= str->capacity)
        str = resize(str);
    
    str->data[str->size] = symbol;
    str->size += 1;

    return str;
}


string* str_from_char(const char symbol) {
    string* str = create_empty();
    if (symbol == 0x00) return str;

    str = push(str, symbol);
    return str;
}


string* str_from_buffer(const char* buffer) {
    string* str = create_empty();
    if (buffer == NULL) return str;

    for (size_t i = 0; i < strlen(buffer); i++)
        str = push(str, buffer[i]);
    return str;
}


string* copy(string* original) {
    string* new = create_empty();
    for (size_t i = 0; i < original->size; i++)
        new = push(new, original->data[i]);
    return new;
}


string* slice(string* input, size_t start, size_t end) {
    string* str = create_empty();
    for (size_t i = MAX(0, start); i < MIN(input->size, end); i++)
        str = push(str, input->data[i]);
    return str;
}


/* Using Knuth–Morris–Pratt algorithm */
#define NOT_FOUND (size_t) -1
size_t find(string* haystack, string* needle, size_t start) {
    size_t haystack_len = haystack->size;
    size_t needle_len = needle->size;
    if ((start >= haystack_len) || (needle_len == 0)) return NOT_FOUND;

    int lps[needle_len];
    int j = 0;
    compute_lps(needle, lps);

    int i = start;
    while (i < haystack_len) {
        if (haystack->data[i] == needle->data[j]) {
            i++;
            j++;
        }
        if (j == needle_len)
            return i - j;
        else if (i < haystack_len && haystack->data[i] != needle->data[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return NOT_FOUND;
}


void compute_lps(string* needle, int lps[]) {
    int length = 0;
    lps[0] = 0;
    int i = 1;
    while (i < needle->size) {
        if (needle->data[i] == needle->data[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) length = lps[length - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}


string** split(string* str, string* delimeter, size_t* output_size) {
    size_t result_size = 1;
    string** result = malloc(1 * sizeof(string*));
    result[0] = str;

    for (size_t split_pos = find(result[result_size-1], delimeter, 0);
         split_pos != NOT_FOUND;
         split_pos = find(result[result_size-1], delimeter, 0)) {
            if (split_pos == 0)
                result[result_size - 1] = slice(result[result_size - 1], 1, -1);
            else {
                result = realloc(result, (result_size + 1) * sizeof(string*));
                string* result_last_copy = copy(result[result_size - 1]);
                result[result_size - 1] = slice(result_last_copy, 0, split_pos);
                string* remainder = slice(result_last_copy, split_pos + 1, -1);
                if (remainder->size > 0) {
                    result[result_size] = remainder;
                    result_size += 1;
                }
            }
    }

    *output_size = result_size;
    return result;
}


bool equal(string* left, string* right) {
    if (left->size != right->size) return false;

    for (size_t i = 0; i < left->size; i++) {
        if (left->data[i] != right->data[i])
            return false;
    }

    return true;
}


bool startswith(string* str, string* prefix) {
    return find(str, prefix, 0) == 0;
}


bool is_num(string* str) {
    if (str->size == 0) return false;
    bool negative = ((str->data[0] == '-') ? true : false);

    for (size_t i = ((negative) ? 1 : 0); i < str->size; i++) {
        if (!(('9' >= str->data[i]) && (str->data[i] >= '0'))) 
            return false;
    }

    return ((negative) ? str->size > 1 : true);
}


int64_t stoi(string* str) {
    int64_t result = 0;
    bool negative = ((str->data[0] == '-') ? true : false);

    for (size_t i = ((negative) ? 1 : 0); i < str->size; i++)
        result = result * 10 + (int64_t)(str->data[i] - '0');

    return ((negative) ? -result : result);
}
