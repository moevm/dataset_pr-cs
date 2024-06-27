#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BAD_ALLOC "Error: bad alloc\n"



typedef struct  MusicalComposition
{
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
    char name[80];
    char author[80];
    int year;

} MusicalComposition;


MusicalComposition *
createMusicalComposition(char *name, char *author, int year)
{
    MusicalComposition *comp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    if (comp == NULL) 
    {
        fprintf(stderr, BAD_ALLOC);
        exit(EXIT_FAILURE);
    }

    strncpy(comp->name, name, sizeof(comp->name)-1);
    strncpy(comp->author, author, sizeof(comp->author)-1);
    comp->year = year;
    comp->next = NULL;
    comp->prev = NULL;

    return comp;

}


MusicalComposition *
createMusicalCompositionList(
    char **array_names, 
    char **array_authors, 
    int *array_years, 
    int n
)
{
    if (n < 1) 
        return NULL;

    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition *prev = head;
    MusicalComposition *curr = head;

    for(size_t i = 1; i < n; i++)
    {
        curr = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        prev->next = curr;
        curr->prev = prev;
        prev = curr;
    }

    return head;

}


void 
push(MusicalComposition *head, MusicalComposition *element)
{
    if (head == NULL)
    {
        element->next = NULL;
        element->prev = NULL;
        return;
    }

    while(head->next != NULL)
        head = head->next;
    
    head->next = element;
    element->prev = head;

}


void 
removeEl(MusicalComposition *head, char *name_for_remove)
{
    if (head == NULL)
        return;
    
    while(strcmp(head->name, name_for_remove) != 0 && head->next != NULL)
        head = head->next;

    if (head->next == NULL && strcmp(head->name, name_for_remove) != 0)
        return;

    if(head->next != NULL && head->prev != NULL)
    {
        head->prev->next = head->next;
        head->next->prev = head->prev;

    } else if(head->next != NULL && head->prev == NULL)
        head->next->prev = NULL;

    else if(head->next == NULL && head->prev != NULL)
        head->prev->next = NULL;
    
    free(head);

}


int 
count(MusicalComposition *head)
{
    if(head == NULL)
        return 0;

    int cnt = 1;
    while(head->next != NULL)
    {
        cnt++;
        head = head->next;
    }

    return cnt;

}


void 
print_names(MusicalComposition *head)
{
    while (head != NULL)
    {
        fprintf(stdout, "%s\n", head->name);
        head = head->next;
    }

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
    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

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

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;

}
