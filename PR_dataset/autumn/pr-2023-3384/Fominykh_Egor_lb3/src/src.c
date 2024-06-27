#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 100

int main(){
	char* sentence;
	char simvol;
	int after = 0, before = 0, a = 0, i = size;
	sentence = (char*) malloc(size * sizeof(char));
	while (1){
		simvol = getchar();
		while (simvol == ' '){
			simvol = getchar();
		}

		while (simvol != '.' && simvol != ';' && simvol != '?' && simvol != '!'){
			sentence[a] = simvol;
			a++;
			if (a >= i - 2){
				i += size;
				sentence = (char*) realloc(sentence, i * sizeof(char));
			}
			
			simvol = getchar();
		}
		
		sentence[a] = simvol;
		sentence[a + 1] = '\0';
		
		if (simvol == '!'){
			printf("%s\n", sentence);
			break;
		}
		
        int count=0;
        for(int j=0;j<strlen(sentence);j++){
            if (isupper(sentence[j])){
                count++;
             }
        }
        
		if (count==1){
			after++;
			printf("%s\n", sentence);
		}
		count = 0;
		before++;
		a = 0;
	}
	printf("Количество предложений до %d и количество предложений после %d\n", before, after);
	free(sentence);
	return 0;
}
