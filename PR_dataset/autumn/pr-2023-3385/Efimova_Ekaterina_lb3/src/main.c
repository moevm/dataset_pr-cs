#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void CreateChar(char **mas, int cnt)
{  
   *mas = malloc(sizeof(char)*cnt);
   
}

void FreeAndNil(char **mas)
{
   free(*mas);
   *mas = NULL;
}


int main()
{  
   char *mas = NULL;
   int cnt = 50;
   char symbol;
   int i = 0;
   int k = 0;
   int t = 0;
   CreateChar(&mas, cnt);
   if (mas == NULL) {
        fprintf(stderr, "Can not malloc().\n");
        return EXIT_FAILURE;
   } 
   while(1) {
      symbol = getchar();
      if (symbol == '?' || symbol == ';' || symbol == '.' || symbol == '!') {
          if (i!= -1){
            mas[i++] = symbol;
            if (i == (cnt - 2)) { 
                cnt+=50;
                char *tmp = realloc(mas, sizeof(*mas)*cnt);
   
                if(tmp == NULL){
                   fprintf(stderr, "Can not realloc().\n");
                   FreeAndNil(&mas);
                   return EXIT_FAILURE; 
                }
                
                mas = tmp;
                   
            }
            mas[i] = '\0';
            puts(mas);
                   
          }
          
          if (symbol == '!') break;
          k+=1;
          i = 0;
      
      }
      
      else {
           if((i == 0 && isblank(symbol)) || i == -1 || symbol == '\n') {
                continue;
           }
      
           if(symbol == '7') {
              i = -1;
              t+=1;
              continue;
            }
            
            if(i == cnt) {
              cnt+=50;
              char *tmp = realloc(mas, sizeof(*mas)*cnt);
              
              if(tmp == NULL){
                  fprintf(stderr, "Can not realloc().\n");
                  FreeAndNil(&mas);
                  return EXIT_FAILURE; 
              }
                            
              mas = tmp;
                   
            }
            
             mas[i++] = symbol;
              
           }
   }
   
   FreeAndNil(&mas);
   printf("Количество предложений до %d и количество предложений после %d \n", k, k - t);
   return 0;
   
}
