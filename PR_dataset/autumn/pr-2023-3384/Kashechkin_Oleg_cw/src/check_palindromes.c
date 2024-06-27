#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_text.h"
#include "check_palindromes.h"

int is_palindrome(char *word)
{
    int len = strlen(word);
    for (int i = 0; i < (len + 1) / 2; i++)
    {
        if (word[i] != word[len - 1 - i])
        {
            return 0;
        }
    }
    return 1;
}

void check_palindromes(Text text)
{
    for (int i = 0; i < text.sentence_count; i++)
    {
        int sentence_palindromes = 0;
        int count_palindromes = 0;
        char *sentence = text.sentences[i].sentence;
        int count_words_in_sentens = 0;
        char *word = strtok(sentence, " ,.");
        
        while (word != NULL)
        {
            count_words_in_sentens++;
            if (is_palindrome(word))
            {
                count_palindromes++;
            }
            word = strtok(NULL, " ,.");
        }

        if (count_words_in_sentens == count_palindromes)
        {
            printf("Палиндромы на месте!\n");
        }
        else if (count_palindromes == 0)
        {
            printf("Кто-то потерял все палиндромы.\n");
        }
        else
        {
            printf("Чего-то не хватает.\n");
        }
    }
}