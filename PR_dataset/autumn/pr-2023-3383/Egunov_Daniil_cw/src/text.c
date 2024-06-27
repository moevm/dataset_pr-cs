#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include "text.h"
#include "sentence.h"

#define EXTENSION_SENTENCE_COUNT 10


struct Text {
    Sentence **sentences;
    size_t sentences_count;
    size_t sentences_allocated_size;
};

Text *Text_create() {
    Text *new = (Text *) malloc(sizeof(Text));
    if (!new) {
        return NULL;
    }

    new->sentences = (Sentence **) malloc(0);
    if (!new->sentences) {
        free(new);
        return NULL;
    }

    new->sentences_count = 0;
    new->sentences_allocated_size = 0;

    return new;
}

void Text_destroy(Text *text) {
    for (size_t i = 0; i < text->sentences_count; i++) {
        Sentence_destroy(text->sentences[i]);
    }
    free(text->sentences);
    free(text);
    text = NULL;
}

size_t Text_get_length(Text *text) {
    return text->sentences_count;
}

Sentence **Text_get_sentences(Text *text) {
    return text->sentences;
}

Sentence *Text_get_sentence(Text *text, size_t index) {
    return text->sentences[index];
}

Text *Text_extend(Text *text, size_t extension_sentence_count) {
    size_t new_size = text->sentences_allocated_size + (extension_sentence_count * sizeof(Sentence *));
    Sentence **temp = (Sentence **) realloc(text->sentences, new_size);
    if (!temp) {
        return NULL;
    }
    text->sentences = temp;
    text->sentences_allocated_size = new_size;

    return text;
}

Text *Text_append_sentence(Text *text, Sentence *sentence) {
    while ((text->sentences_count + 1) * sizeof(Sentence *) > text->sentences_allocated_size) {
        if (!Text_extend(text, EXTENSION_SENTENCE_COUNT)) {
            return NULL;
        }
    }

    text->sentences[text->sentences_count] = sentence;
    text->sentences_count++;

    return text;
}

Text *Text_delete_sentence(Text *text, size_t index) {
    if (text->sentences[index]) {
        Sentence_destroy(text->sentences[index]);
    }
    memmove(text->sentences + index, text->sentences + index + 1,
            (text->sentences_count - index - 1) * sizeof(Sentence *));
    text->sentences_count--;
    return text;
}

Text *Text_optimize_size(Text *text) {
    size_t real_sentences_size = text->sentences_count * sizeof(Sentence *);
    if (real_sentences_size == text->sentences_allocated_size) {
        return text;
    }
    Sentence **sentences_temp = (Sentence **) realloc(text->sentences, real_sentences_size);
    if (!sentences_temp) {
        return NULL;
    }
    text->sentences = sentences_temp;
    text->sentences_allocated_size = real_sentences_size;

    return text;
}

Text *Text_delete_duplicates(Text *text) {
    for (size_t i = 0; i < text->sentences_count; i++) {
        Sentence *s1 = text->sentences[i];
        size_t s1_tokens_cnt = Sentence_get_tokens_count(s1);
        for (size_t j = i + 1; j < text->sentences_count; j++) {
            Sentence *s2 = text->sentences[j];
            bool is_s2_to_delete = true;
            if (s1_tokens_cnt != Sentence_get_tokens_count(s2)) continue;
            for (size_t k = 0; k < s1_tokens_cnt; k++) {
                if (wcscasecmp(Token_get_text(Sentence_get_token(s1, k)),
                               Token_get_text(Sentence_get_token(s2, k))) != 0) {
                    is_s2_to_delete = false;
                    break;
                }
            }
            if (is_s2_to_delete) {
                Text_delete_sentence(text, j);
                j--;
            }
        }
    }

    if (!Text_optimize_size(text)) {
        return NULL;
    }

    return text;
}
