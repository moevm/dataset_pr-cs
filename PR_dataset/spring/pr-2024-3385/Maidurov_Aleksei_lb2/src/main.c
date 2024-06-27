#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition
{
    char *name, *author;
    int year;
    struct MusicalComposition *next, *previous;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition *createMusicalComposition(char *name, char *author, int year)
{
    MusicalComposition *node = malloc(sizeof(MusicalComposition));
    node->name = name;
    node->author = author;
    node->year = year;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

// Функции для работы со списком MusicalComposition

void push(MusicalComposition *head, MusicalComposition *element)
{
    MusicalComposition *curr;
    curr = head;
    if (curr == NULL)
        return;
    while (curr->next)
    {
        curr = curr->next;
    }
    curr->next = element;
    element->previous = curr;
}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n)
{
    MusicalComposition *head, *node;
    head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    for (int i = 1; i < n; i++)
    {
        node = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        push(head, node);
    }
    return head;
}

void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* curr = head;
    while(curr->next) {
        if (!strcmp(curr->name, name_for_remove)) {
            if (!curr->previous) {
                MusicalComposition* next_curr = curr->next;
                curr->name = next_curr->name;
                curr->author = next_curr->author;
                curr->year = next_curr->year;
                curr->next = next_curr->next;
                curr->next->next->previous = curr;
                curr = next_curr;
            }
            else {
                curr->previous->next = curr->next;
                if (curr->next) curr->next->previous = curr->previous;
            }
            free(curr);
            break;
        }
        curr = curr->next;
    }
}


int count(MusicalComposition *head)
{
    MusicalComposition *curr;
    curr = head;
    int n = 0;
    for (; curr != NULL; n++, curr = curr->next);
    return n;
}

void print_names(MusicalComposition *head)
{
    MusicalComposition *curr;
    curr = head;
    for(; curr; curr = curr->next)
    {
        printf("%s\n", curr->name);
    }
}

void freeList(MusicalComposition* head) {
    MusicalComposition* curr = head;
    MusicalComposition* curr_next;
    do {
        curr_next = curr->next;
        free(curr);
        curr = curr_next;
    } while (curr->next);
    free(curr);
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

    freeList(head);
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