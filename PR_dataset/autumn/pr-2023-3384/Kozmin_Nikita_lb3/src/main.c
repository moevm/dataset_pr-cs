#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main()
{
    char **sentenses = calloc(1, sizeof(char*));
    sentenses[0] = calloc(1, sizeof(char));
    size_t cnt_sentences = 1;
    size_t cnt_chars_sentence = 0;
    short int cnt_up = 0;
    char cur_char;
    size_t cnt_delete = 0;

    do
    {
        cur_char = getchar();
        if (isupper(cur_char))
        {
            cnt_up++;
        }
        else if (cur_char == '.' || cur_char == ';' || cur_char == '?')
        {
            if (cnt_up < 2)
            {
                cnt_chars_sentence++;
                sentenses[cnt_sentences-1] = realloc(sentenses[cnt_sentences-1],
                                                     sizeof(char)*(cnt_chars_sentence+1));
                sentenses[cnt_sentences-1][cnt_chars_sentence-1] = cur_char;
                sentenses[cnt_sentences-1][cnt_chars_sentence] = '\0';
                cnt_sentences++;
                sentenses = realloc(sentenses, sizeof(char*)*cnt_sentences);
            }
            else
            {
                cnt_delete++;
                free(sentenses[cnt_sentences-1]);
            }
            sentenses[cnt_sentences-1] = calloc(1, sizeof(char));
            cnt_chars_sentence = 0;
            cnt_up = 0;
            getchar(); // Считываем разделитель
            continue;
        }

        if (cnt_up < 2)
        {
            cnt_chars_sentence++;
            sentenses[cnt_sentences-1] = realloc(sentenses[cnt_sentences-1],
                                                 sizeof(char)*(cnt_chars_sentence+1));
            sentenses[cnt_sentences-1][cnt_chars_sentence-1] = cur_char;
        }
    } while (cur_char != '!');
    cnt_sentences--;
    for (int i = 0; i < cnt_sentences; i++)
    {
        for (int j = 0; sentenses[i][j]; j++)
        {
            printf("%c", sentenses[i][j]);
        }
        free(sentenses[i]);
        printf("\n");
    }
    puts("Dragon flew away!");
    free(sentenses[cnt_sentences]);
    free(sentenses);
    printf("Количество предложений до %ld и количество предложений после %ld",
           cnt_sentences+cnt_delete, cnt_sentences);
    return 0;
}
