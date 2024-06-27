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

MusicalComposition *createMusicalComposition(char *name, char *autor, int year)
{
    MusicalComposition *MusicComp = (MusicalComposition *)malloc(sizeof(MusicalComposition));
    if (MusicComp == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
    }
    MusicComp->name = name;
    MusicComp->author = autor;
    MusicComp->year = year;
    MusicComp->next = NULL;
    MusicComp->prev = NULL;
    return MusicComp;
}

void push(MusicalComposition *head, MusicalComposition *element)
{
    MusicalComposition *tmp = head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = element;
    element->prev = tmp;
}

void removeEl(MusicalComposition *head, char *name_for_remove)
{
    MusicalComposition *tmp = head;
    if (strcmp(tmp->name, name_for_remove) == 0)
    {
        head = tmp->next;
        if (head != NULL)
        {
            head->prev = NULL;
        }
        free(tmp);
        return;
    }
    while (strcmp(tmp->name, name_for_remove) != 0)
    {
        tmp = tmp->next;
    }
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    free(tmp);
}

int count(MusicalComposition *head)
{
    MusicalComposition *tmp = head;
    int count = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    return count;
}

void print_names(MusicalComposition *head)
{
    MusicalComposition *tmp = head;
    while (tmp)
    {
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n)
{
    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition *prev = head;
    for (int i = 1; i < n; i++)
    {
        MusicalComposition *current = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        prev->next = current;
        current->prev = prev;
        prev = current;
    }
    return head;
}

int main()
{
    int length;
    scanf("%d\n", &length);

    char **names = (char **)malloc(sizeof(char *) * length);
    if (names == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
    }
    char **authors = (char **)malloc(sizeof(char *) * length);
    if (authors == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
    }
    int *years = (int *)malloc(sizeof(int) * length);
    if (years == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
    }

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
        if (names[i] == NULL)
        {
            fprintf(stderr, "Memory allocation error!\n");
        }
        authors[i] = (char *)malloc(sizeof(char *) * (strlen(author) + 1));
        if (authors[i] == NULL)
        {
            fprintf(stderr, "Memory allocation error!\n");
        }

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