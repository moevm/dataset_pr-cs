#include "handle_functs/action_with_text_processing.h"

Text_t *
_preprocessing(Text_t *text)
{
    for (size_t i = 0; i < text->len; ++i)
        for (size_t j = i + 1; j < text->len; ++j)
            if (
                compare_sentences(
                    get_sentence(text, i),
                    get_sentence(text, j),
                    false))
                delete_sentence(text, j--);

    return text;
}

Word_t *
_generate_replacement_for_high_noon()
{
    return add_str(
        init_word(),
        L"полдень");
}

Word_t *
_generate_replacement_for_polnoch()
{
    return add_str(
        init_word(),
        L"midnight");
}

bool _check_high_noon(
    Sentence_t *sentence,
    size_t index,
    Word_t *high,
    Word_t *noon)
{
    Word_t *word = get_word(sentence, index);

    if (!compare_words(word, high, true))
        return false;

    word = get_word(sentence, index + 1);

    if (!compare_words(word, noon, true))
        return false;

    return true;
}

bool _check_polnoch(
    Sentence_t *sentence,
    size_t index,
    Word_t *polnoch)
{
    return compare_words(
        get_word(sentence, index),
        polnoch,
        true);
}

void _replace_high_noon(Sentence_t *sentence, size_t index)
{
    Word_t *_replacement = _generate_replacement_for_high_noon();
    delete_word(sentence, index); // high
    Word_t *word = get_word(sentence, index);
    _replacement->end = word->end;
    sentence->data[index] = _replacement;
    free_word(word);
}

void _replace_polnoch(Sentence_t *sentence, size_t index)
{
    Word_t *_replacement = _generate_replacement_for_polnoch();
    Word_t *word = get_word(sentence, index);
    _replacement->end = word->end;
    sentence->data[index] = _replacement;
    free_word(word);
}

Text_t *
_replacing_words(Text_t *text)
{
    _preprocessing(text);

    Word_t *high = init_word();
    add_str(high, L"high");

    Word_t *noon = init_word();
    add_str(noon, L"noon");

    Word_t *polnoch = init_word();
    add_str(polnoch, L"полночь");

    Sentence_t *sentence;

    for (size_t i = 0; i < text->len; ++i)
    {
        sentence = get_sentence(text, i);

        for (size_t j = 1; j < sentence->len; ++j)
        {
            if (_check_high_noon(sentence, j - 1, high, noon))
            {
                _replace_high_noon(sentence, j - 1);
                continue;
            }

            if (_check_polnoch(sentence, j - 1, polnoch))
            {
                _replace_polnoch(sentence, j - 1);
                continue;
            }
        }

        if (_check_polnoch(sentence, sentence->len - 1, polnoch))
        {
            _replace_polnoch(sentence, sentence->len - 1);
            continue;
        }
    }

    free_word(high);
    free_word(noon);
    free_word(polnoch);

    return text;
}

wchar_t
_get_sep_of_date(size_t form)
{
    switch (form)
    {
    case 1:
        return L'/';

    case 2:
        return L'-';

    default:
        error(1, L"invalid case in date");
    }

    return 0;
}

bool _is_valid_date(Word_t *date, size_t form)
{
    wchar_t sep = _get_sep_of_date(form);

    wchar_t ch;
    for (size_t i = 0; i < date->len; ++i)
    {
        ch = get_char(date, i);
        if (!iswdigit(ch) && ch != sep)
            return false;
    }

    return true;
}

size_t
_get_form_of_date(Word_t *word)
{
    if (word->len != 10)
        return 0;

    if (
        get_char(word, 2) == L'/' &&
        get_char(word, 5) == L'/')
    {
        if (!_is_valid_date(word, 1))
            return 0;

        return 1;
    }

    if (
        get_char(word, 4) == L'-' &&
        get_char(word, 7) == L'-')
    {
        if (!_is_valid_date(word, 2))
            return 0;

        return 2;
    }

    return 0;
}

