#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_TO_FIND_SIZE 7
#define REQUIRED_MATCHED_LETTERS 6
#define PROGRAM_INFO "Course work for option 4.13, created by Veronika Maiskaya."
#define TEXT_OUTPUT_INFO "0: Text output after the initial mandatory processing"
#define COUNT_GARBAGE_WORDS_INFO "1: For each sentence, count the number of words 'garbage' in it (case-insensitive). Depending on the quantity, output the following lines: 0 - 'Clean', [1 5] - 'Must be washed', >5 - 'It is a dump'."
#define REPLACE_NUMBERS_INFO "2: Replace all the numbers in the sentences with the entered string."
#define DELETE_UPPERCASE_SENTENCES_INFO "3: Delete all sentences that have three consecutive uppercase letters."
#define SORT_BY_VOWELS_INFO "4: Sort by decreasing the number of words starting with a vowel letter."
#define COMMANDS_INFO "5: Output information about the commands that the program implements."
#define DELETE_MORE_UPPERCASES_INFO "9: Delete sentences with more uppercase letters than the entered string."
#define COMMAND_DOES_NOT_EXIST "This command does not exist."

void printInfo()
{
    puts(PROGRAM_INFO);
}

void errorMsg(const char *error)
{
    printf("Error: %s", error);
    exit(EXIT_FAILURE);
}

void removeLeadingWhitespace(char *sentence)
{
    int leadingWSCount = 0; // WS - Whitespace

    while (isspace(sentence[leadingWSCount]))
        leadingWSCount++;

    if (leadingWSCount != 0)
    {
        strcpy(sentence, sentence + leadingWSCount);
    }
}

void removeChar(char *sentence)
{
    if (strlen(sentence) > 2)
    {
        if (sentence[1] == '\n')
        {
            strcpy(sentence, sentence + 2);
        }
    }
}

void processOneSentence(char ***strings, int *stringsNum, char *oneSentence, int indexChar)
{
    removeLeadingWhitespace(oneSentence);
    if (*stringsNum >= 1)
        removeChar(oneSentence);

    if (*oneSentence != '.' && indexChar > 0)
    {
        *strings = realloc(*strings, (*stringsNum + 1) * sizeof(char *));
        (*strings)[*stringsNum] = oneSentence;
        (*stringsNum)++;
    }
    else
        free(oneSentence);
}

void inputStrings(char ***strings, int *stringsNum)
{
    int flagEnd = 0;

    while (1)
    {
        char *oneSentence = NULL;
        int indexChar = 0;
        int sentenceSize = 2;

        while (1)
        {
            char inputChar = getchar();

            if (indexChar >= sentenceSize - 2)
            {
                sentenceSize *= 2;
                oneSentence = realloc(oneSentence, sentenceSize * sizeof(char));
            }

            if (inputChar == '.')
            {
                oneSentence[indexChar++] = inputChar;
                oneSentence[indexChar] = '\0';
                break;
            }
            else if (inputChar == '\n')
            {
                char nextChar = getchar();
                if (nextChar == '\n')
                {
                    flagEnd = 1;
                    break;
                }
                else
                {
                    oneSentence[indexChar++] = inputChar;
                    oneSentence[indexChar] = '\0';
                    ungetc(nextChar, stdin);
                }
            }
            else
                oneSentence[indexChar++] = inputChar;
        }

        if (oneSentence != NULL)
            processOneSentence(strings, stringsNum, oneSentence, indexChar);

        if (flagEnd == 1)
        {
            if ((*strings)[(*stringsNum) - 1][strlen((*strings)[(*stringsNum) - 1]) - 1] != '.')
                (*strings)[(*stringsNum) - 1][strlen((*strings)[(*stringsNum) - 1]) - 1] = '.';
            break;
        }
    }
}

int areTheyIdentical(char *firstString, char *secondString)
{
    for (int i = 0; i < strlen(firstString) && i < strlen(secondString); i++)
        if (tolower(firstString[i]) != tolower(secondString[i]))
            return 0;

    return 1;
}

