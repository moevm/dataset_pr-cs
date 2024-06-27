//Дана некоторая корневая директория, в которой может находиться некоторое количество папок, в том числе вложенных. В этих папках хранятся некоторые текстовые файлы, имеющие имя вида <filename>.txt. В качестве имени файла используется символ латинского алфавита.
// На вход программе подается строка. Требуется найти и вывести последовательность полных путей файлов, имена которых образуют эту строку.
//  Регистрозависимость
// ! Могут встречаться файлы, в имени которых есть несколько букв и эти файлы использовать нельзя.
// ! Одна буква может встречаться один раз

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#define MAXFILE_NAME_SZ  128

int
file_validator(char* file_name, char letter){ //проверка имени файла заданным критериям
    int res = 0;
    if((strlen(file_name)==5)&&(strstr(file_name, ".txt") - file_name == 1)&&(file_name[0] == letter)){
        res = 1;
    }
    return res;
    
}

char*
dir_lookup(char* root, char letter){
    DIR* root_dir = opendir(root);
//     readdir возвращает указатель на первый из файлов, которые он нашел в этой директории (примерно как strtok). работает до конца файла (в плане директория это же тоже файл и у него тоже есть конец).
// Имя директории или файла не должно превышать 256 байт.
// поэтому нам надо создать буфер, дальше которого точно ничего не уйдет, можно создать динамически, а можно и статически и просто коировать strncpy
// может вернуть тип файла

    if (root_dir){
       
    struct dirent* dir = readdir(root_dir);
    
    while(dir){
        //тут получаем путь к файлу
        char NewPath_to_file[strlen(root) + strlen(dir -> d_name + 1)];
        strcpy(NewPath_to_file, root);
        strcat(NewPath_to_file, "/");
        strcat(NewPath_to_file, dir -> d_name);
            
        if((dir ->d_type == DT_REG) && file_validator(dir ->d_name, letter)){
            char* result = (char*)malloc(strlen(NewPath_to_file)*sizeof(char));
            strncpy(result, NewPath_to_file, strlen(NewPath_to_file));
            return result;
            
            // тут надо стереть название файла из tmp_dir
           // NewPath_to_file[strlen(NewPath_to_file) - 1 - strlen(dir -> d_name)] = '\0';
            
        } else if((dir->d_type == DT_DIR)&&strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")){
            if(dir_lookup(NewPath_to_file, letter)!=NULL)
            {
                return dir_lookup(NewPath_to_file, letter); //это мы заходим во вложенную папку начало рекурсии
            }
            
            
        }    
        dir = readdir(root_dir); // тут зацикливание следующий файл в папке
    }
    closedir(root_dir);
    }
}

int
main(){
    char* key_word=malloc(sizeof(char)*MAXFILE_NAME_SZ);
    scanf("%s",key_word);
    int len =strlen(key_word);
    
    char* path_to_file = "./";
    FILE* result = fopen("result.txt", "w");
    for(int i=0;i<len;i++)
    {
        char* ans = dir_lookup(path_to_file, key_word[i]);
        fprintf(result,"\n%s", ans);
        free(ans);
        
    }
    
    fclose(result);
    
    free(key_word);
    
    
    return 0 ;
}













