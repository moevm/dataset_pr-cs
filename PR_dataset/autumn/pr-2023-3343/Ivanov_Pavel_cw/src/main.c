#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char* str_to_lower(char* sentence){                                             ///service functions--start
    char* result = malloc((strlen(sentence) + 1) * sizeof(char));
    for(size_t i = 0; i < strlen(sentence) + 1; i++){
            result[i] = tolower(sentence[i]);
    }

    return result;
}


int cmp(const void* str1_, const void* str2_){
    char* str1_temp = *((char**) str1_);
    char* str2_temp = *((char**) str2_);

    char* first = malloc((strlen(str1_temp) + 1) * sizeof(char));
    memcpy(first, str1_temp, strlen(str1_temp) + 1);

    size_t len3_str1 = 0, len3_str2 = 0;
    int number_of_word = 0;

    char* tok = strtok(first, " ,\t");

    while(tok != NULL){
        number_of_word++;
        if(number_of_word == 3){
            if(strchr(tok, '.') != NULL){
                tok[strlen(tok) - 1] = '\0';
            }
            len3_str1 = strlen(tok);
            break;
        }
        tok = strtok(NULL, " ,\t");
    }
    if(number_of_word < 3){
        len3_str1 = 3;
    }

    char* second = malloc((strlen(str2_temp) + 1) * sizeof(char));
    memcpy(second, str2_temp, strlen(str2_temp) + 1);

    char* tok2 = strtok(second, " ,\t");
    number_of_word = 0;

    while(tok2 != NULL){
        number_of_word++;
        if(number_of_word == 3){
            if(strchr(tok2, '.') != NULL){
                tok2[strlen(tok2) - 1] = '\0';
            }
            len3_str2 = strlen(tok2);
            break;
        }
        tok2 = strtok(NULL, " ,\t");
    }
    if(number_of_word < 3){
        len3_str2 = 3;
    }

    if(len3_str1 < len3_str2){
        return -1;
    }
    if(len3_str1 > len3_str2){
        return 1;
    }
    return 0;
}


int def_cmp(const void* one_, const void* two_){
    char* one = *(char**)one_;
    char* two = *(char**)two_;

    int digits_one = 0, digits_two = 0;

    for(size_t i = 0; i < strlen(one); i++){
        if((isdigit(one[i]) != 0) && (one[i] != '0')){
            digits_one += (int)one[i];
        }
    }
    for(size_t i = 0; i < strlen(two); i++){
        if((isdigit(two[i]) != 0) && (two[i] != '0')){
            digits_two += (int)two[i];
        }
    }

    if(digits_one < digits_two){
        return -1;
    }
    if(digits_one > digits_two){
        return 1;
    }
    return 0;   
}


char* reverse_str(char* sentence){
    char* reversed = malloc((strlen(sentence) + 1) * sizeof(char));
    size_t ct = 0;
    for(int ch_number = strlen(sentence) - 2; ch_number >= 0; ch_number--){
        reversed[ct++] = sentence[ch_number];
    }
    reversed[ct] = '.';
    reversed[ct + 1] = '\0';

    return reversed;
}                                                                                 ///service functions--end


void def_sort(char** text_in, size_t sentences){
    for(size_t i = 0; i < sentences; i++){
        char** words = malloc(sizeof(char**));

        char* temp = malloc((strlen(text_in[i]) + 1) * sizeof(char));
        memcpy(temp, text_in[i], strlen(text_in[i]) + 1);
        int number_of_word = 0;

        char* tok = strtok(temp, " ,\t");
        while(tok != NULL){
            if(tok[strlen(tok) - 1] == '.'){
                tok[strlen(tok) - 1] = '\0';
            }

            words[number_of_word] = tok;
            number_of_word++;
            words = realloc(words, (number_of_word + 1)*sizeof(char**));
            tok = strtok(NULL, " ,\t");
        }
        qsort(words, number_of_word, sizeof(char**), def_cmp);

        char* new_sentence = malloc(strlen(text_in[i]) + 1);
        size_t ch_number = 0;
        for(size_t i = 0; i < number_of_word; i++){
            for(size_t j = 0; j < strlen(words[i]); j++){
                new_sentence[ch_number++] = words[i][j];
            }
            new_sentence[ch_number++] = ' ';
        }
        new_sentence[ch_number - 1] = '.';
        new_sentence[ch_number] = '\0';
        text_in[i] = new_sentence;
    }
}


void sort_by_len(char** text_in, size_t sentences){
    if(sentences > 1){
        qsort(text_in, sentences, sizeof(char*), cmp);
    }
}


