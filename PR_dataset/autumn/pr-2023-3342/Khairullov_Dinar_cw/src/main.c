#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#define FUNC_INFO_OUTPUT "Help about functions:\n0 - Text output after the initial mandatory processing\n1 - Output all sentences in which all words consist only of numbers.\n2 - Sort the sentences in descending order by the number of capital letters in them.\n3 - Remove all sentences in which a certain word (which the user inputs into your program after selecting this action) appears 2 or more times.\n4 - Transform all sentences so that each occurrence of a digit is replaced with the corresponding substring.\n5 - Displaying the program's function description.\n"
#define WRONG_NUMBER "Wrong number input\n"
#define INFO_CW "Course work for option 4.3, created by Khairullov Dinar.\n"
#define MEMORY_ERROR "Error: error reallocating memory\n"



void find_equal_sentences(int* del_ind_arr, int* del_ind_counter, char** text, int* num_of_sentences);
void repeat_remove(char**text, int* num_of_sentences);
void info_output();
void text_output(char** text, int* num_of_sentences);
void if_another_symbol(char*** text, int* num_of_sentences, int* num_of_symbols, char sym, int* new_sen_flag);
void if_dot_symbol(char*** text, int* num_of_sentences, int* num_of_symbols, char sym, int* new_sen_flag);
void double_pointer_memory_check(char** text);
void pointer_memory_check(char* text);
void clean_memory(char** text, int* num_of_sen);
int get_option(int* case_number);
char** text_input(int* num_of_sentences);
int qsort_cmp(const void* first_str, const void* second_str);
int int_cmp(const void* a, const void* b);
void str_changer(char** text, char* digit_word, int* source_str_counter, int* i, int len_of_word);
int switch_case(int case_number, int res);
void only_digits_sen(char** text, int* num_of_sentences);
void sort_by_upper_letters(char** text, int* num_of_sentences);
void del_sen_with_two_words(char** text, int* num_of_sentences);
void replace_digits(char** text, int* num_of_sentences);
void func_info();
void replace_with_binary(char** text, int* num_of_sen);
void input_binary(char*** text, int i, int* source_str_counter, int* int_number, char** number, int* number_length);



void find_equal_sentences(int* del_ind_arr, int* del_ind_counter, char** text, int* num_of_sentences){
    for(int i = 0; i < *num_of_sentences; i++){
        for(int y = i + 1; y < *num_of_sentences; y++){
            int first_num = strlen(text[i]);
            int second_num = strlen(text[y]);
            int rep_counter = 0;
            if(strstr(text[y], ".") == NULL){
                first_num--;
            }
            if(first_num != second_num){
                continue;
            }
            else{
                for(int x = 0; x < first_num; x++){
                    if(isalpha(text[i][x]) && isalpha(text[y][x])){
                        if(tolower(text[i][x]) == tolower(text[y][x])){
                            rep_counter++;
                        }
                        else{
                            rep_counter = rep_counter;
                        }
                    }
                    else{
                        if(text[i][x] == text[y][x]){
                            rep_counter++;
                        }
                    }
                }
            }
            if(rep_counter == first_num){
                qsort(del_ind_arr, *del_ind_counter, sizeof(int), int_cmp);
                int in_counter = 0;
                for(int z = 0; z < *del_ind_counter; z++){
                    if(del_ind_arr[z] == y){
                        rep_counter = 0;
                        in_counter = 0;
                        break;
                    }
                    else{
                        in_counter++;
                    }
                }
                if(in_counter == *del_ind_counter){
                    del_ind_arr[*del_ind_counter] = y;
                    (*del_ind_counter)++;
                    rep_counter = 0;
                }
            }
        }
    }
}



