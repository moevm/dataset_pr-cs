#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define MAX_PATH_NAME 1024

int add(const char* path);
int mul(const char* path);
int fileAdd(const char* path);
int fileMul(const char* path);

int calculate(const char* path)
{
    int res;
    DIR* dirp;
    struct dirent* dirBuffer;
    char fullPath[MAX_PATH_NAME];

    dirp = opendir(path);
    if (!dirp) { // Cannot open directory
        return 0;
    }

    while ((dirBuffer = readdir(dirp)) != NULL) {
        if (dirBuffer->d_ino == 0) { // Deleted file
            continue;
        }
        if (strcmp(dirBuffer->d_name, ".") == 0 || strcmp(dirBuffer->d_name, "..") == 0) {
            continue;
        }
        // Concat the directory path
        sprintf(fullPath, "%s/%s", path, dirBuffer->d_name);

        if (strcmp(dirBuffer->d_name, "add") == 0) {
            res = add(fullPath);
            continue;
        }
        if (strcmp(dirBuffer->d_name, "mul") == 0) {
            res = mul(fullPath);
            continue;
        }
        printf("%lu - %s [%d] %d\n",
            dirBuffer->d_ino, dirBuffer->d_name, dirBuffer->d_type, dirBuffer->d_reclen);
    }

    closedir(dirp);
    printf("Dir '%s' res %d\n", path, res);
    return res;
}

int add(const char* path)
{
    int res = 0;
    DIR* dirp;
    struct dirent* dirBuffer;
    char fullPath[MAX_PATH_NAME];

    dirp = opendir(path);
    if (!dirp) { // Cannot open directory
        return 0;
    }

    while ((dirBuffer = readdir(dirp)) != NULL) {
        if (dirBuffer->d_ino == 0) { // Deleted file
            continue;
        }
        if (strcmp(dirBuffer->d_name, ".") == 0 || strcmp(dirBuffer->d_name, "..") == 0) {
            continue;
        }
        // Concat the directory path
        sprintf(fullPath, "%s/%s", path, dirBuffer->d_name);

        if (strcmp(dirBuffer->d_name, "add") == 0) {
            res += add(fullPath);
            continue;
        }
        if (strcmp(dirBuffer->d_name, "mul") == 0) {
            res += mul(fullPath);
            continue;
        }
        if (dirBuffer->d_type == DT_REG) {
            res += fileAdd(fullPath);
        }
        printf("%lu - %s [%d] %d\n",
            dirBuffer->d_ino, dirBuffer->d_name, dirBuffer->d_type, dirBuffer->d_reclen);
    }

    closedir(dirp);
    printf("Dir '%s' res %d\n", path, res);
    return res;
}

int mul(const char* path)
{
    int res = 1;
    DIR* dirp;
    struct dirent* dirBuffer;
    char fullPath[MAX_PATH_NAME];

    dirp = opendir(path);
    if (!dirp) { // Cannot open directory
        return 0;
    }

    while ((dirBuffer = readdir(dirp)) != NULL) {
        if (dirBuffer->d_ino == 0) { // Deleted file
            continue;
        }
        if (strcmp(dirBuffer->d_name, ".") == 0 || strcmp(dirBuffer->d_name, "..") == 0) {
            continue;
        }
        // Concat the directory path
        sprintf(fullPath, "%s/%s", path, dirBuffer->d_name);

        if (strcmp(dirBuffer->d_name, "add") == 0) {
            res *= add(fullPath);
            continue;
        }
        if (strcmp(dirBuffer->d_name, "mul") == 0) {
            res *= mul(fullPath);
            continue;
        }
        if (dirBuffer->d_type == DT_REG) {
            res *= fileMul(fullPath);
        }
        printf("%lu - %s [%d] %d\n",
            dirBuffer->d_ino, dirBuffer->d_name, dirBuffer->d_type, dirBuffer->d_reclen);
    }

    closedir(dirp);
    printf("Dir '%s' res %d\n", path, res);
    return res;
}

int fileAdd(const char* path)
{
    int res = 0;
    FILE* fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Cannot open file %s\n", path);
        return 0;
    }

    int i = 0;
    int num;
    while (fscanf(fp, "%d", &num) != EOF) {
        res += num;
        i++;
        if (getc(fp) == '\n') {
            break;
        }
    }
    fclose(fp);
    return res;
}

int fileMul(const char* path)
{
    int res = 1;
    FILE* fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Cannot open file %s\n", path);
        return 0;
    }

    int i = 0;
    int num;
    while (fscanf(fp, "%d", &num) != EOF) {
        res *= num;
        i++;
        if (getc(fp) == '\n') {
            break;
        }
    }
    fclose(fp);
    return res;
}

int main()
{
    int res = calculate("./tmp");

    FILE* fp = fopen("./result.txt", "w");

    fprintf(fp, "%d\n", res);
    fclose(fp);
    printf("%d\n", res);
    return 0;
}
