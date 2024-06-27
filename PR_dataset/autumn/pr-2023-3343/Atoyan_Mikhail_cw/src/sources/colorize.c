#include "../include/colorize.h"

wchar_t *stristr(const wchar_t *String, const wchar_t *Pattern)
{
    wchar_t *pptr, *sptr, *start;

    for (start = (wchar_t *)String; *start != 0; ++start)
    {
        while (((*start != 0) && (towupper(*start) != towupper(*Pattern))))
        {
            ++start;
        }

        if (0 == *start)
            return NULL;

        pptr = (wchar_t *)Pattern;
        sptr = (wchar_t *)start;

        while (towupper(*sptr) == towupper(*pptr))
        {
            sptr++;
            pptr++;

            if (0 == *pptr)
                return (start);
        }
    }

    return NULL;
}

wchar_t *find_second(Sentence sentence)
{
    wchar_t *tmp = malloc(sentence.size * sizeof(wchar_t));
    wcscpy(tmp, sentence.chars);
    wcstok(tmp, L" ,", &tmp);
    wchar_t *result = wcstok(NULL, L" ,.", &tmp);
    if (result == NULL)
    {
        fwprintf(stderr, L"Error: No second word.\n");
        exit(0);
    }
    return result;
}

void print_green(wchar_t *word)
{
    wprintf(L"%ls%ls%ls", GREEN, word, DEFAULT);
}

void print_colorized(Text text)
{
    wchar_t *word = find_second(text.sentences[0]);
    int len = wcslen(word);
    wchar_t buf[len+1];
    for (int i = 0; i < text.size; i++)
    {
        wchar_t *ptr1 = text.sentences[i].chars;
        wchar_t *ptr2 = stristr(text.sentences[i].chars, word);

        if (ptr2 == NULL)
        {
            continue;
        }
        
        while (ptr2 != NULL)
        {
            wcsncpy(buf, ptr2, len);
            buf[len] = L'\0';
            *ptr2 = L'\0';
            wprintf(L"%ls", ptr1);
            print_green(buf);
            ptr1 = ptr2 + len;
            ptr2 = stristr(ptr1, word);
        }
        wprintf(L"%ls\n", ptr1);
    }
}