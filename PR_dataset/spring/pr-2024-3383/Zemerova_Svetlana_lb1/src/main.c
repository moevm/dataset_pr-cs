#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#define STR_BLOCK 50
#define BLOCK 50

char** input(int* lent){
	int lens=STR_BLOCK;
	char **text=(char**)malloc((*lent)*sizeof(char*));
	for (int i=0; i<(*lent); i++) text[i]=(char*)malloc(lens*sizeof(char));
	int fl=1;
	int j=0;
	int i=0;
	char c;
	while(fl){
	if (i==(*lent)-1){
	(*lent)+=10;
	text=(char**)realloc(text, (*lent)*sizeof(char*));
	if (text==NULL) exit(0);}
	if (j==lens-1){
	lens+=10;
	text[i]=(char*)realloc(text[i], lens*sizeof(char));
	if (text[i]==NULL) exit(0);}
	
	if ((c=getchar())!='\n') text[i][j++]=c;
	else{
	text[i][j++]='\0';
	i++;
	j=0;
	lens=STR_BLOCK;
	}
	if (strstr(text[i], "Fin.\0")!=NULL) fl=0;
	}
	*lent=i;
	return text;
}

int findlinks(char** text, int lent){
	char* regString="([A-Za-z]+\\:\\/{2})?([w]{3}\\.)?((\\w+\\.)+\\w+)\\/(\\w+\\/)*(\\w+\\.\\w+)";
	regex_t regComp;
	regmatch_t array_groups[7];
	if (regcomp(&regComp, regString, REG_EXTENDED)){
	printf("Error: Can't compile.\n");
	return 0;
	}
	
	for (int i=0; i<lent; i++){
	if (regexec(&regComp, text[i], 7, array_groups, 0)==0){
	for (int j=array_groups[3].rm_so; j<array_groups[3].rm_eo; j++) printf("%c", text[i][j]);
	printf(" - ");
	for (int j=array_groups[6].rm_so; j<array_groups[6].rm_eo; j++) printf("%c", text[i][j]);
	printf("\n");
	}
	}
	regfree(&regComp);
	return 0;
}

int main(){
	int lent=BLOCK;
	char** text=input(&lent);
	findlinks(text, lent);
	return 0;	
}


