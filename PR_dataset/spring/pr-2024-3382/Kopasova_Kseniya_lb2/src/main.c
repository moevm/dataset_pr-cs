#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 80
// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    
    struct MusicalComposition* next;
} MusicalComposition;

// Создание структуры MusicalComposition
MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* cur = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    cur->name = name;
    cur->author = author;
    cur->year = year;
    cur->next = NULL;
    return cur;
}

// Функции для работы со списком MusicalComposition
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = NULL;
    MusicalComposition* list = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    head = list;
    for (int i=1; i<n; i++){
        list->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        list = list->next;
    }
    return head;
}

//Добавление нового элемента
void push(MusicalComposition* head, MusicalComposition* element){
    if (head == NULL) {
        head = element;
        element->next = NULL;
    } else {
        MusicalComposition *cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = element;
        element->next = NULL;
    }
}
//Удаляем элемент с нужным именем
void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* cur = head;
    
    MusicalComposition* prev = NULL;
    while (cur != NULL) {
        if (strcmp(cur->name, name_for_remove) == 0) {
            if (prev == NULL) {
                head = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
        }
        prev = cur;
        cur = cur->next;
    }
}

//считаем количество элементов списка
int count(MusicalComposition* head){
    MusicalComposition* cur = head;
    int sum = 0;
    while (cur != NULL){
        sum++;
        cur=cur->next;
    }
    return sum;
}
//выводим имена
void print_names(MusicalComposition* head){
    MusicalComposition* cur = head;
    while (cur != NULL){
        printf("\n%s", cur->name);
        cur=cur->next;
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


    printf("%s %s %d\n", head->name, head->author, head->year);//выводит первую конструкцию MusicalComposition
    int k = count(head);

    printf("%d\n", k);//количество элементов
    push(head, element_for_push);

    k = count(head);
    printf("%d", k);
    
    removeEl(head, name_for_remove); 
    print_names(head);

    k = count(head);
    printf("\n%d", k);

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    
    free(names);
    free(authors);
    free(years);

    return 0;
}