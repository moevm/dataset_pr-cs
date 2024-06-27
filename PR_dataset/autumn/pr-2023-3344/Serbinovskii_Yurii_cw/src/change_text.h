#pragma once

#include "structures.h"


int check_repeats(wchar_t* cur_sent, struct Sentence** text, int sent_count);
int mask_approved(wchar_t* sent, wchar_t* mask);
void words_sort(wchar_t* sent);
int delete_sent(wchar_t* sent);