void repeat_remove(char**text, int* num_of_sentences){
    int del_ind_arr[*num_of_sentences];
    int del_ind_counter = 0;
    find_equal_sentences(del_ind_arr, &del_ind_counter, text, num_of_sentences);
    qsort(del_ind_arr, del_ind_counter, sizeof(int), int_cmp);
    for(int arr_ind = 0; arr_ind < del_ind_counter; arr_ind++){
        for(int r = del_ind_arr[arr_ind]; r < *num_of_sentences; r++){
            if(r == del_ind_arr[arr_ind]){
                free(text[r]);
            }
            if(r+1 < *num_of_sentences){
                text[r] = text[r+1];
            }
            else{
                (*num_of_sentences)--;
            }
        }
    }
}



void info_output(){
    printf(INFO_CW);
}



void text_output(char** text, int* num_of_sentences){
    for(int i = 0; i < *num_of_sentences; i++){
        printf("%s\n", text[i]);
    }
}



void clean_memory(char** text, int* num_of_sen){
    for(int i = 0; i < *num_of_sen; i++){
        free(text[i]);
    }
    free(text);
}



int get_option(int* case_number){
    int res = scanf("%d", case_number);
    return res;
}



char** text_input(int* num_of_sentences){
    char** text = malloc(1*sizeof(char*));
    double_pointer_memory_check(text);
    int num_of_symbols = 0;
    char sym;
    int new_sen_flag = 1;
    text[*num_of_sentences] = malloc(1*sizeof(char));
    pointer_memory_check(text[*num_of_sentences]);
    while(1){
        sym = getchar();
        if(sym == '\n'){
            if(new_sen_flag == 0){
                text[*num_of_sentences][num_of_symbols] = sym;
                num_of_symbols++;
                text[*num_of_sentences] = realloc(text[*num_of_sentences], (num_of_symbols + 1)*sizeof(char));
                pointer_memory_check(text[*num_of_sentences]);
            }
            sym = getchar();
            if(sym == '\n'){
                text[*num_of_sentences][num_of_symbols - 1] = '\0';
                if(new_sen_flag){
                    free(text[*num_of_sentences]);
                    (*num_of_sentences)--;
                }
                break;
            }
            else{
                if(new_sen_flag == 1 && ( sym == '\t' || sym == ' ')){
                    continue;
                }
                else{
                    if_another_symbol(&text, num_of_sentences, &num_of_symbols, sym, &new_sen_flag);
                }
            }
        }
        else if (sym == '.'){
            if_dot_symbol(&text, num_of_sentences, &num_of_symbols, sym, &new_sen_flag);
        }
        else{
            if(new_sen_flag == 1 && ( sym == '\t' || sym == ' ')){
                continue;
            }
            else{
                if_another_symbol(&text, num_of_sentences, &num_of_symbols, sym, &new_sen_flag);
            }
        }
    }
    (*num_of_sentences)++;
    return text;
}



void if_another_symbol(char*** text, int* num_of_sentences, int* num_of_symbols, char sym, int* new_sen_flag){
    (*text)[*num_of_sentences][*num_of_symbols] = sym;
    (*num_of_symbols)++;
    (*text)[*num_of_sentences] = realloc((*text)[*num_of_sentences], (*num_of_symbols + 1)*sizeof(char));
    pointer_memory_check((*text)[*num_of_sentences]);
    (*new_sen_flag) = 0;
}



void if_dot_symbol(char*** text, int* num_of_sentences, int* num_of_symbols, char sym, int* new_sen_flag){
    (*text)[*num_of_sentences][*num_of_symbols] = sym;
    (*num_of_symbols)++;
    (*text)[*num_of_sentences] = realloc((*text)[*num_of_sentences], (*num_of_symbols + 1)*sizeof(char));
    pointer_memory_check((*text)[*num_of_sentences]);
    (*text)[*num_of_sentences][*num_of_symbols] = '\0';
    (*num_of_sentences)++;
    (*text) = realloc((*text), ((*num_of_sentences) + 1)*sizeof(char*));
    double_pointer_memory_check((*text));
    *num_of_symbols = 0;
    (*text)[*num_of_sentences] = malloc(1*sizeof(char));
    pointer_memory_check((*text)[*num_of_sentences]); 
    *new_sen_flag = 1;
}



