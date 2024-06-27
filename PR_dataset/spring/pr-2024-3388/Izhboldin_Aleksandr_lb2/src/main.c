#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition
{
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next, *prev;
} MusicalComposition;

// Создание структуры MusicalComposition
MusicalComposition *createMusicalComposition(char *name, char *author, int year)
{
    MusicalComposition *new_musical_composition = (MusicalComposition *) (malloc(sizeof(MusicalComposition)));

    if (new_musical_composition == NULL)
    {
        fprintf(stdout, "----- ERROR: FAILED TO ALLOCATE MEMORY -----\n");
        free(new_musical_composition);
        exit(EXIT_FAILURE);
    }

    new_musical_composition->name = name;
    new_musical_composition->author = author;
    new_musical_composition->year = year;
    new_musical_composition->prev = NULL;
    new_musical_composition->next = NULL;

    return new_musical_composition;
}

// Функции для работы со списком MusicalComposition
MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n)
{
    if (n <= 0)
    {
        fprintf(stdout, "----- ERROR: INCORRECT SIZE OF ARRAYS -----\n");
        exit(EXIT_FAILURE);
    }
    MusicalComposition *musical_composition_list = createMusicalComposition(array_names[0],
                                                                            array_authors[0],
                                                                            array_years[0]);

    MusicalComposition *iter = musical_composition_list;
    for (size_t i = 1; i < n; i++)
    {
        MusicalComposition *new_composition = createMusicalComposition(array_names[i],
                                                                       array_authors[i],
                                                                       array_years[i]);
        iter->next = new_composition;
        new_composition->prev = iter;
        iter = iter->next;
    }

    return musical_composition_list;
}

void push(MusicalComposition *head, MusicalComposition *element)
{
    if (head == NULL)
    {
        fprintf(stdout, "----- ERROR: LIST DOESN'T EXIST -----\n");
        exit(EXIT_FAILURE);
    }
    while (head->next != NULL)
        head = head->next;
    head->next = element;
}

void removeEl(MusicalComposition *head, char *name_for_remove)
{
    while (head != NULL)
    {
        if (strcmp(head->name, name_for_remove) == 0)
        {
            if (head->prev != NULL)
                head->prev->next = head->next;
            if (head->next != NULL)
                head->next->prev = head->prev;
            free(head);
            return;
        }
        head = head->next;
    }

    fprintf(stdout, "----- ERROR: NO ELEMENT WITH NAME: %s -----\n", name_for_remove);
    exit(EXIT_FAILURE);
}

int count(MusicalComposition *head)
{
    int size = 0;
    while (head != NULL)
    {
        size++;
        head = head->next;
    }
    return size;
}

void print_names(MusicalComposition *head)
{
    while (head != NULL)
    {
        printf("%s\n", head->name);
        head = head->next;
    }
}

int main()
{
    int length;
    scanf("%d\n", &length);

    char **names = (char **) malloc(sizeof(char *) * length);
    char **authors = (char **) malloc(sizeof(char *) * length);
    int *years = (int *) malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name, "\n")) = 0;
        (*strstr(author, "\n")) = 0;

        names[i] = (char *) malloc(sizeof(char *) * (strlen(name) + 1));
        authors[i] = (char *) malloc(sizeof(char *) * (strlen(author) + 1));

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
