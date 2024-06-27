#include "stringswork.h"


wchar_t* lower(const wchar_t* str) {
    size_t size = wcslen(str);
    wchar_t* new = malloc(sizeof(wchar_t) * (size + 1));

    if (new == NULL) {
        error(L"Error: недостаточно памяти для уменьшения регистра!");
    }

    for (size_t i = 0; i < size; i++)
        new[i] = towlower(str[i]);
    new[size] = 0x00;

    return new;
}

int compare(const wchar_t* left, const wchar_t* right) {
    wchar_t* left_lower = lower(left);
    wchar_t* right_lower = lower(right);
    int result = wcscmp(left_lower, right_lower);

    free(left_lower);
    free(right_lower);

    return result;
}

bool is_contains(wchar_t symbol, wchar_t* str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (str[i] == symbol) {
            return true;
        }
    }

    return false;
}

wchar_t** realloc_results_buffer(wchar_t** buf, size_t* buf_size) {
    buf = realloc(buf, sizeof(wchar_t*) * (*buf_size + 1));

    if (buf == NULL) error(L"Error: недостаточно памяти для разбивки по словам!");

    *buf_size += 1;
    return buf;
}

wchar_t* make_word_copy(wchar_t* source, size_t len) {
    wchar_t* word = malloc(sizeof(wchar_t) * (len + 1));
    if (word == NULL) {
        error(L"Error: недостаточно памяти для разбивки по словам!");
    }
    wcsncpy(word, source, len);
    word[len] = 0;

    return word;
}

wchar_t** update_results_buffer(wchar_t** buf, size_t* buf_size, wchar_t* word) {
    buf = realloc_results_buffer(buf, buf_size);
    buf[*buf_size-1] = word;
    return buf;
}

#define SPLIT_FILTER L" ,."
#define SPLIT_FILTER_LEN 3
wchar_t** split(wchar_t* str, size_t size) {
    size_t result_size = 0;
    wchar_t** result = NULL;

    size_t last = 0;
    for (size_t i = 0; (i < size) && (str[i] != 0); i++) {
        if (is_contains(str[i], SPLIT_FILTER, SPLIT_FILTER_LEN)) {
            size_t word_len = i - last;
            if (word_len == 0) {
                last = i + 1;
                continue;
            }
            wchar_t* word = make_word_copy(str + last, word_len);
            result = update_results_buffer(result, &result_size, word);
            last = i + 1;
        }
    }

    if (size - last > 0) {
        wchar_t* word = make_word_copy(str + last, size - last);
        result = update_results_buffer(result, &result_size, word);
    }

    result = update_results_buffer(result, &result_size, NULL);
    return result;
}

int compare_words_count(wchar_t* left, wchar_t* right) {
    wchar_t** left_splitted = split(left, wcslen(left));
    wchar_t** right_splitted = split(right, wcslen(right));

    size_t left_words_count = 0;
    size_t right_words_count = 0;
    size_t i = 0;

    while (left_splitted[i] != NULL) {
        free(left_splitted[i]);
        left_words_count++;
        i++;
    }
    free(left_splitted);

    i = 0;
    while (right_splitted[i] != NULL) {
        free(right_splitted[i]);
        right_words_count++;
        i++;
    }
    free(right_splitted);

    return (right_words_count < left_words_count) - (right_words_count > left_words_count);
}

wchar_t* replace(wchar_t* original, wchar_t* pattern, wchar_t* replacement) {
    const size_t replacement_length = wcslen(replacement);
    const size_t pattern_length = wcslen(pattern);
    const size_t original_length = wcslen(original);

    size_t pattern_count = 0;
    wchar_t* original_pointer;
    wchar_t* pattern_loc;

    for (original_pointer = original; (pattern_loc = wcsstr(original_pointer, pattern)) != NULL; original_pointer = pattern_loc + pattern_length) {
        pattern_count++;
    }

    const size_t reslen = original_length + pattern_count * (replacement_length - pattern_length);
    wchar_t* result = malloc(sizeof(wchar_t) * (reslen + 1));
    if (result == NULL) {
        error(L"Error: недостаточно памяти для замены подстроки!");
    }

    wchar_t* retptr = result;
    for (original_pointer = original; (pattern_loc = wcsstr(original_pointer, pattern)) != NULL; original_pointer = pattern_loc + pattern_length) {
        size_t skplen = pattern_loc - original_pointer;

        wcsncpy(retptr, original_pointer, skplen);
        retptr += skplen;

        wcsncpy(retptr, replacement, replacement_length);
        retptr += replacement_length;
    }

    wcscpy(retptr, original_pointer);
    return result;
}

wchar_t* fix_endings(wchar_t* original, size_t* size) {
    wchar_t dle[] = { 0xFFFF, 0x0 };
    wchar_t dle2[] = { 0xFFFE, 0x0 };
    wchar_t* buf =  replace(original, L"тся", dle);
    buf = replace(buf, L"ться", dle2);
    buf = replace(buf, dle, L"ться");
    wchar_t* res = replace(buf, dle2, L"тся");
    free(original); free(buf);
    
    (*size) = wcslen(res);
    return res;
}

wchar_t* find_and_print(wchar_t* original, wchar_t* pattern, size_t* size) {
    wchar_t* green_start = malloc(sizeof(wchar_t) * 5);
    wchar_t* green_end   = malloc(sizeof(wchar_t) * 4);
    wcsncpy(green_start, L"\033[32m", 5);
    wcsncpy(green_end, L"\033[0m", 4);

    size_t pattern_length = wcslen(pattern);
    wchar_t* print_pattern = malloc(sizeof(wchar_t) * (pattern_length + 10));
    wcsncpy(print_pattern, green_start, 5);
    wcsncpy(print_pattern+5, pattern, pattern_length);
    wcsncpy(print_pattern+5+pattern_length, green_end, 4);
    print_pattern[pattern_length + 9] = 0;

    wchar_t* res = replace(original, pattern, print_pattern);
    free(original);
    
    (*size) = wcslen(res);
    return res;
}

bool longer_than_ten(wchar_t* str, size_t size) {
    wchar_t** splitted = split(str, wcslen(str));
    size_t words_count = 0;
    size_t i = 0;
    while (splitted[i] != NULL) {
        free(splitted[i]);
        words_count++;
        i++;
    }
    free(splitted);

    return (words_count <= 10);
}

