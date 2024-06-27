#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition

typedef struct MusicalComposition {
    char name[80];
    char author[80];
    int year;
    struct MusicalComposition *parent;
    struct MusicalComposition *child;
} MusicalComposition;


// Создание структуры MusicalComposition
MusicalComposition *createMusicalComposition(const char *name, const char *author, int year) {
    MusicalComposition *musicalComposition = malloc(sizeof(MusicalComposition));
   
    strcpy(musicalComposition->name, name);
    strcpy(musicalComposition->author, author);
    musicalComposition->year = year;

    return musicalComposition;
}

// Функции для работы со списком MusicalComposition

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n) {
    MusicalComposition *compositions = malloc(sizeof(MusicalComposition) * n);
   

    for (int i = 0; i < n; ++i) {
        strcpy(compositions[i].name, array_names[i]);
        strcpy(compositions[i].author, array_authors[i]);
        compositions[i].year = array_years[i];
        compositions[i].parent = NULL;
        compositions[i].child = NULL;
        if (i != 0) {
            compositions[i].parent = &compositions[i - 1];
            compositions[i - 1].child = &compositions[i];
        }
    }

    return compositions;
}

void push(MusicalComposition *head, MusicalComposition *element) {
    MusicalComposition *current = head;
    while (current->child != NULL) {
        current = current->child;
    }
    current->child = element;
    element->parent = current;
}

void removeEl(MusicalComposition *head, char *name_for_remove) {
    MusicalComposition *current = head;
    while (current != NULL) {
        if (strcmp(name_for_remove, current->name) == 0) {
            current->parent->child = current->child;
            current->child->parent = current->parent;
        };
        current = current->child;
    }
}

int count(MusicalComposition *head) {
    MusicalComposition *current = head;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->child;
    }

    return count;
}

void print_names(MusicalComposition *head) {
    MusicalComposition *current = head;
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->child;
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