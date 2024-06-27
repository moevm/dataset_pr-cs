#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF 10
#define TEXT_END '!'
#define SENTENCE_ENDS ".;?"
#define TARGET '7'
#define OUTPUT_STUB "Количество предложений до %d и количество предложений после %d\n"

void strip_sentences(char **text, int *size);
void insert_new_lines(char **text, int *size, int lines_count);
void remove_target(char **text, int *size, int sentences_count);
int sentences_count(char *text, int size);
int is_sentence_end(char element);
char* input_text(int* size);
void output_text(char* text, int size, int initial_count, int result_count);
int main()
{
    int size = 0;

    char* text = input_text(&size);
    int initial_count = sentences_count(text, size);
    strip_sentences(&text, &size);
    insert_new_lines(&text, &size, initial_count);
    remove_target(&text, &size, initial_count);
    int result_count = sentences_count(text, size);
    output_text(text, size, initial_count, result_count);
    free(text);
    return 0;
}

void output_text(char* text, int size, int initial_count, int result_count) {
    for (int i = 0; i < size; ++i)
    {
        printf("%c", text[i]);
    }
    printf("\n");
    printf(OUTPUT_STUB, initial_count, result_count);
}

char* input_text(int* size) {
    int capacity = BUF;
    char *text = (char *)malloc(capacity * sizeof(char));
    char ch = getchar();
    while (ch != TEXT_END)
    {
        text[(*size)++] = ch;
        if (*size == capacity - 1)
        {
            capacity += BUF;
            text = (char *)realloc(text, capacity * sizeof(char));
            if (text == NULL)
            {
                break;
            }
        }
        ch = getchar();
    }
    text[(*size)++] = TEXT_END;
    text[*size] = '\0';
    return text;
}

void strip_sentences(char **text, int *size)
{
    char *stripped_text = (char *)malloc(*size * sizeof(char));
    int stripped_size = 0;
    char last_char = SENTENCE_ENDS[0];
    for (int i = 0; i < *size; ++i)
    {
        if (is_sentence_end(last_char))
        {
            if (!isspace((*text)[i]))
            {
                stripped_text[stripped_size++] = (*text)[i];
                last_char = (*text)[i];
            }
            else
            {
                last_char = SENTENCE_ENDS[0];
            }
        }
        else
        {
            stripped_text[stripped_size++] = (*text)[i];
            last_char = (*text)[i];
        }
    }
    stripped_text[stripped_size] = '\0';
    free(*text);
    *text = stripped_text;
    *size = stripped_size;
}
void insert_new_lines(char **text, int *size, int sentences_count)
{
    char *inserted_text = (char *)malloc((*size + sentences_count + 1) * sizeof(char));
    int inserted_size = 0;
    for (int i = 0; i < *size; ++i)
    {
        inserted_text[inserted_size++] = (*text)[i];
        if (is_sentence_end((*text)[i]))
        {
            inserted_text[inserted_size++] = '\n';
        }
    }
    inserted_text[inserted_size] = '\0';
    free(*text);
    *text = inserted_text;
    *size = inserted_size;
}
void remove_target(char **text, int *size, int sentences_count)
{
    int *pending_removes_from = (int *)malloc(sentences_count * sizeof(int));
    int *pending_removes_to = (int *)malloc(sentences_count * sizeof(int));
    int pending_removes_size = 0;
    int current_start_index = 0;
    int needs_to_be_removed = 0;
    for (int i = 0; i < *size; ++i)
    {
        if ((*text)[i] == TARGET)
        {
            needs_to_be_removed = 1;
        }
        if (is_sentence_end((*text)[i]))
        {
            if (needs_to_be_removed)
            {
                pending_removes_from[pending_removes_size] = current_start_index;
                pending_removes_to[pending_removes_size] = i + 2;
                pending_removes_size++;
                current_start_index = i + 2;
                needs_to_be_removed = 0;
            }
            else
            {
                current_start_index = i + 2;
            }
        }
    }
    int chars_to_remove = 0;
    for (int j = 0; j < pending_removes_size; ++j)
    {
        for (int l = (pending_removes_from)[j]; l < (pending_removes_to)[j]; ++l)
        {
            (*text)[l] = -1;
            chars_to_remove++;
        }
    }
    char *removed_text = (char *)malloc((*size - chars_to_remove + 1) * sizeof(char));
    int removed_size = 0;
    for (int k = 0; k < *size; ++k)
    {
        if ((*text)[k] != -1)
        {
            removed_text[removed_size++] = (*text)[k];
        }
    }
    removed_text[removed_size] = '\0';
    free(*text);
    free(pending_removes_from);
    free(pending_removes_to);
    *text = removed_text;
    *size = removed_size;
}
int sentences_count(char *text, int size)
{
    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (is_sentence_end(text[i]))
        {
            count += 1;
        }
    }
    return count;
}
int is_sentence_end(char element)
{
    for (int i = 0; i < strlen(SENTENCE_ENDS); ++i)
    {
        if (SENTENCE_ENDS[i] == element)
        {
            return 1;
        }
    }
    return 0;
}
