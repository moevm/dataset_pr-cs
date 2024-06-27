#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define N_CHARS 128

typedef struct {
    int used;
    int total;
    char **paths;
} files_t;

void check_dir(files_t *files, char *path)
{
    DIR *dir = opendir(path);
    struct dirent *ent;

    ent = readdir(dir);
    while (ent != NULL) {
        char newpath[FILENAME_MAX];
        strcpy(newpath, path);
        strcat(newpath, "/");
        strcat(newpath, ent->d_name);

        switch (ent->d_type) {
            case DT_DIR: {
		        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
                    check_dir(files, newpath);
                break;
            }
            case DT_REG:
                if (strcmp(ent->d_name + 1, ".txt") == 0 && isalpha(ent->d_name[0])) {
                    char c = ent->d_name[0];
                    files[c].total++;
                    files[c].paths = realloc(files[c].paths, files[c].total * sizeof(files_t));
                    files[c].paths[files[c].total - 1] = strdup(newpath);
                }
            default:
                break;
        }

        ent = readdir(dir);
    }

    closedir(dir);
}


int main()
{
    files_t *files;
    char str[FILENAME_MAX];

    freopen("result.txt", "w", stdout);
    scanf("%s", str);

    files = malloc(sizeof(files_t) * N_CHARS);
    for (size_t i = 0; i < N_CHARS; i++) {
        files[i].paths = NULL;
        files[i].total = 0;
        files[i].used  = 0;
    }

    check_dir(files, "tmp");

    char *c = str;
    while (*c != '\0') {
        printf("./%s\n", files[*c].paths[files[*c].used]);
        files[*c].used++;
        c++;
    }
    return 1;
}
