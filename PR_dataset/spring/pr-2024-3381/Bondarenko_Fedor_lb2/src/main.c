#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 80

// Описание структуры MusicalComposition
typedef struct MusicalComposition
{
    char *name;
    char *author;
    int year;

    struct MusicalComposition *next;
    struct MusicalComposition *previous;

} MusicalComposition;

void push(MusicalComposition *head, MusicalComposition *element);
void freeMusicalComposition(MusicalComposition *musicalCompositionToFree);

// Создание структуры MusicalComposition

MusicalComposition *createMusicalComposition(char *name, char *author, int year)
{
    MusicalComposition *musicalComposition =
        (MusicalComposition *)malloc(sizeof(MusicalComposition));
    musicalComposition->name = (char *)calloc(CAPACITY, sizeof(char));
    musicalComposition->author = (char *)calloc(CAPACITY, sizeof(char));

    strncpy(musicalComposition->name, name, CAPACITY);
    strncpy(musicalComposition->author, author, CAPACITY);
    musicalComposition->year = year;
    musicalComposition->next = NULL;
    musicalComposition->previous = NULL;

    return musicalComposition;
}

// Функции для работы со списком MusicalComposition

MusicalComposition *createMusicalCompositionList(char **array_names,
                                                 char **array_authors,
                                                 int *array_years, int n)
{
    MusicalComposition *head;
    if (n > 0)
    {
        head = createMusicalComposition(array_names[0], array_authors[0],
                                        array_years[0]);
    }
    for (size_t i = 1; i < n; i++)
    {
        MusicalComposition *element = createMusicalComposition(
            array_names[i], array_authors[i], array_years[i]);
        push(head, element);
    }

    return head;
}

void push(MusicalComposition *head, MusicalComposition *element)
{
    if (head != NULL)
    {
        MusicalComposition *temporary = head;
        while (temporary->next != NULL)
        {
            temporary = temporary->next;
        }

        temporary->next = element;
        element->previous = temporary;
        element->next = NULL;
    }
}

void removeEl(MusicalComposition *head, char *name_for_remove)
{
    MusicalComposition *temporary = head;
    while (temporary != NULL)
    {
        if (!strcmp(temporary->name, name_for_remove))
        {
            if (temporary->previous != NULL)
            {
                temporary->previous->next = temporary->next;
            }
            if (temporary->next != NULL)
            {
                temporary->next->previous = temporary->previous;
            }
            freeMusicalComposition(temporary);
            temporary = NULL;
            break;
        }
        temporary = temporary->next;
    }
}

int count(MusicalComposition *head)
{
    int countOfElements = 0;
    if (head != NULL)
    {
        MusicalComposition *element = head;
        while (element != NULL)
        {
            countOfElements++;
            element = element->next;
        }
    }

    return countOfElements;
}

void print_names(MusicalComposition *head)
{
    if (head != NULL)
    {
        MusicalComposition *element = head;
        while (element != NULL)
        {
            printf("%s\n", element->name);
            element = element->next;
        }
    }
}

void freeMusicalComposition(MusicalComposition *musicalCompositionToFree)
{
    free(musicalCompositionToFree->name);
    free(musicalCompositionToFree->author);
    free(musicalCompositionToFree);
}

int main()
{
    int length;
    scanf("%d\n", &length);

    char **names = (char **)malloc(sizeof(char *) * length);
    char **authors = (char **)malloc(sizeof(char *) * length);
    int *years = (int *)malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name, "\n")) = 0;
        (*strstr(author, "\n")) = 0;

        names[i] = (char *)malloc(sizeof(char *) * (strlen(name) + 1));
        authors[i] = (char *)malloc(sizeof(char *) * (strlen(author) + 1));

        strcpy(names[i], name);
        strcpy(authors[i], author);
    }
    MusicalComposition *head =
        createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push, "\n")) = 0;
    (*strstr(author_for_push, "\n")) = 0;

    MusicalComposition *element_for_push =
        createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove, "\n")) = 0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(head, name_for_remove);
    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i = 0; i < length; i++)
    {
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;
}
