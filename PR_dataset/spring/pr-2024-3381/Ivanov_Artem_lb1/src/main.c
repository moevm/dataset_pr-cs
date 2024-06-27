#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK 100

int main()
{
	size_t maxGroups = 3;

	regex_t regex;
	regmatch_t groupArray[maxGroups];

	int reti;

	reti = regcomp(&regex, "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+:[ ]*~[ ]*# ([ -~]+)\n", REG_EXTENDED);
	if (reti) {
		fprintf(stderr, "Could not compile regex\n");
		exit(EXIT_FAILURE);
	}

	char buffer[BLOCK];
	while (!strstr(buffer, "Fin.")) {
		fgets(buffer, BLOCK, stdin);

		reti = regexec(&regex, buffer, maxGroups, groupArray, 0);
		if (!reti) {
			for (size_t i = 1; i < maxGroups; i++) {
				if (groupArray[i].rm_so == -1)
					break;

				for (size_t j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++)
					printf("%c", buffer[j]);
				if (i < maxGroups - 1) {printf(" - ");}
			}
			printf("\n");
		}
		else if (reti != REG_NOMATCH) {
			char err_buf[BLOCK];
			regerror(reti, &regex, err_buf, sizeof(err_buf));
			fprintf(stderr, "Regex match failed %s\n", err_buf);
			exit(EXIT_FAILURE);
		}
	}
	
	regfree(&regex);
	return 0;
}