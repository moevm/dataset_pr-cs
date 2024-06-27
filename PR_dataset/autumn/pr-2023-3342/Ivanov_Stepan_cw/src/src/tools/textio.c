#include "tools/textio.h"

Wsize_t
print_word(Word_t *word)
{
    return wprintf(L"%ls%lc",
        word->data,
        word->end
    );
}

size_t
scan_word(Word_t *word)
{
    wchar_t ch = getwchar();

    while (
           ch != L'.' 
        && ch != L' ' 
        && ch != L',' 
        && ch != L'\n'
        && ch != L'\t'
    )
    {
        add_char(word, ch);
        ch = getwchar();
    }

    word->end = ch;

    return 0;

}

Ssize_t
print_sentence(Sentence_t *sentence)
{
    Ssize_t cnt_chs = 0;

    for (size_t i = 0; i < sentence->len; ++i)
        cnt_chs += print_word(
            get_word(sentence, i)
        );

    wprintf(L"%lc", L'\n');

    return cnt_chs;

}

wchar_t
_check_end_of_sentence(Sentence_t *sentence)
{
    wchar_t previous_ch = 0;
    wchar_t ch = getwchar();

    while (
           ch == L' ' 
        || ch == L'\t'
    )
    {
        previous_ch = ch;
        ch = getwchar();
    }

    sentence->end = (ch == L'\n')
                        ? ch
                        : previous_ch;

    return ch;

}

void 
_scan_sentence(Sentence_t *sentence)
{
    Word_t *word;

    do
    {
        word = init_word();

        scan_word(word);
        add_word(sentence, word);

    } while (word->end != L'.');

}

static inline bool 
_check_valid_sentence(Sentence_t *sentence)
{
    return get_word(
        sentence,
        sentence->len - 1
    )->end == L'.';

}

wchar_t
scan_sentence(Sentence_t *sentence)
{
    if (
        sentence->len > 0 && _check_valid_sentence(sentence))
        goto no_scan_sentence;

    _scan_sentence(sentence);

no_scan_sentence:
    return _check_end_of_sentence(sentence);
}

Tsize_t
print_text(Text_t *text)
{
    Tsize_t cnt_chs = 0;

    for (size_t i = 0; i < text->len; ++i)
        cnt_chs += print_sentence(
            get_sentence(text, i));
    // wprintf(L"%lc", text->end);

    return cnt_chs;

}

Sentence_t *
_get_sentence_with_word(wchar_t ch)
{
    Word_t *word = init_word();
    add_char(word, ch);
    scan_word(word);

    Sentence_t *sentence = init_sentence();
    add_word(sentence, word);
    return sentence;

}

bool 
_check_end_of_text(Text_t *text, wchar_t *ch)
{
    if (ch[0] == L'\n')
    {
        *ch = getwchar();
        if (ch[0] == L'\n')
        {
            text->end = ch[0];
            return true;
        }
    }

    return false;

}

size_t
scan_text(Text_t *text)
{
    Sentence_t *sentence = init_sentence();
    wchar_t ch;

    do
    {
        ch = scan_sentence(sentence);
        add_sentence(text, sentence);

        if (_check_end_of_text(text, &ch))
            return 0;

        sentence = _get_sentence_with_word(ch);

    } while (true);

}



Word_t * 
getword()
{
    Word_t *word = init_word();
    scan_word(word);
    return word;

}

Sentence_t * 
getsentence()
{
    Sentence_t *sentence = init_sentence();
    scan_sentence(sentence);
    return sentence;

}

Text_t * 
gettext()
{
    Text_t *text = init_text();
    scan_text(text);
    return text;
    
}