void remove_f_l(char** text_in, size_t* sentences){
    size_t ct = 0;
    for(size_t snt_number = 0; snt_number < *sentences; snt_number++){
        char* last_ch_snt = str_to_lower(reverse_str(text_in[snt_number]));
        char* first_ch_snt = str_to_lower(text_in[snt_number]);
        if(first_ch_snt[0] == last_ch_snt[0]){
            continue;
        }
        text_in[ct++] = text_in[snt_number];
        free(first_ch_snt);
        free(last_ch_snt);
    }
    text_in = (char**)realloc(text_in, ct * sizeof(char**)); ///reduce the size of the proposal array to the required size
    *sentences = ct;
}


void is_palindrome(char** text_in, size_t sentences){
    size_t ct = 0;
    for(size_t snt_number = 0; snt_number < sentences; snt_number++){
        char* without_spaces = malloc((strlen(text_in[snt_number]) + 1) * sizeof(char));

        for(size_t ch_number = 0; ch_number < strlen(text_in[snt_number]); ch_number++){ ///remove spaces
            if(isspace(text_in[snt_number][ch_number]) != 0){
                continue;
            }
            without_spaces[ct++] = text_in[snt_number][ch_number];
        }
        without_spaces[ct] = '\0';
        ct = 0;

        char* sent_one = str_to_lower(without_spaces);
        char* sent_two = str_to_lower(reverse_str(without_spaces));
        if(strcmp(sent_one, sent_two) == 0){
            text_in[snt_number] = realloc(text_in[snt_number], (strlen(text_in[snt_number]) + 20) * sizeof(char));
            strcat(text_in[snt_number], " <Palindrome>");
        }else{
            text_in[snt_number] = realloc(text_in[snt_number], (strlen(text_in[snt_number]) + 30) * sizeof(char));
            strcat(text_in[snt_number], " <Nothing interesting>");
        }
        free(sent_one);
        free(sent_two);
        free(without_spaces);
    }
}


void remove_digits(char** text_in, size_t sentences){
    size_t ct = 0;
    for(size_t snt_number = 0; snt_number < sentences; snt_number++){
        char* temp = text_in[snt_number];
        for(size_t ch_number = 0; ch_number < strlen(temp) + 1; ch_number++){
            if(isdigit(temp[ch_number]) != 0){
                continue;
            }
            text_in[snt_number][ct++] = temp[ch_number]; 
        }
        ct = 0;
    }
}


