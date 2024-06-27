#pragma once
struct Sentence;
struct Text;

wchar_t* to_lower(wchar_t *word);

bool is_palindrome1(const wchar_t* word);

int pallindroms_in_sents(struct Sentence *sen);

int pals_analys(struct Text *text);