#include "struct_define.h"
#include "headers.h"
#include <stdlib.h>


struct Sentence *get_sentence()
{
    wchar_t ichar;
    wchar_t* sentence;
    int length = 0;
    wchar_t lchar;
    sentence = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
    do
    {
        wchar_t* tmp;
        ichar = getwchar();
        if (length == 0 && (ichar == ' ')){continue;}
        sentence[length] = ichar;
        length++;
        tmp = (wchar_t*)realloc(sentence, (length + 1) * sizeof(wchar_t));
        sentence = tmp;
        if (ichar == '\n' && lchar == '\n'){break;}
        lchar = ichar;
    } while (ichar != L'.');
    sentence[length] = L'\0';
    struct Sentence *returned_sentence = (struct Sentence*) calloc(1, sizeof(struct Sentence));
    returned_sentence -> str = sentence;
    returned_sentence -> len = length;
    return returned_sentence;
};

struct Text get_text()
{
    int length = 0;
    struct Sentence **text = (struct Sentence **)malloc((length + 1) * sizeof(struct Sentence*));
    struct Sentence *sentence;
    while (1)
    {
        struct Sentence **tmp;
        sentence = get_sentence();
        if(sentence->len > 1 && wcscasecmp(sentence->str, L"\n\n")){
            sentence = fix_sentence(sentence);
            text[length] = sentence;
            length++;
            tmp = (struct Sentence **)realloc(text, (length + 1) * sizeof(struct Sentence*));
            text = tmp;
        }
        if (sentence->len > 1 && sentence->str[0] == '\n' && sentence->str[1] == '\n')
        {
            break;
        }
    }
    struct Text returned_text;
    returned_text.text = text;
    returned_text.len = length;
    return returned_text;
}