#include "output_functions.h"


void process_chosen_function(int chosen_function, struct Sentence **sentences_array, struct Text *text) {
    switch (chosen_function) {
        case 0:
            read_text(text);
            read_sentences(sentences_array, text);
            fill_the_structure(*sentences_array, text->sentences_count);
            do_basic_processing(*sentences_array, text->sentences_count);
            break;
        case 1:
            read_text(text);
            read_sentences(sentences_array, text);
            fill_the_structure(*sentences_array, text->sentences_count);
            convert_to_date(*sentences_array, text->sentences_count);
            break;
        case 2:
            read_text(text);
            read_sentences(sentences_array, text);
            fill_the_structure(*sentences_array, text->sentences_count);
            reverse_sentence(*sentences_array, text->sentences_count);
            break;
        case 3:
            read_text(text);
            read_sentences(sentences_array, text);
            fill_the_structure(*sentences_array, text->sentences_count);
            sort_by_first_word(*sentences_array, text->sentences_count);
            break;
        case 4:
            read_text(text);
            read_sentences(sentences_array, text);
            fill_the_structure(*sentences_array, text->sentences_count);
            delete_short_words(*sentences_array, text->sentences_count);
            break;
        case 5:
            wprintf(FUNCTION_INFO);
            exit(0);
        case 9:
            read_text(text);
            read_sentences(sentences_array, text);
            fill_the_structure(*sentences_array, text->sentences_count);
            replace(*sentences_array, text->sentences_count);
            break;
        default:
            wprintf(ERROR_COMMAND_NOT_FOUND);
            exit(1);
    }
}
