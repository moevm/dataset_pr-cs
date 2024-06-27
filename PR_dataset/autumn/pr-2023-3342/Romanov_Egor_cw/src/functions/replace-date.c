#include "../headers/replace-date.h"

wchar_t *find_year(struct Sentence sentence, wchar_t *month){
    wchar_t *year=malloc(sizeof(wchar_t)*6);
    for (size_t i =0;i<sentence.quantity_of_words;i++){
        if (wcsstr(sentence.words[i].word, month)){
            year = sentence.words[i+1].word;
            break;
        }
    }
    year[wcslen(year)]=L'.';
    year[wcslen(year)]=L'\0';
    return year;
}
wchar_t *find_day(struct Sentence sentence, wchar_t *month){
    wchar_t *day = malloc(sizeof(wchar_t) *3);
    int len;
    for (size_t i =0;i<sentence.quantity_of_words;i++){
        if (wcsstr(sentence.words[i].word, month)){
            day = sentence.words[i-1].word;
            len = wcslen(sentence.words[i-1].word);
            break;
        }
    }
    if (len ==1){
        wchar_t first_number_of_date = day[0];
        day[0] = L'0';
        day[1] = first_number_of_date;
    }
    day[2] = L'\0';
    return day;
}

wchar_t *month_to_num(wchar_t *month, wchar_t **months){
    wchar_t *num_of_month = malloc(sizeof(wchar_t)*5);
    num_of_month[0] = L'/';
    num_of_month[3] = L'/';
    for(size_t i =0; i<12;i++){
        if (wcsstr(months[i],month)){
            if (i<9){

                num_of_month[1] = L'0';
                num_of_month[2] = (wchar_t)(i+49);
            }
            else if (i==9){
                num_of_month[1] = L'1';
                num_of_month[2] = L'0';
            }
            else {
                num_of_month[1] = L'1';
                
                num_of_month[2] = (wchar_t)(39+i);
            }
        }
    }
    num_of_month[4] = L'\0';
    return num_of_month;
}

int find_start_of_date(struct Sentence sentence, wchar_t *month){
    int symbols_between_month_and_start_of_date=1;
    int month_index = wcsstr(sentence.sentence, month) - sentence.sentence;
    int stop_skip_space_flag = 0;
    int step =0;
    while(step<2){
        if (sentence.sentence[month_index-symbols_between_month_and_start_of_date] == L' ' && !stop_skip_space_flag){
            symbols_between_month_and_start_of_date++;
        }
        else if (iswdigit(sentence.sentence[month_index - symbols_between_month_and_start_of_date])){
            step++;
            symbols_between_month_and_start_of_date++;
            stop_skip_space_flag = 1;
        }
        else break;

    }
    return month_index - symbols_between_month_and_start_of_date + 1;

}

void replace(struct Sentence sentence){
    setlocale(LC_ALL, "");
    wchar_t *months[12] = {
        L"января",
        L"февраля",
        L"марта",
        L"апреля",
        L"мая",
        L"июня",
        L"июля",
        L"августа",
        L"сентября",
        L"октября",
        L"ноября",
        L"декабря",
    };
    wchar_t *start = wcsstr(sentence.sentence, L" г.");
    wchar_t *date_in_ordering_format=malloc(sizeof(wchar_t)*100);
    if (start != NULL){
        wchar_t *year;
        wchar_t *day;
        wchar_t *month;
        for (size_t i =0;i<12; i++){
            wchar_t *start2 = wcsstr(sentence.sentence, months[i]);
            if (start2 != NULL){
                month = month_to_num(months[i], months);
                year = find_year(sentence, months[i]);
                day = find_day(sentence, months[i]);

                date_in_ordering_format = realloc(date_in_ordering_format, sizeof(wchar_t)*(wcslen(day)+wcslen(month)+wcslen(year)));
                date_in_ordering_format = wcscat(date_in_ordering_format, day);
                date_in_ordering_format = wcscat(date_in_ordering_format, month);
                date_in_ordering_format = wcscat(date_in_ordering_format, year);

                int start_of_date_index = find_start_of_date(sentence, months[i]);
                sentence.sentence[start_of_date_index] = L'\0';
                sentence.sentence = wcscat(sentence.sentence, date_in_ordering_format);
                // free(date_in_ordering_format);
                // free(day);
                // free(year);
                // free(month);
            }
        }
    }
}

void replace_date(struct Text text){
    text = return_reworked_text(text);
    for (size_t i =0;i<text.quantity_of_sentences;i++){
        replace(text.sentences[i]);
    }
    output(text);
}