#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define END_OF_STRING '\0'

// Описание структуры MusicalComposition
typedef struct MusicalComposition{
        char* name;
        char* author;
        int year;
        struct MusicalComposition* prev;
        struct MusicalComposition* next;
}MusicalComposition;


// Создание структуры MusicalComposition

//MusicalComposition* createMusicalComposition(char* name, char* autor,int year);
MusicalComposition* createMusicalComposition(char* name, char* author, int year){
        MusicalComposition* track = (MusicalComposition*)malloc(sizeof(MusicalComposition));
	if(!track){
		perror("No memory");
	}

        track->name = name;
        track->author = author;
        track->year = year;
        track->next = NULL;
        track->prev = NULL;
        return track;
}

// Функции для работы со списком MusicalComposition

//MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years,int n){
        MusicalComposition* head = NULL;
        MusicalComposition* list = createMusicalComposition(array_names[0],array_authors[0],array_years[0]);
        list->next = NULL;
        list->prev = NULL;
        head = list;

        for(int i = 1;i<n;i++){
                list->next = createMusicalComposition(array_names[i],array_authors[i],array_years[i]);
                MusicalComposition* address_to_save = list;

                list = list->next;
                list->next = NULL;
                list->prev = address_to_save;
        }
        return head;
}

//void push(MusicalComposition* head, MusicalComposition* element);
void push(MusicalComposition* head, MusicalComposition* element){

        if(head==NULL){
                head = element;
                return;
        }else{
            MusicalComposition* cur = head;
            while(cur->next){
                    cur = cur->next;
            }
            element->prev = cur;
            cur->next = element;
            element->next = NULL;
        }
}

//void removeEl(MusicalComposition* head, char* name_for_remove);
void removeEl(MusicalComposition* head, char* name_for_remove){
        if(head==NULL)
                return;

        MusicalComposition* cur = head;
	    if(strcmp(head->name, name_for_remove)==0){
		    return;
		}
        MusicalComposition* save;
        while(cur->next!=NULL){
                if(strcmp(cur->name,name_for_remove)==0){
                    cur->next->prev = cur->prev;
                    cur->prev->next = cur->next;
                    save = cur->next;
                    free(cur);
                    cur = save;
                }else{
                       // if(cur->next!=NULL)
                                cur = cur->next;
                }
        }
}

//int count(MusicalComposition* head);
int count(MusicalComposition* head){
        int counter = 0;
        MusicalComposition* cur = head;
        while(cur->next!=NULL){
                counter++;
                cur = cur->next;}
        return counter+1;
}

//void print_names(MusicalComposition* head);
void print_names(MusicalComposition* head){
        MusicalComposition* cur = head;
        if(head==NULL)
                printf("No music yet:(\n");
        else{
                while(cur->next!=NULL){
                        printf("%s\n",cur->name);
                        cur = cur->next;
                }
                printf("%s\n",cur->name);
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
