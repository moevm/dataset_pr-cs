#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* pathcat(char* path1, char* path2)
{
	int res_path_len = strlen(path1)+strlen(path2)+2;
	char* res_path = malloc(sizeof(char)*res_path_len);
	sprintf(res_path, "%s/%s", path1, path2);
	return res_path;
}


long int count(FILE* current_file, char* operation)
{	
	if (current_file==NULL) return -1;

	long int count, c;
	if (strcmp(operation, "add") == 0)
	{	
		count = 0;
		while(fscanf(current_file, "%ld ", &c)==1) count += c;
		return count;
	}
	else if(strcmp(operation, "mul") == 0)
	{
		count = 1;
		while(fscanf(current_file, "%ld ", &c)==1) count *= c;
		return count;
	}
	else return 0;
}


long int listdir(char* path, char* last_dir)
{
	DIR* dir = opendir(path);
	if (dir == NULL) exit(-1);
	struct dirent* entry;

	long int c;
	if (strcmp(last_dir, "add") == 0) c = 0;
	else if (strcmp(last_dir, "mul") == 0) c = 1;

	while((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			if (strcmp(entry->d_name, "." ) == 0 || strcmp(entry->d_name, "..") == 0) continue;
			char* current_path = pathcat(path, entry->d_name);
			long int count = listdir(current_path, entry->d_name);

			if (strcmp(last_dir, "add") == 0) c+=count;
			else if(strcmp(last_dir, "mul") == 0) c*=count;
			else return count;
		}
		else if (entry->d_type == DT_REG)
		{
			char* current_path = pathcat(path, entry->d_name);
			FILE* current_file = fopen(current_path, "r");
			long int overall = count(current_file, last_dir);
			fclose(current_file);
			if (strcmp(last_dir, "add") == 0) c += overall;
			else if (strcmp(last_dir, "mul") == 0) c *= overall;
		}
	}
	closedir(dir);
	return c;
}


int main()
{
	long int answer = listdir("./tmp", ".");
	FILE* result = fopen("result.txt", "w");
	fprintf(result, "%ld", answer);
	fclose(result);
	return 0;
}


