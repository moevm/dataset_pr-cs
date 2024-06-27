#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* input_text(int *size_text,int* countBefore){
    int capacity = 1;
    char* text = (char*)malloc(sizeof(char));
    char ch = getchar();
    while (ch != '!'){
        text[*size_text] = ch;
		(*size_text)++;

		if((*size_text) >= capacity){
			capacity *= 2;
			text = (char*)realloc(text,capacity * sizeof(char));
		}

		if(ch == '.' || ch == ';' || ch == '?'){
			(*countBefore)++;
		}

		ch = getchar();
	}
	return text;
}

char** split_sentence(char* text,int countBefore,int size_text){
    int capacity = 1;
    int size_sentence = 0;
    char** sentences = (char**)malloc((countBefore + 2)*sizeof(char*));
    for (int i = 0; i < countBefore + 1;i++){
        sentences[i]=(char*)malloc(sizeof(char));
    }
    int j = 0;
    int flag = 1;
    for(int i = 0; i < size_text; i++){
        if (flag == 1 && (text[i] == ' ' || text[i] == '\n')){
            continue;
        }
        else{
            flag = 0;
        }
        sentences[j][size_sentence] = text[i];
        size_sentence++;
        if (size_sentence >= capacity){
            capacity *=2;
            sentences[j] = (char*)realloc(sentences[j],capacity * sizeof(char));
        }
        if (text[i] == '.' || text[i] == ';' || text[i] == '?'){
			flag = 1;
			sentences[j][size_sentence] = '\0';
			j++;
			capacity = 1;
			size_sentence = 0;
        }
    }
    return sentences;
}

int check_uppercase_in_sentence(char* sentence){
    int count = 0;
    for(int i = 0;i < strlen(sentence);i++){
        if (isupper(sentence[i])) count++;
    }
    return count <= 1;
}

void output(char** sentences,int countBefore){
    int countAfter = 0;
    for (int i = 0;i < countBefore;i++){
        if (check_uppercase_in_sentence(sentences[i])){
            countAfter++;
            printf("%s\n", sentences[i]);
        }
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d\n", countBefore, countAfter);
}

int main(){
    int size_text = 0, countBefore = 0;
    char* text = input_text(&size_text,&countBefore);
    char** sentences = split_sentence(text,countBefore,size_text);
    output(sentences,countBefore);
    return 0;
}
