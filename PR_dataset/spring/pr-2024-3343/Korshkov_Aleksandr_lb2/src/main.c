#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition
{
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
    char *name;
    char *author;
    int year;
} MusicalComposition;

MusicalComposition *createMusicalComposition(char *name, char *autor, int year)
{
    MusicalComposition *structure = malloc(sizeof(MusicalComposition));
    structure->name = name;
    structure->author = autor;
    structure->year = year;
    return structure;
}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n)
{
    MusicalComposition *root = malloc(sizeof(MusicalComposition) * n);
    for (int i = 0; i < n; i++)
    {
        root[i].name = array_names[i];
        root[i].author = array_authors[i];
        root[i].year = array_years[i];
        if (i == 0)
        {
            root[i].prev = NULL;
            root[i].next = &root[i + 1];
        }
        if (i == n - 1)
        {
            root[i].next = NULL;
            root[i].prev = &root[i - 1];
        }
        else
        {
            root[i].next = &root[i + 1];
            root[i].prev = &root[i - 1];
        }
    }
    return root;
}

void push(MusicalComposition *head, MusicalComposition *element)
{
    MusicalComposition *old_element = head;
    while (old_element->next != NULL)
    {
        old_element = old_element->next;
    }
    element->prev = old_element;
    old_element->next = element;
}

void removeEl(MusicalComposition *head, char *name_for_remove)
{
    MusicalComposition *element = head;
    while (element != NULL)
    {
        if ((strstr(name_for_remove, element->name) != NULL) && (strlen(name_for_remove) == strlen(element->name)))
        {
            if (element->next == NULL)
            {
                element->prev->next = NULL;
            }
            else
            {
                element->next->prev = element->prev;
                element->prev->next = element->next;
            }
            
        }
        element = element->next;
    }
}

int count(MusicalComposition *head)
{
    int n = 0;
    MusicalComposition *element = head;
    while (element != NULL)
    {
        n++;
        element = element->next;
    }
    return n;
}

void print_names(MusicalComposition *head)
{
    MusicalComposition *element = head;
    while (element != NULL)
    {
        printf("%s\n", element->name);
        element = element->next;
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