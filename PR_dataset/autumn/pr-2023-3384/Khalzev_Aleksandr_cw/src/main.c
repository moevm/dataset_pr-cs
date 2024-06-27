#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct Date{
    int day;
    int month;
    int year;
};

int cmp(const void *a, const void *b) {
    struct Date *A = (struct Date *)a;
    struct Date *B = (struct Date *)b;

    if (A->year != B->year) {
        return A->year - B->year;
    } else if (A->month != B->month) {
        return A->month - B->month;
    } else {
        return A->day - B->day;
    }
}

void rm_pv_pr(char **text, int *ntext) {
    int d;
    for (int i = 0; i < *ntext - 1; i++) {
        for (int j = i + 1; j < *ntext;) {
            if(strlen(text[i]) <= strlen(text[j])){
                d = strlen(text[j]);
            } else{
                d = strlen(text[i]);
            }
            if (strncmp(text[i], text[j], d) == 0) {
                free(text[j]);
                for (int k = j; k < *ntext - 1; k++) {
                    text[k] = text[k + 1];
                }
                (*ntext)--;
            } else {
                j++;
            }
        }
    }
}

int str_int(char* str, int len){
    for(int i = 0; i < len; i++)
    {
        if(isdigit(str[i]) == 0){
            return 0;
        }
    }
    return 1;
}

void addDate(struct Date* dates, int* n_dates, int day, int month, int year) {
    dates = realloc(dates, sizeof(struct Date) * (*n_dates + 1));
    dates[*n_dates].day = day;
    dates[*n_dates].month = month;
    dates[*n_dates].year = year;
    (*n_dates)++;
}

char** write_text(int* c_pr) {
    char** text = NULL;
    char* sent = malloc(sizeof(char));
    char el, pr_el = '\0';
    sent[0] = '\0';
    int len_sent = 1, len_txt = 0;

    while (1){
        el = getchar();

        if (pr_el != '.') {
            if (!isspace(el) || len_sent > 1) {
                len_sent++;
                sent = (char *)realloc(sent, sizeof(char) * len_sent);
                sent[len_sent - 2] = el;
                sent[len_sent - 1] = '\0';
            }
        }else{
            text = realloc(text, sizeof(char*) * (len_txt+1));
            text[len_txt] = sent;
            len_txt++;
            if(el != '\n' && el != ' '){
                sent = malloc(2 * sizeof(char));
                sent[0] = el;
                sent[1] = '\0';
                len_sent = 2;
            } else if(el == '\n' || el == ' '){
                sent = malloc(sizeof(char));
                sent[0] = '\0';
                len_sent = 1;
            }
        }

        if (el == '\n' && pr_el == '\n') {
            break;
        }

        pr_el = el;
    }
    *c_pr = len_txt;
    return text;
}

void data(char** text, int c_pr){
    struct Date* dates = NULL;
    int n_dates = 0, ch = 0;
    for(int i = 0; i < c_pr; i++){
        for(size_t j = 10; j < strlen(text[i]); j++){
            if (text[i][j - 4] == 'y' && text[i][j - 7] == 'm' && text[i][j - 10] == 'd' && isdigit(text[i][j])){

                ch++;
                dates = realloc(dates, sizeof(struct Date) * ch);

                char Dstr[3], Mstr[3], Ystr[5];
                strncpy(Dstr, &text[i][j - 9], 2);
                strncpy(Mstr, &text[i][j - 6], 2);
                strncpy(Ystr, &text[i][j - 3], 4);

                Dstr[2] = '\0';
                Mstr[2] = '\0';
                Ystr[4] = '\0';
                int flag = 0;

                if(str_int(Dstr, 2) && str_int(Mstr, 2) && str_int(Ystr, 4)){
                    flag = 1;
                }

                int day = strtol(Dstr, NULL, 10);
                int month = strtol(Mstr, NULL, 10);
                int year = strtol(Ystr, NULL, 10);

                if(month <= 12 && month >= 1 && flag == 1){

                    if(((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (year >= 0)){
                        if(month == 2 && day <= 29 && day >= 1){
                            addDate(dates, &n_dates, day, month, year);
                        } else if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <= 31 && day >= 1){
                            addDate(dates, &n_dates, day, month, year);
                        } else if(day <= 30 && day >= 1){
                            addDate(dates, &n_dates, day, month, year);
                        }

                    } else if(year >= 0){
                        if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <= 31 && day >= 1){
                            addDate(dates, &n_dates, day, month, year);
                        } else if(day <= 30 && day >= 1){
                            addDate(dates, &n_dates, day, month, year);
                        }
                    }
                }
            }
        }
    }

    qsort(dates, n_dates, sizeof(struct Date), cmp);

    for (int i = 0; i < n_dates; ++i) {
        printf("%.2d:%.2d:%.4d\n", dates[i].day, dates[i].month, dates[i].year);
    }
}

