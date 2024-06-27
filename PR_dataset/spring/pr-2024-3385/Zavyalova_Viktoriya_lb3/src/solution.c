#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define BUF 100

void search_letter(char letter, char *file_path, FILE *file) {

    DIR *dir = opendir(file_path);
    if (!dir) {
        closedir(dir);
        return;
    }
    struct dirent *de = readdir(dir);
    while (de) {
        if ((de->d_type == DT_DIR) && (strcmp(de->d_name, ".") != 0) && (strcmp(de->d_name, "..") != 0)) {
            char new_file_path[strlen(file_path) + 1 + strlen(de->d_name) + 1];
            new_file_path[0] = '\0';
            strcat(new_file_path, file_path);
            strcat(new_file_path, "/");
            strcat(new_file_path, de->d_name);
            search_letter(letter, new_file_path, file);

        } else {
            if ((strlen(de->d_name) >= 4) && (de->d_name[strlen(de->d_name)-4] == '.') && (de->d_name[strlen(de->d_name)-3] == 't') && (de->d_name[strlen(de->d_name)-2] == 'x') && (de->d_name[strlen(de->d_name)-1] == 't') && (de->d_name[0] == letter)){
                fprintf(file, "%s/%s\n", file_path, de->d_name);
			}
		}
		
        de = readdir(dir);
    }
    closedir(dir);
}


int main() {
    int i = 0;
    char word[BUF];
    scanf("%s", word);
    if (strlen(word) >= BUF) {
        word[BUF-1] = '\0';
    }
    char *file_path = "./tmp";
    FILE *file = fopen("result.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    for (; i < strlen(word); i++)
        search_letter(word[i], file_path, file);
    fclose(file);
    return 0;
}