char** compare_by_symbols(char** text, size_t* sentences){
    char** compared_text = malloc(sizeof(char**));
    size_t* idx_to_del = malloc(sizeof(size_t));
    size_t temp = 0, temp1 = 0;

    for(size_t s1 = 0; s1 < *sentences - 1; s1++){ ///set "flags"
        char* first_sentence = str_to_lower(text[s1]);
        for(size_t s2 = s1 + 1; s2 < *sentences; s2++){
            char* second_sentence = str_to_lower(text[s2]);
            if(strcmp(first_sentence, second_sentence) == 0){
                idx_to_del[temp++] = s2;
                idx_to_del = realloc(idx_to_del, (temp + 1)*sizeof(size_t));
            }
            free(second_sentence);
        }
        free(first_sentence);
    }

    for(size_t s = 0; s < *sentences; s++){ 
        size_t flag = 0;
        for(size_t check = 0; check < temp; check++){
            if(idx_to_del[check] == s){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            compared_text[temp1++] = text[s]; ///temp1 and s so that there are no "spaces" in compared_text
            compared_text = realloc(compared_text, (temp1 + 1) * sizeof(char**));
        }
    }

    *sentences = temp1;
    free(idx_to_del);
    return compared_text;
}


char** text_to_sentences(char* raw_text, size_t* sentences){
    size_t number_of_sentence = 0;

    char** text = malloc(sizeof(char**));

    char* tok = strtok(raw_text, ".");
    while(tok != NULL){
        while(tok[0] == '\n' || tok[0] == ' '  || tok[0] == '\t'){
            tok = memmove(&tok[0], &tok[1], strlen(tok));
        }

        char* tok_with_point = malloc((strlen(tok) + 2) * sizeof(char));
        strcpy(tok_with_point, tok);
        tok_with_point[strlen(tok)] = '.';
        tok_with_point[strlen(tok) + 1] = '\0';
        char* ptr_to_n = strchr(tok_with_point, '\n');
        while(ptr_to_n != NULL){
            *ptr_to_n = ' ';
            ptr_to_n = strchr(tok_with_point, '\n');
        }

        text[number_of_sentence++] = tok_with_point;
        text = realloc(text, (number_of_sentence + 1) * sizeof(char**));
        tok = strtok(NULL, ".");
    }

    *sentences = number_of_sentence;
    return text;
}


char* get_raw_text(int* is_correct){
    char ch;
    char* raw_text = malloc(10*sizeof(char));
    size_t number_of_symbol = 0, has_alpha_or_digit = 0;

    getchar();
    while(strstr(raw_text, "\n\n") == NULL){
        ch = getchar();
        if(isalpha(ch) != 0 || isdigit(ch) != 0){
            has_alpha_or_digit = 1;
        }
        raw_text[number_of_symbol++] = ch;
        raw_text = realloc(raw_text, (number_of_symbol + 2)*sizeof(char));
    }
    raw_text[number_of_symbol - 2] = '\0';

    if(strlen(raw_text) == 0 || has_alpha_or_digit  == 0){
        fprintf(stderr, "Error: Invalid text input\n");
        *is_correct = 0;
    }
    return raw_text;
}

void print_text(char** text, size_t* sentences){
    for(int i = 0; i<*sentences; i++){
        puts(text[i]);
        free(text[i]);
    }
}


int main(){
    printf("Course work for option 4.14, created by Pavel Ivanov.\n");
    
    size_t sentences;
    int action = -1, is_correct = 1;
    scanf("%d", &action);

    switch (action){
        case 0: {
            char* raw_text = get_raw_text(&is_correct);
            if(is_correct == 0) return 0;
            char** sentences_from_raw_text = text_to_sentences(raw_text, &sentences);
            char** text = compare_by_symbols(sentences_from_raw_text, &sentences);

            print_text(text, &sentences);
            free(text);
            free(raw_text);
            free(sentences_from_raw_text); 
            break;
        }
        case 1: {
            char* raw_text = get_raw_text(&is_correct);
            if(is_correct == 0) return 0;
            char** sentences_from_raw_text = text_to_sentences(raw_text, &sentences);
            char** text = compare_by_symbols(sentences_from_raw_text, &sentences);

            remove_digits(text, sentences);

            print_text(text, &sentences);
            free(text);
            free(raw_text);
            free(sentences_from_raw_text); 
            break;
        }
        case 2: {
            char* raw_text = get_raw_text(&is_correct);
            if(is_correct == 0) return 0;
            char** sentences_from_raw_text = text_to_sentences(raw_text, &sentences);
            char** text = compare_by_symbols(sentences_from_raw_text, &sentences);

            is_palindrome(text, sentences);

            print_text(text, &sentences);
            free(text);
            free(raw_text);
            free(sentences_from_raw_text);   
            break;
        }
        case 3: {
            char* raw_text = get_raw_text(&is_correct);
            if(is_correct == 0) return 0;
            char** sentences_from_raw_text = text_to_sentences(raw_text, &sentences);
            char** text = compare_by_symbols(sentences_from_raw_text, &sentences);

            remove_f_l(text, &sentences);

            print_text(text, &sentences);    
            free(text);
            free(raw_text);
            free(sentences_from_raw_text);         
            break;
        }
        case 4: {
            char* raw_text = get_raw_text(&is_correct);
            if(is_correct == 0) return 0;
            char** sentences_from_raw_text = text_to_sentences(raw_text, &sentences);
            char** text = compare_by_symbols(sentences_from_raw_text, &sentences);

            sort_by_len(text, sentences);

            print_text(text, &sentences);    
            free(text);
            free(raw_text);
            free(sentences_from_raw_text);     
            break;
        }
        case 9: {
            char* raw_text = get_raw_text(&is_correct);
            if(is_correct == 0) return 0;
            char** sentences_from_raw_text = text_to_sentences(raw_text, &sentences);
            char** text = compare_by_symbols(sentences_from_raw_text, &sentences);

            def_sort(text, sentences);

            print_text(text, &sentences);    
            free(text);
            free(raw_text);
            free(sentences_from_raw_text);     
            break;
        }        
        case 5:
            printf("0 - Вывод текста после первичной обязательной обработки\n\
                    \r1 - В каждом предложении удалить встречающиеся в нем цифры.\n\
                    \r2 - Для каждого предложения вывести \"Palindrome\", если оно является палиндромом, иначе \"Nothing interesting\".\n \
                    \r3 - Удалить все предложения у которых совпадают первый и последний символ без учета регистра.\n \
                    \r4 - Отсортировать предложения по увеличению длины третьего слова, если третьего слова нет, то его длина считается равной 3.\n \
                    \r5 - Вывод справки о функциях, которые реализует программа.\n");
            break;

        default:
            fprintf(stderr, "Error: Invalid command number value\n");
            break;
    }

    return 0;
}