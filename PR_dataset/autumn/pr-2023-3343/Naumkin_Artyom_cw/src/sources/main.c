#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "input.h"
#include "output.h"
#include "textprocessing.h"
#include "countnums.h"
#include "sorted.h"
#include "task_9.h"


int main(void)
{
    printf("Course work for option 4.7, created by Artyom Naumkin.\n");
    size_t mode;
    scanf("%zu", &mode);
    Text text;

    switch (mode)
    {
        case 0:
            text = input_text();
            print_text(&text);
            break;
        case 1:
            text = input_text();
            count_digits(&text);
            break;
        case 2:
            text = input_text();
            flip_all_text(&text);
            print_text(&text);
            break;
        case 3:
            text = input_text();
            remove_with_physics(&text);
            print_text(&text);
            break;
        case 4:
            text = input_text();
            sort_three_letter_word(&text);
            print_text(&text);
            break;
        case 5:
            printf("0 - Read and print text\n"
                    "1 - Print a list of all the numbers found the text\n"
                    "2 - Flip words in the sentence\n"
                    "3 - Delete all sentences with \"physics\"\n"
                    "4 - Sort sentences by reducing the number of words\n"
                    "5 - Help");
            break;
        case 9:
            text = input_text();
            sort_count_words(&text);
            print_text(&text);
            break;
        default:
            fprintf(stderr, "Error: incorrect input");
            exit(0);
    }
    if (mode != 5)
        free_memory(&text);

    return 0;
}