void _get_day_month_year(
    const Word_t *date,
    long *day,
    long *month,
    long *year)
{
    Word_t *_tmp_word = init_word();
    wchar_t *sep = add_char(_tmp_word, _get_sep_of_date(date->end))->data;

    Word_t *_cp_date = copy_word(date);
    wchar_t *_tmp = wcstok(_cp_date->data, sep, NULL); // day/year
    if (date->end == 1)
        *day = wcstol(_tmp, NULL, 10);
    else
        *year = wcstol(_tmp, NULL, 10);

    _tmp = wcstok(NULL, sep, NULL); // month
    *month = wcstol(_tmp, NULL, 10);

    _tmp = wcstok(NULL, sep, NULL); // year/day
    if (date->end == 1)
        *year = wcstol(_tmp, NULL, 10);
    else
        *day = wcstol(_tmp, NULL, 10);

    free_word(_tmp_word);
    free_word(_cp_date);
}

int _compare_date_vals(
    long day, long month, long year,
    long other_day, long other_month, long other_year)
{
    if (year != other_year)
    {
        if (year > other_year)
            return 1;
        else
            return -1;
    }

    if (month != other_month)
    {
        if (month > other_month)
            return 1;
        else
            return -1;
    }

    if (day != other_day)
    {
        if (day > other_day)
            return 1;
        else
            return -1;
    }

    return 0;
}

int _compare_dates(const void *a, const void *b)
{
    Word_t *date = *((Word_t **)a);
    Word_t *other_date = *((Word_t **)b);

    long day, month, year;
    long other_day, other_month, other_year;

    _get_day_month_year(date, &day, &month, &year);
    _get_day_month_year(other_date, &other_day, &other_month, &other_year);

    return _compare_date_vals(
        day, month, year,
        other_day, other_month, other_year);
}

void _sort_dates(Sentence_t *dates)
{
    qsort(
        dates->data,
        dates->len,
        sizeof(get_word(dates, 0)),
        _compare_dates);
}

void _ascending_dates(Text_t *text)
{

    _preprocessing(text);

    Sentence_t *dates = init_sentence();

    Word_t *word, *date;
    Sentence_t *sentence;
    size_t form_of_date;
    for (size_t i = 0; i < text->len; ++i)
    {
        sentence = get_sentence(text, i);

        for (size_t j = 0; j < sentence->len; ++j)
        {
            word = get_word(sentence, j);

            form_of_date = _get_form_of_date(word);

            if (form_of_date)
            {
                date = init_word();
                add_str(date, word->data);
                date->end = (wchar_t)form_of_date; // there end == form_of_date
                add_word(dates, date);
            }
        }
    }

    _sort_dates(dates);

    for (size_t i = 0; i < dates->len; ++i)
        get_word(dates, i)->end = L'\n';

    print_sentence(dates);

    free_sentence(dates);
}

Text_t *
_deleting_sentences(Text_t *text)
{
    _preprocessing(text);

    Sentence_t *sentence;

    for (size_t i = 0; i < text->len; ++i)
    {
        sentence = get_sentence(text, i);

        if (sentence->len < 1)
            continue;

        if (compare_words(
                get_word(sentence, 0),
                get_word(sentence, sentence->len - 1),
                true))
        {
            delete_sentence(text, i);
        }
    }

    return text;
}

size_t
_get_day_number(Word_t *day)
{
    if (day->len != 2)
        return 0;

    if (!is_number(day))
        return 0;

    long day_num = wcstol(day->data, NULL, 10);

    if (day_num < 1 || day_num > 31)
        return 0;

    return day_num;
}

