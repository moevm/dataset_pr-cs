#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition{
    char name[80];
    char author[80];
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
} MusicalComposition;

MusicalComposition* createComposition(char* name, char* author, int year){
    MusicalComposition *composition = (MusicalComposition *) malloc(sizeof(MusicalComposition));
    strcpy(composition->name, name);
    strcpy(composition->author, author);
    composition->year = year;
    composition->next = NULL;
    composition->prev = NULL;

    return composition;
}

MusicalComposition* createCompositionList(char** names, char** authors, int* years, int n){
    MusicalComposition *head = createComposition(names[0], authors[0], years[0]);
    if (n != 1){
        MusicalComposition *composition = createComposition(names[1], authors[1], years[1]);
        head->next = composition;
        for (int i = 2; i < n; i++){
            composition->next = createComposition(names[i], authors[i], years[i]);
            composition = composition->next;
        }
    }
    return head;
}

void pushComposition(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition *composition = head;
    while(composition->next){
        composition = composition->next;
    }
    composition->next = element;
}

void removeComposition(MusicalComposition* head, char* name_for_remove){
    MusicalComposition *del_composition;
    if (strcmp(head->name, name_for_remove) == 0){
        del_composition = head;
        head = head -> next;
        free(del_composition);
    }else{
        while (head->next){
            if (strcmp(head->next->name, name_for_remove) == 0){
                del_composition = head->next;
                head->next = head->next->next;
                free(del_composition);
            }
            head = head->next;
        }
    }
}

int countCompositions(MusicalComposition* head){
    MusicalComposition *composition = head;
    int count = 0;
    while(composition){
        count++;
        composition = composition->next;
    }
    return count;
}

void printCompositionNames(MusicalComposition* head){
    MusicalComposition *composition = head;
    while (composition){
        puts(composition->name);
        composition = composition->next;
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
        fscanf(stdin, "%d\n", years + i);

        (*strstr(name, "\n")) = '\0';
        (*strstr(author, "\n")) = '\0';

        names[i] = (char *) malloc(sizeof(char *) * (strlen(name) + 1));
        authors[i] = (char *) malloc(sizeof(char *) * (strlen(author) + 1));

        strcpy(names[i], name);
        strcpy(authors[i], author);
    }
    MusicalComposition *head = createCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push, "\n")) = '\0';
    (*strstr(author_for_push, "\n")) = '\0';

    MusicalComposition *element_for_push = createComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove, "\n")) = '\0';

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = countCompositions(head);

    printf("%d\n", k);
    pushComposition(head, element_for_push);

    k = countCompositions(head);
    printf("%d\n", k);

    removeComposition(head, name_for_remove);
    printCompositionNames(head);

    k = countCompositions(head);
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