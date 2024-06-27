#include "text.h"



Text* realloc_text(Text* text) {
    size_t new_cap = text->capacity + ALLOC_TEXT;

    Sentence** new_data = realloc(text->data, sizeof(Sentence*) * new_cap);
    if (new_data == NULL) {
        error(L"Error: недостаточно памяти для нового текста!");
    }

    for (size_t i = text->capacity; i < new_cap; i++)
        new_data[i] = NULL;
    
    text->data = new_data;
    text->capacity = new_cap;

    return text;
}

Text* text_initialization() {
    Text* text = malloc(sizeof(Text));
    if (text == NULL) {
        error(L"Error: недостаточно памяти для нового текста!");
    }

    text->data = NULL;
    text->capacity = 0;
    text->size = 0;

    return text;
}

Text* text_free(Text* text) {
    for (size_t i = 0; i < text->capacity; i++) {
        if (text->data[i] != NULL)
            sentence_free(text->data[i]);
    }
    free(text->data);
    text->data = NULL;
    text->capacity = 0;
    text->size = 0;

    return text;
}

Text* add_sentence(Text* text, Sentence* sentence) {
    if (text->capacity <= text->size) {
        realloc_text(text);
    }
    
    text->data[text->size] = sentence;
    text->size += 1;

    return text;
}

Text* read_text() {
    Text* text = text_initialization();
    Sentence* sentence = read_sentence();
    
    while (sentence != NULL) {
        add_sentence(text, sentence);
        sentence = read_sentence();
    }
    
    return text;
}

Text* restruct(Text* text) {
    for (size_t i = 0; i < text->size; i++) {
        const Sentence* current = text->data[i];
        if (current != NULL) {
            continue;
        }
        for (size_t j = i+1; j < text->size; j++) {
            if (text->data[j] != NULL) {
                text->data[i] = text->data[j];
                text->data[j] = NULL;
                break;
            }
        }
    }

    size_t i = 0;
    while ((text->data[i] != NULL) && i < text->capacity) {
        i++;
    }
    text->size = i;

    return text;
}

Text* unique(Text* text) {
    for (size_t i = 0; i < text->size; i++) {
        Sentence* left = text->data[i];
        if (left == NULL) {
            continue;
        }

        for (size_t j = i+1; j < text->size; j++) {
            Sentence* right = text->data[j];
            if ((right != NULL) && (left->size == right->size) && (compare(left->data, right->data) == 0)) {
                sentence_free(right);
                text->data[j] = NULL;
            }
        }
    }

    return restruct(text);
}

Text* apply_fix_endings(Text* text) {
    for (size_t i = 0; i < text->size; i++) {
        Sentence* current = text->data[i];
        current->data = fix_endings(current->data, &(current->size));
        current->capacity = current->size+1;
    }

    return text;
}

int sentence_compare_words_count(const void* left, const void* right) {
    return compare_words_count((*((Sentence**)left))->data, (*((Sentence**)right))->data);
}

Text* sort_by_words_count(Text* text) {
    qsort(text->data, text->size, sizeof(Sentence*), sentence_compare_words_count);
    return text;
}

Text* filter_longer_than_ten(Text* text) {
    for (size_t i = 0; i < text->size; i++) {
        Sentence* current = text->data[i];
        if (!longer_than_ten(current->data, current->size)) {
            sentence_free(current);
            text->data[i] = NULL;
        }
    }

    return restruct(text);
}

Text* double_word_in_every_sentence(Text* text){
    for (size_t i = 0; i < text->size; i++){
        Sentence* sentence = text->data[i];
        double_word(sentence);
    }
}