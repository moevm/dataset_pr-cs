#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* pathcat(const char* path1, const char* path2) {
  int res_path_len =
      strlen(path1) + strlen(path2) +
      2;  // определение длины новой строки с учетом символов / и символа конца строки
  char* res_path =
      malloc(res_path_len * sizeof(char));  // выделение памяти под новую строку
  sprintf(res_path, "%s/%s", path1,
          path2);  // форматный вывод данных в строку return res_path;
  return res_path;
}

int walk_directory(const char* path, int mode) {
  int temp;
  int res = 0;
  if (mode == -1)
    res = 1;
  DIR* dir = opendir(path);
  struct dirent* entry;

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    } else if (entry->d_type == DT_REG) {
      char* path_file = pathcat(path, entry->d_name);
      FILE* file = fopen(path_file, "r");
      if (file) {
        char buffer[256];
        fgets(buffer, 256, file);
        char* number = strtok(buffer, " ");
        while (number != NULL) {
          if (mode == 1) {
            res += atoi(number);
          } else if (mode == -1) {
            res *= atoi(number);
          }
          number = strtok(NULL, " ");
        }
      }
      fclose(file);
    } else if (entry->d_type == DT_DIR) {
      char* path_file = pathcat(path, entry->d_name);
      if (strcmp(entry->d_name, "add") == 0) {
        temp = walk_directory(path_file, 1);
      } else if (strcmp(entry->d_name, "mul") == 0) {
        temp = walk_directory(path_file, -1);
      }
      if (mode == 1) {
        res += temp;
      } else if (mode == -1) {
        res *= temp;
      } else if (mode == 0) {
        return temp;
      }
    }
  }
  closedir(dir);
  return res;
}
int main() {
  char* path = "./tmp";
  FILE* file = fopen("./result.txt", "w");
  fprintf(file, "%d\n", walk_directory(path, 0));
  fclose(file);
  printf("%d\n", walk_directory(path, 0));
  return 0;
}

