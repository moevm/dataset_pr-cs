#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include "input.h"
#include "sentence.h"
#include "text.h"
#include "token.h"
#include "utils.h"

#define START_BUFFER_SIZE 10
#define BUFFER_SIZE_STEP 5


Sentence *write_buffer_to_sentence(Sentence *sentence, wchar_t *buffer) {
    Token *new_token = Token_create(buffer);
    if (!new_token || !Sentence_append_token(sentence, new_token)) {
        Sentence_destroy(sentence);
        return NULL;
    }

    return sentence;
}

wchar_t *wipe_buffer(wchar_t **buffer, size_t *buffer_size, size_t *buffer_length) {
    free(*buffer);
    *buffer = (wchar_t *) malloc(START_BUFFER_SIZE * sizeof(wchar_t));
    if (!*buffer) {
        return NULL;
    }
    *buffer_size = START_BUFFER_SIZE;
    *buffer_length = 0;

    return *buffer;
}

Sentence *read_sentence(bool *is_last_sentence, bool remove_duplicate_whitespaces, bool correct_spaces_with_commas) {
    Sentence *sentence = Sentence_create();
    size_t cur_buffer_length = 0;
    size_t cur_buffer_size = START_BUFFER_SIZE;
    wchar_t *buffer = (wchar_t *) malloc(START_BUFFER_SIZE * sizeof(wchar_t));
    wchar_t ch;

    while (1) {
        // check enough space in the buffer
        if (cur_buffer_length + 3 > cur_buffer_size) {
            size_t new_buffer_size = cur_buffer_size + BUFFER_SIZE_STEP;
            wchar_t *new_buffer = (wchar_t *) realloc(buffer, new_buffer_size * sizeof(wchar_t));
            if (!new_buffer) {
                free(buffer);
                Sentence_destroy(sentence);
                return NULL;
            }
            cur_buffer_size = new_buffer_size;
            buffer = new_buffer;
        }

        ch = (wchar_t) getwchar();

        // checking for two '\n' in a row
        if (cur_buffer_length != 0 && buffer[cur_buffer_length - 1] == L'\n' && ch == L'\n') {
            *is_last_sentence = true;
            if (Sentence_get_tokens_count(sentence) != 0) {
                buffer[cur_buffer_length - 1] = L'.';
                buffer[cur_buffer_length++] = L'\0';
                if (!write_buffer_to_sentence(sentence, buffer)) {
                    free(buffer);
                    Sentence_destroy(sentence);
                    return NULL;
                }
            }
            free(buffer);
            break;
        }

        // checking for whitespace characters at the beginning of a sentence
        if (Sentence_get_tokens_count(sentence) == 0 && cur_buffer_length == 1 &&
            iswspace(buffer[cur_buffer_length - 1])) {
            cur_buffer_length--;
        }

        if (remove_duplicate_whitespaces) {
            if (cur_buffer_length != 0 && iswspace(buffer[cur_buffer_length - 1]) && iswspace(ch)) {
                continue;
            }
        }

        if (correct_spaces_with_commas) {
            // checking for the presence of a space after the comma
            if (cur_buffer_length != 0 && buffer[cur_buffer_length - 1] == L',' && !iswspace(ch)) {
                buffer[cur_buffer_length++] = L' ';
            }
            // checking for the absence of a space before the comma
            if (ch == L',') {
                while (cur_buffer_length != 0 && iswblank(buffer[cur_buffer_length - 1])) {
                    cur_buffer_length--;
                }
            }
        }

        // checking for the end of the token
        if (cur_buffer_length != 0 && (is_separator(buffer[cur_buffer_length - 1]) + is_separator(ch) == 1)) {
            buffer[cur_buffer_length++] = L'\0';

            if (!write_buffer_to_sentence(sentence, buffer)) {
                free(buffer);
                Sentence_destroy(sentence);
                return NULL;
            }
            if (!wipe_buffer(&buffer, &cur_buffer_size, &cur_buffer_length)) {
                Sentence_destroy(sentence);
                return NULL;
            }
        }
        if (ch == L'.') {
            buffer[cur_buffer_length++] = ch;
            buffer[cur_buffer_length++] = L'\0';

            if (!write_buffer_to_sentence(sentence, buffer)) {
                free(buffer);
                Sentence_destroy(sentence);
                return NULL;
            }
            free(buffer);
            break;
        }

        buffer[cur_buffer_length++] = ch;
    }

    if (!Sentence_optimize_size(sentence)) {
        Sentence_destroy(sentence);
        return NULL;
    }

    return sentence;
}

Text *read_text(bool remove_duplicate_whitespaces, bool correct_spaces_with_commas) {
    Text *text = Text_create();
    Sentence *sentence;
    bool is_last_sentence = false;
    while (is_last_sentence != true) {
        sentence = read_sentence(&is_last_sentence, remove_duplicate_whitespaces, correct_spaces_with_commas);
        if (!sentence) {
            Text_destroy(text);
            return NULL;
        }

        if (Sentence_get_tokens_count(sentence) == 0) {
            Sentence_destroy(sentence);
            break;
        }

        if (!Text_append_sentence(text, sentence)) {
            Text_destroy(text);
            return NULL;
        }
    }

    if (!Text_delete_duplicates(text)) {
        Text_destroy(text);
        return NULL;
    }

    return text;
}
