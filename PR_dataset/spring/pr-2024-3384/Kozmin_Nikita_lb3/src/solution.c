#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>


int dir_calculation(char *directory, char command){
    DIR *root_dir = opendir(directory);
    int rslt;
    if (command == '+'){
        rslt = 0;
    }
    else if (command == '*'){
        rslt = 1;
    }
    else{
        return 0;
    }

    if (root_dir){
        struct dirent *dir_element = readdir(root_dir);
        // tmp_dir = directory + (dir_element->d_name)

        while (dir_element){
            char tmp_dir[256];

            strcpy(tmp_dir, directory);
            strcat(tmp_dir, "/");
            strcat(tmp_dir, dir_element->d_name);  

            if (dir_element->d_type == DT_DIR && dir_element->d_name[0] != '.'){
                int dir_calc_rslt;

                if (strcmp(dir_element->d_name, "add") == 0){
                    dir_calc_rslt = dir_calculation(tmp_dir, '+');
                }
                else if (strcmp(dir_element->d_name, "mul") == 0){
                    dir_calc_rslt = dir_calculation(tmp_dir, '*');
                }
                else{
                    dir_calc_rslt = 0;
                }                

                if (command == '+'){
                    rslt += dir_calc_rslt;
                }
                else if (command == '*'){
                    rslt *= dir_calc_rslt;
                }
            }
            else if (dir_element->d_type == DT_REG){
                FILE *file = fopen(tmp_dir, "r");
                int i;
                char c;
                while (fscanf(file, "%d", &i)!=EOF){
                    if (command == '+'){
                        rslt += i;
                    }
                    else if (command == '*'){
                        rslt *= i;
                    }                    
                }
                fclose(file);
            }
            dir_element = readdir(root_dir);
        }
    }

    closedir(root_dir);
    return rslt;
}

int main(){
    DIR *root_dir = opendir("./tmp");
    readdir(root_dir); // dir: .
    readdir(root_dir); // dir: ..
    struct dirent *dir_element = readdir(root_dir); // dir: add or mul
    FILE *file = fopen("./result.txt", "w");
    if (strcmp(dir_element->d_name, "add") == 0){
        fprintf(file, "%d", dir_calculation("./tmp/add", '+'));
    }
    else if (strcmp(dir_element->d_name, "mul") == 0){
        fprintf(file, "%d", dir_calculation("./tmp/mul", '*'));
    }
    else{
        fprintf(file, "%d", 0);
    }
    fclose(file);
    return 0;
}
