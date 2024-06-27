#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


#define N 30;


int main(){
	char* str2="Fin.";
	int f=1;
	do{
		int len=100;
		char* str = (char*)malloc(sizeof(char)*len);
		if(str==NULL){
			free(str);
			exit(1);
		}		
		int i=0;
		do{
			char c=getchar();
			if(i+1==len){
				len+=N;
				str=(char*)realloc(str,sizeof(char)*len);
				if(str==NULL){
					free(str);
					exit(1);
				}
			}
			str[i] = c;
			i++;
			if(i==4 && c=='.'){
				str[i]='\0';
				if(strcmp(str,str2)==0){
					f=0;
				}
			}
		}while(str[i-1] !='\n' && f);
		str[i]='\0';
		char* regex_string = "([a-zA-Z0-9_-]+)@[a-zA-Z0-9_-]+: ?~ ?# (.+)";
	    size_t count_groups = 3;
	    regex_t regex_compiled;
	    regmatch_t array_of_groups[count_groups];
	    if (regcomp(&regex_compiled, regex_string, REG_EXTENDED)){
	        printf("Failed ");
	    };
	    if (regexec(&regex_compiled, str, count_groups, array_of_groups, 0) == 0){
	        for(int j = array_of_groups[1].rm_so; j < array_of_groups[1].rm_eo; j++)
				printf("%c",str[j]);
			printf(" - ");
			for(int j = array_of_groups[2].rm_so; j < array_of_groups[2].rm_eo; j++)
				printf("%c",str[j]);
	    }
	    regfree(&regex_compiled);
		free(str);
	}while (f);
	return 0;
}

