#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>

#define k 2;
int main()
{
    int counts = 0;
    char** text = (char**)malloc(sizeof(char*)*5);
    int real_size =5;
    int f =1;
    while(f){
        char* sentence = (char*)malloc(sizeof(char)*5);
        char c = getchar();
        int c_sym=0;
        int lens =5;
        while (c!='\n' && strncmp("Fin.", sentence,4)){
            sentence[c_sym++] =c;
            if (c_sym > lens-2){
                lens*=k;
                sentence = (char*)realloc(sentence, lens*sizeof(char));
            }
            c=getchar();
        }
        if(strncmp("Fin.", sentence,4) == 0){text[counts++] = sentence;f=0;break;}
        sentence[c_sym] = '\0';
        text[counts++] = sentence;

        if (counts>real_size-2){
            real_size *=k;
            text = (char**)realloc(text, real_size*sizeof(char*));
        }
    }
    regex_t my_reg;
    int status;
    status = regcomp(&my_reg, "([A-Za-z]+:\\/\\/)?(www\\.)?(\\w+\\.[A-Za-z0-9_\\.]+)([A-Za-z0-9_\\/]+)?\\/(\\w+\\.\\w+)", REG_EXTENDED);
    regmatch_t matches[6];
    if (status ==0){

        int status_2;
        for (int i=0;i<counts;i++){
            status_2 = regexec(&my_reg, text[i], 6, matches, 0);
            if (status_2 ==0){

                //printf("%s\n", text[i]);
                for(int j=matches[3].rm_so; j<matches[3].rm_eo;j++){
                    printf("%c", text[i][j]);
                }
                printf("%s", " - ");
                for(int j=matches[5].rm_so; j<matches[5].rm_eo;j++){
                    printf("%c", text[i][j]);
                }
                printf("%c", '\n');
            }
        }
    }
    regfree(&my_reg);
    return 0;
    for (int i=0; i<counts;i++){
        free(text[i]);
    }
    free(text);
}
