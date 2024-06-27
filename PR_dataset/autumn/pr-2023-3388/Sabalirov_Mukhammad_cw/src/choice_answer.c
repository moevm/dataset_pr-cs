#include "choice_answer.h"

void print_text(struct Text *text){
    size_t i;
    for (i = 0; i< text->len; i++)
        wprintf(OUT_STR, text->data[i]->data);
}

void make_all_for_translit(struct Text *text){
    struct Dict *dict = initial_cyrillic_dict();
    struct Text *translit = translit_text(text, dict);
    print_text(translit);
    free_dict(dict);
    free_text(translit);
}

void make_all_for_special(struct Text *text){
    struct Text *special = special_text(text);
    print_text(special);
    free_text(special);
}

void make_all_for_bin(struct Text *text){
    struct Text *bin = bin_text(text);
    print_text(bin);
    free_text(bin);
}

void make_all_for_odd(struct Text *text){
    struct Text *remove_odd = remove_odd_text(text);
    print_text(remove_odd);
}

void make_all_for_double(struct Text *text){
    struct Text *double_t = make_double_text(text);
    print_text(double_t);
    free_text(double_t);
}

void choice_func(){
    int num_of_func;
    wscanf(L"%d", &num_of_func);
    getwchar();
    if (num_of_func == 5){
        wprintf(FUNC_INFO);
    }
    else if ((0 <= num_of_func && num_of_func <= 5) || num_of_func == 9){   
        struct Text *text = read_text();
        switch (num_of_func){
            case 0:{ print_text(text); break; }
            case 1:{ make_all_for_translit(text); break; }
            case 2:{ make_all_for_special(text); break; }
            case 3:{ make_all_for_bin(text); break; }
            case 4:{ make_all_for_odd(text); break; }
            case 9:{ make_all_for_double(text); break; }
            default:{ panic(FUNC_NUM_ERROR); break; }
        }
        free_text(text);
    }
    else{
        wprintf(FUNC_NUM_ERROR);
    }
}
