#include "output_function.h"

void process_chosen_function (int chosen_function, struct Text text) {
    switch (chosen_function)
    {
        case 0:{
            text = input_text();
            record_words(&text);
            delete_empty_sentences(&text);
            delete_equal_sentences(&text);
            output_text(&text);
            memory_clean(&text);
            break;
        }
        case 1:{
            text = input_text();
            record_words(&text);
            delete_empty_sentences(&text);
            delete_equal_sentences(&text);
            int secs = cnt_num_of_secs(text);
            wprintf(L"В тексте %d мин. и %d сек.\n", (secs / 60), (secs - secs / 60 * 60));
            memory_clean(&text);
            break;
        }
        case 2:{
            text = input_text();
            record_words(&text);
            delete_empty_sentences(&text);
            delete_equal_sentences(&text);
            sort_by_codes_of_first_words(&text);
            output_text(&text);
            memory_clean(&text);
            break;
        }
        case 3:{
            text = input_text();
            record_words(&text);
            delete_empty_sentences(&text);
            delete_equal_sentences(&text);
            replace_option_chars(&text);
            output_text(&text);
            memory_clean(&text);
            break;
        }
        case 4:{
            text = input_text();
            record_words(&text);
            delete_empty_sentences(&text);
            delete_equal_sentences(&text);
            delete_sentences_with_three_consonants_in_last_word (&text);
            output_text(&text);
            memory_clean(&text);
            break;
        }
        case 5:{
            print_help();
            break;
        }
        default:{
            wprintf(L"Ошибка. Неверный ввод значения выбора действия.\n");
            break;
        }
        case 8:{
            text = input_text();
            record_words(&text);
            delete_empty_sentences(&text);
            delete_equal_sentences(&text);
            palindrome_sentence_func(&text);
            memory_clean(&text);
            break;
        }
       
    }
}
