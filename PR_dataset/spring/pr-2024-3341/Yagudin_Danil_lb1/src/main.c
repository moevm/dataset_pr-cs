#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<regex.h>

const char* PATTERN = "([a-z]+\\:\\/\\/)?(www\\.)?(([a-z]+\\.)+[a-z]+)\\/([a-z]+\\/)*([a-z]+\\.[a-z0-9]+)";
const char* END_STRING = "Fin.";
const int MAX_MATCHES = 10;
const int BUFFER_SIZE = 2000;

void solution();
void output(regmatch_t* matching_str, char* buffer);

int main(){
    solution();
}

void solution(){

    regex_t regular;
    regmatch_t matching_str[MAX_MATCHES];
    regcomp(&regular, PATTERN, REG_EXTENDED);
    
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);

    while(strncmp(buffer, END_STRING, strlen(END_STRING)) != 0){
        if(regexec(&regular, buffer, MAX_MATCHES, matching_str, 0) == 0){
            output(matching_str, buffer);
        }
        
        fgets(buffer, BUFFER_SIZE, stdin);
    }
}

void output(regmatch_t* matching_str, char* buffer){

    for(int i = matching_str[3].rm_so; i < matching_str[3].rm_eo; i++){
        printf("%c", buffer[i]);
    }

    printf(" - ");

    for(int i = matching_str[6].rm_so; i < matching_str[6].rm_eo; i++){
        printf("%c", buffer[i]);
    }

    printf("\n");

}
