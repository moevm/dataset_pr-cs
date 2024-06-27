#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

#include "text_processing.h"
#include "data.h"
#include "config.h"
#include "util.h"
#include "memory.h"

int isCorrect(Text text)
{
    if (text.length == 0)
    {
        return 0;
    }
    for (size_t i = 0; i < text.length; ++i)
    {
        Sentence sentence = text.data[i];
        if (!(sentenceEndCheck(sentence) && isNotBlank(sentence)))
        {
            return 0;
        }
    }

    return 1;
}

int textEndIsSentenceEnd()
{
    return wcsstr(SENTENCE_ENDS, TEXT_END) != NULL;
}

int sentenceEndCheck(Sentence sentence)
{
    int result = 0;
    wchar_t *last;
    last = wcspbrk(sentence.data, SENTENCE_ENDS);
    while (last != NULL)
    {
        result += 1;
        last = wcspbrk(last + 1, SENTENCE_ENDS);
    }
    return result == 1;
}

int isNotBlank(Sentence sentence)
{
    wchar_t *delimiters = getWordDelimiters();
    wchar_t *src = wcsdup(sentence.data);
    wchar_t *lex;
    wchar_t *last;
    lex = wcstok(src, delimiters, &last);
    free(delimiters);
    free(src);
    return lex != NULL;
}

Text basicFormatting(Text text)
{
    for (size_t i = 0; i < text.length; ++i)
    {
        removeLeadSpaces(&text.data[i]);
    }
    size_t newSize = 0;
    for (size_t h = 0; h < text.length; ++h)
    {
        int res = 0;
        for (size_t d = 0; d < h; ++d)
        {
            if (wcscmp(text.data[h].data, text.data[d].data) == 0)
            {
                res++;
                freeSentence(text.data[h]);
            }
        }
        if (res == 0)
        {
            text.data[newSize++] = text.data[h];
        }
    }
    text.length = newSize;
    return text;
}

Text preCheckFormatting(Text text)
{
    Sentence *lastSentence = &text.data[text.length - 1];
    wchar_t *endLocation = wcsstr(lastSentence->data, TEXT_END);
    if (endLocation != NULL && !textEndIsSentenceEnd())
    {
        endLocation[0] = SENTENCE_ENDS[0];
        for (size_t i = 1; i < wcslen(TEXT_END); ++i)
        {
            lastSentence->length--;
            endLocation[i] = L'\0';
        }
    }
    if (!isNotBlank(text.data[text.length - 1]))
    {
        text.length--;
        freeSentence(text.data[text.length]);
    }
    return text;
}

void removeLeadSpaces(Sentence *sentence)
{
    wchar_t *data = sentence->data;
    size_t i = 0;
    while (iswspace(data[i]))
    {
        i++;
    }
    wchar_t *start = &(sentence->data[i]);
    sentence->length -= i;
    wmemmove(data, start, wcslen(start) + 1);
}

WordCount *countWords(Text text, size_t *resultSize)
{
    WordCount *counts = (WordCount *)malloc(1 * sizeof(WordCount));
    size_t countsSize = 0;
    wchar_t *delimiters = getWordDelimiters();
    for (size_t i = 0; i < text.length; ++i)
    {
        wchar_t *src = wcsdup(text.data[i].data);
        wchar_t *lex;
        wchar_t *last;
        lex = wcstok(src, delimiters, &last);
        while (lex != NULL)
        {
            WordCount *result = bsearch(lex, counts, countsSize, sizeof(WordCount), compareWordCountsBsearch);
            if (result != NULL)
            {
                result->count++;
            }
            else
            {
                WordCount current = {wcsdup(lex), 1};
                counts = (WordCount *)realloc(counts, (countsSize + 1) * sizeof(WordCount));
                counts[countsSize++] = current;
            }
            qsort(counts, countsSize, sizeof(WordCount), compareWordCountsQsort);
            lex = wcstok(NULL, delimiters, &last);
        }
        free(src);
    }
    free(delimiters);
    *resultSize = countsSize;
    return counts;
}

Text sortByLatinCount(Text text)
{
    qsort(text.data, text.length, sizeof(Sentence), compareSortByLatinQsort);
    return text;
}

