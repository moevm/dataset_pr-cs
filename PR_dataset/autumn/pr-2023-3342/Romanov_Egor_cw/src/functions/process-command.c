#include "../headers/process-command.h"

int process_commands(){
    int command = get_option();
    if (!check_command_char(&command)){
        wprintf(L"Error: <Неверный номер команды, команда задаётся числом в диапозоне от 0 до 5>\n");
        return 0;
    }
    if (command == 5){
        give_info_about_functions();
        return 0;
    }

    wchar_t** f_sent = malloc(sizeof(wchar_t*));
    int amount_of_words = 0;
    int ind=0;
    int f_sent_capacity = 2;
    f_sent[amount_of_words] = malloc(sizeof(wchar_t));
    wchar_t character = getwchar();
    if (command==9){
        while(1){
            character = getwchar();
            if (character == L'\n'){
                f_sent[amount_of_words][ind] =L'\0';
                break;
            }
            if (ind >= f_sent_capacity-1){
                f_sent_capacity *=2;
                f_sent[amount_of_words] = realloc(f_sent[amount_of_words], sizeof(wchar_t) *(f_sent_capacity));
            }
            if (character == L' '){
                f_sent[amount_of_words][ind] = L'\0';
                ind =0;
                f_sent_capacity = 2;
                amount_of_words++;
                f_sent = realloc(f_sent, sizeof(wchar_t*) * (amount_of_words+1));
                f_sent[amount_of_words] = malloc(sizeof(wchar_t));
                continue;
            }
            f_sent[amount_of_words][ind++] = character;
        }
    }

    // wprintf(L"%ls\n", f_sent);
        int amount_of_sentences = 0;
        wchar_t **readed_text = read_text(&amount_of_sentences);
        struct Text text = {malloc(sizeof(struct Sentence)*amount_of_sentences), amount_of_sentences};

        if (!amount_of_sentences){
            return 0;
        }

        for (int i=0;i<amount_of_sentences;i++){
            struct Sentence sentence = {malloc(sizeof(struct Word)), readed_text[i], wcslen(readed_text[i]), 0};
            text.sentences[i] = sentence;
        }

        split_sentences_on_words(text);
    switch ((int)command){
        case 0:
            output(return_reworked_text(text));
            free_text(text);
            break;
        case 1:
            print_uniqual_words(text);
            break;
        case 2:
            split_sentences_on_words(text);
            replace_date(text);
            free_text(text);
            break;
        case 3:
            sort_by_length(text);
            break;
        case 4:
            output(delete_special_sentences(text));
            free_text(text);
            break;
        case 9:
            
            function_nine(return_reworked_text(text), f_sent, amount_of_words);
            break;
        default:
            break;
    }
}
