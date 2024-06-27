#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Описание структуры MusicalComposition
typedef struct MusicalComposition {
    char *name, *author;
    int year;
    struct MusicalComposition* next;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    MusicalComposition* _new = malloc(sizeof(MusicalComposition));
    _new->name = name;
    _new->author = author;
    _new->year = year;
    _new->next = NULL;
    return _new;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    // assuming n always >= 1
    MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* cursor = head;

    for (size_t i = 1; i < n; i++) {
        cursor->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        cursor = cursor->next;
    }
    return head;
};

void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition* cursor = head;
    while (cursor->next != NULL) {
        cursor = cursor->next;
    }
    cursor->next = element;
};

MusicalComposition* removeEl(MusicalComposition* node, char* name_for_remove) {
    if (node == NULL)
        return node;
    MusicalComposition* next_valid = removeEl(node->next, name_for_remove);

    if (strcmp(name_for_remove, node->name) == 0) {
        return next_valid;
    } else {
        node->next = next_valid;
        return node;
    }
};

int count(MusicalComposition* head) {
    MusicalComposition* cursor = head;
    int _count = 0;
    while (cursor != NULL) {
        _count++;
        cursor = cursor->next;
    }
    return _count;
};

void print_names(MusicalComposition* head) {
    MusicalComposition* cursor = head;
    while (cursor != NULL) {
        puts(cursor->name);
        cursor = cursor->next;
    }
};

int main() {
    int length;
    scanf("%d\n", &length);

    char** names = (char**)malloc(sizeof(char*) * length);
    char** authors = (char**)malloc(sizeof(char*) * length);
    int* years = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++) {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name, "\n")) = 0;
        (*strstr(author, "\n")) = 0;

        names[i] = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        authors[i] = (char*)malloc(sizeof(char) * (strlen(author) + 1));

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
    (*strstr(name_for_push, "\n")) = 0;
    (*strstr(author_for_push, "\n")) = 0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

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
