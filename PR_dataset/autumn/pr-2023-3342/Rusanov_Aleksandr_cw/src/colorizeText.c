#include "colorizeText.h"


void print_color(Sentence sentence, int start_index, int end_index, const wchar_t *color)
{
    wprintf(L"%S", color);
    for (size_t i = start_index; i < end_index; i++)
    {
        wprintf(L"%C", sentence.string[i]);
    }
    wprintf(L"%S", NONE);
}

void colorize_words(Text *text)
{
    for (size_t index_of_sentence = 0; index_of_sentence < text->size; index_of_sentence++)
    {
        int flag = 0;
        int start_index = 0;
        int end_index = 0;
        for (size_t index = 0; index < text->sentences[index_of_sentence].size; index++)
        {
            Sentence current_sentence = text->sentences[index_of_sentence];
            if (flag == 0 && !is_separator(current_sentence.string[index]))
            {
                flag = 1;
                start_index = index;
            }

            if (flag == 1 && is_separator(current_sentence.string[index]))
            {
                end_index = index;
                int word_length = end_index - start_index;
                int color_choice = word_length % 4;
                switch (color_choice)
                {
                case 0:
                    print_color(current_sentence, start_index, end_index, RED);
                    break;
                case 1:
                    print_color(current_sentence, start_index, end_index, BLUE);
                    break;
                case 2:
                    print_color(current_sentence, start_index, end_index, GREEN);
                    break;
                case 3:
                    print_color(current_sentence, start_index, end_index, YELLOW);
                    break;
                default:
                    break;
                }
                flag = 0;
            }
            if (flag == 0 && is_separator(current_sentence.string[index]))
            {
                wprintf(L"%C", current_sentence.string[index]);
            }
        }
        wprintf(L"\n");
    }
}
