#pragma once

wchar_t** delimiters(wchar_t* sent);

wchar_t* replace_spaces(struct Text* text, int i);

void return_delimiters(struct Text* text_array, int i, wchar_t* sent, wchar_t** delimiters);

void shift_words_in_a_sentence(struct Text* text);