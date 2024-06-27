#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TEXT_SIZE 100
#define MAX_STRINGS 100
#define MAX_LEN 1000
int readText(char **text)
{
    int size = TEXT_SIZE;
    char* str = malloc(sizeof(char) * TEXT_SIZE);
    int x = 0;
    char temp;
    do {
       if (x >= size-2){
           char *t = realloc(str, size+TEXT_SIZE);
           if(!t){
               printf("Error");
               return 0;
           }
           size+=TEXT_SIZE;
           str = t;
       }
       temp = getchar();
       str[x] = temp;
       x++;
    }while(temp!='!');
    str[x] = '\0';
    *text = str;
    return size;
}    
char *processText(char *text, int size){
    char *new_text = malloc(size*sizeof(char)); 
    int src_ind = 0; 
    int dest_ind = 0; 
    int is_sent_start = 0; 
    //int skip_word = 0;
    int need_copy = 0;
    int upper_letters = 0; 
    for (int i = 0; i < size && text[i] != '!'; i++){
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t'){  
            continue;
        }
        else{ 
            if(!is_sent_start){
                src_ind = i;
                is_sent_start = 1;
            }
        }
        
        
        if (isalpha(text[i])){ 
            if (isupper(text[i])){ 
                upper_letters += 1;
            }
        }
        if((text[i] == '.' || text[i] == '?' || text[i] == ';') && (upper_letters <= 1))
            need_copy = 1; 
        if (need_copy){
            int sentence_len = i - src_ind + 1; 
            if (size < dest_ind + sentence_len + 1){
                char *t = realloc(new_text, size+TEXT_SIZE);
                if (!t){
                    printf("Error");
                    return NULL;
                    
            }
            size += TEXT_SIZE;
            new_text = t;
        }
        
            strncpy(new_text + dest_ind, text + src_ind, sentence_len); 
            new_text[dest_ind+sentence_len] = '\n';
            dest_ind += 1;
            dest_ind += sentence_len; 
            is_sent_start = 0;
            need_copy = 0;
            upper_letters = 0;
        }
        if(text[i] == '.' || text[i] == '?' || text[i] == ';'){
            is_sent_start = 0;
            need_copy = 0;
            upper_letters = 0;
        }
    }
        strncpy(new_text + dest_ind, "Dragon flew away!", 17);
        return new_text;
};
int countStrings(char *text){
    int count = 0;
    for (int i = 0; text[i] != '\0';  i++){
         if((text[i] == '.' || text[i] == '?' || text[i] == ';'))
            count++;
    }
    return count;
}
int main(){
    char *text;
    int len = readText(&text);
    int before = countStrings(text);
    char *process_text = processText(text, len);
    int after = countStrings(process_text);
    printf("%s\nКоличество предложений до %d и количество предложений после %d", process_text, before, after);
    free(text);
    free(process_text);
    return 0;
}   
