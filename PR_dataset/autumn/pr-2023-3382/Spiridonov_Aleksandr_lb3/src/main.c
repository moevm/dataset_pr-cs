#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sent_count_and_print(char* sents_before){
	int i = 0;
	int count_alph; 
	int n_sent_aft = 0;
	int flag = 0;
	
	while(sents_before[i] != '\0'){
		if (isspace(sents_before[i]) && (sents_before[i-1]=='.' || sents_before[i-1]==';' || sents_before[i-1]=='?')) {
			sents_before[i] = '\n';
		} 
		i++;
	}
	
	char* token = strtok(sents_before, "\n");
	
	while (token[i] != '\0'){
			if ((int) token[i] >= 65 && (int) token[i] <= 90){
			    count_alph++;
			}
			
			i++;			
		}
		if (count_alph == 1){
			//printf("%s\n", token);	
			n_sent_aft += 1;
			i = 0;
		}else{
			i = 0;

		}
    
	
    while (token != NULL) {
    	count_alph = 0;
    	while (token[i] != '\0'){
			if ((int) token[i] >= 65 && (int) token[i] <= 90){
			    count_alph++;
			}
			
			i++;			
		}
		if (count_alph == 1){
		    if (token[i-1] == '!'){
		        token[i] = '\0';
		    }
			printf("%s\n", token);	
			n_sent_aft += 1;
			i = 0;
		}else{
			i = 0;
            
		}
		
        token = strtok(NULL, "\n");

    }
    return n_sent_aft-1;
}


int main(){
	
	char sym;
	int size = 100;

	char* sents_before = (char*)malloc(size*sizeof(char));
	
	int n_sent_bef = 0;
	int n_sent_aft = 0;
	
	int i = 0;
	
	while(sym != '!'){
		if (i >= size-2){
			size += 10;
			sents_before = (char*)realloc(sents_before, size*sizeof(char));
		}
			
		sym = (char)getchar();
		sents_before[i] = sym;
		
		if ((sents_before[i] == '.') || (sents_before[i] == '?') || (sents_before[i] == ';')){
			n_sent_bef++;
		}
		
		i++;
	}

	sents_before[i+1] = '\0';
	
	n_sent_aft = sent_count_and_print(sents_before);
	
	printf( "Количество предложений до %d и количество предложений после %d", n_sent_bef, n_sent_aft);
	
	free(sents_before);
    return 0;
}