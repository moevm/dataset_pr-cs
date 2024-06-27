#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct MusicalComposition
{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
};

struct MusicalComposition* createMusicalComposition(char* name, char* author, int year)
{
    struct MusicalComposition* musical_composition = (struct MusicalComposition*)malloc(sizeof(struct MusicalComposition));
    musical_composition->name = name;
    musical_composition->author = author;
    musical_composition->year = year;
    musical_composition->prev = NULL;
    musical_composition->next = NULL;
    return musical_composition;
}

struct MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
    struct MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    struct MusicalComposition* prev_musical_composition = head;
    struct MusicalComposition* curr_musical_composition;
    for(int i = 1; i < n; i++)
    {   
        curr_musical_composition = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        prev_musical_composition->next = curr_musical_composition;
        curr_musical_composition->prev = prev_musical_composition;
        prev_musical_composition = curr_musical_composition;
    }
    return head;
}

void push(struct MusicalComposition* head, struct MusicalComposition* element)
{
    struct MusicalComposition* curr_musical_composition = head;
    while (curr_musical_composition->next != NULL)
        curr_musical_composition = curr_musical_composition->next;
        
    curr_musical_composition->next = element;
    element->prev = curr_musical_composition;
}

void removeEl(struct MusicalComposition* head, char* name_for_remove)
{
    struct MusicalComposition* curr_musical_composition = head;
    struct MusicalComposition* next_musical_composition = curr_musical_composition->next;
    do
    {
        if (strcmp(curr_musical_composition->name, name_for_remove) == 0)
        {
            curr_musical_composition->prev->next = next_musical_composition;
            next_musical_composition->prev = curr_musical_composition->prev;
            free(curr_musical_composition);
        }
        curr_musical_composition = next_musical_composition;
        if (next_musical_composition != NULL) next_musical_composition = next_musical_composition->next;
    }while (curr_musical_composition != NULL);
}

int count(struct MusicalComposition* head)
{
    int counting = 0;
    struct MusicalComposition* curr_musical_composition = head;
    while (curr_musical_composition != NULL)
    {
        curr_musical_composition = curr_musical_composition->next;
        counting++;
    }
    return counting;
}

void print_names(struct MusicalComposition* head)
{
    struct MusicalComposition* curr_musical_composition = head;
    do
    {
        puts(curr_musical_composition->name);
        curr_musical_composition = curr_musical_composition->next;
    }while (curr_musical_composition != NULL);
}

int main()
{
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    struct MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    struct MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

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

    for (int i=0;i<length;i++)
    {
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;
}
