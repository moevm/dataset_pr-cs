#include "delete_sentence_if_len_is_less_than_2.h"
#include <string.h>

void delete_sentence_if_len_is_less_than_2(Text *txt)
{
    for (size_t i = 0; i < txt->length; i++)
    {
        Sentence *sent = txt->array_sentence[i];
        if (sent->count_words <= 2)
        {
            free_sentence(sent);
            memmove(txt->array_sentence + i, txt->array_sentence + i +1, sizeof(Sentence*)*(txt->length-i-1));
            txt->length--;
            i--;
        }
    }
}