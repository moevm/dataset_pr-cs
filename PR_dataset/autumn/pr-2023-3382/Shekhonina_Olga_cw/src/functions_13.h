#include "structs.h"

void delete_sentence(Text* text, int num_of_sent);
void delete_repeat_sentence(Text* text);
void replace_highnoon_and_midnight(Text* text);
wchar_t* find_first_word(Sentence* sentence);
wchar_t* find_last_word(Sentence* sentence);
void remove_some_sentences(Text* text);
