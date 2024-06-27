#include "main.h"

Sentence get_sentence()
{
    Sentence sentence;
    sentence.string = malloc(sizeof(wchar_t));
    int sentence_size = 0;
    int memory_buffer = 1;
    wchar_t current_symbol;
    int flag = -1;
    int is_first_symbol = 1;
    do
    {
        current_symbol = getwchar();
        current_symbol = towlower(current_symbol);
        if (current_symbol == L'\n')
        {
            flag++;
        }
        if (is_first_symbol && iswspace(current_symbol))
        {
            continue;
        }
        is_first_symbol = 0;

        sentence.string[sentence_size++] = current_symbol;
        if (sentence_size == memory_buffer)
        {
            memory_buffer *= 2;
            sentence.string = realloc(sentence.string, sizeof(wchar_t) * memory_buffer);
        }

    } while (flag != 1);
    sentence.string[sentence_size] = L'\0';
    sentence.size = sentence_size;
    return sentence;
}

int word_in_sentence(Sentence sentence, wchar_t *word)
{
    wchar_t *was_found = wcsstr(sentence.string, word);
    if (was_found == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void task(Text text, Sentence example_sentence)
{
    int start_index = 0;
    int end_index = 0;
    int flag = 0;
    int is_ok = 1;
    for (size_t index_of_sentence = 0; index_of_sentence < text.size; index_of_sentence++)
    {
        for (int index = 0; index < text.sentences[index_of_sentence].size; index++)
        {
            if (flag == 0 && !isSeparator(text.sentences[index_of_sentence].string[index]))
            {
                flag = 1;
                start_index = index;
            }

            if (flag == 1 && isSeparator(text.sentences[index_of_sentence].string[index]))
            {
                end_index = index;

                int word_length = end_index - start_index;
                wchar_t *word = (wchar_t *)calloc((word_length + 1), sizeof(wchar_t));
                for (size_t i = 0; i < word_length; i++)
                {
                    word[i] = towlower(text.sentences[index_of_sentence].string[start_index + i]);
                }
                word[word_length] = '\0';
                if (!word_in_sentence(example_sentence, word))
                {
                    is_ok = 0;
                }

                free(word);
                flag = 0;
            }
        }
        if (is_ok)
        {
            wprintf(L"%ls\n", text.sentences[index_of_sentence].string);
        }
        is_ok = 1;
    }
}

void menu(int choice)
{
    Text input_text;
    switch (choice)
    {
    case 0:
        input_text = read_text();
        print_text(input_text);
        free_text(&input_text);
        break;
    case 1:
        input_text = read_text();
        colorize_words(&input_text);
        free_text(&input_text);
        break;

    case 2:
        input_text = read_text();
        find_word_usage(input_text);
        free_text(&input_text);
        break;

    case 3:
        input_text = read_text();
        sort_text_by_last_word_length(input_text);
        print_text(input_text);
        free_text(&input_text);
        break;

    case 4:
        input_text = read_text();
        delete_numbers_from_text(input_text);
        print_text(input_text);
        free_text(&input_text);
        break;
    case 5:
        help();
        break;
    case 9:;
        Sentence example_sentence = get_sentence();
        input_text = read_text();
        task(input_text, example_sentence);
        free_text(&input_text);
        free(example_sentence.string);
        break;
    default:
        wprintf(L"Ошибка: неверное значение команды. Для вызова справки нажмите 5.\n");
        break;
    }
}

int main()
{
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.7, created by Rusanov Aleksandr.\n");
    int choice;
    int is_valid = wscanf(L"%ld", &choice);
    Text input_text;
    if (is_valid)
    {
        menu(choice);
    }
    else
    {
        wprintf(L"Ошибка: неверное значение команды. Для вызова справки нажмите 5.\n");
    }
    return 0;
}
