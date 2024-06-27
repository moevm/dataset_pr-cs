#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 128
#define TERMINAL_ZERO '\0'
#define END_LINE '\n'
#define SLASH '/'
#define CURRENT_DIR "."
#define PARENT_DIR ".."

typedef struct Data {
	int size;
	int capacity;
	char** array;
} Data;

Data* createData() {
	Data* element = (Data*) calloc(1, sizeof(Data));
	return element;
}

char* at(Data* element, int index) {
	return element->array[index];
}

void printData(Data *element) {
	for (int i=0; i<element->size; i++) {
		printf("%s\n", at(element, i));
	}
}

void pushBack(Data* element, char* new_element) {
    if (element->size >= element->capacity) {
        element->capacity = (element->size == 0) ? 2 : element->capacity*element->capacity;
        element->array = realloc(element->array, element->capacity*sizeof(char*));
    }
    element->array[element->size++] = new_element;
}

Data* getNewCopy(Data* element, char* new_element) {
	Data* copy = createData();
	for (int i=0; i<element->size; i++) {
		pushBack(copy, at(element, i));
	}
	pushBack(copy, new_element);
	return copy;
}

void getDataFromFile(char* filePath, Data* element) {
	FILE* fin = fopen(filePath, "r");

	char* string = (char*) malloc(CAPACITY*sizeof(char));
	while (fgets(string, CAPACITY, fin)) {
		if (strchr(string, END_LINE)) {
			*(strchr(string, END_LINE)) = TERMINAL_ZERO;
		}
		pushBack(element, string);
		string = (char*) malloc(CAPACITY*sizeof(char));
	}

	fclose(fin);
}

char* getSubPath(char* dirPath, char* subName) {
    char* subPath = (char*) calloc((strlen(dirPath) + strlen(subName) + 2), sizeof(char));
    strcpy(subPath, dirPath);
    subPath[strlen(dirPath)] = SLASH;
    strcat(subPath, subName);
    return subPath;
}

void getTargetFilePath(char* dirPath, char** targetFilePath, char* targetFile) {
	DIR* dir = opendir(dirPath);
	struct dirent* content = readdir(dir);
	while (content) {
		char* subPath = getSubPath(dirPath, content->d_name);
		if (content->d_type == DT_REG && strcmp(content->d_name, targetFile) == 0) {
			(*targetFilePath) = (char*) malloc((strlen(subPath)+1)*sizeof(char));
			strcpy(*targetFilePath, subPath);
		}
		if (content->d_type == DT_DIR) {
			if (strcmp(content->d_name, CURRENT_DIR) != 0 && strcmp(content->d_name, PARENT_DIR) != 0) {
				getTargetFilePath(subPath, targetFilePath, targetFile);
			}
		}
		content = readdir(dir);
	}
	closedir(dir);
}

void output(char* filePath, Data* labyrinthPath) {
    FILE* fout = fopen(filePath, "w");
    char buffer[124];
    for (int i=0; i<labyrinthPath->size; i++) {
		sprintf(buffer, "%s\n", at(labyrinthPath, i));
    	fputs(buffer, fout);
	}
    fclose(fout);
}

void crawling(char* targetFilePath, Data* labyrinthPath, char* targetString, char* resultFile, char* deadlock, char* directoryName) {
	Data* data = createData();
	getDataFromFile(targetFilePath, data);
	if (strcmp(at(data, 0), targetString) == 0) {
		output(resultFile, labyrinthPath);
		return;
	}
	if (strcmp(at(data, 0), deadlock) == 0) {
		return;
	}
	for (int i=0; i<data->size; i++) {
		char* targetFilePath = NULL;
		getTargetFilePath(directoryName, &targetFilePath, strchr(at(data, i), ' ') + 1);

		crawling(targetFilePath, getNewCopy(labyrinthPath, targetFilePath), targetString, resultFile, deadlock, directoryName);
	}
}

int main() {
	char* targetFilePath = NULL;
	getTargetFilePath("./labyrinth", &targetFilePath, "file.txt");
	Data* labyrinthPath = createData();
	pushBack(labyrinthPath, targetFilePath);
	crawling(targetFilePath, labyrinthPath, "Minotaur", "result.txt", "Deadlock", "./labyrinth");
}