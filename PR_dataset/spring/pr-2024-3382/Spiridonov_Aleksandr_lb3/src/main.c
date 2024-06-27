#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


char* file_pathfinder(char* path, char letter){
	DIR* dir = opendir(path);

	if(dir){
		struct dirent* current_dir_file = readdir(dir);

		while(current_dir_file){
			char new_path[200];

			strcpy(new_path, path);
			strcat(new_path, "/");
			strcat(new_path, current_dir_file->d_name);

			if((current_dir_file->d_type == DT_DIR) && current_dir_file->d_name[0] != '.'){
				if (file_pathfinder(new_path, letter))
					return file_pathfinder(new_path, letter);
			}
			else if (strlen(current_dir_file->d_name) == 5 && current_dir_file->d_name[0] == letter){
				char * result = malloc(sizeof(char) * (strlen(new_path)));
                strcpy(result, new_path);
                return result;
			}
			current_dir_file = readdir(dir);		
		}
	}
	closedir(dir);
}

int main(){
	char* input_str = (char*)malloc(sizeof(char)*201);	
	char* path = "./tmp";
	fgets(input_str, 200, stdin);

	FILE* result = fopen("result.txt", "w");

	int length = strlen(input_str)-1;

	for (int i = 0; i < length; i++){
		char* result_path = file_pathfinder(path, input_str[i]);
		fprintf(result, "%s\n" ,result_path);
		free(result_path);

	}

	free(input_str);
	fclose(result);
	return 0;
}