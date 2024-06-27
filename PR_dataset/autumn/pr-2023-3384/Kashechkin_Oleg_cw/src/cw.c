#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <locale.h>
#include "read_text.h"
#include "remove_duplicate_sentences.h"
#include "general_information.h"
#include "basic_processing.h"
#include "check_palindromes.h"
#include "replace_special_symbols.h"
#include "sort_by_latin_letters.h"
#include "remove_mixed_alphabet_sentences.h"

int main()
{
    puts("Course work for option 5.10, created by Oleg Kashechkin.");
    int trigger;
    Text text;
    Text filter_text;
    scanf("%d", &trigger);
    getchar();

    if (trigger == 5)
    {
        general_information();
        return 0;
    }
    else if (trigger < 0 || trigger > 9)
    {
        puts("Error: Invalid input. Outside of [0, 5] range.");
        return 0;
    }
    else
    {
        text = read_text();
        filter_text = remove_duplicate_sentences(text);
    }

    if (trigger == 1)
    {
        setlocale(LC_ALL, "");
    }

    switch (trigger)
    {
    case 0:
        basic_processing(filter_text);
        break;
    case 1:
        check_palindromes(filter_text);
        break;
    case 2:
        replace_special_symbols(filter_text);
        break;
    case 3:
        sort_by_latin_letters(filter_text);
        break;
    case 4:
        remove_mixed_alphabet_sentences(filter_text);
        break;
    // case 9:
    //     big_word(filter_text);
    //     break;
    }
    

    for (int i = 0; i < text.sentence_count; i++)
        free(text.sentences[i].sentence);
    free(text.sentences);

    for (int i = 0; i < filter_text.sentence_count; i++)
        free(filter_text.sentences[i].sentence);
    free(filter_text.sentences);

    return 0;
}