void double_pointer_memory_check(char** text){
    if(text == NULL){
        fprintf(stderr, MEMORY_ERROR);
    }
}



void pointer_memory_check(char* text){
    if(text == NULL){
        fprintf(stderr, MEMORY_ERROR);
    }
}



int qsort_cmp(const void* first_str, const void* second_str){

    char** first_sen = (char**)first_str;
    char** second_sen = (char**)second_str;

    int num_of_words_first = strlen(*first_sen);
    int num_of_words_second = strlen(*second_sen);

    int upper_count_first = 0;
    int upper_count_second = 0;


    for(int i = 0; i < num_of_words_first; i++){
        if(isupper(*(*first_sen+i)) && isalpha(*(*first_sen+i))){
            upper_count_first++;
        }
    }
    for(int i = 0; i < num_of_words_second; i++){
        if(isupper(*(*second_sen+i)) && isalpha(*(*second_sen+i))){
            upper_count_second++;
        }
    }
    return upper_count_second - upper_count_first;
}



int int_cmp(const void* a, const void* b){
    int first_int = *(int*)a;
    int second_int = *(int*)b;
    return second_int - first_int;
}



void str_changer(char** text, char* digit_word, int* source_str_counter, int* i, int len_of_word){
    text[*i] = realloc(text[*i], ((strlen(text[*i]) + 1) + len_of_word + 1)*sizeof(char));
    pointer_memory_check(text[*i]);
    for(int x = 0; x < len_of_word; x++){
        text[*i][*source_str_counter] = digit_word[x];
        (*source_str_counter)++;
    }

}



int switch_case(int case_number, int res){
    if(!res){
        printf(WRONG_NUMBER);
        return 0;
    }
    int num_of_sentences = 0;
    char** text;
    switch(case_number){
        case 0:
            text = text_input(&num_of_sentences);
            repeat_remove(text, &num_of_sentences);
            text_output(text, &num_of_sentences);
            clean_memory(text, &num_of_sentences);
            break;
        case 1:
            text = text_input(&num_of_sentences);
            repeat_remove(text, &num_of_sentences);
            only_digits_sen(text, &num_of_sentences);
            clean_memory(text, &num_of_sentences);
            break;
        case 2:
            text = text_input(&num_of_sentences);
            repeat_remove(text, &num_of_sentences);
            sort_by_upper_letters(text, &num_of_sentences);
            text_output(text, &num_of_sentences);
            clean_memory(text, &num_of_sentences);
            break;
        case 3:
            text = text_input(&num_of_sentences);
            repeat_remove(text, &num_of_sentences);
            del_sen_with_two_words(text, &num_of_sentences);
            text_output(text, &num_of_sentences);
            clean_memory(text, &num_of_sentences);
            break;
        case 4:
            text = text_input(&num_of_sentences);
            repeat_remove(text, &num_of_sentences);
            replace_digits(text, &num_of_sentences);
            text_output(text, &num_of_sentences);
            clean_memory(text, &num_of_sentences);
            break;
        case 5:
            func_info();
            break;
        case 9:
            text = text_input(&num_of_sentences);
            repeat_remove(text, &num_of_sentences);
            replace_with_binary(text, &num_of_sentences);
            text_output(text, &num_of_sentences);
            clean_memory(text, &num_of_sentences);
            break;
        default:
            printf("%s", WRONG_NUMBER);
    }
    return 0;
}



void only_digits_sen(char** text, int* num_of_sentences){
    int res_indexes[*num_of_sentences];
    int res_counter = 0;
    int flag = 0;
    for(int i = 0; i < *num_of_sentences; i++){
        for(int y = 0; y < strlen(text[i]); y++){
            if(isdigit(text[i][y])){
                flag = 1;
            }
            else if(text[i][y] == '.' || text[i][y] == ' ' || text[i][y] == '\n' || text[i][y] == ',' || text[i][y] == '\t'){
                flag = 1;
            }
            else{
                flag = 0;
                break;
            }
        }
        if(flag){
            res_indexes[res_counter] = i;
            res_counter++;
        }
    }
    for(int x = 0; x < res_counter; x++){
        printf("%s\n", text[res_indexes[x]]);
    }
}



