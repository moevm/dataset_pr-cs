#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


typedef struct MusicalComposition {

    struct MusicalComposition *next;
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next2;
    struct MusicalComposition *next3;

} MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition *newMusic = (MusicalComposition*) malloc(sizeof(MusicalComposition));
    newMusic->name = strdup(name);
    newMusic->author = strdup(author);
    newMusic->year = year;
    newMusic->next = NULL;
    return newMusic;
}

void push(MusicalComposition* head, MusicalComposition* element);

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){

    MusicalComposition *music = (MusicalComposition*) createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    music->next2 = NULL;
    int i = 1;
    while (i < n){
        MusicalComposition *music2 = (MusicalComposition*) createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        push(music, music2);
        i++;
    }
    return music;

}

void push(MusicalComposition* head, MusicalComposition* element){

    while(head->next) 
        {head = head->next;}
    head->next = element;
    element->next2 = head;

}

void removeEl(MusicalComposition* head, char* name_for_remove){

    while (strcmp(head->name, name_for_remove) != 0) {
        if (head)
            {head = head->next;}
        else
            {break;}
    }

	if (!head) 
        {return;}
	if (head->next)
        {head->next->next2 = head->next2;}
	if (head->next2) 
        {head->next2->next = head->next;}
}

int count(MusicalComposition* head){

    int cnt = 0;
    while(head){
        cnt++;
        head = head->next;
    }
    return cnt;

}

void print_names(MusicalComposition *head) {

    for (int i = 0; head != NULL; i++) {
        printf("%s\n", head->name);
        head = head->next;
    }

}


int main() {
    int length;
    scanf("%d\n", &length);

    char **names = (char **) malloc(sizeof(char *) * length);
    char **authors = (char **) malloc(sizeof(char *) * length);
    int *years = (int *) malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++) {
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

    for (int i = 0; i < length; i++) {
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;

}