#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
}MusicalComposition;

// Создание структуры MusicalComposition
MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition *new_composition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    new_composition->name = name;
    new_composition->author = author;
    new_composition->year = year;
    new_composition->prev = NULL;
    new_composition->next = NULL;
    return new_composition;
}

// Функции для работы со списком MusicalComposition
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    if (n <= 0 || !array_names || !array_authors || !array_years) {
        return NULL;  // Возвращаем NULL, если переданы некорректные параметры
    }
    MusicalComposition* head = NULL;
    MusicalComposition* tail = NULL;
    MusicalComposition* composition;
    for (int i = 0; i < n; i++) {
        composition = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
         if (head == NULL) {
            head = composition;
            tail = composition;
        } else {
            tail->next = composition;
            composition->prev = tail;
            tail = composition;
        }
    }
    return head;
}

//функция добавляет элемент в конец списка 
void push(MusicalComposition* head, MusicalComposition* element) {
    if (head == NULL) {
        return; // Список пуст
    }
    MusicalComposition* current = head;
    while (current->next != NULL) {
        current = current->next; 
    }
    current->next = element;
    element->prev = current;
}

//функция удаляет элемент element списка, у которого значение name равно значению name_for_remove
void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name_for_remove) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            return;
        }
        current = current->next;
    }
}

//функция возвращает количество элементов списка
int count(MusicalComposition* head){
    int count = 0;
    MusicalComposition* current = head;
    while (current != NULL){
        count++;
        current = current->next;
    }
    return count; 
}

//функция выводит названия композиций.
void print_names(MusicalComposition* head){
    MusicalComposition* current = head;
    while (current != NULL){
        printf("%s\n", current->name);
        current = current->next;
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
