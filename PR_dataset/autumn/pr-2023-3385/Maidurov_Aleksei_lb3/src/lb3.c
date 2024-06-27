#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int find_555(char *main)
{
    char *p = strstr(main, " 555 ");
    if (p == NULL) p = strstr(main, " 555.");
    if (p == NULL) p = strstr(main, " 555;");
    if (p == NULL) p = strstr(main, " 555?");
    if (strstr(main, "555 ") == main) return 1;
    if (p) return 1;
    return 0;
    }

int main() {
    char *sent = malloc(200);
    char chr;
    int size = 200;
    int i = 0;
    char *tmp;
    int good = 0, bad = 0;
    while (1)
    {
        while (isspace((int)(chr = getchar())) && i == 0)
        {
        }
        sent[i++] = chr;
        if (i == size)
        {
            size += 40;
            tmp = realloc(sent, size);
            if (tmp)
            {
                sent = tmp;
            }
            else
            {
                free(sent);
                return 0;
            }
        }
        if (chr == '!')
        {
            sent[i] = '\0';
            puts(sent);
            break;
        }
        if (strchr(".;?", (int)chr))
        {
            sent[i++] = '\0';
            if (find_555(sent))
            {
                bad++;
            }
            else
            {
                puts(sent);
                good++;
            }
            i = 0;
        }
    }
    printf("Количество предложений до %d и количество предложений после %d\n", good + bad, good);
    free(sent);
    return 0;
}
