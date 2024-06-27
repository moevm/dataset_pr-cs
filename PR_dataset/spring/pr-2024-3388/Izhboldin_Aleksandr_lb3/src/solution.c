#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Errors
#define MEMORY_ALLOC_ERROR  1
#define FILE_OPEN_ERROR     2

void my_error(int *err);

// Sentences
typedef struct
{
    size_t size;
    size_t memsize;
    char *sentence;
} Sentence;

#define SENTENCE_BUFFER 512

Sentence *read_sentence(FILE *stream, int *err);
Sentence *create_sentence(int *err);
void delete_sentence(Sentence **sentence);
void add_symbol_to_sentence(Sentence *sentence, char symbol, int *err);
void add_string_to_sentence(Sentence *sentence, char *str, int *err);

// Text (sentences array)
#define TEXT_BUFFER 32

typedef struct
{
    size_t size;
    size_t memsize;
    Sentence **sentences;
} Text;

Text *create_text(int *err);
void delete_text(Text **text);
void add_sentence_to_text(Text *text, Sentence *sentence, int *err);

// Main-settings
#define START_FILE "file.txt"
#define START_DIR "./labyrinth"
#define FILE_EXT ".txt"
#define FILE_DEADLOCK "Deadlock"
#define FILE_TARGET "Minotaur"
#define FILE_INCLUDE_PREF "@include "
#define FILE_OUTPUT "./result.txt"
#define READ_MOD "r"
#define WRITE_MOD "w"

void make_answer(Text *text);
bool is_file_end(Sentence *file_path, Text *pathway, int *err);
Sentence *search_file(char *dir_path, char *file, int *err);

