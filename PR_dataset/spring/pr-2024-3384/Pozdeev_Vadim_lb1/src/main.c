#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * scan_sent(){
    int i = 0;
    unsigned capacity = 10;
    char b = getchar();
    char * sentence = malloc(sizeof(char)*capacity);
    for(;b!='\n'&&b!=EOF;i++){
        if (i >= capacity) {
            capacity*=2;
            sentence = realloc(sentence, capacity * sizeof(char));
        }
        sentence[i] = b;
        b = getchar();
    }
    sentence[i++] = '\0';
    return sentence;
}
char ** scan(int * i) {
    *i = 0;
    char ** text = malloc(sizeof(char *) * 1);
    char * sent = scan_sent();
    for (; strcmp(sent, "Fin."); (*i)++) {
        text[*i] = malloc(sizeof(char) * (strlen(sent) + 1));
        strcpy(text[*i], sent);
        text = realloc(text, sizeof(char *) * ((*i) + 2));
        sent = scan_sent();}
    return text;
}

int main()
{
    regex_t re;
    char * pattern = "([a-z]+://)?(www\\.)?([a-z]+(\\.[a-z]+)+)\\/(([a-z]+\\/)*)([a-z]+\\.[a-z0-9]+)*$";
    int  status;
    if((status=regcomp(&re, pattern, REG_EXTENDED))!= 0)
        fprintf(stderr, "Error\n");
    int size = 0;
    char ** text = scan(&size);
    regmatch_t pmatch[9];
        for (int i = 0; i < size; i++) {
        if (regexec(&re, text[i], 9, pmatch, 0) == 0) {
            printf("%.*s - %.*s\n", pmatch[3].rm_eo - pmatch[3].rm_so, text[i] + pmatch[3].rm_so,
            pmatch[7].rm_eo - pmatch[7].rm_so, text[i] + pmatch[7].rm_so);
        }
    }
    regfree( &re);
}
