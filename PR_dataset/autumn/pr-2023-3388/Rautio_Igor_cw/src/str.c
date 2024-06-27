#include "str.h"

size_t word_count(str_t str,size_t size){
    size_t count  = 0;
    for (size_t i = 0;i < (size - 1); i ++){
        if (isspace(str[i]) && (!isspace(str[i+1]))){
            count ++;

        }
    }
    if (!isspace(str[0])){
            count += 1;
        }
        return count;
}
str_t init_string(size_t capacity) {
    str_t pointer = malloc(sizeof(char) * (capacity + 1));
    memset(pointer, 0x00, sizeof(char) * (capacity + 1));
    return pointer;
}

str_t realloc_string(str_t str, size_t* capacity) {
    size_t new_capacity = *capacity + READ_WINDOW;
    str_t new_buffer = realloc(str, sizeof(char) * (new_capacity + 1));
    memset(new_buffer + *capacity + 1, 0x00, sizeof(char) * READ_WINDOW);

    *capacity = new_capacity;
    return new_buffer;
}

str_t add_to_string(str_t str, char symbol, size_t* size, size_t* capacity) {
    str_t buffer = str;
    if (*capacity <= *size)
        buffer = realloc_string(buffer, capacity);
        
    buffer[*size] = symbol;
    *size += 1;

    return buffer;
}

str_t convert_to_string(unsigned int num) {
    size_t return_size = 0;
    size_t return_capacity = START_CAPACITY;
    str_t return_buffer = init_string(return_capacity);
    
    while (num > 0) {
        unsigned int digit = num % 10;
        char symbol = (char)digit + '0';
        return_buffer = add_to_string(return_buffer, symbol, &return_size, &return_capacity);
        num /= 10;
    }

    return return_buffer;
}

str_t read_sentence(size_t* size) {
    size_t return_size = 0;
    size_t return_capacity = START_CAPACITY;
    str_t return_buffer = init_string(return_capacity);

    char input; get(&input);

    if ((input == '\n') && (get(&input) == '\n')) {
        free(return_buffer);
        return NULL;
    }
    if (input == EOF) panic("Error: unexpected end of input stream! Check correctness of last sentence.");

    while (input != '.') {
        if (return_size == 0 && ((input == ',') || (input == ' '))) {
            get(&input);
            continue;
        }

        if (input == '\n') panic("Error: unexpected end of line! Check correctness of sentences.");
        if ((input == EOF) || (input == '\0')) panic("Error: unexpected end of input stream! Check correctness of last sentence.");

        return_buffer = add_to_string(return_buffer, input, &return_size, &return_capacity);
        get(&input);
    }
    return_buffer = add_to_string(return_buffer, '.', &return_size, &return_capacity);

    *size = return_size;
    return return_buffer;
}

str_t replace(str_t original, str_t pattern, str_t replacement, size_t* size) {
    const size_t original_size = strlen(original);
    const size_t pattern_size = strlen(pattern);
    const size_t replace_size = strlen(replacement);

    size_t pattern_count = 0;
    str_t original_pointer;
    str_t pattern_location;

    for (original_pointer = original; (pattern_location = strstr(original_pointer, pattern)) != NULL; original_pointer = pattern_location + pattern_size)
        pattern_count++;

    const size_t return_size = original_size + pattern_count * (replace_size - pattern_size);
    str_t return_buffer = init_string(return_size);

    str_t return_pointer = return_buffer;
    for (original_pointer = original; (pattern_location = strstr(original_pointer, pattern)) != NULL; original_pointer = pattern_location + pattern_size) {
        size_t skip_size = pattern_location - original_pointer;

        strncpy(return_pointer, original_pointer, skip_size);
        return_pointer += skip_size;

        strncpy(return_pointer, replacement, replace_size);
        return_pointer += replace_size;
    }
    strcpy(return_pointer, original_pointer);
    
    free(original);
    *size = return_size;
    return return_buffer;
}

int is_contains(char symbol, str_t str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (str[i] == symbol) return 1;
    }
    return 0;
}

str_t slice(str_t str, size_t size, size_t start, size_t len) {
    if ((size == 0) || (start >= size) || (str == NULL)) return NULL;

    const size_t return_size = MIN(len, size - start + 1);
    str_t return_buffer = init_string(return_size);

    for (size_t i = 0; i < return_size; i++)
        return_buffer[i] = str[start + i];
    
    return return_buffer;
}

size_t get_return_size(str_t str, size_t size){
    str_t str_pointer = str;
    str_t last_delimiter = str_pointer;
    size_t return_size = 0;
    if (size < 2) return_size = 1;
    else {
        while (*str_pointer) {
            if (is_contains(*str_pointer, SPLIT_FILTER, SPLIT_FILTER_LEN)) {
                return_size += ((str_pointer - last_delimiter == 1) ? 1 : 2);
                last_delimiter = str_pointer;
            }
            str_pointer++;
        }
        return_size += last_delimiter < (str + strlen(str) - 1);
    }
    return return_size;
}

str_t* split(str_t str, size_t size, size_t* return_buffer_size) {
    size_t return_size = get_return_size(str, size);
    str_t* return_buffer = malloc(sizeof(char*) * (return_size + 1));
    memset(return_buffer, 0x00, sizeof(char*) * (return_size + 1));

    size_t i = 0, pointer_size = size;
    str_t str_pointer = str;
    for (size_t word_len = strcspn(str_pointer, SPLIT_FILTER); str_pointer != (str + size); word_len = strcspn(str_pointer, SPLIT_FILTER)) {
        if (word_len > 0) {
            return_buffer[i] = slice(str_pointer, pointer_size, 0, word_len);
            return_buffer[i+1] = init_string(1);
            return_buffer[i+1][0] = str_pointer[word_len];
            i += 2;
        } else {
            return_buffer[i] = init_string(1);
            return_buffer[i][0] = str_pointer[word_len];
            i += 1;
        }
        str_pointer += (word_len + 1);
        pointer_size -= (word_len + 1);
    }
    *return_buffer_size = return_size;
    return return_buffer;
}


str_t join(str_t* strings, size_t size, size_t* return_buffer_size) {
    size_t* strings_sizes = malloc(sizeof(size_t) * size);
    for (size_t i = 0; i < size; i++)
        strings_sizes[i] = strlen(strings[i]);
    
    const size_t return_size = calc_sum(strings_sizes, size);
    str_t return_buffer = init_string(return_size);

    for (size_t i = 0; i < size; i++) {
        const size_t offset = calc_sum(strings_sizes, i);
        for (size_t j = 0; j < strings_sizes[i]; j++)
            return_buffer[offset + j] = strings[i][j];
    }

    free(strings_sizes);
    free(strings);
    *return_buffer_size = return_size;
    return return_buffer;
}

size_t sum_ord(str_t str, size_t size) {
    size_t sum = 0;
    for (size_t i = 0; i < size; i++)
        sum += (unsigned char)str[i];
    return sum;
}

size_t find_year(str_t str, size_t size, size_t* year_length) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 4; j > 0; j--) {
            if (size - i >= j) {
                str_t part = slice(str, size, i, j);
                long long return_buffer = strtoll(part, NULL, 10);
                if ((return_buffer > 0) && !is_contains(' ', part, strlen(part))) {
                    *year_length = j;
                    free(part);
                    return i;
                }
                free(part);
            }
        }
    }

    return -1;
}

