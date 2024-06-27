#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition
{
    char *name;
    char *author;
    int year;
    struct MusicalComposition *left;
    struct MusicalComposition *right;
} MusicalComposition;

MusicalComposition *createMusicalComposition(char *name, char *author, int year);
MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n);
void push(MusicalComposition *head, MusicalComposition *element);
void removeEl(MusicalComposition *head, char *name_for_remove);
int count(MusicalComposition *head);
void print_names(MusicalComposition *head);

MusicalComposition *createMusicalComposition(char *name, char *author, int year)
{
    MusicalComposition *composition = (MusicalComposition *)malloc(sizeof(MusicalComposition));
    composition->name = name;
    composition->author = author;
    composition->year = year;
    composition->left = NULL;
    composition->right = NULL;
    return composition;
}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n)
{
    if (n <= 0)
    {
        return NULL;
    }
    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    for (int i = 1; i < n; ++i)
    {
        MusicalComposition *new = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        push(head, new);
    }
    return head;
}

void push(MusicalComposition *head, MusicalComposition *element)
{
    MusicalComposition *temp = head;
    if (temp != NULL)
    {
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        temp->right = element;
        element->left = temp;
    }
}

void removeEl(MusicalComposition *head, char *name_for_remove)
{
    MusicalComposition *temp = head;
    if (!strcmp(temp->name, name_for_remove)) {
        return;
    }
    while (temp != NULL)
    {
        if (!strcmp(temp->name, name_for_remove))
        {
            if (temp->left != NULL)
            {
                temp->left->right = temp->right;
            }
            if (temp->right != NULL)
            {
                temp->right->left = temp->left;
            }
            free(temp);
            temp = NULL;
            break;
        }
        temp = temp->right;
    }
}

int count(MusicalComposition *head)
{
    MusicalComposition *temp = head;
    int count = 0;
    while (temp != NULL)
    {
        count += 1;
        temp = temp->right;
    }
    return count;
}

void print_names(MusicalComposition *head)
{
    MusicalComposition *temp = head;
    while (temp != NULL)
    {
        printf("%s\n", temp->name);
        temp = temp->right;
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