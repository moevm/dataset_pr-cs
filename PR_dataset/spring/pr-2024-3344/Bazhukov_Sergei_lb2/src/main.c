#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

typedef struct MusicalComposition
{
    char *name;
    char *author;
    int year;
    struct MusicalComposition *prev;
    struct MusicalComposition *next;
} MusicalComposition;

MusicalComposition *createMusicalComposition(char *name, char *autor, int year);
MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n);
void push(MusicalComposition *head, MusicalComposition *element);
void removeEl(MusicalComposition *head, char *name_for_remove);
int count(MusicalComposition *head);
void print_names(MusicalComposition *head);

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

MusicalComposition *createMusicalComposition(char *name, char *autor, int year)
{
    MusicalComposition *composition = (MusicalComposition *)malloc(sizeof(MusicalComposition));
    composition->name = name;
    composition->author = autor;
    composition->year = year;
    composition->prev = NULL;
    composition->next = NULL;
    return composition;
}

void push(MusicalComposition *head, MusicalComposition *element)
{
    MusicalComposition *p = head;
    while (p->next)
    {
        p = p->next;
    }
    p->next = element;
    element->prev = p;
}

void removeEl(MusicalComposition *head, char *name_for_remove)
{
    MusicalComposition *p = head;
    while (p && strcmp(p->name, name_for_remove))
    {
        p = p->next;
    }
    if (p->prev == NULL) p->next->prev = NULL;
    else if (p->next == NULL) p->prev->next = NULL;
    else
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    free(p);
}

int count(MusicalComposition *head)
{
    int count = 0;
    MusicalComposition *p = head;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

void print_names(MusicalComposition *head)
{
    MusicalComposition *p = head;
    while (p)
    {
        printf("%s\n", p->name);
        p = p->next;
    }
}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n){   
    if (n < 1) return NULL;
    MusicalComposition* head;
    for (size_t i = 0; i < n; i++)
    {   
        
        MusicalComposition *p = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        if (i){
            push(head, p);
        }
        else{
            head = p;
        }
    }
    return head;
}