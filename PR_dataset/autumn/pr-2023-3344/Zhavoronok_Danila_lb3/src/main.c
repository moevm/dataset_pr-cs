#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct String
{
    char *text;
    int length;
    int capacity;
} string;

typedef struct Text
{
    string **sentences;
    int length;
    int capacity;
} text;

void init_str(string *str)
{
    str->capacity = 2048;
    str->length = 0;
    str->text = (char *)malloc(str->capacity * sizeof(char));
}

void init_text(text *txt)
{
    txt->capacity = 16;
    txt->length = 0;
    txt->sentences = (string **)malloc(txt->capacity * sizeof(string *));
}

void enlarge_str(string *str)
{
    str->capacity *= 2;
    str->text = (char *)realloc((str->text), str->capacity * sizeof(char));
    // printf("enlarged str. new capacity: %d\n", str->capacity);
}

void enlarge_text(text *txt)
{
    txt->capacity *= 2;
    txt->sentences = (string **)realloc((txt->sentences), txt->capacity * sizeof(string *));
    // printf("enlarged str. new capacity: %d\n", txt->capacity);
}

void append_str(string *str, char *ch)
{
    strcat(str->text, ch);
    str->length++;
    if (str->length == str->capacity - 1)
        enlarge_str(str);
}

void append_text(text *txt, string *str)
{
    txt->sentences[txt->length++] = str;
    if (txt->length == txt->capacity)
        enlarge_text(txt);
}

void print_str(string *str)
{
    // printf("%s length: %d, addres: %d\n", str->text, str->length, str);
    printf("%s\n", str->text);
}

void print_text(text *txt)
{
    for (int i = 0; i < txt->length; i++)
    {
        print_str(txt->sentences[i]);
    }
    // printf("\n");
}

int more_than_one_uppercase_letter(string *str)
{
    int count = 0;
    for (int i = 0; i < str->length; i++)
    {
        if ('A' <= str->text[i] && str->text[i] <= 'Z')
            count++;
        if (count > 1)
            return 1;
    }
    return 0;
}

text *get_text()
{
    int inputed_sentences = 0;

    text *text = malloc(sizeof(text));
    init_text(text);

    char *temp = malloc(sizeof(char));
    do
    {
        string *str = malloc(sizeof(string));
        init_str(str);
        do
        {
            *temp = getchar();
            if ((*temp == ' ' || *temp == '\t' ) && str->length == 0)
                continue;
            append_str(str, temp);
        } while (*temp != ';' && *temp != '.' && *temp != '?' && *temp != '!');
        if (!more_than_one_uppercase_letter(str))
            append_text(text, str);
        else
            free(str);

        inputed_sentences++;
    } while (*temp != '!');

    print_text(text);
    printf("Количество предложений до %d и количество предложений после %d", inputed_sentences - 1, text->length - 1);

    free(temp);
    return text;
}

int main()
{
    get_text();
    return 0;
}