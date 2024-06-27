#include "palindrom_processing.h"

// Function 1
void check_text_on_palindromes(int *err)
{
    if (*err) return;
    Text *text = Text_read(err);
    if (*err) return;
    text = basic_processing(text, err);
    if (*err) return;
    for (size_t i = 0; i < text->size; ++i)
    {
        Sentence *new_sentence = Sentence_copy(text->sentences[i], err);
        if (*err) return;

        int status_of_sentence = check_sentence_on_palindromes(new_sentence);
        if (status_of_sentence == 2)
            wprintf(L"Палиндромы на месте!\n");
        else if (status_of_sentence == 1)
            wprintf(L"Чего-то не хватает.\n");
        else
            wprintf(L"Кто-то потерял все палиндромы.\n");

        Sentence_delete(&new_sentence);
    }
    Text_delete(&text);
}

// Check sentence on palindroms and return:
// 2 - all words are palindroms
// 1 - some words are palindroms
// 0 - no palindroms in sentence
int check_sentence_on_palindromes(Sentence *sentence)
{
    if (sentence == NULL) return 0;
    bool was_palindrome = false;
    bool all_palindromes = true;
    wchar_t *buffer;
    wchar_t *split = wcstok(sentence->sentence, DELIMITERS, &buffer);
    while (split != NULL)
    {
        if (is_palindrome(split))
            was_palindrome = true;
        else
            all_palindromes = false;

        split = wcstok(NULL, DELIMITERS, &buffer);
    }

    return was_palindrome + all_palindromes;
}

// Check word if it's palindrome or not
bool is_palindrome(wchar_t *word)
{
    wchar_t *left_ptr = word, *right_ptr = word + wcslen(word) - 1;

    while (left_ptr <= right_ptr)
    {
        if (*left_ptr != *right_ptr)
            return false;

        left_ptr++;
        right_ptr--;
    }

    return true;
}