Text replaceNotChars(Text text)
{
    for (size_t i = 0; i < text.length; ++i)
    {
        Sentence sentence = text.data[i];
        size_t newSizeMax = 1;
        for (size_t j = 0; j < sentence.length; ++j)
        {
            if (iswalpha(sentence.data[j]))
            {
                newSizeMax += 1;
            }
            else
            {
                newSizeMax += 11;
            }
        }

        wchar_t *newData = (wchar_t *)calloc(newSizeMax, sizeof(wchar_t));
        size_t charsWritten = 0;
        for (size_t h = 0; h < sentence.length; ++h)
        {
            wchar_t chr = sentence.data[h];
            if (iswalpha(chr))
            {
                charsWritten += swprintf(newData + charsWritten, newSizeMax - charsWritten, L"%lc", chr);
            }
            else
            {
                charsWritten += swprintf(newData + charsWritten, newSizeMax - charsWritten, L"%d", chr);
            }
        }
        freeSentence(sentence);
        size_t newSize = wcslen(newData);
        sentence.data = newData;
        sentence.length = newSize;
        text.data[i] = sentence;
    }
    return text;
}

Text removeSentencesWithoutSpecial(Text text)
{
    size_t newSize = 0;
    for (size_t h = 0; h < text.length; ++h)
    {
        if (wcspbrk(text.data[h].data, SPECIAL_CHARS) != NULL && !hasUppercaseLetters(text.data[h]))
        {
            freeSentence(text.data[h]);
        }
        else
        {
            text.data[newSize++] = text.data[h];
        }
    }
    text.length = newSize;
    return text;
}

Text filterByString(Text text, wchar_t *src)
{
    wchar_t *newSrc = wcsdup(src);
    for (size_t i = 0; i < wcslen(newSrc); ++i)
    {
        newSrc[i] = towlower(newSrc[i]);
    }
    Text newText;
    newText.data = (Sentence *)malloc(1 * sizeof(Sentence));
    newText.length = 0;
    size_t newSize = 0;
    wchar_t *wordDelims = getWordDelimiters();
    for (size_t i = 0; i < text.length; ++i)
    {
        size_t sentenceWordsSize;
        wchar_t **sentenceWords = getWords(text.data[i].data, wordDelims, &sentenceWordsSize);
        size_t compared = 0;
        for (size_t k = 0; k < sentenceWordsSize; ++k)
        {
            wchar_t *searchFor = (wchar_t *)calloc(wcslen(sentenceWords[k]) + 3, sizeof(wchar_t));
            wcscat(searchFor, L" ");
            wcscat(searchFor, sentenceWords[k]);
            wcscat(searchFor, L" ");
            searchFor[wcslen(sentenceWords[k]) + 2] = L'\0';
            if (wcsstr(newSrc, searchFor) != NULL || wcsstr(newSrc, sentenceWords[k]) != NULL)
            {
                compared++;
            }
        }
        if (compared == sentenceWordsSize)
        {
            Sentence newSentence;
            newSentence.data = wcsdup(text.data[i].data);
            newSentence.length = text.data[i].length;
            newText.data[newSize++] = newSentence;
            newText.data = (Sentence *)realloc(newText.data, (newSize + 1) * sizeof(Sentence));
        }
    }
    newText.length = newSize;
    free(newSrc);
    free(wordDelims);
    return newText;
}

wchar_t **getWords(wchar_t *src, wchar_t *delims, size_t *nsize)
{

    wchar_t **words = (wchar_t **)malloc(1 * sizeof(wchar_t *));
    size_t wordsSize = 0;
    wchar_t *newSrc = wcsdup(src);
    wchar_t *last;
    wchar_t *lex = wcstok(newSrc, delims, &last);
    while (lex != NULL)
    {
        wchar_t *add = wcsdup(lex);
        for (size_t i = 0; i < wcslen(add); ++i)
        {
            add[i] = towlower(add[i]);
        }
        words[wordsSize++] = add;
        words = (wchar_t **)realloc(words, (wordsSize + 1) * sizeof(wchar_t *));
        lex = wcstok(NULL, delims, &last);
    }
    *nsize = wordsSize;
    free(newSrc);
    return words;
}