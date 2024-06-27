#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


/* ДИНАМИЧЕСКИЙ МАССИВ */ // Наследовано и переработано из курсовой работы за первый семестр

#define VLA_EXPAND_BLOCK_SIZE 8

/* Для строк - динамический массив строк  */
typedef struct vlas_t {
	size_t cap;
	size_t len;
	char** data;
} vlas_t;


vlas_t vlas_init(void){
	vlas_t vla = {
		VLA_EXPAND_BLOCK_SIZE,
		0,
		(char**) malloc(VLA_EXPAND_BLOCK_SIZE * sizeof(char*))
	};

	if(vla.data == NULL){
        puts("Error: Memory allocation failed");
        exit(EXIT_FAILURE);
	}

	return vla;
}


void vlas_append(vlas_t* vlap, char* item){

	if(vlap->len == vlap->cap){ 
		vlap->cap += VLA_EXPAND_BLOCK_SIZE;
		vlap->data = (char**) realloc(vlap->data, vlap->cap * sizeof(char*));

		if(vlap->data == NULL){
            puts("Error: Memory allocation failed");
			exit(EXIT_FAILURE);	
		}
	}

	vlap->len++; 
	vlap->data[vlap->len - 1] = item; 
}


void vlas_free(vlas_t* vlap){
    for(size_t i = 0; i < vlap->len; i++)
        free(vlap->data[i]);

    free(vlap->data);
}


#define BUFFER_SIZE 128 // Было желание сделать и динамические строки, объеденить их c vlas_t через _Generic, но это опять много кода не по теме

vlas_t read_text(void){
    vlas_t txt = vlas_init();

    char* str;
    do {

        str = (char*) malloc(BUFFER_SIZE * sizeof(char));
        char* status = fgets(str, BUFFER_SIZE, stdin);

        if(status == NULL){
            free(str);

            #ifdef DEBUG
            if(feof(stdin))
                puts("EOF reached");
            else if (ferror(stdin))
                puts("Error: Some error occurred, please call perror(...)");
            #endif

            break;
        }

        vlas_append(&txt, str);

    } while (strcmp(str, "Fin.")); // В массив попадает "Fin."

    return txt;
}


/* ДОБАВЛЕНИЯ К regex.h */

#define REG_NOFLAGS 0
#define REG_COMP_OK 0
#define REG_MATCH 0
#define REGERROR_HAS_IMPL // TODO: определять до компиляции

void print_err(regex_t* preg, int code){

        #ifdef REGERROR_HAS_IMPL
        size_t size = regerror(code, preg, 0, 0);
        char msg[size];
        regerror(code, preg, msg, size);

        puts(msg);
        #else
        puts("Error: Function regerror do not have implementation for details");
        #endif
}


/* Вырезает из строки src подстроку res, начиная с so, заканчивая eo - 1. 
 * Возвращает NULL, если:
 * 1) индекс конца меньше индекса начала,
 * 2) хотя бы один из индексов отрицателный
 * 3) индексы равны */
char* str_slice(const char* src, int so, int eo){ // regoff_t > int !!!
    
    /* Проверка индексов */
    if(eo < so || so < 0 || eo < 0 || so == eo)
        return NULL;


    size_t size = eo - so + 1;
    char* res = (char*) malloc(size * sizeof(char));

    /* Вырезание подстроки */ // можно strncpy
    size_t j = 0;
    for(size_t i = so; i < eo; i++)
        res[j++] = src[i];
    
    res[j] = '\0';

    return res;

}


/* Достает из соответствующей шаблону строки match_str группы по group_array.
 * Записывает их в пользовательский массив str_array. */
void extract_groups(char** str_array, const char* match_str, regmatch_t* group_array, size_t size){
    

    for(size_t i = 0; i < size; i++){
        regoff_t so = group_array[i].rm_so;
        regoff_t eo = group_array[i].rm_eo;

        char* tmp = str_slice(match_str, so, eo);
        
        // TODO: обработка ошибки str_slice
        // Быть может лучше оставить NULL в str_array, и работать с ним в main

        str_array[i] = tmp;
    }
}


int main(void){
   
    /* СЧИТЫВАНИЕ ТЕКСТА */
    vlas_t txt = read_text();


    /* ПОИСК И ВЫВОД КОМАНД СУПЕРПОЛЬЗОВАТЕЛЯ */

    /* Подготовка регулярного выражения */
    const char* pattern = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+ ?: ?~ ?# ([ -~]+)?"; // TODO: именованные группы, GNU не принимает (?:)
    
    enum {MATCHED_STRING, USERNAME, CMD}; // 0 - строка 1 - имя пользователя 2 - команда
    size_t MAX_GROUPS = 3; 
    regmatch_t group_array[MAX_GROUPS];

    /* Компиляция регулярного выражения */
    int status;
    regex_t preg;
    if((status = regcomp(&preg, pattern, REG_EXTENDED)) != REG_COMP_OK){ // REG_EXTENDED = стандарт ERE вместо BRE
        puts("Error: Failed to compile regexp");
        print_err(&preg, status);
        exit(EXIT_FAILURE);
    }
 
    #ifdef DEBUG
    puts("--------------------");
    #endif
   
    /* Применение регулярного выражения к строке и вывод */
    char* str_array[MAX_GROUPS];

    for(size_t i = 0; i < txt.len; i++){

        char* str = txt.data[i];

        if((status = regexec(&preg, str, MAX_GROUPS, group_array, REG_NOFLAGS)) == REG_MATCH){
       
            extract_groups(str_array, str, group_array, MAX_GROUPS);
            
            #ifdef DEBUG
            printf("[%s] - [%s]\n", str_array[USERNAME], str_array[CMD] == NULL ? "" : str_array[CMD]);
            #else
            printf("%s - %s\n", str_array[USERNAME], str_array[CMD] == NULL ? "" : str_array[CMD]);
            #endif
    
            for(size_t i = 0; i < MAX_GROUPS; i++)
                free(str_array[i]);

        } else {
            #ifdef DEBUG
            printf("%s -> ", str);
            print_err(&preg, status); // REG_NOMATCH и REG_ENOSYS
            #endif
        }
    }


    /* ЗАВЕРШЕНИЕ РАБОТЫ ПРОГРАММЫ */

    vlas_free(&txt);
    regfree(&preg);

    return 0;
}
