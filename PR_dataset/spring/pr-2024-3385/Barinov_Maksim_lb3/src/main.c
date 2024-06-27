#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void proc(char *file, int type, int *res) {
	FILE *f = fopen(file, "r");
	int d;
	while (fscanf(f, "%d", &d) == 1) {
		if (type) *res *= d;
		else *res += d;
	}
	fclose(f);
}

int func(const char* path, int type) {
	int res = 0;
	if (type) res = 1;
	DIR *dir = opendir(path);
	if (dir) {
		struct dirent *de = readdir(dir);
		while(de) {
			if (!strcmp(de->d_name, "add")) {
				char *cur = malloc(sizeof(char) * (strlen(path) + 5));
				strcpy(cur, path);
				strcat(cur,	"add/");
				if (type) res *= func(cur, type);
				else res += func(cur, type);
				free(cur);
			} else if (!strcmp(de->d_name, "mull")) {
				char *cur = malloc(sizeof(char) * (strlen(path) + 5));
				strcpy(cur, path);
				strcat(cur, "mul/");
				if (type) res *= func(cur, type);
				else res += func(cur, type);
				free(cur);
			} else if (strstr(de->d_name, ".txt") != NULL) {
				char *file = malloc(sizeof(char) * (strlen(path) + strlen(de->d_name) + 1));
				strcpy(file, path);
				strcat(file, de->d_name);
				proc(file, type, &res);
			}
			de = readdir(dir);
		}
		closedir(dir);
	}
	return res;
}

int main(){
	char path[]="./tmp/";
  	char updated[13];
  	int result;
  	DIR *dir = opendir(path);
  	if (dir){
    		struct dirent *d = readdir(dir);
    		while (d){
      			if (strcmp(d->d_name,"add") == 0){
                		strcpy(updated, path);
                		strcat(updated, "add/");
                		result = func(updated, 0);
                		break;
      			}
      			if (strcmp(d->d_name, "mul") == 0){
        			strcpy(updated, path);
        			strcat(updated, "mul/");
        			result = func(updated, 1);
        			break;
      			}
      			d = readdir(dir);
   		 }
  	}
  	closedir(dir);
  	FILE *f;
  	f = fopen("result.txt", "w");
  	fprintf(f, "%d", result);
  	fclose(f);
  	return 0;
}

