#include <stdio.h>
#include <string.h>
#include <dirent.h>
void sch(char bucva, char* pat, FILE* file){
    DIR *dir = opendir(pat); 
    if(dir) {
        struct  dirent *de = readdir(dir);  
        while (de) { 
            if ((de->d_type == DT_DIR) && (strcmp(de->d_name, ".") != 0) && (strcmp(de->d_name, "..") != 0)){
                char put[strlen(de->d_name)+strlen(pat)+1];
                put[0]='\0';
                strcat(put, pat);
                strcat(put, "/");
                strcat(put, de->d_name);
                sch(bucva, put, file);
            }
            else if ((de->d_type == DT_REG) && (de->d_name[0] == bucva) && (strlen(de->d_name)==5)){
                fprintf(file, "%s/%s\n", pat, de->d_name);
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}
int main(){
    char slovo[100];
    scanf("%s", slovo);
    char* pat = "./tmp";
    FILE *file=fopen("result.txt", "w");
    int n = strlen(slovo);
    for(int i = 0; i<n; ++i){
        sch(slovo[i], pat, file);
    }
}