void ud_nech_pr(char** text, int len_text) {
    for(int i = 0; i < len_text; i++) {
        int ch_sl = 0;
        for(size_t j = 1; j < strlen(text[i]); j++) {
            if((text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == ':' || text[i][j] == ';') && text[i][j-1] != ' ' && text[i][j-1] != ',' && text[i][j-1] != ':' && text[i][j-1] != ';'){
                ch_sl++;
            } else if(text[i][j] == '.' && text[i][j-1] != ' '){
                ch_sl++;
                if(ch_sl % 2 == 0){
                    printf("%s\n", text[i]);
                }
                break;
            } else if(text[i][j] == '.' && text[i][j-1] == ' '){
                if(ch_sl % 2 == 0){
                    printf("%s\n", text[i]);
                }
                break;
            }
        }
    }
}

void cifr_slov(char** text, int len_text) {
    for (int i = 0; i < len_text; i++) {
        char* sentence = text[i];
        char* word = strtok(sentence, " ");

        while (word) {
            size_t word_length = strlen(word);
            int has_digit = 0;

            for (size_t j = 0; j < word_length; j++) {
                if (isdigit(word[j])) {
                    has_digit = 1;
                    break;
                }
            }

            if (!has_digit) {
                if(word[word_length-1] == '.' || word[word_length-1] == ',' || word[word_length-1] == ':' || word[word_length-1] == ';'){
                    for (size_t j = 0; j < word_length - 2; j++) {
                        word[j] = tolower(word[j]);
                    }
                }else{
                    for (size_t j = 0; j < word_length - 1; j++) {
                        word[j] = tolower(word[j]);
                    }
                }
            }
            printf("%s ", word);
            word = strtok(NULL, " ");
        }

        printf("\n");
    }
}

void up_bkv(char** text, int len) {
    for (int i = 0; i < len; i++) {
        char* sent = text[i];
        int hasUppercase = 0;

        for (int j = 0; sent[j] != '\0'; j++) {
            if (isupper(sent[j])) {
                hasUppercase = 1;
                break;
            }
        }

        if (!hasUppercase) {
            printf("%s\n", sent);
        }
    }
}

void function_help(){
    puts(
            "List of commands:\n"
            "  0 - print text after primary processing.\n"
            "  1 - find all dates in the text and display them in ascending order.\n"
            "  2 - Remove all sentences with an odd number of words.\n"
            "  3 - Convert all words that do not have numbers so that all letters except the last one are capitalized.\n"
            "  4 - Print all sentences that do not have upper letters.\n"
            "  5 - print function help."
        );
}

struct s_word{
    char* bkv;
    int sum;
};

int cmp_1(const void *a, const void *b) {
    struct s_word *A = (struct s_word *)a;
    struct s_word *B = (struct s_word *)b;

    if(A->sum > B->sum) {
        return 1;
    }
    if(A->sum < B->sum){
        return -1;
    }
    return 0;
}

void cifr_slov_sort(char ** text, int len_text){
    for (int i = 0; i < len_text; i++) {
        char* sentence = text[i];
        char* word = strtok(sentence, " ,:.;");
        struct s_word* sent_1 = NULL;
        int size = 0;

        while (word) {
            int sum_word = 0;
            for(size_t j = 0; j < strlen(word); j++){
                if(isdigit(word[j])){
                    int ch = word[j] - '0';
                    sum_word += ch;
                }
            } if (sum_word == 0){
                printf("%s ", word);
            } else{
                size++;
                sent_1 = realloc(sent_1, sizeof(struct s_word) * size);
                sent_1[size - 1].bkv = word;
                sent_1[size - 1].sum = sum_word;
            }
            word = strtok(NULL, " ,.:;");
        }
        if(size != 0){
            qsort(sent_1, size, sizeof(struct s_word), cmp_1);
            for (int i = 0; i < size - 1; ++i) {
                printf("%s ", sent_1[i].bkv);
            }
            printf("%s.\n", sent_1[size - 1].bkv);
        }
    }
}

int main()
{
    printf("Course work for option 4.4, created by Aleksandr Khalzev.\n");

    int n;
    scanf("%i", &n);

    if((n >= 6 || n < 0) && n != 9){
        printf("Error: wrong value of 'n'\n");
        return 0;
    }

    if (n == 5){
        function_help();
        return 0;
    }

    int c_pr = 0;
    char** text;

    text = write_text(&c_pr);
    rm_pv_pr(text, &c_pr);

    if(n == 9){
        cifr_slov_sort(text, c_pr);
    }

    switch (n)
    {
        case 0:
            for(int i = 0; i < c_pr; i++){
                printf("%s\n", text[i]);
            }
            break;
        case 1:
            data(text, c_pr);
            break;
        case 2:
            ud_nech_pr(text, c_pr);
            break;
        case 3:
            cifr_slov(text, c_pr);
            break;
        case 4:
            up_bkv(text, c_pr);
            break;
    }

    free(text);

    return 0;
}
