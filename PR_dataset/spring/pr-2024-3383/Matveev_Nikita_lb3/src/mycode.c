#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
void final(char* start, char** massiv, int c, char** res, int* num, int* flag){
    int i;
    for (i=0; i<c; i++){
        if (strstr(massiv[i], start) !=NULL && (*flag)!=1){
            int r =*num;
            res[r] = (char*)malloc(sizeof(char)*256);
            strcpy(res[r], massiv[i]);
            (*num)++;
            //printf("%s\n", massiv[i]);
            FILE* fle;
            fle = fopen(massiv[i], "r");
            char line[250];
            char** array = (char**)malloc(50*sizeof(char*));
            int k =0;
            while(fgets(line, 250, fle)!=NULL){
                if(line[strlen(line)-1]=='\n') line[strlen(line)-1] = '\0';
                array[k] = (char*)malloc(250 * sizeof(char));
                strcpy(array[k], line);
                k++;
            }
            fclose(fle);
            if (strcmp(array[0], "Minotaur")==0){
                (*flag) = 1;
                break;
            }
            int l;
            char my_file[256];
            for (l =0; l<k; l++){
                strcpy(my_file, strstr(array[l], "file"));
                final(my_file, massiv, c, res, num, flag);
            }
            int j;
            for (j=0; j<k; j++) free(array[j]);
        }
    }
};
void filesearch(int* res,  char* str, char** gl){
    DIR* my;
    my = opendir(str);
    struct dirent* ep;
    if (my != NULL){
        ep = readdir(my);
        while (ep != NULL) {
            if (ep->d_name[0] != '.' && ep->d_type == DT_DIR){
                char* temp_str =(char*)malloc(256);
                strcpy(temp_str, str);
                strcat(temp_str, "/");
                strcat(temp_str, ep->d_name);
                filesearch(res, temp_str, gl);
                //printf("%s\n", temp_str);
                free(temp_str);
            }//perebor papok
            else if(ep->d_type == DT_REG){
                FILE* fle;
                char* name =(char*)malloc(256);
                strcpy(name, str);
                strcat(name, "/");
                strcat(name, ep->d_name);
                fle = fopen(name, "r");
                char line[250];
                fgets(line, 250, fle);
                if(line[strlen(line)-1]=='\n') line[strlen(line)-1] = '\0';
                //puts(line);
                fclose(fle);
                if (strcmp(line, "Deadlock")!=0){
                    int r  =*res;
                    gl[r] = (char*)malloc(sizeof(char)*256);
                    strcpy(gl[r], name);
                    (*res)++;//printf(name);
                }
                free(name);
                //free(line);
            }//end of file.*/}
            ep = readdir(my);
        }
        closedir(my);
    }
}
int main(){
    char str[256] = "./labyrinth";
    int result = 0;
    int my_count = 0;
    int f =0;
    char** global= (char**)malloc(sizeof(char*)*3000);
    char** itog= (char**)malloc(sizeof(char*)*3000);
    char firstfile[100] = "file.txt";
    filesearch(&result, str, global);
    final(firstfile, global, result, itog, &my_count, &f);
    FILE* fl = fopen("result.txt", "w");
    int rr;
    for (rr =0; rr<my_count; rr++){
        printf("%s\n", itog[rr]);
        fprintf(fl, "%s\n", itog[rr]);
        free(itog[rr]);
    }
    fclose(fl);
    free(itog);
    int j;
    for (j =0; j<result; j++){
        free(global[j]);
    }
    free(global);
}
