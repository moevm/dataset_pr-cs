#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* previous;
}MusicalComposition;

// Создание структуры MusicalComposition
MusicalComposition* createMusicalComposition(char* name, char* author, int year){
    MusicalComposition* mus_compos = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    mus_compos->name = name;
    mus_compos->author = author;
    mus_compos->year = year;
    return mus_compos;
}

// Функции для работы со списком MusicalComposition
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head;
    if(n != 0){
        head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
        if(n != 1){
            MusicalComposition *temp = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);
            head->next = temp;
            temp->previous = head;
            for (int i = 2; i < n; i++) {
                temp->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
                temp->next->previous = temp;
                temp = temp->next;
            }
        }
    }
    return head;
}

// Добавление элемента в конец списка
void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition *temp = head;
    while(temp->next != 0)
        temp = temp->next;
    temp->next = element;
    element->previous = temp;
    element->next = NULL;
}

// Удаление элемента, у которого name равен name_for_remove
void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition *temp = head;
    while(temp != 0){
        if(!strcmp(temp->name, name_for_remove)){
            if(temp->previous == NULL && temp->next == NULL){
            	free(temp);
                head = NULL;
            }else if(temp->previous == NULL){
                head = temp->next;
                free(head->previous);
            }else if(temp->next == NULL){
                MusicalComposition *temp_second = temp->previous;
                free(temp);
                temp_second->next = NULL;
            }else{
                MusicalComposition *temp_previous = temp->previous;
                temp_previous->next = temp->next;
                temp->next->previous = temp_previous;
                free(temp);
            }
            break;
        }
        temp = temp->next;
    }
}

// Количество элементов в списке
int count(MusicalComposition* head){
    MusicalComposition *temp = head;
    int k = 1;
    while (temp->next){
        k += 1;
        temp = temp->next;
    }
    return k;
}

// Вывод названия композиций
void print_names(MusicalComposition* head){
    MusicalComposition *temp = head;
    for (size_t i = 0; i < count(head); i++){
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++){
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
