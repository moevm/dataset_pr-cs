#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition {
    char *name;
    char *author;
    int year;

    struct MusicalComposition *prev;
    struct MusicalComposition *next;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition *createMusicalComposition(char *name, char *author, int year) {
    MusicalComposition *temp = (MusicalComposition *) malloc(sizeof(MusicalComposition));
    if (temp == NULL) {
        return NULL;
    }

    temp->name = strdup(name);
    temp->author = strdup(author);
    temp->year = year;
    temp->prev = NULL;
    temp->next = NULL;

    return temp;
}

// Функции для работы со списком MusicalComposition

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n) {
    if (n < 1) {
        return NULL;
    }
    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition *prev = head;

    for (size_t i = 1; i < n; i++) {
        MusicalComposition *curr = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        if (curr == NULL) {
            while (prev) {
                prev = prev->prev;
                free(prev->next);
            }
            return NULL;
        }
        prev->next = curr;
        curr->prev = prev;
        prev = curr;
    }

    return head;
}

void push(MusicalComposition *head, MusicalComposition *element) {
    MusicalComposition *curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = element;
    element->prev = curr;
}

void removeEl(MusicalComposition *head, const char *name_for_remove) {
    MusicalComposition *curr = head;
    while (curr) {
        if (strcmp(curr->name, name_for_remove) == 0) {
            free(curr->name);
            free(curr->author);
            if (curr->prev && curr->next) {
                // middle element in list
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            } else if (curr->prev) {
                // last element in list
                curr->prev->next = NULL;
            } else if (curr->next) {
                // first element in list
                MusicalComposition *new_head = curr->next;
                curr->name = new_head->name;
                curr->author = new_head->author;
                curr->year = new_head->year;
                curr->next = new_head->next;

                free(new_head);
                break;
            } else {
                // there is only one item in the list and it needs to be deleted
            }
            free(curr);
            break;
        }
        curr = curr->next;
    }
}

int count(MusicalComposition *head) {
    int cnt = 0;
    MusicalComposition *curr = head;
    while (curr) {
        cnt++;
        curr = curr->next;
    }
    return cnt;
}

void print_names(MusicalComposition *head) {
    MusicalComposition *curr = head;
    while (curr) {
        printf("%s\n", curr->name);
        curr = curr->next;
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

