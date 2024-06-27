#ifndef SORTED_H
#define SORTED_H

size_t count_word_len_three(const char *sentence, size_t len);
int compare_three_letter_word(const void* a, const void* b);
void sort_three_letter_word(Text* text);

#endif
