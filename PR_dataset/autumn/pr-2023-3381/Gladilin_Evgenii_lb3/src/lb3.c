#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
	int l = 1;
	char c = getchar();
	char *str = malloc(l+1);
	int count_sent_before = 0;
	int count_sent_after = 0;
	str[0] = c;
	
	while (!(strstr(str,"Dragon flew away!"))){
		c = getchar();
		str = realloc(str,l+3);
		str[l++] = c;
		str[l] = '\0';
	}
	str[l+1] = '\0';
	char *str_output = malloc(l+1);

	int i = 0;
	str_output[i++] = str[0];
	for (int k = 1;k<l;k++){	
		if(isspace(str[k]) && ((str[k-1] == '.') || (str[k-1] == ';'))){
			str_output[i++] = '\n';
			count_sent_before++;
			count_sent_after++;
		}
		else if(str[k]=='\n'){
			continue;
		}
		else if(~(isspace(str[k])) && ((str[k-1] == '.') || (str[k-1] == ';'))){
                        str_output[i++] = '\n';
			str_output[i++] = str[k];
                        count_sent_before++;
                        count_sent_after++;
                }

		else if(str[k]== '?'){
			int sent_start_index = k;
			while((str_output[sent_start_index]!='.') && (str_output[sent_start_index]!=';') && (sent_start_index != -1)){
				str_output[sent_start_index--] = '\0';
			}
			k++;
			i = sent_start_index+1;
			if (sent_start_index != -1){
				str_output[i++] = '\n';
			}
			str_output[i] = str[k];
			str_output[i+1] = '\0';
			count_sent_before++;
		}
		else{
			str_output[i++] = str[k];
		}

	}
	for(i = 0; str_output[i];i++){
		printf("%c",str_output[i]);
	}
	printf("\nКоличество предложений до %d и количество предложений после %d",count_sent_before,count_sent_after);
	free(str);
	free(str_output);
	return 0;
}
