#include "get_text.h"

struct Sentence *get_str()
{
    wchar_t symbol;
    size_t str_length = 0;
    int max_size = STEP;
    wchar_t *str = (wchar_t *)malloc(sizeof(wchar_t) * max_size);
    do
    {
        if (str_length >= max_size - 2)
        {
            max_size += STEP;
            wchar_t *temp;
            temp = (wchar_t *)realloc(str, sizeof(wchar_t) * max_size);
            if (temp != NULL)
                str = temp;
        }
        symbol = (wchar_t)getwchar();
        str[str_length] = symbol;
        str_length++;
    } while (symbol != L'.' && symbol != L'\n');
    str[str_length] = L'\0';
    struct Sentence *received_str = (struct Sentence *)calloc(1, sizeof(struct Sentence));
    received_str->sentence = str;
    received_str->str_length = str_length;
    return received_str;
}

struct Sentence *delete_trash(struct Sentence *str)
{
    while (iswblank(str->sentence[0]))
    {
        str->str_length--;
        wcsncpy(str->sentence, str->sentence + 1, str->str_length); // here can be overlap
        str->sentence[str->str_length] = L'\0';
    }
    str->words_count = 1;
    for (size_t i = 0; i < str->str_length; i++)
    {
        if (iswblank(str->sentence[i]) || str->sentence[i] == L',')
            str->words_count++;
    }
    if (str->sentence[str->str_length - 1] == L'\n')
        str->sentence[str->str_length - 1] = L'.'; // if '\n' in sentence then comment this
    return str;
}

struct Text get_text()
{
    int max_size = STEP, t_length = 0, end_counter = 0;
    struct Sentence **received_text = (struct Sentence **)malloc(max_size * sizeof(struct Sentence *));
    while (1)
    {
        struct Sentence *received_sentence = get_str();
        if (received_sentence->str_length > 1)
            delete_trash(received_sentence);
        if (t_length >= max_size - 2)
        {
            max_size += STEP;
            struct Sentence **temp;
            temp = (struct Sentence **)realloc(received_text, max_size * sizeof(struct Sentence *));
            if (temp != NULL)
                received_text = temp;
        }
        if (received_sentence->sentence[0] != L'\n')
        {
            int flag = 0;
            for (size_t i = 0; i < t_length; i++)
            {
                if (wcscasecmp(received_sentence->sentence, received_text[i]->sentence) == 0)
                    flag = -1;
            }
            if (received_sentence->str_length == 1 && received_sentence->sentence[0] != L'\n')
                flag = -1;
            if (flag != -1)
            {
                received_text[t_length++] = received_sentence;
            }
            else
            {
                free(received_sentence->sentence);
                free(received_sentence);
            }
            end_counter = 0;
        }
        else
        {
            free(received_sentence->sentence);
            free(received_sentence);
            end_counter++;
            if (end_counter == 2)
            {
                break;
            }
        }
    }
    struct Text text;
    text.text = received_text;
    text.length = t_length;
    return text;
}

void withdraw_text(struct Text txt)
{
    if (txt.length != (size_t)0)
    {
        for (int i = 0; i < txt.length; i++)
        {
            wprintf(L"%ls\n", txt.text[i]->sentence);
            // wprintf(L"%d\n", txt.text[i]->str_length);
        }
    }
    else
    {
        wprintf(L"Error: текст пустой.\n");
    }
}