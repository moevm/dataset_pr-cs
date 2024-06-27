#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define check_mem_alloc(x) ({ if(x == NULL) { puts("Unable to allocate memory!"); exit(1); } })

typedef struct Textfile_struct {
        long id;
        int string_len;
        char* string;
} Textfile;

int textfile_comp(const void* a_ptr, const void* b_ptr)
{
        const Textfile* a = *((const Textfile**)a_ptr);
        const Textfile* b = *((const Textfile**)b_ptr);
        if(a->id < b->id) return -1;
        if(a->id > b->id) return 1;
        return 0;
}

// accepts path string, pointers to two empty string arrays and pointers to two int variable
// after execution there are filesnames in files array (files_len is length of this array)
// same for dirnames in dirs array
void listdir(const char* path, char*** files, char*** dirs, int* files_len, int* dirs_len)
{
        //variable initialization
        *files = (char**)malloc(sizeof(char*));
        *dirs = (char**)malloc(sizeof(char*));
        *files_len = 0;
        *dirs_len = 0;
        
        DIR* directory = opendir(path);
        if(directory) {
                struct dirent* element = readdir(directory);
                while(element) {
                        if(element->d_type == DT_REG) { // if element is a file
                                (*files_len)++;
                                char** new_files = (char**)realloc(*files, sizeof(char*) * (*files_len));
                                check_mem_alloc(new_files);
                                *files = new_files;
                                (*files)[(*files_len)-1] = (char*)malloc(sizeof(char) * (strlen(element->d_name)+1));
                                strcpy((*files)[(*files_len)-1], element->d_name);
                        }
                        else if(element->d_type == DT_DIR && element->d_name[0] != '.') { // if element is a dir (exclude hidden dirs)
                                (*dirs_len)++;
                                char** new_dirs = (char**)realloc(*dirs, sizeof(char*) * (*dirs_len));
                                check_mem_alloc(new_dirs);
                                *dirs = new_dirs;
                                (*dirs)[(*dirs_len)-1] = (char*)malloc(sizeof(char) * (strlen(element->d_name)+1));
                                strcpy((*dirs)[(*dirs_len)-1], element->d_name);
                        }
                        element = readdir(directory);
                }
        }
        else {
                free(files);
                free(dirs);
        }
        closedir(directory);
}

void parse_textfile(const char* path, long* text_id, char** text, int* len)
{
        // Open file & read integer and space from beginning
        FILE* file = fopen(path, "r");
        fscanf(file, "%ld ", text_id);

        // Get file size
        struct stat filestat;
        stat(path, &filestat);
        off_t filesize = filestat.st_size;

        // Get read offset in bytes
        long read_offset = ftell(file);

        // Now, string size in bytes is filesize-read_offset; since char size is 1 byte -> string size in bytes = string len
        *len = filesize - read_offset;
        
        *text = (char*)malloc(sizeof(char) * ((*len)+1));
        fgets(*text, (*len)+1, file);

        // Remove unwanted \n from string if it exists
        if((*text)[(*len)-1] == '\n') {
                (*text)[(*len)-1] = '\0';
                (*len)--;
        }

        fclose(file);
}

void walk(const char* path, Textfile*** texts_array, int* texts_array_len)
{
        // Initialize variables and scan given directory
        char** files;
        char** dirs;
        int files_len, dirs_len;
        listdir(path, &files, &dirs, &files_len, &dirs_len);

        // Get text from every presented text file and append texts
        for(int i = 0; i < files_len; i++) {
                // Get file extension and check it's .txt
                // Also check it's not the output file of the program
                char* ext = strrchr(files[i], '.');
                if(ext != NULL && !strcmp(ext, ".txt") && (strcmp(path, ".") || strcmp(files[i], "result.txt"))) {
                        // Generate path
                        char* filepath = (char*)malloc(strlen(path)+strlen(files[i])+2);
                        strcpy(filepath, path);
                        strcat(filepath, "/");
                        strcat(filepath, files[i]);

                        // Parse file
                        char* string;
                        int string_len;
                        long text_id;
                        parse_textfile(filepath, &text_id, &string, &string_len);

                        // Create element
                        Textfile* new_text = (Textfile*)malloc(sizeof(Textfile));
                        new_text->id = text_id;
                        new_text->string_len = string_len;
                        new_text->string = (char*)malloc(string_len+1);
                        strcpy(new_text->string, string);

                        // Add element to texts_array
                        (*texts_array_len)++;
                        Textfile** new_texts_array = (Textfile**)realloc(*texts_array, sizeof(Textfile*) * (*texts_array_len));
                        check_mem_alloc(new_texts_array);
                        *texts_array = new_texts_array;
                        (*texts_array)[(*texts_array_len)-1] = new_text;

                        // Free memory
                        free(filepath);
                        free(string);
                }
                free(files[i]);
        }

        // Recusively scan all subdirs
        for(int i = 0; i < dirs_len; i++) {
                // Generate path
                char* dirpath = (char*)malloc(strlen(path)+strlen(dirs[i])+2);
                strcpy(dirpath, path);
                strcat(dirpath, "/");
                strcat(dirpath, dirs[i]);
                
                walk(dirpath, texts_array, texts_array_len);
                
                free(dirpath);
                free(dirs[i]);
        }

        free(files);
        free(dirs);
}

int main()
{
        FILE* output_file = fopen("result.txt", "w");
        Textfile** texts = (Textfile**)malloc(sizeof(Textfile*));
        int texts_count = 0;
        walk(".", &texts, &texts_count);

        qsort(texts, texts_count, sizeof(Textfile*), textfile_comp);

        for(int i = 0; i < texts_count; i++) {
                fprintf(output_file, "%ld %s\n", texts[i]->id, texts[i]->string);
                free(texts[i]->string);
                free(texts[i]);
        }
        
        free(texts);
        fclose(output_file);
        return 0;
}
