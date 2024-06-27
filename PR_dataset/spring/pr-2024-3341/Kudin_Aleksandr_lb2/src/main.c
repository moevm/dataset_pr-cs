#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Song {
    char* title;
    char* composer;
    int releaseYear;
    struct Song* next;
    struct Song* prev;
} Song;

Song* createSong(char* title, char* composer, int releaseYear) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    newSong->title = (char*)calloc(strlen(title) + 1, sizeof(char));
    newSong->composer = (char*)calloc(strlen(composer) + 1, sizeof(char));
    strcpy(newSong->title, title);
    strcpy(newSong->composer, composer);
    newSong->releaseYear = releaseYear;
    newSong->next = NULL;
    newSong->prev = NULL;
    return newSong;
}

Song* createSongList(char** titles, char** composers, int* years, int count) {
    Song* listHead = createSong(titles[0], composers[0], years[0]);
    Song* current = listHead;
    for (int i = 1; i < count; i++) {
        Song* nextSong = createSong(titles[i], composers[i], years[i]);
        nextSong->prev = current;
        current->next = nextSong;
        current = nextSong;
    }
    return listHead;
}

void addSong(Song* head, Song* newSong) {
    Song* end = head;
    while (end->next != NULL)
        end = end->next;
    end->next = newSong;
    newSong->prev = end;
}

void deleteSong(Song* head, char* titleToRemove) {
    Song* temp = head;
    while (temp != NULL && strcmp(temp->title, titleToRemove) != 0)
        temp = temp->next;
    if (temp != NULL && strcmp(temp->title, titleToRemove) == 0) {
        if (temp->prev != NULL)
            temp->prev->next = temp->next;
        if (temp->next != NULL)
            temp->next->prev = temp->prev;
        free(temp->title);
        free(temp->composer);
        free(temp);
    }
}

int countSongs(Song* head) {
    int count = 0;
    Song* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void printTitles(Song* head) {
    Song* current = head;
    while (current != NULL) {
        puts(current->title);
        current = current->next;
    }
}

int main() {
    int length;
    scanf("%d\n", &length);

    char** titles = (char**)malloc(sizeof(char*) * length);
    char** composers = (char**)malloc(sizeof(char*) * length);
    int* years = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++) {
        char title[80];
        char composer[80];

        fgets(title, 80, stdin);
        fgets(composer, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        title[strcspn(title, "\n")] = 0;
        composer[strcspn(composer, "\n")] = 0;

        titles[i] = (char*)malloc(sizeof(char) * (strlen(title) + 1));
        composers[i] = (char*)malloc(sizeof(char) * (strlen(composer) + 1));

        strcpy(titles[i], title);
        strcpy(composers[i], composer);
    }

    Song* head = createSongList(titles, composers, years, length);

    char titleForAdd[80];
    char composerForAdd[80];
    int yearForAdd;

    char titleForDelete[80];

    fgets(titleForAdd, 80, stdin);
    fgets(composerForAdd, 80, stdin);
    fscanf(stdin, "%d\n", &yearForAdd);
    titleForAdd[strcspn(titleForAdd, "\n")] = 0;
    composerForAdd[strcspn(composerForAdd, "\n")] = 0;

    Song* newSong = createSong(titleForAdd, composerForAdd, yearForAdd);

    fgets(titleForDelete, 80, stdin);
    titleForDelete[strcspn(titleForDelete, "\n")] = 0;

    printf("%s %s %d\n", head->title, head->composer, head->releaseYear);
    int k = countSongs(head);

    printf("%d\n", k);
    addSong(head, newSong);

    k = countSongs(head);
    printf("%d\n", k);

    deleteSong(head, titleForDelete);
    printTitles(head);

    k = countSongs(head);
    printf("%d\n", k);

    for (int i = 0; i < length; i++) {
        free(titles[i]);
        free(composers[i]);
    }
    free(titles);
    free(composers);
    free(years);

    return 0;
}
