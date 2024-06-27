#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


char* readsentence() {
    char c;
    int max_len = 100;
    int step = 20;
    int len_sent = 0;
    char* sentence = (char*)malloc(max_len);
    c = getchar();
    for(int i = 0; i<max_len; i++) {
        if(len_sent >= max_len) {
            max_len = max_len + step;
            sentence = (char*)realloc(sentence, max_len);
        }
        sentence[i] = c;
        len_sent++;
        if(c == '\n') {
            sentence[i+1] = '\0';
            break;
        }
        c = getchar();
    }
    return sentence;
}

int main() {
    int count_groups = 3;
    char* pattern = "([A-Za-z0-9_]+)@[A-Za-z0-9_-]+:\\s*~\\s*# (.+)\n";

    regex_t compiled_pattern;
    regmatch_t capturing_groups[count_groups];

    regcomp(&compiled_pattern, pattern, REG_EXTENDED);

    char* sentence = malloc(100);
    while (!strstr(sentence, "Fin.")) {
        free(sentence);
        char* sentence = readsentence();
		if (regexec(&compiled_pattern, sentence, count_groups, capturing_groups, 0) == 0) {
            for (int i = 1; i < count_groups; i++) {
				if (capturing_groups[i].rm_so == -1) {
					break;
				}
				for (int j = capturing_groups[i].rm_so; j < capturing_groups[i].rm_eo; j++) {
					printf("%c", sentence[j]);
				}
				if (i==1) {
				    printf(" - ");
				}
			}
			printf("\n");
		}
	}
	free(sentence);
	regfree(&compiled_pattern);
    return 0;
}