void sort_by_upper_letters(char** text, int* num_of_sentences){
    qsort(text, *num_of_sentences, sizeof(char*), qsort_cmp);
}



void del_sen_with_two_words(char** text, int* num_of_sentences){
    char word[100];
    scanf("%s", word);
    int word_counter = 0;
    int del_sen[*num_of_sentences];
    int del_sen_counter = 0;
    for(int i = 0; i < *num_of_sentences; i++){
        char* first_pointer = strstr(text[i], word);
        while(first_pointer != NULL){
            if((first_pointer - text[i] == 0) || ((first_pointer - text[i] > 0) && !(isalnum(first_pointer[-1])))){
                if( !( isalnum(first_pointer[strlen(word)]) ) ){
                    word_counter++;
                }
            }
            first_pointer = strstr(first_pointer + strlen(word), word);
        }
        if(word_counter >= 2){
            del_sen[del_sen_counter] = i;
            del_sen_counter++;
        }
        word_counter = 0;
    }
    qsort(del_sen, del_sen_counter, sizeof(int), int_cmp);
    for(int arr_ind = 0; arr_ind < del_sen_counter; arr_ind++){
        for(int r = del_sen[arr_ind]; r < *num_of_sentences; r++){
            if(r == del_sen[arr_ind]){
                free(text[r]);
            }
            if(r+1 < *num_of_sentences){
                text[r] = text[r+1];
            }
            else{
                (*num_of_sentences)--;
            }
        }
    }
}



void replace_digits(char** text, int* num_of_sentences){
    char zero[] = {'Z', 'e', 'r', 'o'};
    char one[] = {'O', 'n', 'e'};
    char two[] = {'T', 'W', 'o'};
    char three[] = {'T', 'h', 'r', 'e', 'e'};
    char four[] = {'F', 'o', 'u', 'r'};
    char five[] = {'F', 'i', 'v', 'e'};
    char six[] = {'S', 'i', 'x'};
    char seven[] = {'S', 'e', 'v', 'e', 'n'};
    char eight[] = {'E', 'i', 'g', 'h', 't'};
    char nine[] = {'N', 'i', 'n', 'e'};
    char* copy_of_str;
    for(int i = 0; i < *num_of_sentences; i++){
        copy_of_str = malloc((strlen(text[i]) + 1)*sizeof(char));
        pointer_memory_check(copy_of_str);
        strcpy(copy_of_str, text[i]);
        int source_str_counter = 0;
        for(int y = 0; y < strlen(copy_of_str) + 1; y++){
            if(isdigit(copy_of_str[y])){
                if(copy_of_str[y] == '0'){
                    str_changer(text, zero, &source_str_counter, &i, 4);
                }
                if(copy_of_str[y] == '1'){
                    str_changer(text, one, &source_str_counter, &i, 3);
                }
                if(copy_of_str[y] == '2'){
                    str_changer(text, two, &source_str_counter, &i, 3);
                }
                if(copy_of_str[y] == '3'){
                    str_changer(text, three, &source_str_counter, &i, 5);
                }
                if(copy_of_str[y] == '4'){
                    str_changer(text, four, &source_str_counter, &i, 4);
                }
                if(copy_of_str[y] == '5'){
                    str_changer(text, five, &source_str_counter, &i, 4);
                }
                if(copy_of_str[y] == '6'){
                    str_changer(text, six, &source_str_counter, &i, 3);
                }
                if(copy_of_str[y] == '7'){
                    str_changer(text, seven, &source_str_counter, &i, 5);
                }
                if(copy_of_str[y] == '8'){
                    str_changer(text, eight, &source_str_counter, &i, 5);
                }
                if(copy_of_str[y] == '9'){
                    str_changer(text, nine, &source_str_counter, &i, 4);
                }
            }
            else{
                text[i] = realloc(text[i], (strlen(text[i]) + 2)*sizeof(char));
                pointer_memory_check(text[i]);
                text[i][source_str_counter] = copy_of_str[y];
                source_str_counter++;
            }
        }
        free(copy_of_str);
    }
}