void deleteIdentical(char ***strings, int *stringsNum)
{
    for (int i = 0; i < (*stringsNum) - 1; i++)
    {
        for (int j = i + 1; j < (*stringsNum); j++)
        {
            if (areTheyIdentical((*strings)[i], (*strings)[j]))
            {
                free((*strings)[j]);
                for (int k = j; k < (*stringsNum - 1); k++)
                    (*strings)[k] = (*strings)[k + 1];
                (*stringsNum)--;
                (*strings) = realloc((*strings), sizeof(char *) * (*stringsNum));
                j--;
            }
        }
    }
}

void findGarbage(char **strings, int *stringsNum)
{
    char wordToFind[WORD_TO_FIND_SIZE] = "garbage";

    for (int i = 0; i < *stringsNum; i++)
    {
        int matchedLetters = 0;
        int foundWords = 0;
        for (int j = 0; j < strlen(strings[i]); j++)
        {
            if (tolower(strings[i][j]) == wordToFind[matchedLetters])
            {
                if ((matchedLetters == REQUIRED_MATCHED_LETTERS) && (strchr(" .,", strings[i][j + 1])))
                    foundWords++;
                matchedLetters++;
            }
            else if (matchedLetters > 0)
                matchedLetters = 0;
            else
                matchedLetters = 0;
        }
        if (foundWords == 0)
            printf("Clean\n");
        else if ((foundWords <= 5) && (foundWords >= 1))
            printf("Must be washed\n");
        else
            printf("It is a dump\n");
    }
}

void replaceNums(char ***strings, int *stringsNum)
{
    char *replaceString = (*strings)[0];
    int replaceLength = strlen(replaceString);
    replaceString[replaceLength - 1] = '\0';
    replaceLength--;

    for (int i = 1; i < (*stringsNum); i++)
    {
        int originalLength = strlen((*strings)[i]);
        int newStringLength = originalLength;

        for (int j = 0; j < originalLength; j++)
        {
            if (isdigit((*strings)[i][j]))
            {
                newStringLength += replaceLength - 1;
            }
        }

        char *temp = malloc(newStringLength + 1);
        int tempIndex = 0;

        for (int j = 0; j < originalLength; j++)
        {
            if (isdigit((*strings)[i][j]))
            {
                strncpy(temp + tempIndex, replaceString, replaceLength);
                tempIndex += replaceLength;
            }
            else
            {
                temp[tempIndex++] = (*strings)[i][j];
            }
        }

        temp[tempIndex] = '\0';

        free((*strings)[i]);
        (*strings)[i] = temp;
    }

    replaceString[replaceLength] = '.';
}

void deleteThree(char ***strings, int *stringsNum)
{
    for (int i = 0; i < *stringsNum; i++)
    {
        int flag = 0;
        int lenString = strlen((*strings)[i]);
        for (int j = 0; j < lenString; j++)
        {
            if (isupper((*strings)[i][j]))
                flag++;
            else
                flag = 0;
            if (flag == 3)
            {
                free((*strings)[i]);
                for (int k = i; k < (*stringsNum - 1); k++)
                    (*strings)[k] = (*strings)[k + 1];
                (*stringsNum)--;
                (*strings) = realloc((*strings), sizeof(char *) * (*stringsNum));
                i--;
                break;
            }
        }
    }
}

int countVowels(const char *string)
{
    int wordsWowels = 0;
    int newWord = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        if (isalpha(string[i]))
        {
            if (newWord == 0)
            {
                if (strchr("euioaEUIOA", string[i]))
                {
                    wordsWowels++;
                }
                else
                    newWord = 1;
            }
        }
        else
            newWord = 0;
    }
    return wordsWowels;
}

int comparator(const void *firstString, const void *secondString)
{
    const char *strOne = *(const char **)firstString;
    const char *strTwo = *(const char **)secondString;

    int vowelsFirst = countVowels(strOne);
    int vowelsSecond = countVowels(strTwo);

    if (vowelsFirst > vowelsSecond)
        return -1;
    else if (vowelsFirst < vowelsSecond)
        return 1;
    else
        return 0;
}

void sortByVowels(char ***strings, int *stringsNum)
{
    qsort((*strings), (*stringsNum), sizeof(char *), comparator);
}

void printResult(char **strings, int stringsNum)
{
    for (int i = 0; i < stringsNum; i++)
    {
        puts(strings[i]);
    }
}

