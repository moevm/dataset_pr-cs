#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <regex.h>

#define BUF_SIZE 300

typedef struct {
  long long number;
  char* content;
} FileInfo;


typedef struct {
  long long size;
  FileInfo* items;
} FileList;

const char* SEARCH_DIR = "./";
const char* RESULT_FILE = "./result.txt";
const char* EXT_PATTERN = "^.*\\.txt$";


void InitializeFileList(FileList* list, long long number, char* content) {
  list->size++;
  list->items = (FileInfo*)malloc(sizeof(FileInfo));
  list->items[0].number = number;
  list->items[0].content = strdup(content);
}


void AddToFileList(FileList* list, long long number, char* content) {
  list->items = (FileInfo*)realloc(list->items, sizeof(FileInfo) * (list->size + 1));
  list->items[list->size].number = number;  
  list->items[list->size].content = strdup(content);
  list->size++;
}


int CheckFileExtension(const char* filename) {
  regex_t regex;
  regmatch_t matches[1];
  regcomp(&regex, EXT_PATTERN, REG_EXTENDED);
  int result = regexec(&regex, filename, 1, matches, 0);
  regfree(&regex);
  return result == 0;
}


void AnalyzeFile(char* filepath, FileList* list) {
  FILE* file = fopen(filepath, "r");
  if (file) {
    long long number;
    char buffer[BUF_SIZE];
    fscanf(file, "%Ld ", &number);
    fgets(buffer, BUF_SIZE - 1, file);
    if (list->size == 0)
      InitializeFileList(list, number, buffer);
    else
      AddToFileList(list, number, buffer);
  } else {
    fprintf(stderr, "Ошибка открытия файла %s\n", filepath);
  }
  fclose(file);
}


void OutputFileList(FileList* list) {
  FILE* file = fopen(RESULT_FILE, "w");
  for(int i = 0; i < list->size; i++) {
    fprintf(file, "%Ld %s", list->items[i].number, list->items[i].content);
    if (i < list->size - 1)
      fprintf(file, "\n");
  } 
  fclose(file);
}


int CompareData(const void* a, const void* b) {
  FileInfo* fa = (FileInfo*)a;
  FileInfo* fb = (FileInfo*)b;
  return (fa->number > fb->number) - (fa->number < fb->number);
}

void SortFileList(FileList* list) {
  qsort(list->items, list->size, sizeof(FileInfo), CompareData);
}


void FreeFileList(FileList* list) {
  for(unsigned long long i = 0; i < list->size; i++) {
    free(list->items[i].content);
  }
  free(list->items);
}


char* CreateSubPath(const char* base, const char* addition) {
  char* new_path = (char*)malloc(strlen(base) + strlen(addition) + 2);
  sprintf(new_path, "%s/%s", base, addition);
  return new_path;
}

int IsNotDotOrDotDot(const char* name) {
  return strcmp(name, ".") && strcmp(name, "..");
}

void AnalyzeDirectory(const char* path, FileList* list) {
  DIR* dir = opendir(path);
  if (dir) {
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_type == DT_REG && CheckFileExtension(entry->d_name)) {
        char* full_path = CreateSubPath(path, entry->d_name);
        AnalyzeFile(full_path, list);
        free(full_path);
      } else if (entry->d_type == DT_DIR && IsNotDotOrDotDot(entry->d_name)) { // Используем новую функцию здесь
        char* full_path = CreateSubPath(path, entry->d_name);
        AnalyzeDirectory(full_path, list);
        free(full_path);
      }
    }
    closedir(dir);
  } else {
    fprintf(stderr, "Ошибка открытия директории %s\n", path);
  }
}

int main() {
  FileList list = {0};
  AnalyzeDirectory(SEARCH_DIR, &list);
  SortFileList(&list);
  OutputFileList(&list);
  FreeFileList(&list);
}
