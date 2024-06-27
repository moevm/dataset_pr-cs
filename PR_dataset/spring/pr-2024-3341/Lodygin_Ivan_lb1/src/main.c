#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#define PATTERN "\\(\\w\\+://\\)\\?\\(\\([wW]\\)\\{3\\}.\\)\\?\\(\\w\\+\\.\\)\\+\\w\\+\\(\\w\\+/\\)\\+\\w\\+\\.\\w\\+"
#define SEP "\n\t "
#define WWW_LEN 4

char* input() {
	char* text = calloc(10, sizeof(char));
	char symbol;
	int i = 0;
	while(1) {
		symbol = getchar();
		text = realloc(text, (i+10)*sizeof(char));
		text[i] = symbol;
		if(i>2
		&& text[i-3] == 'F'
		&& text[i-2] == 'i'
		&& text[i-1] == 'n'
		&& text[i] == '.'){
			text[i+1] = '\0';
			break;
		}
		i++;
	}
	return text;
}

void link_processing(char* link) {
    char* host_start = strstr(link, "://");
    if (host_start) {
        host_start += 3;
    } else {
        host_start = link;
    }

    if (strstr(host_start, "www.") == host_start) {
        host_start += 4;
    }

    char* host_end = strchr(host_start, '/');
    if (!host_end) {
        host_end = host_start + strlen(host_start);
    }

    while (host_start < host_end) {
        printf("%c", *host_start);
        host_start++;
    }
    printf(" - ");
    char* file_name_start = strrchr(link, '/');
    if (file_name_start) {
        file_name_start++;
    } else {
        file_name_start = link;
    }
    printf("%s\n", file_name_start);
}


void text_processing(char *text) {
	regex_t regular_expression;
	regcomp(&regular_expression, PATTERN, 0);
	size_t nmatch = 1;
	regmatch_t pmatch[nmatch];
	char *word;
	word = strtok(text, SEP);
	while(1) {
		if(strcmp(word, "Fin.") == 0) break;
		if((regexec(&regular_expression, word, nmatch, pmatch, 0) == 0)) {
			link_processing(word);
		}
		word = strtok(NULL, SEP);
	}
}

int main() {
	char* text = input();
	text_processing(text);
	return 0;
}