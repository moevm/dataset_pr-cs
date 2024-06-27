#include "processing.h"


wchar_t* wcslow(const wchar_t* str) {
    size_t size = wcslen(str);
    wchar_t* new = malloc(sizeof(wchar_t) * (size + 1));
    if (new == NULL) panic(L"Error: not enough memory to lower wide string!");

    for (size_t i = 0; i < size; i++)
        new[i] = towlower(str[i]);
    new[size] = 0x00;
    return new;
}

int wcsincmp(const wchar_t* left, const wchar_t* right) {
    wchar_t* left_lower = wcslow(left);
    wchar_t* right_lower = wcslow(right);
    int result = wcscmp(left_lower, right_lower);
    free(left_lower);
    free(right_lower);
    return result;
}

size_t calc_cyrillic(const wchar_t* str) {
    if (str == NULL) return 0;
    
    size_t size = wcslen(str);
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        wchar_t current_char = towlower(str[i]);
        if ((current_char >= L'а') && (current_char <= L'я')) count++;
    }
    return count;
}

int calc_cyrillic_diff(const wchar_t* left, const wchar_t* right) {
    size_t count_left = calc_cyrillic(left);
    size_t count_right = calc_cyrillic(right);
    
    return (count_left < count_right) - (count_left > count_right);
}

TimeStamp get_current_time() {
    time_t getted_timestamp = time(NULL);
    struct tm* now_time = localtime(&getted_timestamp);
    
    TimeStamp return_struct;
    return_struct.hours = now_time->tm_hour;
    return_struct.minutes = now_time->tm_min;

    return return_struct;
}

bool is_zeros(wchar_t* str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (str[i] != L'0') return false;
    }
    return true;
}

bool check_is_time(wchar_t* str) {
    long hours = wcstoull(str, NULL, 10);
    long minutes = wcstoull(str+3, NULL, 10);
    if ((str[2] == L':') &&
        (((0 < hours) && (hours <= HOURS_MAX) && !is_zeros(str, 2)) ||
         ((hours == 0) && is_zeros(str, 2))) &&
        (((0 < minutes) && (minutes <= MINUTES_MAX) && !is_zeros(str+3, 2)) ||
         ((minutes == 0) && is_zeros(str+3, 2))))
            return true;
    return false;
}

TimeStamp* realloc_search_results(TimeStamp* buf, size_t* buf_size) {
    if (*buf_size == 0) {
        buf = malloc(sizeof(TimeStamp));
        if (buf == NULL) panic(L"Error: can`t allocate memory for search results!");
    } else {
        buf = realloc(buf, sizeof(TimeStamp)*(*buf_size+1));
        if (buf == NULL) panic(L"Error: can`t allocate more memory for search results!");
    }

    (*buf_size) += 1;
    return buf;
}

void* find_times(wchar_t* str, size_t size) {
    size_t buf_size = 0;
    TimeStamp* result = NULL;

    if (wcslen(str) < TIMESTAMP_MIN_STR_LEN)
        return result;
        
    for (size_t i = 0; i < size-5; i++) {
        if (check_is_time(str+i)) {
            long hours = wcstoull(str+i, NULL, 10);
            long minutes = wcstoull(str+i+3, NULL, 10);

            result = realloc_search_results(result, &buf_size);
            result[buf_size-1].hours   = hours;
            result[buf_size-1].minutes = minutes;
        }
    }

    if (buf_size > 0) {
        result = realloc_search_results(result, &buf_size);
        result[buf_size-1].hours   = END_OF_RESULTS;
        result[buf_size-1].minutes = END_OF_RESULTS;
    }

    return (void*)result;
};

void print_times(void* times, size_t line_number) {
    const TimeStamp* results = (TimeStamp*)times;
    TimeStamp current_time = get_current_time();

    size_t index = 0;
    while (true) {
        long hours   = results[index].hours;
        long minutes = results[index].minutes;

        if ((hours == END_OF_RESULTS) && (minutes == END_OF_RESULTS)) break;
        wprintf(L"%lu %ld\n", line_number, labs(hours - current_time.hours) * 60 + labs(minutes - current_time.minutes));

        index++;
    }
};

wchar_t* delete_big_latin(wchar_t* str, size_t* size) {
    bool* mask = malloc(sizeof(bool) * (*size));
    memset(mask, 0x1, sizeof(bool) * (*size));

    size_t new_size = *size;
    for (size_t i = 0; i < *size; i++) {
        wchar_t current_char = str[i];
        if ((L'A' <= current_char) && (current_char <= L'Z')) {
            mask[i] = 0;
            new_size -= 1;
        }
    }

    wchar_t* new_ptr = malloc(sizeof(wchar_t) * new_size + 1);
    size_t j = 0;
    for (size_t i = 0; i < *size; i++) {
        if (mask[i]) {
            new_ptr[j] = str[i];
            j += 1;
        }
    }

    new_ptr[j] = 0;
    *size = new_size;
    free(str);

    return new_ptr;
}

bool is_contains(wchar_t c, wchar_t* str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (str[i] == c) return true;
    }
    return false;
}

bool have_spec_symbols(wchar_t* str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (is_contains(str[i], SPEC_FILTER, SPEC_FILTER_SIZE)) return true;
    }
    return false;
}

wchar_t* make_copy(wchar_t* str, size_t size) {
    wchar_t* copy_buf = malloc(sizeof(wchar_t) * (size+1));
    if (copy_buf == NULL) panic(L"Error: can`t allocate memory when copying words!");

    wcsncpy(copy_buf, str, size+1);
    copy_buf[size] = L'\0';

    return copy_buf;
}

wchar_t* make_joinable(wchar_t* str, size_t size) {
    size_t last_char_pos = size-1;
    if (str[last_char_pos-1] == L'.')
        last_char_pos -= 1;

    str[last_char_pos] = L' ';
    str[last_char_pos+1] = L'\0';

    return str;
}

wchar_t* update_copy_buffer(wchar_t* buf, size_t* buf_size, wchar_t* word_to_add, size_t word_size) {
    buf = realloc(buf, sizeof(wchar_t)*(*buf_size + 2*(word_size+1)));
    if (buf == NULL) panic(L"Error: can`t allocate memory when copying words!");

    word_to_add = make_copy(word_to_add, word_size);
    word_to_add = make_joinable(word_to_add, word_size);

    wcscpy(buf+(*buf_size), word_to_add);
    wcscpy(buf+(*buf_size)+word_size+1, word_to_add);

    free(word_to_add);
    (*buf_size) += 2*(word_size+1);
    return buf;
}

wchar_t* copy_words(wchar_t* str, size_t* size) {
    size_t new_size = 0;
    wchar_t* result = NULL;

    wchar_t* str_buf = make_copy(str, *size);
    wchar_t* internal_state = NULL;
    for (wchar_t* word = wcstok(str_buf, L" ", &internal_state); word != NULL; word = wcstok(NULL, L" ", &internal_state))
        result = update_copy_buffer(result, &new_size, word, wcslen(word) + 1);

    result[new_size-3] = L'.';
    result[new_size-2] = L'\0';

    free(str_buf);
    free(str);
    *size = new_size;
    return result;
}