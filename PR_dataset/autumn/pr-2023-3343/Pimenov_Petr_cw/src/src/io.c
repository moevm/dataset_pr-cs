#include <wchar.h>
#include <stdlib.h>

#include "io.h"
#include "data.h"
#include "config.h"
#include "memory.h"

void writeString(wchar_t *string)
{
    wprintf(L"%ls", string);
}

void writeSentence(Sentence sentence)
{
    wprintf(L"%ls\n", sentence.data, sentence.length);
}

void writeText(Text text)
{
    for (size_t i = 0; i < text.length; ++i)
    {
        writeSentence(text.data[i]);
    }
}

void writeError(wchar_t *cause)
{
    wprintf(L"Error: %ls\n", cause);
}

void writeWordCounts(WordCount *counts, size_t countsSize)
{
    for (size_t i = 0; i < countsSize; ++i)
    {
        wprintf(L"%ls %d\n", counts[i].data, counts[i].count);
    }
}

int readInt()
{
    int input;
    wscanf(L"%d", &input);
    getwchar();
    return input;
}

wchar_t *readString()
{
    size_t size = 0;
    size_t capacity = MEMORY_BLOCK_SIZE;
    wchar_t *data = (wchar_t *)malloc(capacity * sizeof(wchar_t));
    wint_t chr = getwchar();
    while (chr != L'\n' && chr != WEOF)
    {
        data[size++] = chr;
        if (size == capacity - 1)
        {
            capacity += MEMORY_BLOCK_SIZE;
            data = (wchar_t *)realloc(data, capacity * sizeof(wchar_t));
        }
        chr = getwchar();
    }
    data[size] = L'\0';
    return data;
}

Sentence readSentence()
{
    size_t size = 0;
    size_t capacity = MEMORY_BLOCK_SIZE;
    Sentence sentence;
    wchar_t *data = (wchar_t *)malloc(capacity * sizeof(wchar_t));
    wint_t lastChar = getwchar();
    if (lastChar == WEOF || lastChar == L'\0')
    {
        sentence.data = NULL;
        sentence.length = 0;
        return sentence;
    }
    data[size++] = lastChar;
    data[size] = L'\0';
    if (wcschr(SENTENCE_ENDS, lastChar) != NULL || wcsstr(data, TEXT_END) != NULL)
    {
        sentence.data = data;
        sentence.length = size;
        return sentence;
    }
    wint_t currentChar = getwchar();
    while (currentChar != WEOF && currentChar != '\0')
    {
        data[size++] = currentChar;
        data[size] = L'\0';
        if (size == capacity - 1)
        {
            capacity += MEMORY_BLOCK_SIZE;
            data = (wchar_t *)realloc(data, capacity * sizeof(wchar_t));
            if (data == NULL)
            {
                sentence.data = NULL;
                sentence.length = 0;
                return sentence;
            }
        }
        if (wcschr(SENTENCE_ENDS, currentChar) != NULL || wcsstr(data, TEXT_END))
        {
            break;
        }
        lastChar = currentChar;
        currentChar = getwchar();
    }
    sentence.data = data;
    sentence.length = size;
    return sentence;
}

Text readText()
{
    size_t size = 0;
    Sentence *data = (Sentence *)malloc(1 * sizeof(Sentence));
    Text text;
    Sentence sentence = readSentence();
    while (sentence.data != NULL)
    {
        data[size++] = sentence;
        data = (Sentence *)realloc(data, (size + 1) * sizeof(Sentence));
        if (data == NULL)
        {
            freeSentences(data, size);
            text.data = NULL;
            text.length = 0;
            return text;
        }
        if (wcsstr(sentence.data, TEXT_END))
        {
            break;
        }
        sentence = readSentence();
    }
    text.data = data;
    text.length = size;
    return text;
}
