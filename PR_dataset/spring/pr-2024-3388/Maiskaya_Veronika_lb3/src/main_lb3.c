#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define BUFFER_SIZE 100
#define DIRECTORY_PATH "./tmp"
#define RESULT_FILE "result.txt"
#define DOT "."
#define TWO_DOTS ".."
#define FILENAME_LENGTH_WITH_EXTENSION 5
#define WRITE_MODE "w"

void createFilePath(char *newPath, const char *basePath, const char *entryName)
{
    snprintf(newPath, BUFFER_SIZE, "%s/%s", basePath, entryName);
}

void searchAndWrite(char word, const char *path, FILE *outputFile)
{
    DIR *directory = opendir(path);
    if (!directory)
    {
        fprintf(stderr, "Unable to open directory: %s\n", path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL)
    {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, DOT) && strcmp(entry->d_name, TWO_DOTS))
        {
            char newPath[BUFFER_SIZE];
            createFilePath(newPath, path, entry->d_name);
            searchAndWrite(word, newPath, outputFile);
        }
        else
        {
            if (strlen(entry->d_name) == FILENAME_LENGTH_WITH_EXTENSION && entry->d_name[0] == word)
                fprintf(outputFile, "%s/%s\n", path, entry->d_name);
        }
    }

    closedir(directory);
}

char *inputWord()
{
    char *word = malloc(BUFFER_SIZE * sizeof(char));
    if (!word)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    scanf("%s", word);
    return word;
}

FILE *openOutputFile(const char *fileName)
{
    FILE *file = fopen(fileName, WRITE_MODE);
    if (!file)
    {
        fprintf(stderr, "Unable to create/open output file: %s\n", fileName);
        exit(1);
    }
    return file;
}

void closeOutputFile(FILE *file)
{
    fclose(file);
}

void processWord(const char *word, const char *path, FILE *outputFile)
{
    for (size_t i = 0; i < strlen(word); i++)
    {
        searchAndWrite(word[i], path, outputFile);
    }
}

int main()
{
    char *word = inputWord();
    FILE *outputFile = openOutputFile(RESULT_FILE);

    const char *path = DIRECTORY_PATH;
    processWord(word, path, outputFile);

    closeOutputFile(outputFile);
    free(word);

    return 0;
}
