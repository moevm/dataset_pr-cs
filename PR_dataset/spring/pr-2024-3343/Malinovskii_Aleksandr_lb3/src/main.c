#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
 
void list_files(const char *dirPath,char cur_val,FILE *file) {
    DIR *dir = opendir(dirPath);
    struct dirent *de;
    if (dir) {
        while ((de = readdir(dir)) != NULL) {
            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
                char fullPath[257];
                snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, de->d_name);
 
                if (strstr(de->d_name,".txt")==NULL) {
                    list_files(fullPath,cur_val,file); 
                } else if(de->d_name[0]==cur_val&& de->d_name[1]=='.') {
                    fprintf(file,"%s\n",fullPath);
                    printf("%s\n", fullPath); 
                }
            }
        }
        closedir(dir);
    }
}
 
int main() {
    char s [100];
    fgets(s,100,stdin);
    FILE *file;
    file=fopen("result.txt","w");
    const char *folderPath = "./tmp";
    for (size_t i = 0; i < strlen(s); i++){
        list_files(folderPath,s[i],file);
    }
    fclose(file);
    return 0;
}