void func_info(){
    printf("%s", FUNC_INFO_OUTPUT);
}



void replace_with_binary(char** text, int* num_of_sen){
    char* copy_of_sen;
    for(int i = 0; i < *num_of_sen; i++){
        int source_str_counter = 0;
        copy_of_sen = malloc((strlen(text[i])+1)*sizeof(char));
        pointer_memory_check(copy_of_sen);
        strcpy(copy_of_sen, text[i]);
        for(int y = 0; y < strlen(copy_of_sen) + 1; y++){
            if(isdigit(copy_of_sen[y])){
                int number_length = 0;
                int int_number = 0;
                char* number = malloc(1*sizeof(char));
                for(int x = y; x < strlen(copy_of_sen) + 1; x++){
                    if(isdigit(copy_of_sen[x])){
                        number[number_length] = copy_of_sen[x];
                        number = realloc(number, (strlen(number) + 1)*sizeof(char));
                        pointer_memory_check(number);
                        number_length++;
                        y++;
                    }
                    else{
                        number[number_length] = '\0';
                        break;
                    }
                }
                y--;
                input_binary(&text, i, &source_str_counter, &int_number, &number, &number_length);
            }
            else{
                text[i] = realloc(text[i], (strlen(text[i]) + 2)*sizeof(char));
                pointer_memory_check(text[i]);
                text[i][source_str_counter] = copy_of_sen[y];
                source_str_counter++;
            }
        } 
        free(copy_of_sen);
    }
}



void input_binary(char*** text, int i, int* source_str_counter, int* int_number, char** number, int* number_length){
    (*text)[i] = realloc((*text)[i], (strlen((*text)[i]) + 3)*sizeof(char));
    pointer_memory_check((*text)[i]);
    (*text)[i][*source_str_counter] = '0';
    (*source_str_counter)++;
    (*text)[i][*source_str_counter] = 'b';
    (*source_str_counter)++;
    *int_number = atoi(*number);
    free(*number);
    int ost = 0;
    char* numberb = malloc(1*sizeof(char));
    pointer_memory_check(numberb);
    int b_counter = 0;
    do{
        ost = (*int_number)%2;
        (*int_number) = (int)((*int_number)/2);
        if(ost == 0){
            numberb[b_counter] = '0';
            b_counter++;
            numberb = realloc(numberb, (strlen(numberb) + 2)*sizeof(char));
            pointer_memory_check(numberb);
        }
        else if(ost == 1){
            numberb[b_counter] = '1';
            b_counter++;
            numberb = realloc(numberb, (strlen(numberb) + 2)*sizeof(char));
            pointer_memory_check(numberb);
        }
    }while(*int_number > 0);
    for(int t = strlen(numberb) - 1; t >=0; t--){
        if(numberb[t] == '0'){
            (*text)[i] = realloc((*text)[i], (strlen((*text)[i]) + 2)*sizeof(char));
            pointer_memory_check((*text)[i]);
            (*text)[i][*source_str_counter] = '0';
            (*source_str_counter)++;
        }
        else if(numberb[t] == '1'){
            (*text)[i] = realloc((*text)[i],(strlen((*text)[i]) + 2)*sizeof(char));
            pointer_memory_check((*text)[i]);
            (*text)[i][*source_str_counter] = '1';
            (*source_str_counter)++;
        }
    }
    free(numberb);
    *number_length = 0;
}



int main(){
    int case_number;
    info_output();
    int res = get_option(&case_number);
    switch_case(case_number, res);
    return 0;
}
