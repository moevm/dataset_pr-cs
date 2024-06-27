#include "text_reading.h"

struct Sentence* sentence_reading() {
    size_t mem_size = START_SIZE;
    wchar_t* buf = malloc(mem_size * sizeof(wchar_t));

    if (buf == NULL) {
        wprintf(MEMORY_ERROR);
        exit(1);
    }

    size_t i = 0;
    wchar_t temp_char = (wchar_t)getwchar();
    
    if (temp_char == L'\n') {
        temp_char = (wchar_t)getwchar();
        if (temp_char == L'\n') return NULL;
    }
    
    while (temp_char != L'.') {
        if (temp_char == L'\n') {
            temp_char = (wchar_t)getwchar();
            if (temp_char == L'\n') return NULL;
        }

        if ((i == 0) && (temp_char == L' ')) {
            temp_char = (wchar_t)getwchar();
            continue;
        }

        if (i >= mem_size - 2) {
            mem_size += START_SIZE;
            wchar_t* oldbuf = realloc(buf, mem_size * sizeof(wchar_t));

            if (oldbuf == NULL) {
                wprintf(MEMORY_ERROR);
                free(buf);
                exit(1);
            } else {
                buf = oldbuf;
            }
        }

        if (!(buf[i - 1] == L' ' && temp_char == L' ')) {
            buf[i++] = temp_char;
        }

        temp_char = (wchar_t)getwchar();
    }
    buf[i] = L'.';
    buf[i+1] = L'\0';

    struct Sentence* sentence = malloc(sizeof(struct Sentence));
    sentence->sentence = buf;

    return sentence;
}


struct Text input_text () {
    int mem_size = START_SIZE;
    struct Sentence **sent_pointers = malloc(mem_size * sizeof(struct Sentence*));
    int i = 0;
    struct Sentence *temp_sent = sentence_reading();

    while (temp_sent != NULL) {
        if (i >= mem_size - 1) {
            mem_size += START_SIZE;
            struct Sentence **old_sentences = realloc(sent_pointers, mem_size * sizeof(struct Sentence *));
            if (old_sentences == NULL) {
                wprintf(MEMORY_ERROR);
                free(sent_pointers);
                exit(2);
            } else sent_pointers = old_sentences;
        }

        sent_pointers[i++] = temp_sent;
        temp_sent = sentence_reading();
    }

    struct Text text;
    text.sentences = sent_pointers;
    text.amount_of_sentences = i;
    return text;
}
