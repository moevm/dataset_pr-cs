#include "dates.h"

int datecomp(const void *a, const void *b) {
    Date *A = (Date*)a;
    Date *B = (Date*)b;

    return difftime(mktime(B->raw), mktime(A->raw));
}

Date ** findshortdates(wchar_t *str) {
    int length = 0;
    Date **result = malloc(sizeof(Date *));
    wchar_t *ptr;
    wchar_t *token = wcstok(str, SENTENCE_DELIMITERS, &ptr);

    while(token != NULL) {
        char *chartoken = malloc(wcslen(token)); 
        wcstombs(chartoken, token, wcslen(token));
        struct tm *raw = malloc(sizeof(struct tm));

        char *d1 = strptime(chartoken, "%d/%m/%y", raw);
        char *d2 = strptime(chartoken, "%y-%m-%d", raw);

        if((d1 != NULL) || (d2 != NULL)) {
            Date *date = malloc(sizeof(Date));
            date->raw = raw; 
            date->string = token;

            result = realloc(result, (length + 2) * sizeof(Date*));
            result[length] = date;
            length++;
        }

        token = wcstok(NULL, SENTENCE_DELIMITERS, &ptr);
    }

    result[length] = NULL;
    return result; 
}

int islongdate(wchar_t *s) {
    int res = iswdigit(s[0]) &&
    iswdigit(s[1]) &&
    iswspace(s[2]) && 
    iswalpha(s[3]) && 
    iswalpha(s[4]) && 
    iswalpha(s[5]) && 
    iswspace(s[6]) && 
    iswdigit(s[7]) &&
    iswdigit(s[8]) &&
    iswdigit(s[9]) &&
    (iswdigit(s[10]) || !iswalpha(s[10]));

    return res;
}

wchar_t *parsemonth(wchar_t *month) {
    if(wcslen(month) > 3) return NULL;
    wchar_t *months[12] = {L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun", L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec"};
    wchar_t *mon = malloc(sizeof(wchar_t) * 4);
    mon[0] = L'\0';
    wcsncat(mon, month, 3);

    for(int i = 0; i < 12; i++) {
        if(!icmp(mon, months[i])) {
            wchar_t *result = malloc(sizeof(wchar_t) * 3);
            result[0] = L'0' + ((i + 1)/10);
            result[1] = L'0' + ((i + 1)%10);
            result[2] = L'\0';

            return result;
        }
    }

    return NULL;
}

int parsenum(wchar_t *s) {
    char *c = malloc(wcslen(s) + 1);
    wcstombs(c, s, wcslen(s));
    return atoi(c);
}

int isday(wchar_t *s) {
    return parsenum(s) <= 31 && parsenum(s) >= 1;
}

int isyear(wchar_t *s) {
    return parsenum(s) <= 9999 && parsenum(s) >= 1;
}

int ismonth(wchar_t *s) {
    return parsemonth(s) != NULL;
}

wchar_t *replacelongdates(wchar_t *str) {
    wchar_t *result = malloc(sizeof(wchar_t) * (wcslen(str) + 1) * 2);
    result[0] = L'\0';
    wcscat(result, str);
    wchar_t *ptr;
    wchar_t * a = wcstok(str, SENTENCE_DELIMITERS, &ptr);
    wchar_t * b = wcstok(NULL, SENTENCE_DELIMITERS, &ptr);
    wchar_t * c = wcstok(NULL, SENTENCE_DELIMITERS, &ptr);

    while(c != NULL) {

        if(isday(a) && ismonth(b) && isyear(c)) {
            wchar_t *date = malloc((wcslen(a) + wcslen(b) + wcslen(c)) * 2 * sizeof(wchar_t));
            date[0] = L'\0';
            wcscat(date, a);
            wcscat(date, L" ");
            wcscat(date, b); 
            wcscat(date, L" ");
            wcscat(date, c);

            struct tm t = {
                0,0,0,parsenum(a), parsenum(parsemonth(b)) - 1, parsenum(c) - 1900
            };
            t.tm_isdst = 0;

            wchar_t *newdate = malloc(40 * sizeof(wchar_t));
            wcsftime(newdate, 40, L"%d.%m.%Y", &t);

            if(difftime(time(NULL), mktime(&t)) < 0) {
                wcscat(newdate, L" Not");
            }
            wcscat(newdate, L" Happened");
            result = replace(result, date, newdate);
        }

        a = b;
        b = c;
        c = wcstok(NULL,  SENTENCE_DELIMITERS, &ptr);
    }
    // result = realloc(result, (wcslen(result) + 1) * sizeof(wchar_t));
    return result;
}