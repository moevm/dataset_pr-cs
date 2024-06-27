#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define READ_MODE "r"
#define WRITE_MODE "w"
#define PATH_LENGTH 13
#define UP_MEMORY 5

int fileMul(const char *path);
int fileAdd(const char *path);
int processDirectory(const char *path);
void updatePath(char *upd_path, const char *path, const char *suffix);

int main(){
    char path[] = "./tmp/";
    processDirectory(path);
    return 0;
}

void updatePath(char *upd_path, const char *path, const char *suffix){
    strcpy(upd_path, path);
    strcat(upd_path, suffix);
}

int processDirectory(const char *path){
    char upd_path[PATH_LENGTH];
    int result;
    DIR *dir = opendir(path);
    if (dir){
        struct dirent *d = readdir(dir);
        while (d){
            if (strcmp(d->d_name, "add") == 0){
                updatePath(upd_path, path, "add/");
                result = fileAdd(upd_path);
                break;
            }
            if (strcmp(d->d_name, "mul") == 0){
                updatePath(upd_path, path, "mul/");
                result = fileMul(upd_path);
                break;
            }
            d = readdir(dir);
        }
        closedir(dir);

        FILE *f;
        f = fopen("result.txt", "WRITE_MODE");
        fprintf(f, "%d", result);
        fclose(f);
    }
    return result;
}

int fileAdd(const char *path){
  	int sum = 0;
  	DIR *dir = opendir(path);
  	if (dir){
    		struct dirent *di = readdir(dir);
    		while(di){
      			if (strcmp(di->d_name, "add") == 0){
        			char *upd_path = malloc(sizeof(char)*(strlen(path)+UP_MEMORY));
                    updatePath(upd_path, path, "add/");
        			sum += fileAdd(upd_path);
      			}
      			else if (strcmp(di->d_name,"mul") == 0){
       				char *upd_path = malloc(sizeof(char)*(strlen(path)+UP_MEMORY));
                        updatePath(upd_path, path, "mul/");
                	sum += fileMul(upd_path);
            		}
      			else if (strstr(di->d_name, ".txt") != NULL){
        			char *file = malloc(sizeof(char)*(strlen(path)+strlen(di->d_name)+1));
        			strcpy(file, path);
        			strcat(file, di->d_name);
        			FILE *f = fopen(file, "READ_MODE");
        			int d;
        			while (fscanf(f, "%d", &d) == 1){
          				sum += d;
        			}
        			fclose(f);
      			}
      			di = readdir(dir);

    		}
    		closedir(dir);
  	}
  	return sum;
}


int fileMul(const char *path){
	int mult  = 1;
    	DIR *dir = opendir(path);
        if (dir){
        	struct dirent *di = readdir(dir);
            	while(di){
                	if (strcmp(di->d_name,"add") == 0){
                    		char *upd_path = malloc(sizeof(char)*(strlen(path)+UP_MEMORY));
                            updatePath(upd_path, path, "add/");
                    		mult *= fileAdd(upd_path);
          			free(upd_path);
        		}
                	else if (strcmp(di->d_name,"mul") == 0){
                    		char *upd_path = malloc(sizeof(char)*(strlen(path)+UP_MEMORY));
                            updatePath(upd_path, path, "mul/");
                    		mult *= fileMul(upd_path);
          			free(upd_path);
                	}
                	else if (strstr(di->d_name, ".txt") != NULL){
          			char *file = malloc(sizeof(char)*(strlen(path)+strlen(di->d_name)+1));
                    		strcpy(file, path);
                    		strcat(file, di->d_name);
                    		FILE *f = fopen(file, "READ_MODE");
                    		int d;
                    		while (fscanf(f, "%d", &d) == 1){
                        		mult *= d;
                    		}
                    		fclose(f);

                	}
               		 di = readdir(dir);
            	}
    		closedir(dir);
   	 }
    
  	return mult;
}
