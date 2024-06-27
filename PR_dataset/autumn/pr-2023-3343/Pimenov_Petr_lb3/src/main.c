#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BLOCK_SIZE 10
#define TEXT_END '!'
#define SENTENCE_ENDS ".;?"
#define REMOVE_TARGET '7'
#define OUTPUT_STUB "Количество предложений до %ld и количество предложений после %ld\n"

void strip_sentences(char **text, size_t *size);
void insert_new_lines(char **text, size_t *size, size_t lines_count);
void remove_target(char **text, size_t *size, size_t sentences_count);
size_t sentences_count(char *text, size_t size);
int is_sentence_end(char element);

int main()
{
    size_t size = 0;
    size_t capacity = BLOCK_SIZE;
    char *text = (char *)malloc(capacity * sizeof(char));
    char ch = getchar();
    while (ch != TEXT_END)
    {
        text[size++] = ch;
        if (size == capacity - 1)
        {
            capacity += BLOCK_SIZE;
            text = (char *)realloc(text, capacity * sizeof(char));
            if (text == NULL)
            {
                // если realloc вернул NULL, то считывание текста далее невозможно, программу следует завершить
                break;
            }
        }
        ch = getchar();
    }
    text[size++] = TEXT_END;
    text[size] = '\0';

    size_t initial_count = sentences_count(text, size);
    strip_sentences(&text, &size);
    insert_new_lines(&text, &size, initial_count);
    remove_target(&text, &size, initial_count);
    size_t result_count = sentences_count(text, size);
    for (size_t i = 0; i < size; ++i)
    {
        printf("%c", text[i]);
    }
    printf("\n");
    printf(OUTPUT_STUB, initial_count, result_count);
    free(text);
    return 0;
}

void strip_sentences(char **text, size_t *size)
{
    char *stripped_text = (char *)malloc(*size * sizeof(char));
    size_t stripped_size = 0;
    char last_char = SENTENCE_ENDS[0];
    for (size_t i = 0; i < *size; ++i)
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
void insert_new_lines(char **text, size_t *size, size_t sentences_count)
{
    char *inserted_text = (char *)malloc((*size + sentences_count + 1) * sizeof(char));
    size_t inserted_size = 0;
    for (size_t i = 0; i < *size; ++i)
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
void remove_target(char **text, size_t *size, size_t sentences_count)
{
    size_t *pending_removes_from = (size_t *)malloc(sentences_count * sizeof(size_t));
    size_t *pending_removes_to = (size_t *)malloc(sentences_count * sizeof(size_t));
    size_t pending_removes_size = 0;
    size_t current_start_index = 0;
    int needs_to_be_removed = 0;
    for (size_t i = 0; i < *size; ++i)
    {
        if ((*text)[i] == REMOVE_TARGET)
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
    size_t chars_to_remove = 0;
    for (size_t j = 0; j < pending_removes_size; ++j)
    {
        for (size_t l = (pending_removes_from)[j]; l < (pending_removes_to)[j]; ++l)
        {
            (*text)[l] = -1;
            chars_to_remove++; // записываем в ячейки на удаление несимвольное значение
        }
    }
    char *removed_text = (char *)malloc((*size - chars_to_remove + 1) * sizeof(char));
    size_t removed_size = 0;
    for (size_t k = 0; k < *size; ++k)
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
size_t sentences_count(char *text, size_t size)
{
    size_t count = 0;
    for (size_t i = 0; i < size; ++i)
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
    for (size_t i = 0; i < strlen(SENTENCE_ENDS); ++i)
    {
        if (SENTENCE_ENDS[i] == element)
        {
            return 1;
        }
    }
    return 0;
}