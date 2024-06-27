#include"Structs.h"
#include"Input.h"
#include<stdlib.h>
#include<wctype.h>
#include<wchar.h>


                



wchar_t* sentence_to_char(struct Sentence sentence)
{
    size_t cnt_char = 0;
    wchar_t* char_arr = (wchar_t*)malloc((cnt_char + 2) * sizeof(wchar_t));

    for (int i = 0; i < sentence.words_count; ++i)
    {
        for (int j = 0; j < sentence.words[i].letters_count; ++j)
        {
            char_arr = (wchar_t*)realloc(char_arr, (cnt_char + 2) * sizeof(wchar_t));


            char_arr[cnt_char] = towlower(sentence.words[i].letters[j]);
            cnt_char++;
            char_arr[cnt_char] = '\0';

        }
    }
    return char_arr;
}


int input_args(int* operation_number, int* max_word_len)
{
    wscanf(L"%d", operation_number);
    if (*operation_number == 5)
    {
        return 0;
    }
    if(*operation_number == 9)
    {
        wchar_t buf[1000];
        wscanf(L"%ls\n", &buf);
        *max_word_len = wcslen(buf);
    }
    return 1;
}

struct Text input_letter(struct Text text,wchar_t symbol)
{
    text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters_count++;
                text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters =
                        (wchar_t*)realloc(text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters,
                                          ((text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters_count) + 1) * sizeof(wchar_t));
                text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters[text.sentences[text.sentences_count - 1].
                words[text.sentences[text.sentences_count - 1].words_count - 1].letters_count - 1] = symbol;
                return text;
}

struct Text input_word(struct Text text)
{
    text.sentences[text.sentences_count - 1].words_count++;
    text.sentences[text.sentences_count - 1].words = (struct Word*)realloc(text.sentences[text.sentences_count - 1].words, text.sentences[text.sentences_count - 1].words_count
                                                                                                                           * sizeof(struct Word));
    text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters_count = 0;
    text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters = (wchar_t*)malloc(2 * sizeof(wchar_t));
    return text;
}

struct Text input_sentence(struct Text text)
{
    text.sentences_count++;
    text.sentences = (struct Sentence*)realloc(text.sentences, text.sentences_count * sizeof(struct Sentence));
    text.sentences[text.sentences_count - 1].words_count = 0;
    text.sentences[text.sentences_count - 1].words = (struct Word*)malloc(1 * sizeof(struct Word));
    return text;
}

struct Text check_zero_sentences(struct Text text)
{
    if (wcslen(text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters) == 0)
    {
        free(text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters);
        text.sentences[text.sentences_count - 1].words_count--;

    }
    return text;
}

struct Text remove_identical_sentences(struct Text text)
{
    int is_unique = 1;
    wchar_t* new_sentence = sentence_to_char(text.sentences[text.sentences_count - 1]);
    for (int i = 0; i < text.sentences_count - 1; ++i)
    {
        wchar_t* orig_sentence = sentence_to_char(text.sentences[i]);
        if (!wcscmp(new_sentence, orig_sentence))
        {
            is_unique = 0;
            free(orig_sentence);
            break;
        }


        free(orig_sentence);
    }
    free(new_sentence);

    if (!is_unique || text.sentences[text.sentences_count - 1].words[0].letters[0] == '\n')
    {
        text.sentences[text.sentences_count - 1].words_count = 0;
        free(text.sentences[text.sentences_count - 1].words);
        text.sentences_count--;
    }
    return text;
}

struct Text input_text()
{
    struct Text text;

    text.sentences_count = 0;
    text.sentences = (struct Sentence*)malloc(1 * sizeof(struct Sentence));
    wchar_t sym = '0';
    wchar_t last_sym = '0';
    do
    {
        text = input_sentence(text);
        do
        {
            text = input_word(text);
            do
            {
                last_sym = sym;
                sym = getwchar();

                if (sym == ' ' || sym == '\n')
                {
                    break;
                }
                text = input_letter(text,sym);


            } while (sym != ' ' && sym != '.' && sym != ',' && sym != '\n');

            text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters[text.sentences[text.sentences_count - 1].words[text.sentences[text.sentences_count - 1].words_count - 1].letters_count] = '\0';

            text = check_zero_sentences(text);

            text = remove_identical_sentences(text);


        } while (sym != '.' && !(sym == '\n' && last_sym == '\n'));

    } while (!(sym == '\n' && last_sym == '\n'));

    return text;
}