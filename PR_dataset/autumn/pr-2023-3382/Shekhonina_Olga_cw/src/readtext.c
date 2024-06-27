#include "readtext.h"

Sentence* readsent() {
    int LEN_SENT = 100;
    wchar_t now;
    wchar_t past;
    Sentence* sentence = (Sentence*)malloc(sizeof(Sentence));
    wchar_t* ptr_sent = (wchar_t*)malloc(LEN_SENT*sizeof(wchar_t));
    sentence->len_sent = 0;
    now = getwchar();
    while(now == L' ' || now == L'\t' || now == L'\n') {
        past = now;
        now = getwchar();
        if(now == L'\n' && past == L'\n') {
            return NULL;
        }
    }
    int i = 0;
    while(1) {
        if(sentence->len_sent >= LEN_SENT) {
            LEN_SENT = LEN_SENT + STEP;
            wchar_t* new_ptr_sent = (wchar_t*)realloc(ptr_sent, LEN_SENT*sizeof(wchar_t));
            if(new_ptr_sent == NULL) {
                wprintf(L"Error"); //что-то написать
                free(ptr_sent);
                break;
            }else {
                ptr_sent = new_ptr_sent;
            }
        }
        ptr_sent[i] = now;
        sentence->len_sent++;
        if(now == L'.'){
            ptr_sent[i+1] = L'\0';
            break;
        }
        past = now;
        now = getwchar();
        i++;
    }
    sentence->sentence = ptr_sent;
    return sentence;
}

Text* readtext() {
    int NUM_SENT = 100;
    Text* text = (Text*)malloc(sizeof(Text));
    text->count_sent = 0;
    Sentence** ptr_text = (Sentence**)malloc(NUM_SENT*sizeof(Sentence*));
    DateArray* arr1 = (DateArray*)malloc(sizeof(DateArray));
    arr1->size = 0;
    arr1->capacity = 20;
    Date** dates1 = (Date**)malloc(20*sizeof(Date*));
    arr1->arr = dates1;
    text->slash_dates = arr1;
    DateArray* arr2 = (DateArray*)malloc(sizeof(DateArray));
    arr2->size = 0;
    arr2->capacity = 20;
    Date** dates2 = (Date**)malloc(20*sizeof(Date*));
    arr2->arr = dates2;
    text->dash_dates = arr2;
    DateArray* arr3 = (DateArray*)malloc(sizeof(DateArray));
    arr3->size = 0;
    arr3->capacity = 20;
    Date** dates3 = (Date**)malloc(20*sizeof(Date*));
    arr3->arr = dates3;
    text->space_dates = arr3;
    int i = 0;
    while(1) {
        if(text->count_sent >= NUM_SENT) {
            NUM_SENT = NUM_SENT + STEP;
            Sentence** new_ptr_text = (Sentence**)realloc(ptr_text, NUM_SENT*sizeof(Sentence*));
            if(new_ptr_text == NULL) {
                wprintf(L"Error:"); //что-то написать
                free(ptr_text);
                break;
            } else{
                ptr_text = new_ptr_text;
            }
        }
        Sentence* buf = readsent();
        if(buf==NULL){
            break;
        }
        ptr_text[i] = buf;
        text->count_sent++;
        i++;
    }
    text->pr_sent = ptr_text;
    return text;
}
