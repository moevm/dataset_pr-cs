#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition
{
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
} MusicalComposition;

MusicalComposition *createMusicalComposition(char *name, char *author, int year)
{
    MusicalComposition *composition = (MusicalComposition *)malloc(sizeof(MusicalComposition));
    composition->name = name;
    composition->author = author;
    composition->year = year;
    return composition;
}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n)
{
    MusicalComposition *list[n];
    for (int i = 0; i < n; i++)
    {
        list[i] = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
    }
    list[0]->prev = NULL;
    list[0]->next = list[1];
    int last_el = n - 1;
    list[last_el]->next = NULL;
    list[last_el]->prev = list[n - 2];
    for (int i = 1; i < last_el; i++)
    {
        list[i]->prev = list[i - 1];
        list[i]->next = list[i + 1];
    }
    return list[0];
}

void push(MusicalComposition *head, MusicalComposition *element)
{
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = element;
    element->prev = head;
    element->next = NULL;
}

void removeEl(MusicalComposition *head, char *name_for_remove)
{
    MusicalComposition *pointer = head;
    if ((strcmp(head->name, name_for_remove) == 0))
    {
        head->next->prev = NULL;
        head = head->next;
    }
    while (1)
    {
        pointer = pointer->next;
        if (strcmp(pointer->name, name_for_remove) == 0)
        {
            if (pointer->next != NULL)
                pointer->next->prev = pointer->prev;
            pointer->prev->next = pointer->next;
        }
        if (pointer->next == NULL)
            break;
    }
}

int count(MusicalComposition *head)
{
    int count = 0;
    MusicalComposition *pointer = head;
    while (1)
    {
        count++;
        if (pointer->next == NULL)
            break;
        pointer = pointer->next;
    }
    return count;
}

void print_names(MusicalComposition *head)
{
    MusicalComposition *pointer = head;
    while (1)
    {
        printf("%s\n", pointer->name);
        if (pointer->next != NULL)
        {
            pointer = pointer->next;
        }
        else
            break;
    }
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
    MusicalComposition *head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push, "\n")) = 0;
    (*strstr(author_for_push, "\n")) = 0;

    MusicalComposition *element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

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