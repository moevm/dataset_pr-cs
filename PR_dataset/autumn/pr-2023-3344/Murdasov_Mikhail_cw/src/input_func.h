#pragma once

int change_option();

int repeat_sent_check(struct Text *text, struct Sentence* sent);

int bad_sentence(wchar_t* sent);

void remove_first_space(wchar_t* sent);

void text_processing(struct Text* text, struct Sentence string);

void input_text(struct Text* text);