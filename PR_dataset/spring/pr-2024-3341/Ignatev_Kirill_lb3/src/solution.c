#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>


#define MAX_FILE_COUNT 3000
#define ENDLINE '\n'
#define ENDSTR '\0'
#define MAX_STR_SIZE 256

const char* current_dir = ".";
const char* parrent_dir = "..";


char* getFilename(char* buf){
    char* filename = malloc(MAX_STR_SIZE*sizeof(char));
    int index=0;
    int filename_start_index=9;
    for (int i = filename_start_index; i < strlen(buf); ++i) {
        filename[index]=buf[i];
        index++;
    }
    if (filename[index-1]==ENDLINE){
        filename[index-1]=ENDSTR;
    }else {
        filename[index] = ENDSTR;
    }
    return filename;
}

//Поиск файла

char *pathcat(const char *path1, const char *path2){
    int res_path_len = strlen(path1) + strlen(path2) + 2;
    char *res_path = malloc(res_path_len*sizeof(char));
    sprintf(res_path, "%s/%s", path1 ,path2);
    return res_path;
}

void checkFile(bool* found, char** allFiles, char* full_path_file, int* index);

char *find_file(const char *dir_name, const char *filename, char** allFiles, int* index, bool* found){
    char *full_path_file = NULL;
    DIR *dir = opendir(dir_name);
    if(dir){
        struct dirent *reading_element = readdir(dir);
        while (reading_element){
            if(reading_element->d_type == DT_REG && !strcmp(reading_element->d_name, filename)){

                full_path_file = pathcat(dir_name, filename);

                checkFile(found, allFiles, full_path_file, index);

            }else if (reading_element->d_type == DT_DIR &&
                      strcmp(reading_element->d_name, current_dir) != 0 &&
                      strcmp(reading_element->d_name, parrent_dir) != 0){

                char *new_dir = pathcat(dir_name, reading_element->d_name);

                full_path_file = find_file(new_dir, filename, allFiles, index, found);
                free(new_dir);
            }
            if(full_path_file)
                break;
            reading_element = readdir(dir);
        }
        closedir(dir);
    }else
        printf("Failed to open %s directory\n", dir_name);
    return full_path_file;
}

void checkFile(bool* found, char** allFiles, char* full_path_file, int* index){
    FILE *file=fopen(full_path_file, "r");
    char buf[MAX_STR_SIZE];
    if (file){
        while ((fgets(buf, MAX_STR_SIZE, file))!=NULL){
            if (*found== true)
                break;

            if (strcmp(buf, "Minotaur")==0){
                allFiles[*index]=full_path_file;
                (*index)++;
                *found = true;
                break;
            }else{
                char* nameNextFile = getFilename(buf);
                if (strcmp(nameNextFile, "")==0){
                    nameNextFile=NULL;
                    break;
                }
                if (nameNextFile!=NULL){
                    if (*index>0){

                        if (strcmp(allFiles[*index-1], full_path_file)!=0){
                            allFiles[*index] = full_path_file;
                            (*index)++;
                        }
                        for (int i = 0; i < *index-1; ++i) {
                            if(strcmp(allFiles[i], full_path_file)==0){
                                for (int j = i++; j < (*index)-1; ++j) {
                                    allFiles[j]="NULL";
                                }
                            }
                        }
                    }else{
                        allFiles[*index] = full_path_file;
                        (*index)++;
                    }
                    find_file("./test", nameNextFile, allFiles, index, found);
                }
            }
        }
        fclose(file);
    }
}

void createResultFile(int index, char** allFiles){
    FILE *res = fopen("result.txt", "w");
    for (int i = 0; i<index; ++i){
        if(strcmp(allFiles[i], "NULL")!=0) {
            fprintf(res, "%s\n", allFiles[i]);
        }
    }
    fclose(res);
}

int main(){
    char** allFiles = malloc(MAX_FILE_COUNT*sizeof(char));
    int index=0;
    bool found=false;
    find_file("./test", "file.txt", allFiles, &index, &found);
    createResultFile(index,allFiles);
    free(allFiles);
    return 0;
}