size_t
_get_month_number(Word_t *month)
{
    const wchar_t *str = month->data;

    if (!wcscmp(str, L"Jan"))
        return 1;
    else if (!wcscmp(str, L"Feb"))
        return 2;
    else if (!wcscmp(str, L"Mar"))
        return 3;
    else if (!wcscmp(str, L"Apr"))
        return 4;
    else if (!wcscmp(str, L"May"))
        return 5;
    else if (!wcscmp(str, L"Jun"))
        return 6;
    else if (!wcscmp(str, L"Jul"))
        return 7;
    else if (!wcscmp(str, L"Aug"))
        return 8;
    else if (!wcscmp(str, L"Sep"))
        return 9;
    else if (!wcscmp(str, L"Oct"))
        return 10;
    else if (!wcscmp(str, L"Nov"))
        return 11;
    else if (!wcscmp(str, L"Dec"))
        return 12;
    else
        return 0;
}

size_t
_get_year_number(Word_t *year)
{
    if (!is_number(year))
        return 0;

    long year_num = wcstol(year->data, NULL, 10);

    if (year_num < 0)
        return 0;

    return year_num;
}

const wchar_t *
_get_chronic_date(
    size_t day,
    size_t month,
    size_t year)
{
    int val = _compare_date_vals(
        day, month, year,
        30, 11, 2023);

    switch (val)
    {
    case 1:
        return L"Not Happened";

    case 0:
    case -1:
        return L"Happened";

    default:
        error(1, L"invalid case for chronic dates");
        return L"";
    }
}

void _displaying_specific_dates(Text_t *text)
{
    _preprocessing(text);

    Sentence_t *sentence;
    Word_t *word;
    for (size_t i = 0; i < text->len; ++i)
    {
        sentence = get_sentence(text, i);

        for (size_t j = 2; j < sentence->len; ++j)
        {
            word = get_word(sentence, j - 2);
            size_t day = _get_day_number(word);
            if (!day)
                continue;

            word = get_word(sentence, j - 1);
            size_t month = _get_month_number(word);
            if (!month)
                continue;

            word = get_word(sentence, j);
            size_t year = _get_year_number(word);
            if (!year)
                continue;

            wprintf(L"%02zd.%02zd.%zd\t%ls\n",
                    day, month, year,
                    _get_chronic_date(day, month, year));
        }
    }
}

Word_t *
_generate_replacement_for_big_word()
{
    return word_add_str(
        word_init(),
        L"(большое слово)");
}

void _replace_big_word(Sentence_t *sentence, size_t i)
{
    Word_t *_replacement = _generate_replacement_for_big_word();
    Word_t *word = sentence_get_word(sentence, i);
    _replacement->end = word->end;
    sentence->data[i] = _replacement;
    word_free(word);
}

void _replace_big_words(Text_t *text, Word_t *length_word)
{
    _preprocessing(text);

    Word_t *word;
    Sentence_t *sentence;

    for (size_t i = 0; i < text->len; ++i)
    {
        sentence = text_get_sentence(text, i);

        for (size_t j = 0; j < sentence->len; ++j)
        {
            word = sentence_get_word(sentence, j);

            if (word->len > length_word->len)
                _replace_big_word(sentence, j);
        }
    }
}

int action_with_text_processing(Action action)
{
    Word_t *length_word;
    if (action == REPLACE_BIG_WORDS)
        length_word = getword();

    Text_t *text = gettext();


    switch (action)
    {
    case PREPROCESSING:
        _preprocessing(text);
        print_text(text);
        break;

    case REPLACING_WORDS:
        _replacing_words(text);
        print_text(text);
        break;

    case ASCENDING_DATES:
        _ascending_dates(text);
        break;

    case DELETING_SENTENCES:
        _deleting_sentences(text);
        print_text(text);
        break;

    case DISPLAYING_SPECIFIC_DATES:
        _displaying_specific_dates(text);
        break;

    case REPLACE_BIG_WORDS:
        _replace_big_words(text, length_word);
        print_text(text);
        word_free(length_word);
        break;

    default:
        free_text(text);
        error(1, L"Мёртвый кейс..");
    }

    free_text(text);

    return 0;
}
