#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#define STEP 10

char* pathcat(const char* path1, const char* path2){
	int res_path_len = strlen(path1) + strlen(path2) + 2;

	char* res_path = (char*)malloc(res_path_len*sizeof(char));
	if(!res_path)
		perror("Could not find memory");

	sprintf(res_path,"%s/%s",path1,path2);

	return res_path;
}

char* find_file(const char* dir_name, const char* filename){
	char* full_path_file = NULL;
	DIR* dir = opendir(dir_name);
	if(dir){
		struct dirent* de = readdir(dir);
		while(de){
			if(de->d_type == DT_REG && !strcmp(de->d_name,filename) ){
				full_path_file = pathcat(dir_name,filename);
			}else if (de->d_type == DT_DIR && strcmp(de->d_name,".")!=0&&strcmp(de->d_name,"..")!=0){
				char* new_dir = pathcat(dir_name,de->d_name);
				full_path_file = find_file(new_dir,filename);
				free(new_dir);
			}
			if(full_path_file)
				break;
			de = readdir(dir);
		}
		closedir(dir);
	}else
		printf("Failed to open %s directory\n", dir_name);
	return full_path_file;
}

char* find_filename(const char* filename){
        const char* prefix = "file";
        const char* postfix = ".txt";
        const char* start = strstr(filename,prefix);
	const char* end = strstr(filename,postfix);

        if(start!=NULL&&end!=NULL){
                int end = strlen(filename);
                int length = end-9+1;
                char* result = (char*)malloc(length*sizeof(char));
		
		if(!result){
			perror("Could not find memory");
			return NULL;
		}

		int k = 0;
                for(int i = 9;i<end;i++)
                        result[k++] = filename[i];
                result[k] = '\0';
		
                return result;
        }else
                return NULL;
}

int read_files(const char* path_st, char** paths, int* i, FILE* fp){
	FILE* start_file = fopen(path_st,"r");
	if(!start_file){
		puts("Failed to open your file>0<\n");
		return 0;
	}
	char* filename = (char*)malloc(STEP * sizeof(char));
	if(!filename){
		perror("Could not find memory");
		return 0;
	}

	int index = 0;
	int max_size = STEP;
	char c = EOF;
	do{
		c = fgetc(start_file);
		if((c=='\n'||c==EOF)&&index>0){
			filename[index] = '\0';
			
			if(strcmp(filename,"Minotaur")==0){
				for(int k = 0;k<(*i)-1;k++)
					fprintf(fp,"./%s\n",paths[k]);
				fprintf(fp,"./%s\n",path_st);
				return 1;
			}else if(strcmp(filename,"Deadlock")==0){
				free(paths[--(*i)]);
				return 0;
			}	
			filename = find_filename(filename);
			
			char* path = find_file("labyrinth",filename);
			int len = strlen(path);

			paths[(*i)] = (char*)malloc((len+1)*sizeof(char));
			if(!paths[(*i)]){
				printf("Could not find memory");
				return 0;
			}
			
			strcpy(paths[(*i)],path);
			(*i)++;
			if(path){
				int r = read_files(path,paths,i,fp);
			}else
				printf("File %s not found\n",filename);
	
			free(path);
			index = 0;
		}else{
			filename[index++] = c;
		}
		if(index >= max_size){
			max_size += STEP;
			filename = realloc(filename,max_size);
			if(!filename){
				perror("Could not find memory");
				return 0;
			}
		}

	}while(c!=EOF);
	paths[--(*i)] = '\0';
	fclose(start_file);
}

int main(){
	FILE *fp = fopen("result.txt","w");
	if(!fp){
		perror("Error");
		return 1;
	}

	char* start_path = find_file("labyrinth","file.txt");
	char** paths = (char**)malloc(3500*sizeof(char*));
	if(!paths){
		perror("Could not find memory");
		return 0;
	}
	int i = 0;

        fprintf(fp,"./%s\n",start_path);

	int p = read_files(start_path,paths,&i,fp);
	
	fclose(fp);
	for(int j = 0;j<i;j++){
		free(paths[j]);}
	free(paths);
	
	return 0;
}
