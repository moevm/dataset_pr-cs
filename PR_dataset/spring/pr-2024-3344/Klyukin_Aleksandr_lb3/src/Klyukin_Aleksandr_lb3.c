#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void solve(char *dir_name, FILE *f, char sign)
{
    DIR *dir = opendir(dir_name);
    if (dir)
    {
        struct dirent *de = readdir(dir);
        char *path;

        while (de)
        {

            if (de->d_type == DT_REG && strlen(de->d_name) == 5 && de->d_name[0] == sign && de->d_name[1] == '.' &&
                de->d_name[2] == 't' && de->d_name[3] == 'x' && de->d_name[4] == 't')
            {

                fprintf(f, "%s/%s\n", dir_name, de->d_name);
            }

            else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            {

                int res_path_len = strlen(dir_name) + strlen(de->d_name) + 2; //
                char *path = malloc(res_path_len * sizeof(char)); // выделение памяти под новую строку
                path[0] = '\0';

                strcat(path, dir_name);
                strcat(path, "/");
                strcat(path, de->d_name);
                solve(path, f, sign);

                free(path);
            }

            de = readdir(dir);
        }
        closedir(dir);
    }
    else
    {
        return;
    }
}

int main()
{
    char *dir_name = "./tmp";
    FILE *file = fopen("./result.txt", "w");
    char *inp_string = (char *)malloc(sizeof(char) * 1000);
    scanf("%s", inp_string);

    for (size_t i = 0; i < strlen(inp_string); i++)
        solve(dir_name, file, inp_string[i]);

    fclose(file);
    return 0;
}