int main(void)
{
    int err = 0;
    Text *pathway = create_text(&err);
    is_file_end(search_file(START_DIR, START_FILE, &err), pathway, &err);
    make_answer(pathway);
    if (err)
    {
        my_error(&err);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void make_answer(Text *text)
{
    FILE *file = fopen(FILE_OUTPUT, WRITE_MOD);
    if (file)
        for (int i = text->size - 1; i >= 0; i--)
            fprintf(file, "%s\n", text->sentences[i]->sentence);

    delete_text(&text);
    fclose(file);
}

bool is_file_end(Sentence *file_path, Text *pathway, int *err)
{
    FILE *file = fopen(file_path->sentence, READ_MOD);
    bool is_found = 0;

    if (file)
    {
        while (true)
        {
            Sentence *line = read_sentence(file, err);
            if (!line || line->size == 0)
            {
                delete_sentence(&line);
                *err = MEMORY_ALLOC_ERROR;
                break;
            }

            if (!strcmp(line->sentence, FILE_DEADLOCK))
            {
                delete_sentence(&line);
                break;
            }

            if (!strcmp(line->sentence, FILE_TARGET))
            {
                is_found = true;
                delete_sentence(&line);
                break;
            }

            bool next = is_file_end(search_file(START_DIR, line->sentence + strlen(FILE_INCLUDE_PREF), err),
                                        pathway, err);
            if (next)
            {
                is_found = true;
                delete_sentence(&line);
                break;
            }

            delete_sentence(&line);
        }
    } else
    {
        *err = FILE_OPEN_ERROR;
        my_error(err);
    }

    if (is_found)
        add_sentence_to_text(pathway, file_path, err);
    else
        delete_sentence(&file_path);

    fclose(file);
    return is_found;
}

Sentence *search_file(char *dir_path, char *file, int *err)
{
    DIR *dir = opendir(dir_path);
    Sentence *ans = NULL;
    if (dir)
    {
        struct dirent *de = readdir(dir);
        while (de)
        {
            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            {
                Sentence *full_path = create_sentence(err);
                add_string_to_sentence(full_path, dir_path, err);
                add_symbol_to_sentence(full_path, '/', err);
                add_string_to_sentence(full_path, de->d_name, err);
                if (*err)
                {
                    my_error(err);
                    delete_sentence(&full_path);
                    break;
                }

                if (strlen(de->d_name) >= strlen(FILE_EXT) && strstr(de->d_name, FILE_EXT)) // if file
                {
                    if (!strcmp(de->d_name, file))
                    {
                        ans = full_path;
                        break;
                    }
                } else // if directory
                {
                    Sentence *next = search_file(full_path->sentence, file, err);
                    if (next != NULL)
                    {
                        ans = (Sentence *) next;
                        delete_sentence(&full_path);
                        break;
                    }
                }

                delete_sentence(&full_path);
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
    return ans;
}


void my_error(int *err)
{
    switch (*err)
    {
        case MEMORY_ALLOC_ERROR:
            fprintf(stdout, "Error: Memory allocation error\n");
            break;
        case FILE_OPEN_ERROR:
            fprintf(stdout, "Error: Failed to open file\n");
            break;
    }
}

// Create a sentence and read from stream
Sentence *read_sentence(FILE *stream, int *err)
{
    Sentence *sentence = create_sentence(err);
    if (*err)
    {
        delete_sentence(&sentence);
        return NULL;
    }
    while (true)
    {
        char c = (char) fgetc(stream);
        if (c != EOF && c != '\n')
            add_symbol_to_sentence(sentence, c, err);

        if (*err)
        {
            delete_sentence(&sentence);
            my_error(err);
            return NULL;
        }

        if (c == EOF || c == '\n')
            break;
    }
    return sentence;
}

// Constructor for sentences
Sentence *create_sentence(int *err)
{
    Sentence *new_sentence = malloc(sizeof(Sentence));
    if (new_sentence == NULL)
    {
        delete_sentence(&new_sentence);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }
    new_sentence->size = 0;
    new_sentence->memsize = SENTENCE_BUFFER;
    new_sentence->sentence = calloc(SENTENCE_BUFFER, sizeof(char));
    if (new_sentence->sentence == NULL)
    {
        delete_sentence(&new_sentence);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }
    return new_sentence;
}

// Destructor for sentences
void delete_sentence(Sentence **sentence)
{
    free((*sentence)->sentence);
    (*sentence)->sentence = NULL;
    free(*sentence);
    *sentence = NULL;
}

// Add symbol to sentence in the end
void add_symbol_to_sentence(Sentence *sentence, char symbol, int *err)
{
    if (sentence == NULL)
        return;
    if (*err)
        return;

    if (sentence->size >= sentence->memsize)
    {
        sentence->memsize += SENTENCE_BUFFER;
        sentence->sentence = realloc(sentence->sentence, sentence->memsize * sizeof(char));
        if (sentence->sentence == NULL)
        {
            delete_sentence(&sentence);
            *err = MEMORY_ALLOC_ERROR;
            return;
        }
    }
    sentence->sentence[sentence->size] = symbol;
//    sentence->sentence[sentence->size+1] = '\0';
    sentence->size++;
}


void add_string_to_sentence(Sentence *sentence, char *str, int *err)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        add_symbol_to_sentence(sentence, str[i], err);
        if (*err)
        {
            my_error(err);
            delete_sentence(&sentence);
            return;
        }
    }
}

Text *create_text(int *err)
{
    Text *new_text = (Text *) malloc(sizeof(Text));
    if (new_text == NULL)
    {
        delete_text(&new_text);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }

    new_text->size = 0;
    new_text->memsize = TEXT_BUFFER;
    new_text->sentences = (Sentence **) calloc(TEXT_BUFFER, sizeof(Sentence *));
    if (new_text->sentences == NULL)
    {
        delete_text(&new_text);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }

    return new_text;
}

// Destructor for text
void delete_text(Text **text)
{
    for (size_t i = 0; i < (*text)->size; i++)
        if ((*text)->sentences[i] != NULL)
            delete_sentence(&((*text)->sentences[i]));

    free((*text)->sentences);
    (*text)->sentences = NULL;
    free(*text);
    *text = NULL;
}

// Add sentence to text
void add_sentence_to_text(Text *text, Sentence *sentence, int *err)
{
    if (text == NULL || sentence == NULL) return;

    if (*err)
    {
        delete_sentence(&sentence);
        delete_text(&text);
        return;
    }

    if (text->size >= text->memsize)
    {
        text->memsize += TEXT_BUFFER;
        text->sentences = (Sentence **) realloc(text->sentences, text->memsize * sizeof(Sentence *));
        if (text->sentences == NULL)
        {
            delete_sentence(&sentence);
            delete_text(&text);
            *err = MEMORY_ALLOC_ERROR;
            return;
        }
    }
    text->sentences[text->size] = sentence;

    text->size++;
}