#include <stdio.h>
#include <regex.h>
#include <string.h>

int main() {
    // Компиляция регулярного выражения
    regex_t regexCompiled;
    if (regcomp(&regexCompiled, "((\\w+\\.)+\\w+)(.*)\\/(\\w+\\.\\w+)", REG_EXTENDED)) {
        printf("Regular expression compilation error.\n");
        return 0;
    }

    // Инициализация переменных
    const size_t maxSize = 5;
    regmatch_t groupArr[maxSize];
    char str[1000];

    // Обработка ввода
    while (fgets(str, 1000, stdin)) {
        if (strstr(str, "Fin.") != NULL) {
            break;
        }
        if (regexec(&regexCompiled, str, maxSize, groupArr, 0) == 0) {
            // Извлечение данных из групп регулярного выражения
            char website[1000];
            char file[1000];
            strncpy(website, str + groupArr[1].rm_so, groupArr[1].rm_eo - groupArr[1].rm_so);
            strncpy(file, str + groupArr[4].rm_so, groupArr[4].rm_eo - groupArr[4].rm_so);
            website[groupArr[1].rm_eo - groupArr[1].rm_so] = '\0';
            file[groupArr[4].rm_eo - groupArr[4].rm_so] = '\0';

            // Вывод результатов
            printf("\n%s - %s", (strstr(website, "www.") != NULL) ? &website[4] : website, file);
        }
    }

    // Освобождение памяти
    regfree(&regexCompiled);
    return 0;
}
