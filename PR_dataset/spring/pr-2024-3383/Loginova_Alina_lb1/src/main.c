#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#define GROUPS_AMOUNT 7
#define REGEX "(\\w+://)?(www.)?(([A-Za-z0-9]+\\.)+[A-Za-z0-9]+)/([A-Za-z0-9]+/)*([A-Za-z0-9]+\\.[A-Za-z0-9]+)"
#define URL_GROUP 3
#define FILE_GROUP 6


typedef struct String {
    size_t capacity, length;
    char* chars;
} String;

typedef struct Link {
    char *URL, *file;
} Link;

void resize (String* s) {
    if (s->length + 1 == s->capacity) {
        s->capacity *= 2;
        char *temp =  realloc(s->chars, s->capacity);
        if(!temp) {
            free(s->chars);
            printf("Memory allocation error");
            exit(1);
        }
        s->chars = temp;
    }
}

char read_next_char(String *s) {
    char c = (char)getchar();
    resize(s);
    s->chars[s->length++] = c;
    s->chars[s->length] = '\0';
    return c;
}

String create() {
    String s = { 1, 0,calloc(s.capacity, sizeof(char)) };
    return s;
}

void clear_string(String *s) {
    s->length = 0;
}

void read_input(String *s) {
    while(read_next_char(s) != '\n' && strcmp(s->chars, "Fin.") != 0);
}

void set_link(regmatch_t *groups, char *s, Link *link) {
    s[groups[URL_GROUP].rm_eo] = '\0';
    s[groups[FILE_GROUP].rm_eo] = '\0';
    link->URL = &s[groups[URL_GROUP].rm_so];
    link->file = &s[groups[FILE_GROUP].rm_so];
}

void print(Link *link) {
    static int need_lf = 0;
    if(link->URL && link->file) {
        if (need_lf)
            printf("\n");
        else
            ++need_lf;
        printf("%s - %s", link->URL, link->file);
    }
}

Link parse(String *s, regex_t *regex) {
    Link link;
    regmatch_t groups[GROUPS_AMOUNT];
    int res;

    for (char *sub_s = strtok(s->chars, " "); sub_s != NULL; sub_s = strtok(NULL, " ")) {
        res = regexec(regex, sub_s, GROUPS_AMOUNT, groups, 0);
        if(res == 0 && groups[URL_GROUP].rm_so != -1 && groups[FILE_GROUP].rm_so != -1) {
            set_link(groups, sub_s, &link);
            print(&link);
        } else {
            link.URL = NULL; link.file = NULL;
        }
    }
    return link;
}

int main() {
    regex_t regex;
    if (regcomp(&regex, REGEX, REG_EXTENDED) == 0) {
        String s = create();
        for(read_input(&s); strcmp(s.chars, "Fin.") != 0; read_input(&s)) {
            parse(&s, &regex);
            clear_string(&s);
        }
        free(s.chars);
    }
    else
        printf("Regex compilation error");
    regfree(&regex);
    return 0;
}