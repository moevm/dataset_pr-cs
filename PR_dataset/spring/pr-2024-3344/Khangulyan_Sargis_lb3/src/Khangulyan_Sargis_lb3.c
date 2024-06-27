#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#define size 5000
int count = 0;

int comparator(const void* a, const void* b){
    const char* A = *(const char**)a;
    const char* B = *(const char**)b;

    if (atoll(A) > atoll(B)) return 1;
    if (atoll(A) < atoll(B)) return -1;
    return 0;
}


void add_solution(const char* file, char** solution){
    if (strstr(file, ".txt")){
        FILE* o_file = fopen(file, "r");

        if (o_file){
            solution[count] = (char*)malloc(sizeof(char)*size);
            fgets(solution[count++], size, o_file);        
        }
        fclose(o_file);
    }
}

void find_solution(const char* dir, char** solution){
    DIR* o_dir = opendir(dir);
    char* THE_WAY = (char*)malloc(sizeof(char)*size);
    if (o_dir == NULL) return;

    if (o_dir){
        struct dirent* temp;
        while ((temp = readdir(o_dir)) != NULL){
             
            if (temp->d_type == DT_REG){
                strcpy(THE_WAY, dir);
                strcat(THE_WAY, "/");
                strcat(THE_WAY, temp->d_name);
                add_solution(THE_WAY, solution);
            }
            else if (strcmp(temp->d_name, ".") != 0 && strcmp(temp->d_name, "..") != 0){
                strcpy(THE_WAY, dir);
                strcat(THE_WAY, "/");
                strcat(THE_WAY, temp->d_name);
                find_solution(THE_WAY, solution);
            }
        }     
    }

    closedir(o_dir);
}

int main(){
    char** solution = (char**)malloc(sizeof(char*)*size);
    find_solution(".", solution);
    qsort(solution, count, sizeof(char*), comparator);

    FILE* result = fopen("./result.txt", "w");
    for (int i = 0; i < count; i++){
        fprintf(result, "%s\n", solution[i]);
        free(solution[i]);
    }
    free(solution);
    fclose(result);

    return 0;
}