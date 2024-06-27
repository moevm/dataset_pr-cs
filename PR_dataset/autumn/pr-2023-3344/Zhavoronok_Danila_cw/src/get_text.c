#include "get_text.h"
#include <stdlib.h>

int whcar_is_in_range(wchar_t key, wchar_t left_bound, wchar_t right_bound)
{
    return left_bound <= key && key <= right_bound;
}

text *get_text()
{
    text *text = create_text();

    wchar_t *temp = (wchar_t *)malloc(sizeof(wchar_t));

    int endl_count = 0;
    do
    {
        endl_count = 0;
        wchar_t prev_ch = L' ';
        sentence *str = create_sentence();
        do
        {
            *temp = getwchar();
            // wprintf(L"%d\n", *temp);
            if (*temp == L'\n')
                endl_count++;
            else if (prev_ch == L'\n')
                endl_count = 0;

            if ((*temp == L' ' || *temp == L'\t' || *temp == L'\n') && str->length == 0)
                continue;

            append_wchar_to_sentence(str, temp);

            if (whcar_is_in_range(towupper(*temp), L'A', L'Z'))
                str->counter++;

            prev_ch = *temp;
        } while (*temp != L'.' && endl_count != 2);

        int shift = endl_count == 2 ? 2 : 1;
        if (str->length >= shift)
        {
            str->text[str->length - shift] = L'\0';
            str->length -= shift;
        }

        if (find_sentence_in_text(text, str, 0) == NULL && str->length > 0)
        {
            append_text(text, str);
        }
        else
        {
            free_sentence(str);
        }

    } while (endl_count != 2);
    free(temp);

    return text;
}
