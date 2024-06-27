#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_LEN 1024
#define INITIAL_BUFFER_SIZE 1024


int cmp_strings(const void *a, const void *b) 
{
    long a_num = atol( *((char**)a) ); 
    long b_num = atol( *((char**)b) );
    if (a_num > b_num) return 1;
    if (a_num < b_num) return -1;
    return 0;
}

void read_text_files(const char* path, char*** lines, int* count_lines) 
{
    DIR* dir = opendir(path);
    if (!dir) 
    {
        perror(path);
        exit(EXIT_FAILURE);
    }

    struct dirent* entry;
    while ((entry = readdir(dir))) 
    {
        char full_path[MAX_LEN];
        sprintf(full_path, "%s/%s", path, entry->d_name);

        if (entry->d_type == DT_DIR) 
        {
            if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
            {
                continue;
            }
            read_text_files(full_path, lines, count_lines);
        }

        if (entry->d_type == DT_REG && strstr(entry->d_name, ".txt") && !strstr(entry->d_name, "result.txt")) 
        {
            FILE* file = fopen(full_path, "r");
            if (file) 
            {
                int buffer_size = INITIAL_BUFFER_SIZE;
                char* line = malloc(buffer_size);
                int len_line = 0;
                int sym;
                while ((sym = fgetc(file)) != EOF) 
                {
                    if (len_line + 1 >= buffer_size) 
                    {
                        buffer_size *= 2;
                        char* new_line = realloc(line, buffer_size);
                        line = new_line;
                    }

                    line[len_line++] = (char)sym;
                }
                line[len_line] = '\0';

                (*lines)[(*count_lines)++] = line;
                *lines = (char**)realloc(*lines, sizeof(char*) * (*count_lines + 1));
                fclose(file);
            }
        }
    }
    closedir(dir);
}


int main() 
{
    char current_dir[MAX_LEN];
    if (!getcwd(current_dir, sizeof(current_dir))) 
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    int count_lines = 0;
    char** lines = (char**)calloc(1, sizeof(char*));

    read_text_files(current_dir, &lines, &count_lines);
    qsort(lines, count_lines, sizeof(char*), cmp_strings);

    char end[] = "/result.txt";
    strcat(current_dir, end);
    FILE* file = fopen(current_dir, "w+");
    fprintf(file, "%s", lines[0]);
    free(lines[0]);

    for (int i = 1; i < count_lines; i++) 
    {
        fprintf(file, "\n%s", lines[i]);
        free(lines[i]);
    }

    free(lines);
    fclose(file);
    return 0;
}