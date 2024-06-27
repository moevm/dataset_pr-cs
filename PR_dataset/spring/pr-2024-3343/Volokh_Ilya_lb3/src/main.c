#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

#define SIZE 500

typedef struct PathResult {
    char path[SIZE];
} PathResult;

char *pathcat(const char *path1, const char *path2)
{
    int res_path_len = strlen(path1) + strlen(path2) + 2;
    char *res_path = malloc(res_path_len * sizeof(char));
    sprintf(res_path, "%s/%s", path1, path2);
    return res_path;
}

char *file_name(const char *included) {
    char *pattern = "@include (file_[0-9]*\\.txt)";
    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret != 0) {
        fprintf(stderr, "Regex compilation failed\n");
        exit(EXIT_FAILURE);
    }
    regmatch_t groups[2];
    ret = regexec(&regex, included, 2, groups, 0);
    if (ret == 0) {
        if (groups[1].rm_so != -1 && groups[1].rm_eo != -1) {
            int len = groups[1].rm_eo - groups[1].rm_so;
            char *matched_group = malloc((len + 1) * sizeof(char));
            if (matched_group == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            strncpy(matched_group, included + groups[1].rm_so, len);
            matched_group[len] = '\0';
            regfree(&regex);
            return matched_group;
        }
    }
    regfree(&regex);
    return NULL;
}

char *find_file(const char *dir_name, const char *filename)
{
    char *full_path_file = NULL;
    DIR *dir = opendir(dir_name);
    if (dir)
    {
        struct dirent *de = readdir(dir);
        while (de)
        {
            if (de->d_type == DT_REG && !strcmp(de->d_name, filename))
            {

                full_path_file = pathcat(dir_name, filename);
            }
            else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            {
                char *new_dir = pathcat(dir_name, de->d_name);
                full_path_file = find_file(new_dir, filename);
                free(new_dir);
            }
            if (full_path_file)
                break;
            de = readdir(dir);
        }
        closedir(dir);
    }
    else
        printf("Failed to open %s directory\n", dir_name);
    return full_path_file;
}

int check_file_content(const char *data) {
    if (strcmp(data, "Deadlock") == 0) {
        return 0;
    } else if (strcmp(data, "Minotaur") == 0) {
        return 1;
    }
    return 2;
}

int searching_for_Minotaur(const char *file_path, PathResult *result) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("Failed to open %s file\n", file_path);
        exit(0);
    }
    char information[SIZE];
    while (fgets(information, SIZE, file) != NULL) {
        if (check_file_content(information) == 1) {
            fclose(file);
            return 1;
        } else if (check_file_content(information) == 0) {
            fclose(file);
            return 0;
        } else {
            char *filesname = file_name(information);
            if (filesname != NULL) {
                char *file_from_the_link = find_file("labyrinth", filesname);
                if (file_from_the_link != NULL) {
                    if (searching_for_Minotaur(file_from_the_link, result)) {
                        strcat(result->path, "./");
                        strcat(result->path, file_from_the_link);
                        strcat(result->path, "\n");
                        free(file_from_the_link);
                        free(filesname);
                        fclose(file);
                        return 1;
                    }
                    free(file_from_the_link);
                }
                free(filesname);
            }
        }
    }
    fclose(file);
    return 0;
}

int main()
{
    PathResult *result = malloc(sizeof(PathResult)); 
    char *file = find_file("labyrinth", "file.txt");
     searching_for_Minotaur(file, result);
    strcat(result->path, "./");
    strcat(result->path, file);
    strcat(result->path, "\n");
    
    int counter = 0;
    char **result_file = malloc(sizeof(char *));
    char *token = strtok(result->path, "\n");
    while (token != NULL)
    {
        result_file[counter++] = token;
        result_file = realloc(result_file, sizeof(char *) * (counter + 1));
        token = strtok(NULL, "\n");
    }

    FILE *res_file = fopen("result.txt", "w");
    for (int i = counter - 1; i > -1; i--)
    {
	fprintf(res_file, "%s\n", result_file[i]);
    }

    fclose(res_file);
    free(result);
    free(result_file);
    free(file);
    return 0;
}






