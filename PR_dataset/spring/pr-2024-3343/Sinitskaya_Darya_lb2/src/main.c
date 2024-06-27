#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//описание структуры MusicalComposition
typedef struct MusicalComposition {
    char name[80]; 
    char author[80];
    int year;
    struct MusicalComposition* next; //следующий элемент
    struct MusicalComposition* prev; //предыдущий элемент
} MusicalComposition;

//создание структуры MusicalComposition
MusicalComposition* createMusicalComposition(char* name, char* author, int year) {
    //выделение памяти под новую музыкальную композицию
    MusicalComposition* newComposition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    //копирование переданных значений имени и автора
    strcpy(newComposition->name, name);
    strcpy(newComposition->author, author);
    //присвоение года созданной композиции
    newComposition->year = year;
    //указатель на след. элемент устанавл. в NULL так как элемент еще не добавлен в список
    newComposition->next = NULL;
    //указатель на пред. элемент устанавл. в NULL так как элемент еще не добавлен в список
    newComposition->prev = NULL;
    //возвращение указателя на новую музыкальную композицию
    return newComposition;
}

//функция создания списка MusicalComposition
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n) {
    //указатель на начало списка
    MusicalComposition* head = NULL;
    //указатель для перемещения по списку
    MusicalComposition* current = NULL;

    //создание списка композиций на основе переданных данных
    for (int i = 0; i < n; i++) {
        MusicalComposition* newComposition = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
	//если список пустой, устанавливаем новую композицию как начальный элемент списка
        if (head == NULL) {
            head = newComposition;
            current = head;
        } else {
            //если список не пустой, добавляем новую композицию в конец списка
            current->next = newComposition; //указание на следующую композицию
            newComposition->prev = current; //создание ссылки на предыдущую композицию
            current = newComposition; //перемещение указателя на новую композицию
        }
    }
    //возвращение указателя на начало списка музыкальных композиций
    return head;
}

//добавление нового элемента в конец списка
void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition* current = head;
    //перемещение в конец списка
    while (current->next != NULL) {
        current = current->next;
    }
    //добавление нового элемента
    current->next = element;
    element->prev = current;
}

//удаление элемента из списка по названию
void removeEl(MusicalComposition* head, char* name_for_remove) {
    MusicalComposition* current = head;
    //перебор элементов списка
    while (current != NULL) {
        //поиск элемента по названию и удаление его из списка
        if (strcmp(current->name, name_for_remove) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            //освобождение памяти, занимаемой удаляемым элементом
            free(current);
            break;
        }
        //переход к следующему элементу
        current = current->next;
    }
}

//подсчет количества элементов в списке
int count(MusicalComposition* head) {
    int count = 0; //инициализация счётчика количества элементов
    MusicalComposition* current = head;
    //перебор элементов списка
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

//вывод названий композиций из списка
void print_names(MusicalComposition* head) {
    MusicalComposition* current = head;
    //перебор элементов списка
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}

int main() {
    int length;
    scanf("%d\n", &length);

    char** names = (char**)malloc(sizeof(char*) * length);
    char** authors = (char**)malloc(sizeof(char*) * length);
    int* years = (int*)malloc(sizeof(int) * length);

    //считывание и заполнение массивов данных
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

    //создание списка музыкальных композиций
    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);

    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    //добавление новой композиции
    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push, "\n")) = 0;
    (*strstr(author_for_push, "\n")) = 0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    //удаление композиции по названию и вывод результатов
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

    //освобождение памяти
    for (int i = 0; i < length; i++) {
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;
}
