#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


#define MAX_FILES 200
#define INPUT_SIZE  2000

char ans[MAX_FILES][INPUT_SIZE];
char word[MAX_FILES];

void rec_bypass(char *path){
   char new_Path[INPUT_SIZE];
   DIR *directory = opendir(path);

   if(!directory){
      return;
   }
   struct dirent *de;

   while((de = readdir(directory)) != NULL){
      if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){

         snprintf(new_Path, sizeof(new_Path),"%s/%s", path, de->d_name);
         struct stat file_info;
         if(stat(new_Path, &file_info) == -1)
         	perror("Error open file");
         if (S_ISREG(file_info.st_mode)){
            if(strlen(de->d_name) != 5){
               continue;
            }
            for(size_t i = 0; i < strlen(word);i++){
               if(word[i] == de->d_name[0]){
                  strcpy(ans[i],new_Path);
                  break;
               }
            }
         }
         if(S_ISDIR(file_info.st_mode)){
            rec_bypass(new_Path);
         }  
      }
   }
   closedir(directory);
}


int main(){
   fgets(word, MAX_FILES, stdin);
   char *path = "./tmp";
   rec_bypass(path);
   FILE *file = fopen("result.txt","w");

   if(file == NULL)
      return 1;
   
   for(size_t i = 0; i < strlen(word); i++)
      fprintf(file,"%s\n",ans[i]);
   fclose(file);

   return 0;
}
