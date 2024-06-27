#include "myfunc.h"
#include "mysupport.h"
#include "myinout.h"

void f1(Text* text) {
    time_t t = time(NULL);
    int cur_min = ((long int) t / 60) % (60 * 24); // current minutes

    int hour = 0;
    int minute = 0;

    for (int i = 0; i < text->count; ++i) {
        for (int j = 0; j < text->sentence[i].count; ++j) {
            if (text->sentence[i].symbol[j] == L':') {
                if (!(mygethour(&(text->sentence[i]), j, &hour) && mygetminute(&(text->sentence[i]), j, &minute))) {
					hour = 0;
					minute = 0;
                    continue;
                }
                
                minute += hour * 60;
                
                int diff = minute - cur_min;
                diff *= (diff > 0) ? 1 : -1; 
                
                printf1(j, diff);

                hour = 0;
                minute = 0;
            }
        }
    }
}

void f2(Text* text) {
    int is_error = 0;

    for (int i = 0; i < text->count; ++i) {
        Sentence sentence;
        sentence.count = 0;
        sentence.symbol = (wchar_t*) malloc(1 * sizeof(wchar_t));

        if (sentence.symbol == NULL) {
            printallocerror("func_2", "one symbol", "malloc");
            is_error = 1;
            break;
        }

        for (int j = 0; j < text->sentence[i].count; ++j) {
            if (!myisupper(text->sentence[i].symbol[j])) {
                sentence.symbol[sentence.count] = text->sentence[i].symbol[j];
                sentence.count++;
                sentence.symbol = (wchar_t*) realloc(sentence.symbol, (sentence.count + 1) * sizeof(wchar_t));

                if (sentence.symbol == NULL) {
                    printallocerror("func_2", "symbol", "realloc");
                    is_error = 1;
                    break;
                }
            }
        }

        if (is_error) {
            myfreesentence(&sentence);
            break;
        }

        myfreesentence(&(text->sentence[i]));
        text->sentence[i].count = sentence.count;
        text->sentence[i].symbol = (wchar_t*) malloc((sentence.count + 1) * sizeof(wchar_t));

        if (text->sentence[i].symbol == NULL) {
            printallocerror("func_2", "symbol", "malloc");
            is_error = 1;
            break;
        }

        for (int j = 0; j < sentence.count; ++j) {
            text->sentence[i].symbol[j] = sentence.symbol[j];
        }

        myfreesentence(&sentence);
    }


    if (is_error) {
        myfreetext(text);
        exit(1);
    }
}

void f3(Text* text) {
    qsort(text->sentence, text->count, sizeof(Sentence), compare);
}

void f4(Text* text) {
    for (int i = text->count - 1; i > 0; --i) {
        int is_delete = 1;

        for (int j = 0; j < text->sentence[i].count; ++j) {
            int c = text->sentence[i].symbol[j];
            if (c == L'№' || c == L'*' || c == L'$' || c == L'#' || c == L'@') {
                is_delete = 0;
            }
        }

        if (is_delete) {
            myfreesentence(&(text->sentence[i]));
            for (int j = i; j < text->count - 1; ++j) {
                text->sentence[j] = text->sentence[j + 1];
            }
            text->count--;
            text->sentence = (Sentence*) realloc(text->sentence, (text->count + 1) * sizeof(Sentence));

            if (text->sentence == NULL) {
                printallocerror("func_4", "sentence", "realloc");
                myfreetext(text);
                exit(1);
            }
        }
    }
}

void f9(Text* text) {
    int is_error = 0;

    wchar_t* temp = (wchar_t*) malloc(30 * sizeof(wchar_t));
    temp[0] = L'\0';
    
    int is_find = 0;
    

    for (int i = 0; i < text->count; ++i) {
        int maxc = text->sentence[i].count;
        wchar_t* result = (wchar_t*) malloc(maxc * sizeof(wchar_t));
        int k = 0;
        int t = 0;
        for (int j = 0; j < text->sentence[i].count; ++j) {
            if (iswalpha(text->sentence[i].symbol[j])) {

                if (iswupper(text->sentence[i].symbol[j])) {
                    temp[k] = towlower(text->sentence[i].symbol[j]);
                } else {
                    temp[k] = text->sentence[i].symbol[j];
                }
                k++;
                temp[k] = L'\0';

                result[t] = text->sentence[i].symbol[j];
                t++;
                
                is_find = 1;
            } else {
                if (is_find) {
                    if (wcscmp(temp, L"smile") == 0) {
                        maxc += 4;
                        result = (wchar_t*) realloc(result, maxc * sizeof(wchar_t));
                        result[t++] = L' ';
                        result[t++] = L':';
                        result[t++] = L'=';
                        result[t++] = L')';
                    } 

                    free(temp);
                    wchar_t* temp = (wchar_t*) malloc(30 * sizeof(wchar_t));
                    k = 0;
                    temp[0] = L'\0';

                    is_find = 0;
                }

                result[t] = text->sentence[i].symbol[j];
                t++;

            }
        }

        myfreesentence(&(text->sentence[i]));
        text->sentence[i].count = t;
        text->sentence[i].symbol = (wchar_t*) malloc((t + 1) * sizeof(wchar_t));

        if (text->sentence[i].symbol == NULL) {
            printallocerror("func_9", "symbol", "malloc");
            is_error = 1;
            break;
        }

        for (int j = 0; j < t; ++j) {
            text->sentence[i].symbol[j] = result[j];
        }

        free(result);
        
    }
}