void countGarbageWords(char ***strings, int *stringsNum)
{
    inputStrings(strings, stringsNum);
    deleteIdentical(strings, stringsNum);
    findGarbage(*strings, stringsNum);
}

void displayTextOutput(char ***strings, int *stringsNum)
{
    inputStrings(strings, stringsNum);
    deleteIdentical(strings, stringsNum);
    printResult(*strings, *stringsNum);
}

void replaceNumbersWithString(char ***strings, int *stringsNum)
{
    inputStrings(strings, stringsNum);
    deleteIdentical(strings, stringsNum);
    replaceNums(strings, stringsNum);
    printResult(*strings, *stringsNum);
}

void deleteSentencesWithThreeUppercase(char ***strings, int *stringsNum)
{
    inputStrings(strings, stringsNum);
    deleteIdentical(strings, stringsNum);
    deleteThree(strings, stringsNum);
    printResult(*strings, *stringsNum);
}

void sortByVowelsCount(char ***strings, int *stringsNum)
{
    inputStrings(strings, stringsNum);
    deleteIdentical(strings, stringsNum);

    sortByVowels(strings, stringsNum);
    printResult(*strings, *stringsNum);
}

void displayProgramCommandsInfo()
{
    puts(TEXT_OUTPUT_INFO);
    puts(COUNT_GARBAGE_WORDS_INFO);
    puts(REPLACE_NUMBERS_INFO);
    puts(DELETE_UPPERCASE_SENTENCES_INFO);
    puts(SORT_BY_VOWELS_INFO);
    puts(COMMANDS_INFO);
    puts(DELETE_MORE_UPPERCASES_INFO);
}

void deleteWithMoreUppercase(char ***strings, int *stringsNum)
{
    char stringToPut[120];
    fgets(stringToPut, 120, stdin);
    int letters = 0;

    for (int i = 0; i < strlen(stringToPut); i++)
    {
        if (isupper(stringToPut[i]))
            letters++;
    }
    inputStrings(strings, stringsNum);
    deleteIdentical(strings, stringsNum);

    for (int i = 0; i < *stringsNum; i++)
    {
        int lettersString = 0;
        for (int j = 0; j < strlen((*strings)[i]); j++)
        {
            if (isupper((*strings)[i][j]))
                lettersString++;
        }
        if (lettersString > letters)
        {
            free((*strings)[i]);
            for (int k = i; k < (*stringsNum - 1); k++)
                (*strings)[k] = (*strings)[k + 1];
            (*stringsNum)--;
            (*strings) = realloc((*strings), sizeof(char *) * (*stringsNum));
            i--;
        }
    }
    printResult(*strings, *stringsNum);
}

void chooseOption(char *optionNum, char ***strings, int *stringsNum)
{
    switch (*optionNum)
    {
    case '0':
        displayTextOutput(strings, stringsNum);
        break;
    case '1':
        countGarbageWords(strings, stringsNum);
        break;
    case '2':
        replaceNumbersWithString(strings, stringsNum);
        break;
    case '3':
        deleteSentencesWithThreeUppercase(strings, stringsNum);
        break;
    case '4':
        sortByVowelsCount(strings, stringsNum);
        break;
    case '5':
        displayProgramCommandsInfo();
        break;
    case '9':
        deleteWithMoreUppercase(strings, stringsNum);
        break;
    default:
        errorMsg(COMMAND_DOES_NOT_EXIST);
    }
}

void inputOptionNum(char *optionNum)
{
    scanf("%c", optionNum);
    char charAfterOption = getchar();
    if (charAfterOption != '\n')
        errorMsg(COMMAND_DOES_NOT_EXIST);
}

void freeMemoryOfStrings(char ***strings, int *stringsNum)
{
    for (int i = 0; i < (*stringsNum); i++)
    {
        free((*strings)[i]);
    }
    free(*strings);
}

int main()
{
    printInfo();

    int stringsNum = 0;
    char **strings = NULL;
    char optionNum;

    inputOptionNum(&optionNum);
    chooseOption(&optionNum, &strings, &stringsNum);
    freeMemoryOfStrings(&strings, &stringsNum);

    return 0;
}
