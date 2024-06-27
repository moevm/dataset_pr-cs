#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define CAPACITY 16
#define REQUIRED_DIRECTORY "./tmp"
#define DT_REG 8
#define DT_DIR 4

void getString(char **string);
void getRequiredPathsIntoArray(const char *directoryPath, char *stringToProcess,
                               char **pathsArray, size_t *pathsArrayLength);
char *pathcat(const char *path1, const char *path2);

int main()
{
    char *stringToProcess = (char *)malloc(CAPACITY * sizeof(char));
    getString(&stringToProcess);

    char **pathsArray =
        (char **)malloc(strlen(stringToProcess) * sizeof(char *));
    for (size_t i = 0; i < strlen(stringToProcess); i++)
    {
        pathsArray[i] = (char *)calloc(CAPACITY, sizeof(char));
    }
    size_t pathsArrayLength = 0;
    getRequiredPathsIntoArray(REQUIRED_DIRECTORY, stringToProcess, pathsArray,
                              &pathsArrayLength);

    FILE *answer = fopen("result.txt", "w");
    for (size_t i = 0; i < strlen(stringToProcess); i++)
    {
        for (size_t j = 0; j < strlen(stringToProcess); j++)
        {
            if (stringToProcess[i] == pathsArray[j][strlen(pathsArray[j]) - 5])
            {
                fprintf(answer, "%s\n", pathsArray[j]);
                break;
            }
        }
    }
    fclose(answer);

    for (size_t i = 0; i < strlen(stringToProcess); i++)
    {
        free(pathsArray[i]);
    }

    free(pathsArray);
    free(stringToProcess);

    return 0;
}

void getString(char **string)
{
    char ch = getchar();
    size_t charIndex = 0;
    size_t capacityForString = CAPACITY;
    while (1)
    {
        if (charIndex == capacityForString - 1)
        {
            capacityForString += CAPACITY;
            *string =
                (char *)realloc(*string, capacityForString * sizeof(char));
        }

        (*string)[charIndex++] = ch;
        ch = getchar();

        if (ch == EOF || ch == '\0' || ch == '\n')
        {
            break;
        }
    }
}

void getRequiredPathsIntoArray(const char *directoryPath, char *stringToProcess,
                               char **pathsArray, size_t *pathsArrayLength)
{
    DIR *directory = opendir(directoryPath);
    if (directory)
    {
        struct dirent *directoryElement = readdir(directory);
        while (directoryElement)
        {
            if (strcmp(directoryElement->d_name, ".") != 0 &&
                strcmp(directoryElement->d_name, "..") != 0)
            {
                char *directoryFilePath =
                    pathcat(directoryPath, directoryElement->d_name);

                if (directoryElement->d_type == DT_DIR)
                {
                    getRequiredPathsIntoArray(directoryFilePath,
                                              stringToProcess, pathsArray,
                                              pathsArrayLength);
                    free(directoryFilePath);
                }
                else if (directoryElement->d_type == DT_REG &&
                         strlen(directoryElement->d_name) == 5)
                {
                    for (size_t i = 0; i < strlen(stringToProcess); i++)
                    {
                        if (stringToProcess[i] == directoryElement->d_name[0])
                        {
                            if (CAPACITY < strlen(directoryFilePath))
                            {
                                pathsArray[*pathsArrayLength] =
                                    (char **)realloc(
                                        pathsArray[*pathsArrayLength],
                                        strlen(directoryFilePath) *
                                            sizeof(char));
                            }
                            strcpy(pathsArray[(*pathsArrayLength)++],
                                   directoryFilePath);
                            break;
                        }
                    }
                    free(directoryFilePath);
                }
                else if (strlen(directoryElement->d_name) != 5)
                {
                    free(directoryFilePath);
                }
            }
            directoryElement = readdir(directory);
        }
        closedir(directory);
    }
}

char *pathcat(const char *path1, const char *path2)
{
    int resPathLength = strlen(path1) + strlen(path2) + 2;
    char *resPath = malloc(resPathLength * sizeof(char));
    sprintf(resPath, "%s/%s", path1, path2);

    return resPath;
}
