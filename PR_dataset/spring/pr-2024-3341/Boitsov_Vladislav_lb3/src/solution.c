#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<stdbool.h>
#include<sys/types.h>
#include<regex.h>

#define BUF_SIZE 300

typedef struct dirent dirent;
typedef struct file_data_node
{
  long long num;
  char* data;
  
}file_data_node;

typedef struct file_list
{
  long long num;
  file_data_node* array;
}file_list;

const char* dir_separator = "/";
const char* current_dir = ".";
const char* parent_dir = "..";
const char* root_dir = "./";
const char* output_file_name = "./result.txt";
const char* file_extension_pattern = "^.*\\.txt$";

file_list makeList()
{
  file_list list;
  list.num=0;
  return list;
}

void listInit(file_list* list, long long data_num, char* data)
{
  list->num++;
  list->array = (file_data_node*)malloc(sizeof(file_data_node));
  list->array[0].num=data_num;
  list->array[0].data = (char*)malloc(sizeof(char)*(strlen(data)+1));
  strcpy(list->array[0].data, data);
}

void listAppend(file_list* list, long long data_num, char* data)
{
  list->array=(file_data_node*)realloc(list->array, sizeof(file_data_node)*(list->num+1));
  list->array[list->num].num=data_num;  
        list->array[list->num].data = (char*)malloc(sizeof(char)*(strlen(data)+1));
        strcpy(list->array[list->num].data, data);
  list->num++;
}

int fileExtensionCheck(const char* file_name)
{
  regex_t pattern_compiled;
  regmatch_t groups_array[1];
  regcomp(&pattern_compiled, file_extension_pattern, REG_EXTENDED);
  int res=regexec(&pattern_compiled, file_name, 1, groups_array, 0);
  regfree(&pattern_compiled);
  return res==0;
}

void fileAnalisys(char* file_path, file_list* array)
{
  FILE* fp = fopen(file_path, "r");
  if (fp)
  {
    long long num;
    char buf[BUF_SIZE];
    fscanf(fp, "%Ld ", &num);
    fgets(buf, BUF_SIZE - 1, fp);
    if (array->num==0)
      listInit(array, num, buf);
    else
      listAppend(array, num, buf);
  }
  else
    fprintf(stderr, "Error in opening file %s\n", file_path);
  fclose(fp);
}

void printFileList(file_list* list)
{
  FILE* fp = fopen(output_file_name, "w");
  for(int i=0;i<list->num;i++)
  {
    fprintf(fp, "%Ld %s", list->array[i].num, list->array[i].data);
    if (i<list->num-1)
      fprintf(fp, "\n");
  } 
  fclose(fp);
}

int dataCompare(const void* first_elem, const void* second_elem)
{
  long long first_num = ((file_data_node*)first_elem)->num;
  long long second_num = ((file_data_node*)second_elem)->num;
  if (first_num>second_num)
    return 1;
  else if (first_num<second_num)
    return -1;
  else
    return 0;
}

void sortList(file_list* list)
{
  qsort((void*)list->array, list->num, sizeof(file_data_node), dataCompare);
}

void cleanList(file_list* list)
{
  for(unsigned long long i=0;i<list->num;i++)
  {
    free(list->array[i].data);
  }
  free(list->array);
  
}

char* makeSubPath(const char* old_path, const char* addition)
{
  char* new_path=(char*)malloc(sizeof(char)*(strlen(addition)+strlen(old_path)+2));
  strcpy(new_path, old_path);
  strcat(new_path, dir_separator);
  strcat(new_path, addition);
  return new_path;
}

bool isDirToCheck(dirent* dir_iter)
{
	return dir_iter->d_type == DT_DIR && strcmp(dir_iter->d_name, current_dir) && strcmp(dir_iter->d_name, parent_dir);
}

void dirAnalisys(const char* dir_path, file_list* array)
{
  DIR* cur_dir = opendir(dir_path);
  if (cur_dir)
  {
    dirent* dir_iter = readdir(cur_dir);
    while(dir_iter)
    {
      if (dir_iter->d_type==DT_REG && fileExtensionCheck(dir_iter->d_name))
      {
		char* temp_path=makeSubPath(dir_path, dir_iter->d_name);
        fileAnalisys(temp_path, array);
        free(temp_path);
      }
      if (isDirToCheck(dir_iter))
      {
        char* temp_path=makeSubPath(dir_path, dir_iter->d_name);
        dirAnalisys(temp_path, array);
        free(temp_path);
      }
      dir_iter = readdir(cur_dir);
    } 
  }
  else
    fprintf(stderr, "Error in opening %s\n", dir_path);
  closedir(cur_dir);
}

int main()
{
  file_list array = makeList();
  dirAnalisys(root_dir, &array);
  sortList(&array);
  printFileList(&array);
  cleanList(&array);
}