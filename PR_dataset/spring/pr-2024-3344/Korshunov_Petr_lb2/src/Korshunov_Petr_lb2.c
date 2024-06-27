#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition MUSCOMP;
// Описание структуры MusicalComposition
struct MusicalComposition
{
    char *name;
    char *author;
    int year;
    MUSCOMP *prev;
    MUSCOMP *next;
};

// Создание структуры MusicalComposition

MUSCOMP *createMusicalComposition(char *name, char *autor, int year);

// Функции для работы со списком MusicalComposition

MUSCOMP *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n);

void push(MUSCOMP *head, MUSCOMP *element);

void removeEl(MUSCOMP *head, char *name_for_remove);

int count(MUSCOMP *head);

void print_names(MUSCOMP *head);

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
    MUSCOMP *head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push, "\n")) = 0;
    (*strstr(author_for_push, "\n")) = 0;

    MUSCOMP *element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

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

MUSCOMP *createMusicalComposition(char *name, char *autor, int year)
{
    MUSCOMP *mus = (MUSCOMP *)malloc(sizeof(MUSCOMP));

    if (!mus)
    {
        printf("Error: failed to allocate memory");
        exit(0);
    }

    mus->name = name;
    mus->author = autor;
    mus->year = year;

    return mus;
}

MUSCOMP *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n)
{
    MUSCOMP *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    head->prev = NULL;
    MUSCOMP *prev = head;
    for (int i = 1; i < n; i++)
    {
        MUSCOMP *temp = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        prev->next = temp;
        temp->prev = prev;
        prev = temp;
    }
    prev->next = NULL;

    return head;
}

void push(MUSCOMP *head, MUSCOMP *element)
{
    MUSCOMP *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = element;
    element->prev = temp;
    element->next = NULL;

    return;
}

void removeEl(MUSCOMP *head, char *name_for_remove)
{
    MUSCOMP *temp = head;
    while (temp->next != NULL)
    {
        if (strcmp(temp->name, name_for_remove) == 0)
        {
            MUSCOMP *before = temp->prev;
            MUSCOMP *after = temp->next;
            before->next = after;
            after->prev = before;
            free(temp);
            temp = after;
        }
        else
        {
            temp = temp->next;
        }
    }
}

int count(MUSCOMP *head)
{
    MUSCOMP *temp = head;
    int c = 1;
    while (temp->next != NULL)
    {
        ++c;
        temp = temp->next;
    }
    return c;
}

void print_names(MUSCOMP *head)
{
    MUSCOMP *temp = head;
    while (temp->next != NULL)
    {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
    printf("%s\n", temp->name);
}