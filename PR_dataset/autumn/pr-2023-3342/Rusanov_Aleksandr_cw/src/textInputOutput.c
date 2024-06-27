#include "textInputOutput.h"

void help()
{
    wprintf(L"Доступны следующие операции с текстом:\n");
    wprintf(L"0 - Первичная обработка текста (удалить все повторно встречающиеся предложения)\n");
    wprintf(L"1 - “Раскрасить” каждое слово в зависимости от остатка от деления его длины на 4. Если остаток равен 0 - ");
    wprintf(L"%S", RED);
    wprintf(L"красный ");
    wprintf(L"%S", NONE);
    wprintf(L"цвет, 1 - ");
    wprintf(L"%S", BLUE);
    wprintf(L"синий");
    wprintf(L"%S", NONE);
    wprintf(L", 2 - ");
    wprintf(L"%S", GREEN);
    wprintf(L"зеленый");
    wprintf(L"%S", NONE);
    wprintf(L", 3 - ");
    wprintf(L"%S", YELLOW);
    wprintf(L"желтый");
    wprintf(L"%S", NONE);
    wprintf(L".\n");
    wprintf(L"2 - Распечатать каждое слово, которое начинается и заканчивается на заглавную букву, и номера предложений, в которых оно встречается .\n");
    wprintf(L"3 - Отсортировать предложения по длине последнего слова в предложении.\n");
    wprintf(L"4 - Удалить все числа из предложений. Число - набор подряд идущих цифр, перед и после которого стоят пробелы.\n");
}

Sentence read_sentence(int *new_line_char_count)
{
    Sentence sentence;
    sentence.string = malloc(sizeof(wchar_t));
    int sentence_size = 0;
    int memory_buffer = 1;
    wchar_t current_symbol;
    int is_first_symbol = 1;
    do
    {
        current_symbol = getwchar();
        if (current_symbol == L'\n')
        {
            (*new_line_char_count)++;
            if ((*new_line_char_count) == 2)
            {
                break;
            }
            continue;
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

    } while (current_symbol != L'.');
    sentence.string[sentence_size] = L'\0';
    sentence.size = sentence_size;
    return sentence;
}

Text read_text()
{
    Text text;
    text.sentences = malloc(sizeof(Sentence));
    int text_size = 0;
    int memory_buffer = 1;
    int new_line_char_count = 0;
    while (1)
    {
        Sentence temp_sentence = read_sentence(&new_line_char_count);
        int is_equal = 0;
        for (int i = 0; i < text_size; ++i)
        {
            if (wcscasecmp(temp_sentence.string, text.sentences[i].string) == 0)
            {
                is_equal = 1;
                break;
            }
        }
        if (new_line_char_count == 2)
        {
            break;
        }
        else
        {
            new_line_char_count = 0;
        }
        if (is_equal)
        {
            continue;
        }

        wchar_t *buffer;
        wchar_t *copy_of_string = wcsdup(temp_sentence.string);
        wchar_t *check_result = wcstok(copy_of_string, L" ,.", &buffer);
        if (check_result == NULL)
        {
            free(copy_of_string);
            continue;
        }
        free(copy_of_string);

        text.sentences[text_size++] = temp_sentence;
        text.size = text_size;
        if (text_size == memory_buffer)
        {
            memory_buffer *= 2;
            text.sentences = realloc(text.sentences, sizeof(Sentence) * memory_buffer);
        }
    }
    if (text.sentences[0].string == NULL)
    {
        fwprintf(stderr, L"Error: некорректный ввод.\n");
        exit(0);
    }
    return text;
}

void print_text(Text text)
{
    for (int i = 0; i < text.size; i++)
    {
        wprintf(L"%ls\n", text.sentences[i].string);
    }
    printf("\n");
}

void free_text(Text *text)
{
    for (size_t i = 0; i < text->size; i++)
    {
        free(text->sentences[i].string);
    }
    free(text->sentences);
}
