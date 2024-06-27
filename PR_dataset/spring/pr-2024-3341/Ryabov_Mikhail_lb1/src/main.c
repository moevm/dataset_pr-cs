#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
const char* regexString = "([a-z0-9]+\\:\\/\\/)?(www\\.)?(([a-z0-9\\.]+)?[a-z0-9]+\\.[a-z0-9]+)\\/(([a-z0-9\\/]+)?[a-z0-9]+\\/)?([a-z0-9]+\\.[a-z0-9]+)";

char** getText(int* countSen);
char** sepText(char* text, int countSen);
void checkMathReg(char** sentences, int countSen);

int main(){
    int countSen;
    char** sentences = getText(&countSen);
    checkMathReg(sentences, countSen);
    return 0;
}

char** getText(int* countSen){
    int size = 0, capacity = 1;
    char* text = (char*)malloc(sizeof(char) * capacity);

    char letter = getchar();
    (*countSen) = 1;
    while (1){

        text[size++] = letter;

        if (letter == '\n')
            (*countSen) ++;

        if (size >= 4 && text[size-1] == '.' && text[size-2] == 'n' && text[size-3] == 'i' && text[size-4] == 'F')
            break;

        if (size >= capacity){

            capacity *= 2;
            text = (char*)realloc(text, sizeof(char) * capacity);

        }

        letter = getchar();
    }
    text[size] = '\0';

    char** sentences = sepText(text, *countSen);
    return sentences;
}

char** sepText(char* text, int countSen){
    char** sentences = (char**)malloc(sizeof(char*) * countSen);
    int size = 0;

    char* line = strtok(text, "\n");
    while(line != NULL){
        sentences[size++] = line;
        line = strtok(NULL, "\n");
    }

    return sentences;
}

void checkMathReg(char** sentences, int countSen){
    regex_t regexCompiled;
    regmatch_t groups[8];
    int size, sizeMatched = 0;
	char** matchedSentences = (char**)malloc(sizeof(char*));

    regcomp(&regexCompiled, regexString, REG_EXTENDED);
    
    for(int j = 0; j < countSen; j++){
        if (regexec(&regexCompiled, sentences[j], 8, groups, 0) == 0) {
            matchedSentences = realloc(matchedSentences, sizeof(char*) * (sizeMatched+1));
            char* regLine = (char*)malloc(sizeof(char)*100);
            size = 0;
		    
            for (int i=groups[3].rm_so; i<groups[3].rm_eo; i++)
		        regLine[size++] = sentences[j][i];
	        
                regLine[size++] = ' ';
                regLine[size++] = '-';
                regLine[size++] = ' ';

		    for (int i=groups[7].rm_so; i<groups[7].rm_eo; i++)
		        regLine[size++] = sentences[j][i];
	         
            regLine[size] = '\0';
            matchedSentences[sizeMatched++] = regLine;
	    }
    }
    for(int i = 0; i < sizeMatched; i++){
        if (i == sizeMatched - 1)
            printf("%s", matchedSentences[i]);
        else
            printf("%s\n", matchedSentences[i]);
    }
}

