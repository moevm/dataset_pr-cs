#include "processing.h"


Text *initial_processing(Text *text) {
    Text *result = malloc(sizeof(Text));
    result->length = 0; 
    result->sentences = malloc(0);
    
    for(int i = 0; i < text->length; i++) {
        int is_duplicate = 0;
        for(int j = 0; j < result->length; j++) {
            if(!icmp(result->sentences[j].text, text->sentences[i].text)) {
                is_duplicate = 1;
                break;
            }
        }

        if(!is_duplicate) {
            Text_push(result, text->sentences[i].text);
        }
    }

    return result;
}

Text *process_1(Text * text) {

    for(int i = 0; i < text->length; i++) {
        wchar_t *sentence = text->sentences[i].text;
        wchar_t *replaced_sentence = malloc(wcslen(sentence) * 2 * sizeof(wchar_t));
        replaced_sentence[0] = L'\0';
        wcscat(replaced_sentence, sentence);
        replaced_sentence = replaceall(replaced_sentence, L"high noon", L"полдень");
        replaced_sentence = replaceall(replaced_sentence, L"полночь", L"midnight");
        text->sentences[i].text = replaced_sentence;
    }

    return text;
}

Text *process_2(Text * text) {
    int length = 0;
    Date ** dates = malloc(0);
    
    for(int i = 0; i < text->length; i++) {
        wchar_t *sentence = text->sentences[i].text;
        Date ** dates = findshortdates(sentence);
        
        int i = 0;
        while(dates[i] != NULL) {
            dates = realloc(dates, (length + 1) * sizeof(Date *));
            dates[length] = dates[i];
            length++;
        }
    }
    
    qsort(dates, length, sizeof(Date*), datecomp);
    Text * result = malloc(sizeof(Text));

    for(int i = 0; i < length; i++) {
        Text_push(result, dates[i]->string);
    }

    return result;
}

Text *process_3(Text * text) {
    Text * result = malloc(sizeof(Text));
    result->length = 0;
    result->sentences = malloc(0);

    for(int i = 0; i < text->length; i++) {
        wchar_t *sentence = text->sentences[i].text;
        wchar_t *sentence_copy = malloc(sizeof(wchar_t) * wcslen(sentence) + 1);
        memcpy(sentence_copy, sentence, (wcslen(sentence) - 1) * sizeof(wchar_t));
        sentence_copy = trim(sentence_copy, SENTENCE_DELIMITERS);

        wchar_t *ptr;
        wchar_t *token = wcstok(sentence_copy, SENTENCE_DELIMITERS, &ptr);
        wchar_t *start = token;
        wchar_t *end;
        while(token != NULL) {
            end = token; 
            token = wcstok(NULL, SENTENCE_DELIMITERS, &ptr);
        }
        if(icmp(start, end)) {
            Text_push(result, sentence);
        }
    }

    return result;
}

Text *process_4(Text * text) {

    for(int i = 0; i < text->length; i++) {
        wchar_t *sentence = text->sentences[i].text;
        wchar_t *replaced_sentence = replacelongdates(sentence);
        text->sentences[i].text = replaced_sentence;
    }

    return text;
}

Text * split_by_space(wchar_t * s) {
    Text * text = malloc(sizeof(Text));
    wchar_t *str = replace(s, L"^L", L" ");
    str = replace(s, L"^N", L" ");

    wchar_t *ptr;
    wchar_t *token = wcstok(str, ALL_DELIMITERS, &ptr);
    while(token != NULL) {
        if(!isempty(token)) {
            wchar_t *st = malloc(sizeof(wchar_t) * (1 + wcslen(token)));
            st[0] = L'\0';
            wcscat(st, token);
            Text_push(text, st);
        }
        token = wcstok(NULL, ALL_DELIMITERS, &ptr);
    }

    return text;
}

typedef struct {
    int length; 
    int count;
} Foo;

int find_foo(Foo * foo, int count, int key) {
    for(int i = 0; i < count; i++) {
        if(foo[i].length == key) {
            return i;
        }
    }

    return -1;
}

int find_max_count(Foo *foo, int count) {
    int max_count = -1;
    int max_count_len = -1;

    for(int i = 0; i < count; i++) {
        if(foo[i].count > max_count) {
            max_count = foo[i].count; 
            max_count_len = foo[i].length;
        } 
        if((foo[i].count == max_count) && (foo[i].length < max_count_len)) {
            max_count_len = foo[i].length;
        }
    }

    return max_count_len;
}

// Text * process_9(Text * text) {
//     Text * result = malloc(sizeof(Text));
//     result->length = 0;
//     result->sentences = malloc(0);
//     int foo_count = 0;
//     Foo *foo = malloc(0);

//     for(int i = 0; i < text->length; i++) {
//         int len = wcslen(text->sentences[i].text);
//         int idx = find_foo(foo, foo_count, len);

//         if(idx == -1) {
//             foo = realloc(foo, sizeof(Foo) * (foo_count + 1));
//             Foo f = {len, 1};
//             foo[foo_count] = f;
//             foo_count++;
//         } else {
//             foo[idx].count++;
//         }
//     }

//     int len = find_max_count(foo, foo_count);
//     for(int i = 0; i < text->length; i++) {
//         wchar_t * sentence = text->sentences[i].text;
//         if(wcslen(sentence) == len) {
//             Text_push(result, sentence);
//         }
//     }

//     return result;
// }

int sum(wchar_t *text) {
    int s = 0;
    wchar_t *number = malloc(sizeof(wchar_t) * 10);
    int n = 0;

    for(int i = 0; i < wcslen(text); i++) {
        if(iswdigit(text[i])) {
            number[n++] = text[i];
        } else {
            if(n == 0) continue;
            number[n] = L'\0';
            s += parsenum(number);
            for(int j = 0; j < 10; j++) number[j] = '\0';
            n = 0;
        }
    }
    
    return s;
}

Text * process_9(Text * text) {
    Text * result = malloc(sizeof(Text));


    for(int i = 0; i < text->length; i++) {
        wchar_t * sentence = text->sentences[i].text;
        int s = sum(sentence);
        wchar_t *res = malloc(16 * sizeof(wchar_t));
        swprintf(res, 15, L"%d", s);
        
        Text_push(result, res);
    }

    return result;
}