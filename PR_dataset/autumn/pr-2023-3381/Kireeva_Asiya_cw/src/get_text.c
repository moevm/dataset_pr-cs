#include "get_text.h"

void delete_tab(struct Sentence *cur_sent)
{
    while (iswblank(cur_sent->sentence[0]))
    {
        cur_sent->number_of_letters--;
        wcsncpy(cur_sent->sentence, cur_sent->sentence + 1, cur_sent->number_of_letters);
        cur_sent->sentence[cur_sent->number_of_letters] = L'\0';
    }
    cur_sent->sentence[cur_sent->number_of_letters] = L'\0';
}

struct Sentence *get_sentence()
{
    int current_size = ADD_SIZE, counter = 0;
    wchar_t *cur_sentence = (wchar_t *)malloc(sizeof(wchar_t) * current_size);
    wchar_t c;
    do
    {
        if (counter + 2 >= current_size)
        {

            wchar_t *s = (wchar_t *)realloc(cur_sentence, sizeof(wchar_t) * (current_size + ADD_SIZE));
            if (s != NULL)
            {
                cur_sentence = s;
                current_size += ADD_SIZE;
            }
            else
            {
                wprintf(L"Error: Ошибка выделения памяти.\n");
            }
        }
        c = getwchar();
        cur_sentence[counter] = c;
        counter++;
    } while (c != L'.' && c != L'\n');
    if (cur_sentence[counter - 1] == L'\n' && counter > 1)
    {
        cur_sentence[counter - 1] = L'.';
    }
    cur_sentence[counter] = L'\0';
    struct Sentence *sent = (struct Sentence *)calloc(1, sizeof(struct Sentence));
    sent->sentence = cur_sentence;
    sent->number_of_letters = counter;
    return sent;
}

struct Text get_text()
{
    int current_size = ADD_SIZE, counter = 0, flag = 0;
    struct Sentence **cur_text = (struct Sentence **)malloc(sizeof(struct Sentence *) * current_size);
    wchar_t c = getwchar();
    while (1)
    {
        struct Sentence *sent = get_sentence();
        if (counter + 2 >= current_size)
        {
            struct Sentence **s = (struct Sentence **)realloc(cur_text, sizeof(struct Sentence *) * (current_size + ADD_SIZE));
            if (s != NULL)
            {
                cur_text = s;
                current_size += ADD_SIZE;
            }
            else
            {
                wprintf(L"Error: Ошибка выделения памяти.\n");
            }
        }
        if (sent->sentence[0] == L'\n')
        {
            free(sent->sentence);
            free(sent);
            flag++;
            if (flag == 2)
            {
                break;
            }
        }
        else
        {
            flag = 0;
            if (sent->sentence[0] == '.')
            {
                free(sent->sentence);
                free(sent);
                continue;
            }
            if (sent->number_of_letters != 1)
            {
                delete_tab(sent);
            }
            int fl = 1;
            for (int i = 0; i < counter; i++)
            {
                if (wcscasecmp(sent->sentence, cur_text[i]->sentence) == 0)
                {
                    fl = 0;
                    break;
                }
            }
            if (fl)
            {
                cur_text[counter] = sent;
                counter++;
            }
            else
            {
                free(sent->sentence);
                free(sent);
            }
        }
    }
    struct Text text;
    text.text = cur_text;
    text.number_of_sentences = counter;
    if (text.number_of_sentences == 0 || (text.number_of_sentences == 1 && text.text[0]->sentence[0] == L'.'))
    {
        wprintf(L"Error: Пользователь ничего не ввел.\n");
        exit(0);
    }
    else
    {
        struct Sentence **s = (struct Sentence **)realloc(text.text, sizeof(struct Sentence *) * counter);
        if (s != NULL)
        {
            text.text = s;
        }
        else
        {
            wprintf(L"Error: Ошибка выделения памяти.\n");
            free(text.text);
        }
    }
    return text;
}