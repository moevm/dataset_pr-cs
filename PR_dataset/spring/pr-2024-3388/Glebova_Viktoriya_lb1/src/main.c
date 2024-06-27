#include <stdio.h>
#include <regex.h>
#include <string.h>

int main(){
    int max_group = 3;
    regex_t regex_compiled;
    regmatch_t groupArray[max_group];
    char buf[400];
    char* regex_string = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.+)";
    if (regcomp(&regex_compiled, regex_string, REG_EXTENDED) != 0){
        printf("Regex compilation failed");
        return 1;
    }
    while (fgets(buf, 400, stdin)){
        if (strcmp(buf, "Fin.") == 0) {
            break;
        }
		if (regexec(&regex_compiled, buf, max_group, groupArray, 0) == 0){
	        for(int j = groupArray[1].rm_so; j < groupArray[1].rm_eo; j++){
				printf("%c",buf[j]);
	        }
			printf(" - ");
			for(int j = groupArray[2].rm_so; j < groupArray[2].rm_eo; j++){
				printf("%c",buf[j]);
			}
	    }
    }
    regfree(&regex_compiled);
    return 0;
}
