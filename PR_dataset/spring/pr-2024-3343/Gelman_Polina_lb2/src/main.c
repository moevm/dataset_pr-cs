#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MusicalComposition
{
    char* name;
    char* author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* author, int year)
{
    MusicalComposition* musComp = malloc(sizeof(MusicalComposition));
    musComp->name = name;
    musComp->author = author;
    musComp->year = year;
    
    return musComp;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
    MusicalComposition* MusicalCompositionList = malloc(sizeof(MusicalComposition) * n);
    for (int i = 0; i < n; ++i)
    {
        MusicalCompositionList[i].name = array_names[i];
        MusicalCompositionList[i].author = array_authors[i];
        MusicalCompositionList[i].year = array_years[i];
        
        if (i > 0) {
            MusicalCompositionList[i].prev = &MusicalCompositionList[i - 1];
        }
        
        if (i < n - 1) {
            MusicalCompositionList[i].next = &MusicalCompositionList[i + 1];
        }
    }
    
    return MusicalCompositionList;
}

void push(MusicalComposition*  head, MusicalComposition* element)
{
    MusicalComposition* ptr = head;
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = element;
    element->prev = ptr;
}

void removeEl (MusicalComposition*  head, char* name_for_remove)
{
    MusicalComposition *ptr = head;
    while(ptr != NULL)
    {
        if (strcmp(name_for_remove, ptr->name) == 0)
        {
            ptr->prev->next = ptr->next;
            ptr->next->prev = ptr->prev;
        };
        ptr = ptr->next;
    }
}

int count(MusicalComposition*  head)
{
    MusicalComposition* ptr = head;
    int cnt = 0;
    while (ptr != NULL){
        cnt++;
        ptr = ptr->next;
    }
    return cnt;
}

void print_names(MusicalComposition*  head) 
{
    MusicalComposition* ptr = head;
    while (ptr != NULL){
        printf("%s\n", ptr->name);
        ptr = ptr->next;
    }
}


int main(){
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
