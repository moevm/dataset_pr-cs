#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include <dirent.h> 
#include <unistd.h>

int 
cmp(const void *a, const void *b){
	char **lineA = (char **)a; 
    char **lineB = (char **)b; 
    long numA = atol(*lineA); 
    long numB = atol(*lineB); 
    if (numA < numB){
        return -1;
	}
    if (numA > numB){
        return 1;
	}
    return 0;
}

void 
list_dir(char* path, char*** ans, int* count){
	DIR *dir = opendir(path);

	if(dir){
		struct dirent *de = readdir(dir);
		while (de){
			char c_path[1024];
			sprintf(c_path, "%s/%s", path, de->d_name);
			if((de->d_type == DT_REG) && (strstr(de->d_name, ".txt"))){
				if(strstr(de->d_name, "result.txt")){
					de = readdir(dir);
                    continue;
                }
				FILE *fin;
				fin = fopen(c_path, "r");
				if (fin){
					char c = fgetc(fin);
					int i = 0;
					int len_str = 40;
					(*ans)[(*count)] = malloc(sizeof(char)*len_str);
					while(c != EOF){
						(*ans)[(*count)][i] = c;
						i++;
						if(i + 2 == len_str){
							len_str += 20;
							(*ans)[(*count)] = realloc((*ans)[(*count)], sizeof(char)*len_str);
						}
						c = fgetc(fin);
					}
					(*ans)[(*count)][i] = '\0';
					(*ans)[(*count)] = realloc((*ans)[(*count)], (i+1)*sizeof(char));
					(*count) += 1;
					(*ans) = realloc((*ans), sizeof(char*)*((*count)+1));
					fclose(fin);
				}
			}else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
				list_dir(c_path, ans, count);
				de = readdir(dir);
				continue;
			}
			de = readdir(dir);
		}
		closedir(dir);
	}else{
		printf("Failed to open %s directory\n", path);
	}
}

int
main(){
	char path[1024];
	getcwd(path, sizeof(path));
	char** ans = malloc(sizeof(char*));
	int count = 0;
	list_dir(path, &ans, &count);
	qsort(ans, count, sizeof(char*), cmp);
	char end[] = "/result.txt";
	strcat(path, end);
	FILE *fout = fopen(path, "w+");
	fprintf(fout, "%s", ans[0]);
	free(ans[0]);
	for (int j = 1; j < count; j++){
		fprintf(fout, "\n%s", ans[j]);
		free(ans[j]);
	}
	fclose(fout);
	free(ans);

	return 0;
} 