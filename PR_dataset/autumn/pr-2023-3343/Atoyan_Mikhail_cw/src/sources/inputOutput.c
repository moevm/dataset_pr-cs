#include "../include/inputOutput.h"

int get_command()
{
    int userCommand;
    wscanf(L"%d", &userCommand);
    return userCommand;
}

Text get_text()
{
    Text text;
    text.sentences = malloc(sizeof(Sentence));
    int textSize = 0, textBuffer = 1;
    int nCounter = 0;
    for (;;)
    {
        Sentence tempSentence = get_sentence(&nCounter);
        int equalSentence = 0;
        for (int i = 0; i < textSize; ++i)
        {
            if (wcscasecmp(tempSentence.chars, text.sentences[i].chars) == 0)
            {
                equalSentence = 1;
                break;
            }
        }
        if (nCounter == 2)
            break;
        else
            nCounter = 0;
        if (equalSentence == 1)
            continue;
        wchar_t *tokBuffer;
        if (wcstok(wcsdup(tempSentence.chars), L" ,.", &tokBuffer) == NULL)
        {
            continue;
        }
        text.sentences[textSize++] = tempSentence;
        text.size = textSize;
        if (textSize == textBuffer)
        {
            textBuffer *= 2;
            text.sentences = realloc(text.sentences, sizeof(Sentence) * textBuffer);
        }
    };
    if (text.sentences[0].chars == NULL)
    {
        fwprintf(stderr, L"Error: Incorrect input.\n");
        exit(0);
    }
    return text;
}

Sentence get_sentence(int *nCounter)
{
    Sentence sentence;
    sentence.chars = malloc(sizeof(wchar_t));
    sentence.amofwords = 1;
    int sentenceSize = 0;
    int sentenceBuffer = 1;
    wchar_t tempChar;
    int firstChar = 1;
    do
    {
        tempChar = getwchar();
        if (tempChar == L'\n')
        {
            (*nCounter)++;
            if ((*nCounter) == 2)
            {
                break;
            }
            continue;
        }
        
        if (firstChar && iswspace(tempChar))
        {
            continue;
        }

        firstChar = 0;

        sentence.chars[sentenceSize++] = tempChar;
        if (sentenceSize == sentenceBuffer)
        {
            sentenceBuffer *= 2;
            sentence.chars = realloc(sentence.chars, sizeof(wchar_t) * sentenceBuffer);
        }

        if (tempChar == L' ' || tempChar == L','){
            sentence.amofwords += 1;
        }


    } while (tempChar != L'.');
    sentence.chars[sentenceSize] = L'\0';
    sentence.size = sentenceSize;
    return sentence;
}

wchar_t *get_word(){
    wchar_t* word = malloc(sizeof(wchar_t)*1000);
    wchar_t temp;
    int iterator = 0;
    temp = getwchar();
    while ((temp = getwchar()) != L'\n'){
        word[iterator] = temp;
        iterator++;
    }
    word[iterator] = L'\0';
    return word;
}

void print_text(Text text)
{
    for (int i = 0; i < text.size; i++)
    {
        wprintf(L"%ls\n", text.sentences[i].chars);
    }
    printf("\n");
}