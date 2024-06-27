#include "text.h"
int cmp(const void* first_str,const void* second_str){
    str_t *first = (str_t*)first_str;
    str_t *second = (str_t*)second_str;

    if (word_count(*first,strlen(*first)) == word_count(*second,strlen(*second))){
            return strlen(*first) > strlen(*second);
        }
    if (word_count(*first,strlen(*first)) < word_count(*second,strlen(*second))){
        return -1;
    }
    else{
        
        return 1;
    }
}
text_t sort_text(text_t text,size_t size_text){
    qsort(text,size_text,sizeof(str_t),cmp);
    return text;

}
text_t init_text(size_t capacity, size_t** str_sizes) {
    text_t pointer = malloc(sizeof(str_t) * capacity);
    memset(pointer, 0x00, sizeof(str_t) * capacity);

    size_t* sizes = malloc(sizeof(size_t) * capacity);
    memset(sizes, 0x00, sizeof(size_t) * capacity);

    *str_sizes = sizes;
    return pointer;
}

text_t realloc_text(text_t text, size_t* capacity, size_t** str_sizes) {
    size_t new_capacity = *capacity + READ_WINDOW;
    str_t* new_buffer = realloc(text, sizeof(str_t*) * new_capacity);
    memset(new_buffer + *capacity, 0x00, sizeof(str_t*) * READ_WINDOW);

    size_t* sizes = realloc(*str_sizes, sizeof(size_t) * new_capacity);
    memset(sizes + *capacity, 0x00, sizeof(size_t) * READ_WINDOW);

    *capacity = new_capacity;
    *str_sizes = sizes;
    return new_buffer;
}

text_t add_to_text(text_t text, str_t str, size_t str_size, size_t** str_sizes, size_t* size, size_t* capacity) {
    text_t buffer = text;
    if (*capacity <= *size)
        buffer = realloc_text(buffer, capacity, str_sizes);
        
    buffer[*size] = str;
    (*str_sizes)[*size] = str_size;
    *size += 1;

    return buffer;
}

text_t read_text(size_t* size, size_t** str_sizes) {
    size_t return_size = 0;
    size_t return_capacity = START_CAPACITY;
    text_t return_buffer = init_text(return_capacity, str_sizes);

    size_t str_size = 0;
    str_t str = read_sentence(&str_size);
    while (str != NULL) {
        return_buffer = add_to_text(return_buffer, str, str_size, str_sizes, &return_size, &return_capacity);
        str = read_sentence(&str_size);
    }

    *size = return_size;
    return return_buffer;
}

text_t defragmentate(text_t text, size_t* size, size_t** str_sizes) {
    for (size_t i = 0; i < *size; i++) {
        const str_t current = text[i];
        if (current != NULL) continue;

        for (size_t j = i+1; j < *size; j++) {
            text[i] = text[j];
            (*str_sizes)[i] = (*str_sizes)[j];
            text[j] = NULL;
            (*str_sizes)[j] = 0;
        }
    }
    
    size_t return_size = 0;
    while ((text[return_size] != NULL) && return_size < *size) {
        return_size++;
    }

    *size = return_size;
    return text;
}

text_t unique(text_t text, size_t* size, size_t** str_sizes) {
    for (size_t i = 0; i < *size; i++) {
        str_t left = text[i];
        if (left == NULL) continue;
        for (size_t j = i+1; j < *size; j++) {
            str_t right = text[j];
            if ((right != NULL) && ((*str_sizes)[i] == (*str_sizes)[j]) && (strcasecmp(left, right) == 0)) {
                free(right);
                text[j] = NULL;
                (*str_sizes)[j] = 0;
            }
        }
    }

    return defragmentate(text, size, str_sizes);
}

