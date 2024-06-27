#include <stdio.h>
#include <wchar.h>


double avg_word_len (wchar_t* sent) {
    double words_count = 0;
    double words_len = 0;
    wchar_t* buffer;
    wchar_t sent_cp[wcslen(sent)];
    wcscpy(sent_cp, sent);
    wchar_t* word = wcstok(sent_cp, L" ,", &buffer);

    while (word != NULL)
    {
        words_len += wcslen(word);
        words_count++;
        word = wcstok(NULL, L" ,", &buffer);
    }
    return (double)(words_len/words_count);
}