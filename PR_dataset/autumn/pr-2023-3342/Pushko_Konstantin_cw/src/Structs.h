#include<wchar.h>
struct Text
{
    struct Sentence* sentences;
    int sentences_count;
};
struct Sentence
{
    struct Word* words;
    int words_count;
    int latin_letters_count;
};
struct Word
{
    wchar_t* letters;
    int letters_count;

};
struct Unique_Word
{
    wchar_t* letters;
    int words_count;
};