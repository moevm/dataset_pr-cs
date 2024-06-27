#include <stdio.h>
#include <string.h>
#include <regex.h>

//метод печати соответствующего URL
void Print_Correct_URL(char* s, regmatch_t groupArray) {
    for(int i = groupArray.rm_so; i < groupArray.rm_eo; i++)
        printf("%c", s[i]);
}

int main() {
    //максимальное количество групп в регулярном выражении
    size_t maxGroups = 10;
    //регулярное выражение для проверки URL
    char* regexString = "([a-zA-Z0-9]+:\\/\\/)?(www\\.)?([a-zA-Z_0-9\\-]+(\\.[a-zA-Z0-9_\\-]+)+)((\\/[a-zA-Z0-9_\\-]+)+)?(\\/([a-zA-Z0-9_\\-]+\\.[a-zA-Z0-9_\\-]+\n))";
    //компилиция регулярного выражения
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    regcomp(&regexCompiled, regexString, REG_EXTENDED);
    
    char s[100];
    //чтение ввода с клавиатуры пока есть ввод
    while (fgets(s, 100, stdin)) {
        //проверка соответствие строки регулярному выражению
        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0) {
            //печать соответствующего URL
            Print_Correct_URL(s, groupArray[3]);
            printf(" - ");
            Print_Correct_URL(s, groupArray[8]);
        }
    }

    //освобождение памяти, выделенной под компилированное регулярное выражение
    regfree(&regexCompiled);
    return 0;
}
