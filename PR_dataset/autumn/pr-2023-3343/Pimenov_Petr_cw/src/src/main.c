#include <locale.h>
#include <stdlib.h>

#include "io.h"
#include "data.h"
#include "text_processing.h"
#include "memory.h"
#include "config.h"

void processOption(int option);

int main()
{
    setlocale(LC_CTYPE, "");
    writeString(INFO);
    int option = readInt();
    switch (option)
    {
    case 0:;
    case 1:;
    case 2:;
    case 3:;
    case 4:;
    case 9:;
        processOption(option);
        break;

    case 5:;
        writeString(HELP_0);
        writeString(HELP_1);
        writeString(HELP_2);
        writeString(HELP_3);
        writeString(HELP_4);
        writeString(HELP_5);
        writeString(HELP_6);
        break;

    default:;
        writeError(L"Invalid option.");
        break;
    }
    return 0;
}

void processOption(int option)
{
    Text text;
    switch (option)
    {
    case 0:;
        text = readText();
        if (text.data == NULL)
        {
            writeError(L"Memory allocation error.");
            return;
        }
        text = preCheckFormatting(text);
        if (isCorrect(text))
        {
            text = basicFormatting(text);
        }
        else
        {
            writeError(L"Invalid input.");
            break;
        }
        writeText(text);
        break;

    case 1:;
        text = readText();
        if (text.data == NULL)
        {
            writeError(L"Memory allocation error.");
            return;
        }
        text = preCheckFormatting(text);
        if (isCorrect(text))
        {
            text = basicFormatting(text);
        }
        else
        {
            writeError(L"Invalid input.");
            break;
        }
        size_t size;
        WordCount *counts = countWords(text, &size);
        writeWordCounts(counts, size);
        freeWordCounts(counts, size);
        free(counts);
        break;

    case 2:;
        text = readText();
        if (text.data == NULL)
        {
            writeError(L"Memory allocation error.");
            return;
        }
        text = preCheckFormatting(text);
        if (isCorrect(text))
        {
            text = basicFormatting(text);
        }
        else
        {
            writeError(L"Invalid input.");
            break;
        }
        text = replaceNotChars(text);
        writeText(text);
        break;

    case 3:;
        text = readText();
        if (text.data == NULL)
        {
            writeError(L"Memory allocation error.");
            return;
        }
        text = preCheckFormatting(text);
        if (isCorrect(text))
        {
            text = basicFormatting(text);
        }
        else
        {
            writeError(L"Invalid input.");
            break;
        }
        text = sortByLatinCount(text);
        writeText(text);
        break;

    case 4:;
        text = readText();
        if (text.data == NULL)
        {
            writeError(L"Memory allocation error.");
            return;
        }
        text = preCheckFormatting(text);
        if (isCorrect(text))
        {
            text = basicFormatting(text);
        }
        else
        {
            writeError(L"Invalid input.");
            break;
        }
        text = removeSentencesWithoutSpecial(text);
        writeText(text);
        break;
    case 9:;
        wchar_t *src = readString();
        text = readText();
        if (text.data == NULL)
        {
            writeError(L"Memory allocation error.");
            return;
        }
        text = preCheckFormatting(text);
        if (isCorrect(text))
        {
            text = basicFormatting(text);
        }
        else
        {
            writeError(L"Invalid input.");
            break;
        }
        Text newText = filterByString(text, src);
        writeText(newText);
        freeText(newText);
        free(src);
        break;
    default:;
        break;
    }
    freeText(text);
}
