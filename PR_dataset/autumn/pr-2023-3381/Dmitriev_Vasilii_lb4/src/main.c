#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000

struct Words{
    char** words;
    int size;
};


struct Words* get_words(char* text){
    int i=0;
    char** words = (char**)malloc(SIZE * sizeof(char*));
    char* word = strtok(text," .");
    while(word !=NULL){
        words[i] = (char*)malloc(100 * sizeof(char));
        strcpy(words[i],word);
        word = strtok(NULL," .");
        i++;
    }
    struct Words* new_words = malloc(sizeof(struct Words));
    new_words->words = words;
    new_words->size = i;
    return new_words;
}

int compare(const void* one, const void* two){
    const char** o = (const char**)one;
    const char** t = (const char**)two;
    int result = strcmp(*o,*t);
    return result;
}

char* read_text(int size){
    char* text = (char*)malloc(size * sizeof(char));
    fgets(text,size * sizeof(char),stdin);
    text = strtok(text,"\n");
    return text;
}

void all_free(struct Words* struct_words){
    for (int i=0;i<(struct_words->size);i++){
        // printf("%s",struct_words->words[i]);
        free(struct_words->words[i]);
    }
    free(struct_words->words);
    free(struct_words);

}

int main(){
    char* text = read_text(SIZE);
    char* word = read_text(30);

    struct Words* struct_words = get_words(text);
    qsort(struct_words->words,struct_words->size,sizeof(char*),compare);
    char** adress = (char**)bsearch(&word,struct_words->words,struct_words->size,sizeof(char*),compare);
    
    if (adress!=NULL){
        puts("exists");
    }
    else{
        puts("doesn't exist");

    }
    
    free(text);
    free(word);
    all_free(struct_words);
    return 0;
}

