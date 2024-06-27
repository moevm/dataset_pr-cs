#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition{
    char* name;
    char* autor;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
    
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
    MusicalComposition* element = malloc(sizeof(MusicalComposition));
    element->name = name;
    element->autor = autor;
    element->year = year;
    element->prev = NULL;
    element->next = NULL;
    
    return element;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* MusicalCompositionList = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);

    for(int i = 1; i<n; i++){
        MusicalComposition* new_el = createMusicalComposition(array_names[i],array_authors[i],array_years[i]);
        MusicalComposition* temp = MusicalCompositionList;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_el;
        new_el->prev = temp;
    }

    return MusicalCompositionList;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* temp = head;
    
    if(temp == NULL){
        head = element;
    }else{
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = element;
        element->prev = temp;
    }
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* temp = head;
    
    while(temp != NULL){
        if(strstr(temp->name, name_for_remove)){
            if(temp->prev != NULL && temp->next != NULL){
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            if(temp->prev == NULL && temp->next != NULL){
                temp->next->prev = NULL;
            }
            if(temp->prev != NULL && temp->next == NULL){
                temp->prev->next = NULL;
            }
            break;
        }
        temp = temp->next;
    }
}

int count(MusicalComposition* head){
    MusicalComposition* temp = head;
    int count = 0;
    
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    
    return count;
}

void print_names(MusicalComposition* head){
    MusicalComposition* temp = head;
    
    while(temp != NULL){
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

    for (int i=0;i<length;i++)
    {
        char* name = malloc(sizeof(char)*80);
        char* author = malloc(sizeof(char)*80);;

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
    char* name_for_push = malloc(sizeof(char)*80);
    char* author_for_push = malloc(sizeof(char)*80);
    int year_for_push;

    char* name_for_remove = malloc(sizeof(char)*80);

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->autor, head->year);
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