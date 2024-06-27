#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 10
#define END_OF_STRING '\0'
#define EXCLURE_SENTENCE '7'

char* read_text() {
        char ch = getchar();
        int capacity = BLOCK_SIZE;
        int sentenceCount = 0;
        char* text = (char*)malloc(capacity+1);

        while (1) {
                text[sentenceCount++] = ch;
                if (sentenceCount == capacity - 1) {
                        capacity += BLOCK_SIZE;
                        text = (char*)realloc(text, capacity + 1);
                }
                if(ch=='?' || ch=='.' || ch==';'){
                        text[sentenceCount++] = '@';
                        if (sentenceCount == capacity - 1) {
                                capacity += BLOCK_SIZE;
                                text = (char*)realloc(text, capacity + 1);
                        }
                }
                ch = getchar();
                if (ch == EOF) {
                        break;
                }
        }
        text[sentenceCount-1] = END_OF_STRING;
        return text;
}

int warning(char* sentence) {
        int len = strlen(sentence);
        for (int i = 0; i < len; i++) {
                if (sentence[i] == EXCLURE_SENTENCE) {
                        return 0;
                }
        }
        return 1;
}

char* wordMeater(char* text) {
        int length = strlen(text);
        int sentenceCount = 0;
        int newSentenceCount = 0;
        int count_of_deleted_sentences = 0;
        char* formattedText = (char*)malloc(length * 2);

        char* sentence = strtok(text, "@");
        while (sentence != NULL) {
                int len = strlen(sentence);
                if (warning(sentence)) {
                        for (int i = 0; i < len; i++) {
                                if (i == 0 && (sentence[i] == '\t' || sentence[i] == ' ')) {
                                        continue;
                                }
                                formattedText[newSentenceCount++] = sentence[i];
                        }
                        formattedText[newSentenceCount++] = '\n';
                }else{count_of_deleted_sentences++;}
                sentenceCount++;
                sentence = strtok(NULL, "@");

        }

        char add[1000];
        formattedText[newSentenceCount] = '\0';
        sprintf(add,"Количество предложений до %d и количество предложений после %d\n",sentenceCount-1,sentenceCount-count_of_deleted_sentences-1);
        int len_added = strlen(add);
        formattedText = (char*)realloc(formattedText, newSentenceCount+1+len_added);
        strncat(formattedText,add,len_added);
        formattedText[newSentenceCount+len_added+1] = '\0';

        return formattedText;
}

void output(char* result){
        int len = strlen(result);
        for(int i = 0; i < len; i++){
                printf("%c",result[i]);}
}

int main() {
        char* read = read_text();
        char* result = wordMeater(read);
        if (result == NULL) {
                printf("Error in wordMeater function\n");
                return 1;
        }

        output(result);

        free(read);
        free(result);
        return 0;
}
