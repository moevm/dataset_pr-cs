#include "output_function.h"

void process_chosen_function (int chosen_function, struct Text text) {
    switch (chosen_function)
    {
    case 0:{
        text = input_text();
        record_words(&text);
        delete_empty_sents(&text);
        delete_equal_sentences(&text);
        output_text(&text);
        break;
    }
    case 1:{
        text = input_text();
        record_words(&text);
        delete_empty_sents(&text);
        delete_equal_sentences(&text);
        int secs = cnt_num_of_secs(text);
        wprintf(L"В тексте %d мин. и %d сек.\n", (secs / 60), (secs - secs / 60 * 60));
        break;
    }
    case 2:{
        text = input_text();
        record_words(&text);
        delete_empty_sents(&text);
        delete_equal_sentences(&text);
        sort_by_codes_of_1st_words(&text);
        output_text(&text);
        break;
    }
    case 3:{
        text = input_text();
        record_words(&text);
        delete_empty_sents(&text);
        delete_equal_sentences(&text);
        replace_option_chars(&text);
        output_text(&text);
        break;
    }
    case 4:{
        text = input_text();
        record_words(&text);
        delete_empty_sents(&text);
        delete_equal_sentences(&text);
        delete_sentences_with_3_consonants(&text);
        output_text(&text);
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
    }
    
}