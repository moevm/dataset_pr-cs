#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Files(FILE *inp, char *main_path, char letter)
{

    DIR *dir = opendir(main_path);

    if (!dir)
        return;

    struct dirent *dp = readdir(dir);
    char *path;

    while (dp != NULL)
    {

        if (dp->d_type == DT_DIR && strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {

            path = (char *)malloc(sizeof(char) * (strlen(main_path) + strlen(dp->d_name) + 2));
            path[0] = '\0';

            strcat(path, main_path);
            strcat(path, "/");
            strcat(path, dp->d_name);
            Files(inp, path, letter);

            free(path);
        }
        else
        {

            if (dp->d_type == DT_REG && strlen(dp->d_name) == 5 && dp->d_name[0] == letter && dp->d_name[1] == '.' &&
                dp->d_name[2] == 't' && dp->d_name[3] == 'x' && dp->d_name[4] == 't')
            {

                fprintf(inp, "%s/%s\n", main_path, dp->d_name);
            }
        }

        dp = readdir(dir);
    }

    closedir(dir);
}

int main()
{
    char *main_path = "./tmp";
    FILE *file = fopen("./result.txt", "w");

    char *inp_string = (char *)malloc(sizeof(char) * 1000);
    scanf("%s", inp_string);

    for (size_t i = 0; i < strlen(inp_string); i++)
        Files(file, main_path, inp_string[i]);

    fclose(file);
    free(inp_string);

    return 0;
}