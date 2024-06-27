#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_part(int start, int end, char* buffer){
    for(int i = start; i < end; i++)
        printf("%c",buffer[i]);
}

int main(){
    regex_t regex;
    char* regex_str =  "((\\w+:\\/\\/)?(www\\.)?((\\w+\\.)+\\w+)(\\/\\w+)*\\/(\\w+\\.\\w+))\n";
    char buf[100];
    int max_groups = 8;
    regmatch_t groups[max_groups];
    if (regcomp(&regex, regex_str, REG_EXTENDED)) {
    	printf("Could not compile regex\n");
    	exit(1);
    }

    while(!strstr(buf,"Fin.")){
        fgets(buf, 100, stdin);
        if (regexec(&regex, buf, max_groups, groups, 0) == 0) {
        	print_part(groups[4].rm_so, groups[4].rm_eo, buf);
        	printf(" - ");
        	print_part(groups[7].rm_so, groups[7].rm_eo, buf);
        	printf("\n");
        }

    }
    regfree(&regex);
    return 0;
}