#include <regex.h>
#include <stdio.h>

#define REGERROR_HAS_IMPL // TODO: определять до компиляции

void print_err(regex_t* preg, int code){

        #ifdef REGERROR_HAS_IMPL
        size_t size = regerror(code, preg, 0, 0);
        char msg[size];
        regerror(code, preg, msg, size);

        puts(msg);
        #else
        puts("Error");
        #endif
}


int main(void){

    /* Подготовка регулярного выражения */
    const char* pattern = "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+) ?: ?~ ?# ([ -~]+)?"; // TODO: именованные группы, GNU не принимает (?:)

    size_t max_groups = 4; // 0 - string!
    regmatch_t group_array[max_groups];


    /* Компиляция регулярного выражения */
    int err;
    regex_t preg;
    if((err = regcomp(&preg, pattern, REG_EXTENDED)) != 0){ // REG_EXTENDED = стандарт ERE вместо BRE
        puts("Failed to compile regexp!");
        print_err(&preg, err);

        return 0;
    }

    /*
    if(preg.re_nsub != max_groups - 1){
        // TODO: Возможно это работает так (Если не стоит флаг REG_NOSUB)
        puts("Warning: nsub != max_groups - 1"); // Индикатор того, что не все группы были интерпретированы, хотя есть, например, REG_EBRACK
    }
    */

    // regcomp инициализирует программу для исполнения в regexec
    
    
    /* Применение регулярного выражения к строке и вывод */ // TODO: считывание с файла
    char str[BUFSIZ];
    fgets(str, BUFSIZ, stdin);
    
    if((err = regexec(&preg, str, max_groups, group_array, 0)) == 0){
        puts("Match!");

        for(size_t i = 0; i < max_groups; i++){
            
            regoff_t so = group_array[i].rm_so;
            regoff_t eo = group_array[i].rm_eo;

            if(so == -1){
                printf("Group %ld: none\n", i);
                continue;
            }

            printf("Group %ld: [%d;%d] [", i, so, eo);
            for(size_t j = so; j < eo; j++) // eo = real offset + 1
                putchar(str[j]);

            puts("]");
        }

    } else {
        print_err(&preg, err); // REG_NOMATCH и REG_ENOSYS
    }
    

    regfree(&preg);
    return 0;
}