text_t replace_dates(text_t text, size_t* size, size_t** str_sizes) {
    const str_t months[12] = {"Jan", "Feb", "Mar", "Apr",
                              "May", "Jun", "Jul", "Aug",
                              "Sep", "Oct", "Nov", "Dec"};
    str_t hours_to_end = convert_to_string(get_hours_to_end_of_year());

    for (size_t i = 0; i < *size; i++) {
        str_t current_str = text[i];
        size_t offset = 0;
        size_t year_length = 0;
        size_t year_pos = find_year(current_str, (*str_sizes)[i], &year_length);
        while (year_pos != -1) {
            str_t date_candidate = slice(current_str + offset, (*str_sizes)[i] - offset, year_pos, year_length+7);

            if ((date_candidate != NULL) && (strlen(date_candidate) == year_length+7)) {
                struct tm date;
                str_t convert_result = strptime(date_candidate, "%Y %b %d", &date);
                if (convert_result != NULL) {
                    current_str = replace(current_str, date_candidate, hours_to_end, &(*str_sizes)[i]);
                    offset += strlen(hours_to_end);
                } else {
                    offset += year_length+7;
                }
            } else if (date_candidate != NULL)
                offset += strlen(date_candidate);
            else break;

            free(date_candidate);
            year_pos = find_year(current_str + offset, (*str_sizes)[i] - offset, &year_length);
        }
        text[i] = current_str;
    }
    
    return text;
}

text_t color_words(text_t text, size_t* size, size_t** str_sizes) {
    str_t green_start = "\033[32m";
    str_t red_start = "\033[31m";
    str_t color_end = "\033[0m";

    for (size_t i = 0; i < *size; i++) {
        str_t current_str = text[i];
        size_t split_size = 0;
        str_t* words = split(current_str, (*str_sizes)[i], &split_size);
        for (size_t j = 0; j < split_size; j++) {
            if (is_contains(words[j][0], SPLIT_FILTER, SPLIT_FILTER_LEN)) continue;
            
            size_t word_len = strlen(words[j]);
            str_t new_word = init_string(word_len+9);
            str_t color_start = (((j / 2) % 2 == 0) ? red_start : green_start);
            
            strncpy(new_word, color_start, 5);
            strncpy(new_word + 5, words[j], word_len);
            strncpy(new_word + word_len + 5, color_end, 4);

            free(words[j]);
            words[j] = new_word;
        }

        free(text[i]);
        text[i] = join(words, split_size, &(*str_sizes)[i]);
    }
    
    return text;
}

text_t delete_with_same_begin_end(text_t text, size_t* size, size_t** str_sizes) {
    for (size_t i = 0; i < *size; i++) {
        str_t current_str = text[i];
        size_t split_size = 0;
        str_t* words = split(current_str, (*str_sizes)[i], &split_size);
        if (split_size >= 4) {
            if (strcmp(words[0], words[split_size-2]) == 0) {
                free(text[i]);
                text[i] = NULL;
                (*str_sizes)[i] = 0;
            }
        }
        free(words);
    }
    
    return defragmentate(text, size, str_sizes);
}

int first_word_code_sum_comparator(const void* left, const void* right) {
    str_t left_str  = *(str_t *)left;
    str_t right_str = *(str_t *)right;

    size_t left_split_size, right_split_size;
    str_t* left_split  = split(left_str, strlen(left_str), &left_split_size);
    str_t* right_split = split(right_str, strlen(right_str), &right_split_size);

    size_t left_sum  = sum_ord(left_split[0], strlen(left_split[0]));
    size_t right_sum = sum_ord(right_split[0], strlen(right_split[0]));

    return (left_sum > right_sum) - (left_sum < right_sum);
}

text_t update_sizes(text_t text, size_t* size, size_t** str_sizes) {
    for (size_t i = 0; i < *size; i++) {
        str_t current_str = text[i];
        (*str_sizes)[i] = strlen(current_str);
    }

    return text;
}

text_t sort_by_codes(text_t text, size_t* size, size_t** str_sizes) {
    qsort(text, *size, sizeof(str_t), first_word_code_sum_comparator);
    return update_sizes(text, size, str_sizes);
}

