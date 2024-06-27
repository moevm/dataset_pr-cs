#include "text_reading.h"

struct Sentence* sentence_reading () {
    int mem_size = START_SIZE;
    wchar_t* buf = malloc(mem_size * sizeof(wchar_t));
    int i = 0;
    wchar_t temp_char;
    do{
        if (i >= mem_size - 1) {
            mem_size += START_SIZE;
            wchar_t *oldbuf;
            oldbuf = realloc(buf, mem_size * sizeof(wchar_t));
            if (oldbuf == NULL) {
                wprintf(MEMORY_ERROR);
                free(buf);
                exit(1);
            }else {
                buf = oldbuf;
            }
        }
        temp_char = (wchar_t) getwchar();
        if ((i == 0) && (temp_char == ' ')) continue;
        if (!(buf[i - 1] == ' ' && temp_char == ' ')) {
            buf[i++] = temp_char;
        }
    } while (temp_char != L'.' && temp_char != L'\n');
    buf[i++] = L'\0';
    struct Sentence *sentence = malloc(sizeof(struct Sentence));
    sentence->sentence = buf;
    return sentence;
}


struct Text input_text () {
    int mem_size = START_SIZE;
    struct Sentence **sent_pointers = malloc(mem_size * sizeof(struct Sentence*));
    int i = 0;
    struct Sentence *temp_sent;
    do{
        if (i >= mem_size - 1) {
            mem_size += START_SIZE;
            struct Sentence **old_sentences = realloc(sent_pointers, mem_size * sizeof(struct Sentence *));
            if (old_sentences == NULL) {
                wprintf(MEMORY_ERROR);
                free(sent_pointers);
                exit(2);
            }else {
                sent_pointers = old_sentences;
            }
        }
        temp_sent = sentence_reading();
        if (temp_sent->sentence[wcslen(temp_sent->sentence) - 1] != L'\n') {
            sent_pointers[i++] = temp_sent;
        }
    } while (temp_sent->sentence[wcslen(temp_sent->sentence) - 1] != L'\n');
    struct Text text;
    text.sentences = sent_pointers;
    text.amount_of_sentences = i;
    return text;
}