#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK 100;
const char* TEXT_FORMAT_OUT = "%s\n";

typedef struct {
    char* sentence;
    int size;
} Sentence;

typedef struct {
    Sentence* sentences;
    int size;
    int real_size;
    int start_size;
    int finish_size;
} Text;

Text createText() {
    Text text;
    text.size = 10;
    text.real_size = 0;

    text.start_size = -1;
    text.finish_size = -1;

    text.sentences = malloc(text.size * sizeof(Sentence));
    return text;
}

void addSentence(Text* text, Sentence sentence) {
    if(text->real_size == text->size) {
        text->size += BLOCK;
        text->sentences = realloc(text->sentences, text->size * sizeof(Sentence));
    }
    text->sentences[text->real_size++] = sentence;
}

Sentence readSentence(Text* text) {
    Sentence sentence;
    sentence.size = BLOCK;
    sentence.sentence = (char*)malloc(sentence.size * sizeof(char));

    char ch;
    int i;

    for(i=0; i<=sentence.size; i++) {
        ch = getchar();
        sentence.sentence[i] = ch;

        if (sentence.sentence[i] == ' ' && i==0)
            i--;
        
        if (strchr(".;!?", ch)) {
            i++;
            break;
        }

        if(i == sentence.size) {
            sentence.size += BLOCK;
            sentence.sentence = (char*)realloc(sentence.sentence, sentence.size * sizeof(char));
        }
    }

    sentence.sentence[i] = '\0';
    return sentence;
}

void freeText(Text* text) {
    for(int i=0; i<text->real_size; i++)            
        free(text->sentences[i].sentence);

    free(text->sentences);
}

int main() {
    Text text = createText();
    Sentence sentence;

    int i;
    for(i=0; i<=text.real_size; i++) {
        sentence = readSentence(&text);
        text.start_size++;
        text.finish_size++;

        if (strchr(sentence.sentence, '?')) {
            free(sentence.sentence);
            i--;
            text.finish_size--;
            continue;
        } 

        addSentence(&text, sentence);
        if(!strcmp(sentence.sentence, "Dragon flew away!"))
            break;
    }

    for(int i=0; i<text.real_size; i++) {
        printf(TEXT_FORMAT_OUT, text.sentences[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d", text.start_size, text.finish_size);

    freeText(&text);    
    return 0;
}