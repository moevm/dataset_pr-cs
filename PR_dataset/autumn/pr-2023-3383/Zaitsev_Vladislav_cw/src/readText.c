#include "readText.h"

char *readSentence(){
        int size = SENT_SIZE;
        char *buf = (char *)calloc(size, sizeof(char));
        int sent_len = 0;
        int is_sent_start = 1;
        char temp;
	int ncount = 0;
	int end_of_text = 0;
	do{
                if (sent_len >= size - 2){
                        char *t = (char *)realloc(buf, size+SENT_SIZE * sizeof(char));
                        if (!t) {
                                printf("Error: ошибка выделения памяти");
                                free(buf);
                                return NULL;
                        }
                                size+= SENT_SIZE;
                                buf = t;
                }
                temp = getchar();
                if (is_sent_start){
                        if(temp == '\t' || temp == ' '){
                                continue;
                        }
                        else{
                                is_sent_start = 0;
                        }
                }
		if (temp == '\n'){
		       if (ncount == 1){
				end_of_text = 1;
				break;	
		       }
		       else{
			       ncount++;
			}
		}
		else{
			ncount = 0;
                	buf[sent_len] = temp;
                	sent_len++;
		}
        }while(temp != '.');
	if (end_of_text){
		buf[sent_len] = '\n';
	}
	else{
		buf[sent_len] = '\0';
	}
        return buf;
	}

char **readText(int *len_text){
        int sizeT = TEXT_SIZE;
        char **text= (char**)calloc(sizeT, sizeof(char *));
        int n = 0;
        char *temp;
        int nlcount = 0;
        do{
               if (n >= sizeT - 2){
                        char **t = (char**)realloc(text, (sizeT+TEXT_SIZE) * sizeof(char *));
                        if(!t) {
                                printf("Error: ошибка выделения памяти");
                                freeText(text, n);
                                return NULL;
                        }
                                sizeT += TEXT_SIZE;
                                text = t;
               }
                temp = readSentence();
                if (temp[strlen(temp)-1]  == '\n'){
                        nlcount++;
                        free(temp);
                }
                else{
                    if(strlen(temp) > 2){
                            nlcount = 0;
			    temp[strlen(temp)-1]  == '\0';
                            text[n] = temp;
                            n++;
                    }
                    else{
                        free(temp);
                    }
                }
	}while(nlcount<1);
        *len_text = n;
        return text;
}

