#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "text.h"
#include "fatal_error.h"

int is_consonant(char c)
{
    c = tolower(c);
    if (c < 'a' || c > 'z') return 0;

    static char table[] = {
        0, 1, 1, 1, 0, 1, 1, // ABCDEFG
        1, 0, 1, 1, 1, 1, 1, // HIJKLMN
        0, 1, 0, 1, 1, 1, 0, // OPQRSTU
        1, 1, 1, 0, 1,       // VWXYZ
    };

    return table[c - 'a'];
}

int is_alphabet(char c)
{
    return isalnum(c) || isspace(c) || c == ',' || c == '-' || c == '.';
}

void input_text(text_t *text)
{
    string_t str;
    int cnt_char = 1, cnt_line = 1;
    char prev = '\0';
    char cur = '\0';

    string_init(&str, 0);

    while (1) {
        cur = getchar();

        if (cur == EOF)
            fatal_error("Invalid input. Unexpected EOF. Use double \'\\n\' instead.");

        if (cur == '\n') {
            if (prev == '\n')
                break;

            prev = '\n';
            cur = ' ';
            cnt_line++;
            cnt_char = 1;
        }
        else
            prev = cur;

        if ((isspace(cur) || cur == ',') && str.len == 0)
            continue;

        if (!is_alphabet(cur))
            fatal_error("Invalid input. Unexpected symbol at %d:%d.", cnt_line, cnt_char);

        if (cur == '.') {
            if (str.len != 0) {
                string_push_back(&str, '.');
                *text_extend(text) = str;
                string_init(&str, 0);
            }
            else {
                string_push_back(&text->sentences[text->len - 1], '.');
            }
        }
        else {
            string_push_back(&str, cur);
        }
        
        cnt_char++;
    }

    if (str.len != 0)
        *text_extend(text) = str;
    else
        string_deinit(&str);

    for (size_t i = 0; i < text->len; i++) {
        string_push_back(&text->sentences[i], '\0');
        string_update_hash(&text->sentences[i]);
        string_update_word_count(&text->sentences[i]);
    }
}

int filter_remove_duplicates(text_t *text, string_t *str, void *dummy)
{
    for (string_t *prev = text->sentences; prev != str; prev++) {
        if (string_eq(prev, str))
            return 0;
    }
    return 1;
}

int filter_by_length_range(text_t *text, string_t *str, void *dummy)
{
    return str->word_count > 2 && str->word_count < 7;
}

int filter_by_average_length(text_t *text, string_t *str, size_t *total)
{
    return str->word_count * text->len <= (*total);
}

int string_timesum_comparator(const void *a, const void *b)
{
    return ((string_t*)b)->timesum - ((string_t*)a)->timesum;
}

void print_text(text_t *text)
{
    for (size_t i = 0; i < text->len; i++)
        puts(text->sentences[i].data);
}

// COMMANDS START HERE

void command_sort_by_timesum(text_t *text)
{
    for (size_t i = 0; i < text->len; i++)
        string_update_timesum(&text->sentences[i]);

    qsort(text->sentences, text->len, sizeof(string_t), string_timesum_comparator);
}

void command_filter_by_length_range(text_t *text)
{
    text_filter(text, filter_by_length_range, NULL);
}

void command_lower_to_upper_consonants(text_t *text)
{
    for (size_t i = 0; i < text->len; i++) {
        char *ptr = text->sentences[i].data;
        while (*ptr != '\0') {
            if (is_consonant(*ptr))
                *ptr = toupper(*ptr);
            ptr++;
        }
    }
}

void command_filter_by_average_length(text_t *text)
{
    size_t total = 0;
    for (size_t i = 0; i < text->len; i++)
        total += text->sentences[i].word_count;

    text_filter(text, (text_filter_func_t)filter_by_average_length, &total);
}

void command_print_help()
{
    puts(
        "Receives input from stdin\n"
        "stdin:\n"
        "  COMMAND\n"
        "  TEXT...\n"
        "  ...\n"
        "\n"
        "List of commands:\n"
        "  0 - print preprocessed text.\n"
        "  1 - sort descending all sentences by time-sum and print resulted text.\n"
        "  2 - print sentences longer than 2 and less than 7 words.\n"
        "  3 - replace lowercase consonant letters with uppercase ones.\n"
        "  4 - remove all sentences with more then average letter count.\n"
        "  5 - print help message.\n"
        "  9 - duplicate all sentences.\n"
        "\n"
        "TEXT is a sequence of sentences separated by \'.\'. Sentence is a sequence of words separated by \' \', \',\' or \'\\n\'. Word is a sequence of latin letters and numbers OR \'-\' symbol. Double \'\\n\' is interpreted as an end of text. Any violation from these simple rules will be considered an invalid input.\n"
    );
}

void command_duplicate_sentences(text_t *text)
{
    for (size_t i = 0; i < text->len; i++) {
        string_t *str = &text->sentences[i];
        
        size_t len = str->len - 1;
        
        size_t cnt = 0;
        while (str->data[len - 1] == '.') {
            str->data[len - 1] = ' ';
            len--;
            cnt++;
        }

        str->data = realloc(str->data, len * 2 + 2 + cnt);
        str->capacity = len * 2 + 2 + cnt;

        strncat(str->data + len + 1, str->data, len);
        memset(str->data + len * 2 + 1, '.', cnt);
        str->data[len * 2 + 2] = '\0';
    }
}

int main()
{
    text_t text;
    int cmd;

    puts("Course work for option 4.21, created by Kirill Gorsky.");
    if (scanf("%d", &cmd) == 0)
        fatal_error("Invalid input. Command is not an integer.");

    if (cmd != 9 && (cmd < 0 || cmd > 5))
        fatal_error("Invalid input. Outside of [0, 5] range.");

    if (cmd != 5) {
        text_init(&text);
        input_text(&text);
        text_filter(&text, filter_remove_duplicates, NULL);
    }

    switch (cmd) {
        case 1:
            command_sort_by_timesum(&text);
            break;
        case 2:
            command_filter_by_length_range(&text);
            break;
        case 3:
            command_lower_to_upper_consonants(&text);
            break;
        case 4:
            command_filter_by_average_length(&text);
            break;
        case 5:
            command_print_help();
            break;
        case 9:
            command_duplicate_sentences(&text);
        default:
            break;
    }

    if (cmd != 5) {
        print_text(&text);
        text_deinit(&text);
    }

    return 0;
}