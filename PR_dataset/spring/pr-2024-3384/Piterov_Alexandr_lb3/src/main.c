
#include <sys/types.h>
#include <dirent.h>

#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TARGET "result.txt"
#define WRKDIR "./tmp"

/*
#if (__STDC_VERSION__ < 199901L)
#define DT_REG 4
#define DT_DIR 8
#endif
*/

char* paths[BUFSIZ];

void dirwalk(const char* dirpath) {
    
    DIR* dp = opendir(dirpath);
    struct dirent* entry;

    while ((entry = readdir(dp)) != NULL) {
        
        int len = snprintf(NULL, 0L, "%s/%s", dirpath, entry->d_name);
        char* path = (char*) malloc((len + 1) * sizeof(char));
        snprintf(path, len + 1, "%s/%s", dirpath, entry->d_name);

        switch(entry->d_type) {
            case DT_REG: ;
                char* name;
                name = strdup(entry->d_name);
                strtok(name, ".");

                if (strlen(name) != 1)
                    free(path);
                else 
                    paths[(int)entry->d_name[0]] = path;

                free(name);
                break;
            case DT_DIR:
                if (strcmp(entry->d_name, ".") != 0
                    && strcmp(entry->d_name, "..") != 0) 
                    dirwalk(path);

                free(path);
                break;
        };
    }

    closedir(dp);
}


int main(int argc, char** argv) {

    /* Ввод данных */
    /*
    if (argc != 2) {
        puts("Usage: ./prog 'string'");
        exit(EXIT_FAILURE);
    }
    */
    
    char buf[BUFSIZ];
    scanf("%s", buf);

    /* Обход файловой системы */
    dirwalk(WRKDIR);

    /* Вывод результата поиска */
    /* Реализация через системне вызовы
    int fd;
    if ((fd = creat(TARGET, 0666)) == -1) {
        perror("syscall creat");
        exit(EXIT_FAILURE);
    }
    */
    
    FILE* fp = fopen("result.txt", "w");
    
    /*
    #if (__STDC_VERSION__ < 199901L)
    fputs("Warning: using C89!\n", stderr);
    char* str;
    for (str = argv[1]; *str != '\0'; str++) {
    #else
    for (char* str = argv[1]; *str != '\0'; str++) {
    #endif
    */
    /* for (char* str = argv[1]; *str != '\0'; str++) { */
    for (char* str = buf; *str != '\0'; str++) {
        char* path;
        if((path = paths[(int)*str]) == NULL) {
            fprintf(stderr, "Error: symbol '%c' not found\n", *str);
            exit(EXIT_FAILURE);
        }
        
        /* 
        int size = strlen(path) + 1;
        if (write(fd, path, size) != size
            || write(fd, "\n", 1) != 1) {
            perror("syscall write");
            exit(EXIT_FAILURE);
        } 
        */
        
        if(fputs(path, fp) == EOF || fputc('\n', fp) == EOF) { 
            perror("Failed to write");
            exit(EXIT_FAILURE);
        }
    }

    /* Очистка */
    int i;
    for (i = 0; i < BUFSIZ; i++) {
        free(paths[i]);
    }

    /* close(fd); */
    fclose(fp);
    exit(EXIT_SUCCESS);
}

