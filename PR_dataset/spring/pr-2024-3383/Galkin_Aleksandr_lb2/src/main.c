#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition {
    char *name;
    char *author;
    int year;
    struct MusicalComposition *prev;
    struct MusicalComposition *next;
} MusicalComposition;

MusicalComposition *createMusicalComposition(char *name, char *author, int year) {
    MusicalComposition *composition = (MusicalComposition *) calloc(1, sizeof(MusicalComposition));
    composition->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(composition->name, name);
//    composition->name = strdup(name);
    composition->author = (char *) malloc(sizeof(char) * (strlen(author) + 1));
    strcpy(composition->author, author);
//    composition->author = strdup(author);
    composition->year = year;
    return composition;
}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n) {
    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition *tmp1 = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
    head->prev = NULL;
    head->next = tmp1;
    tmp1->prev = head;
    for (int i = 2; i < n; i++) {
        tmp1->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        tmp1->next->prev = tmp1;
        tmp1->next->next = NULL;
        tmp1 = tmp1->next;
    }
    return head;
}

void push(MusicalComposition *head, MusicalComposition *element) {
    MusicalComposition *tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = element;
    element->prev = tmp;
    element->next = NULL;
}

void removeEl(MusicalComposition *head, char *name_for_remove) {
    MusicalComposition *tmp = head;
    for (; tmp != NULL;) {
        if (strcmp(tmp->name, name_for_remove) == 0) {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            free(tmp->author);
            free(tmp->name);
            free(tmp);
        }
        tmp = tmp->next;
    }
}

int count(MusicalComposition *head) {
    MusicalComposition *tmp = head;
    int n = 0;
    for (; tmp != NULL;) {
        n++;
        tmp = tmp->next;
    }
    return n;
}

void print_names(MusicalComposition *head) {
    MusicalComposition *tmp = head;
    for (; tmp != NULL;) {
        printf("%s\n", tmp->name);
        tmp = tmp->next;
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