#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* txtGenerator(char** text, int textSize);

char** txtRead(int* textSize, int* TextsizeRefac);


int main() {
    int textSize = 0;
    
    int question = 0;
    
    char** text = txtRead(&textSize, &question);
    
    char* newText = txtGenerator(text,textSize);
    
    printf("%sКоличество предложений до %d и количество предложений после %d", newText,textSize + question -1, textSize -1);
    
    return 0;
}

char** txtRead(int* textSize, int* TextsizeRefac){
    
    int sentenceBuffer = 1;
    
    int textBuffer = 1;
    
    int sentenceSize = 0;
    
    char tempChar;

    char* sentence = malloc(sizeof(char) * sentenceBuffer);
    
    char** text = malloc(sizeof(char*)*textBuffer);

   do{
        tempChar = getchar();
        
        if(tempChar=='\n'){
            
            continue;
        }
        sentence[sentenceSize++] = tempChar;
        
        if (sentenceSize >= sentenceBuffer){
            
            sentenceBuffer *= 2;
            
            sentence = realloc(sentence, sizeof(char) * sentenceBuffer);
        }

        if(tempChar=='.' || tempChar==';' || tempChar=='!'){
            
            sentence[sentenceSize] = '\0';
            
            if (sentence[0]==' '){
                
                memmove(sentence,sentence+1, strlen(sentence));
            }
            text[(*textSize)++] = strdup(sentence);
            
            sentenceSize=0;
            
            sentenceBuffer=1;
            
            if ((*textSize)>=textBuffer){
                
                textBuffer *= 2;
                
                text = realloc(text,sizeof(char*)*textBuffer);
            }
        }
        if (tempChar=='?'){
            
            sentenceSize=0;
            
            sentenceBuffer=1;
            
            (*TextsizeRefac) ++;
        }
    }  while (tempChar!='!');
    
    free(sentence);
    
    return text;
}

char* txtGenerator(char** text, int textSize){
    
    char* txtNew = calloc(1, sizeof(char));

    for (int i = 0; i < textSize; ++i) {
        
        txtNew = realloc(txtNew, strlen(txtNew) + strlen(text[i]) + 2);
        
        strcat(txtNew, text[i]);
        
        strcat(txtNew, "\n");
    }
    return txtNew;
}