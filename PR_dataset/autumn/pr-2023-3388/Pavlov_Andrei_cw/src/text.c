#include "text.h"



Text* reallocate_text(Text* text) {
    size_t new_cap = text->capacity + text->fib_last;

    Sentence** new_data = realloc(text->data, sizeof(Sentence*) * new_cap);
    if (new_data == NULL) panic(L"Error: can`t allocate more memory for Text data!");

    for (size_t i = text->capacity; i < new_cap; i++)
        new_data[i] = NULL;
    text->data = new_data;

    text->fib_last = text->capacity;
    if (text->capacity == 0) text->fib_last = 1;
    text->capacity = new_cap;

    return text;
}

Text* init_text() {
    Text* text = malloc(sizeof(Text));
    if (text == NULL) panic(L"Error: can`t allocate memory for new Text instance!");

    text->data = NULL;
    text->capacity = 0;
    text->size = 0;
    text->fib_last = 1;

    return text;
}

Text* free_text(Text* text) {
    for (size_t i = 0; i < text->capacity; i++) {
        if (text->data[i] != NULL)
            free_sentence(text->data[i]);
    }
    free(text->data);
    text->data = NULL;
    text->capacity = 0;
    text->size = 0;
    text->fib_last = 1;
    return text;
}

Text* add(Text* text, Sentence* sent) {
    if (text->capacity <= text->size) reallocate_text(text);
    
    text->data[text->size] = sent;
    text->size += 1;

    return text;
}

Text* read_text() {
    Text* text = init_text();
    Sentence* sent = read_sentence();
    
    while (sent != NULL) {
        add(text, sent);
        sent = read_sentence();
    }
    
    return text;
}

Text* optimize(Text* text) {
    for (size_t i = 0; i < text->size; i++) {
        const Sentence* current_sentence = text->data[i];
        if (current_sentence != NULL) continue;
        for (size_t j = i+1; j < text->size; j++) {
            if (text->data[j] != NULL) {
                text->data[i] = text->data[j];
                text->data[j] = NULL;
                break;
            }
        }
    }

    size_t last_nonzero_index = 0;
    while ((text->data[last_nonzero_index] != NULL) && last_nonzero_index < text->capacity) last_nonzero_index++;
    text->size = last_nonzero_index;

    return text;
}

Text* save_only_unique(Text* text, int (*comp)(const wchar_t *, const wchar_t *)) {
    for (size_t i = 0; i < text->size; i++) {
        Sentence* left = text->data[i];
        if (left == NULL) continue;
        for (size_t j = i+1; j < text->size; j++) {
            Sentence* right = text->data[j];
            if ((right != NULL) && (left->size == right->size) && (comp(left->data, right->data) == 0)) {
                free_sentence(right);
                text->data[j] = NULL;
            }
        }
    }

    return optimize(text);
}

void find_and_print(Text* text, void* (*finder)(wchar_t *, size_t), void (*printer)(void *, size_t)) {
    for (size_t i = 0; i < text->size; i++) {
        void* search_results = finder(text->data[i]->data, text->data[i]->size);
        if (search_results != NULL) {
            printer(search_results, i+1);
            free(search_results);
        }
    }
}

Text* apply(Text* text, wchar_t * (*func)(wchar_t *, size_t*)) {
    for (size_t i = 0; i < text->size; i++) {
        Sentence* current = text->data[i];
        current->data = func(current->data, &(current->size));
        current->capacity = current->size+1;
    }

    return text;
}

Text* sort(Text* text, int (*comp)(const wchar_t *, const wchar_t *)) {
    DECLARE_COMPARATOR_ADAPTER(comp);
    qsort(text->data, text->size, sizeof(Sentence*), comparator_adapter);
    return text;
}

Text* filter(Text* text, bool (*func)(wchar_t *, size_t)) {
    for (size_t i = 0; i < text->size; i++) {
        Sentence* current = text->data[i];
        if (!func(current->data, current->size)) {
            free_sentence(current);
            text->data[i] = NULL;
        }
    }

    return optimize(text);
}
