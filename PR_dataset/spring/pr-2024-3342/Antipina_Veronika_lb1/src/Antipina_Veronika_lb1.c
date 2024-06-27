#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define BLOCK_SIZE 10
#define END_OF_STRING '\0'

char* input(){
        int capacity = BLOCK_SIZE;
        char* text = malloc(capacity*sizeof(char));
        if(text==NULL){
            printf("ERROR: couldn't allocate memory\n");
            return 0;
        }
        int k = 0;

        char ch = getchar();
        char ch_one = 'a';
        char ch_two = 'a';
        char ch_three = 'a';
        char ch_four = 'a';

        while(ch_one!='F'||ch_two!='i'||ch_three!='n'||ch_four!='.'){
                text[(k)++] = ch;
                if((k) == (capacity)-1){
                        (capacity)+=BLOCK_SIZE;
                        text = (char*)realloc(text,(capacity)*sizeof(char));
                        if(text==NULL){
                            printf("ERROR: could not find the memory! And it's just the beginning...\n");
                            return 0;
                        }
                }
                ch_one = ch_two;
                ch_two = ch_three;
                ch_three = ch_four;
                ch_four = ch;
                ch = getchar();
        }
        text[(k)] = END_OF_STRING;
        return text;
}

char** split_text(char* text, int* k){
        int capacity = BLOCK_SIZE;
        char** text_done = (char**)malloc(capacity*sizeof(char*));
        if(text_done==NULL){
            printf("ERROR: No memory left! Buy me Ginkoum, please!!");
            return 0;
        }
        char* sentence = strtok(text,"\n");

        while(sentence!=NULL){
                int sent_len = strlen(sentence);
                text_done[(*k)] = malloc((sent_len+1)*sizeof(char));
                if(text_done[(*k)]==NULL){
                    printf("ERROR: Sorry, I don't have enough memory:(\n");
                    return 0;                    
                }

                strcpy(text_done[(*k)], sentence);

                (*k)++;
                if((*k) == capacity-1){
                        capacity+=BLOCK_SIZE;
                        text_done = (char**)realloc(text_done,capacity*sizeof(char*));
                        if(text_done==NULL){
                            printf("ERROR: Oh no! Could not find the memory!\n");
                            return 0;
                        }
                }
                sentence = strtok(NULL,"\n");
        }
        return text_done;
}

int main(){
        char* text = input();
        int k = 0;

        char** text_done = split_text(text,&k);

        char* regexString = "(([A-z]*):\\/\\/)?(www.)?([A-z0-9]+([_\\-\\.]+[A-z]+)+)\\/((([A-z]*)\\/)*)([A-z0-9_\\-]+\\.[A-z0-9_\\-]+)";


        regex_t regexCompiled;
        regmatch_t groupArray[BLOCK_SIZE];

        if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
                printf("Can't compile regular expression:(\n");
                return 0;
        };

        for(int index = 0; index < k; index++){
                if(regexec(&regexCompiled,text_done[index],BLOCK_SIZE,groupArray,0)==0){
                        int i = 4;

                        for(int j = groupArray[i].rm_so;j<groupArray[i].rm_eo;j++)
                                printf("%c",text_done[index][j]);
                        printf(" - ");

                        i = 9;
                        for(int j = groupArray[i].rm_so;j<groupArray[i].rm_eo;j++)
                                printf("%c",text_done[index][j]);
                        printf("\n");
                }
        }

        free(text);
        for(int i = 0;i<k;i++)
                free(text_done[i]);
        free(text_done);

        regfree(&regexCompiled);

        return 0;
}
