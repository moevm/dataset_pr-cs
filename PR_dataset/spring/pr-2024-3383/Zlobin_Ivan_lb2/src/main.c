#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition {
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;

} MusicalComposition;


// Создание структуры MusicalComposition

MusicalComposition *createMusicalComposition(char *name, char *autor, int year) {
    MusicalComposition *lst = malloc(sizeof(MusicalComposition));
    lst->name = strdup(name);
    lst->author = strdup(autor);
    lst->year = year;
    lst->next = NULL;
    lst->prev = NULL;
    return lst;
}

// Функции для работы со списком MusicalComposition

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n) {
    MusicalComposition *lst1 = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition *tmp = lst1;
    for (int i = 1; i < n; ++i) {
        MusicalComposition *lst = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        lst->prev = tmp;
        tmp->next = lst;
        tmp = lst;
    }
    tmp->next = NULL;
    return lst1;
}

void push(MusicalComposition *head, MusicalComposition *element) {
    MusicalComposition *tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = element;
    element->next = NULL;
    element->prev = tmp;
}

void removeEl(MusicalComposition *head, char *name_for_remove) {
    MusicalComposition *tmp = head;
    while (strcmp(tmp->name, name_for_remove)) {
        tmp = tmp->next;
    }
    free(tmp->name);
    free(tmp->author);
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    free(tmp);
}

int count(MusicalComposition *head) {
    int cnt = 0;
    MusicalComposition *tmp = head;
    while (tmp != NULL) {
        ++cnt;
        tmp = tmp->next;
    }
    return cnt;
}

void print_names(MusicalComposition *head) {
    MusicalComposition *tmp = head;
    while (tmp != NULL) {
        printf("%s\n", tmp->name);
        tmp = tmp->next;
    }
}


int main(void) {
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
