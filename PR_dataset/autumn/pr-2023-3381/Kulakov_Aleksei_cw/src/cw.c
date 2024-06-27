#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void clearFunc(char** arr, int len) {
    for (int i = 0; i < len; i++) {
        int pos = 0;
        while (pos < strlen(arr[i]) - 1 && (arr[i][pos] == ' ' || arr[i][pos] == '\t')) {
            pos++;
        }
        if (pos > 0) {
            memmove(arr[i], arr[i] + pos, strlen(arr[i]) - pos + 1);
        }
        if (strlen(arr[i]) == 1) {
            arr[i] = NULL;
            continue;
        }
    }
    for (int i = 0; i < len; i++) {
        if (arr[i] != NULL) {
            for (int j = i + 1; j < len; j++) {
                if (arr[j] != NULL) {
                    if (strlen(arr[i]) == strlen(arr[j])) {
                        int p = 1;
                        for (int j1 = 0; j1 < strlen(arr[i]); j1++) {
                            if (tolower(arr[i][j1]) != tolower(arr[j][j1])) {
                                p = 0;
                                break;
                            }
                        }
                        if (p) {
                            arr[j] = NULL;
                        }
                    }
                }
            }
        }
    }

}
void funcPrint(char** arr, int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] != NULL) {
            printf("%s\n", arr[i]);
        }
    }
}
int func1(char** arr, int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] != NULL) {
            char* c = strstr(arr[i], "Robin");
            while (c != NULL) {
                int pos = c - arr[i], k = strlen(arr[i]) - pos - 5;
                char* tmp = (char*)malloc((k + 1) * sizeof(char));
                if (tmp == NULL) {
                    printf("Error: memory limit");
                    return 0;
                }
                strcpy(tmp, arr[i] + pos + 5);
                arr[i] = realloc(arr[i], (strlen(arr[i]) + 7) * sizeof(char));
                c = strstr(arr[i], "Robin");
                strcpy(arr[i] + pos, "I am Batman");
                strcpy(arr[i] + pos + 11, tmp);
                c = strstr(arr[i], "Robin");
                free(tmp);
            }
            arr[i][strlen(arr[i])] = '\0';
        }
    }
    funcPrint(arr, len);
    return 1;
}
int comp(const void* sa, const void* sb) {
    int kA = 0, kB = 0;
    const char* a = *(const char**)sa;
    const char* b = *(const char**)sb;
    if (a == NULL || b == NULL) {
        return 0;
    }
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] == ',') {
            kA++;
        }
    }
    for (int i = 0; i < strlen(b); i++) {
        if (b[i] == ',') {
            kB++;
        }
    }
    return kA - kB;
}
void func2(char** arr, int len) {
    qsort(arr, len, sizeof(char*), comp);
    funcPrint(arr, len);
}
void func3(char** arr, int len) {
    for (int i = 0; i < len; i++) {
        int sum = 0;
        if (arr[i] == NULL) {
            continue;
        }
        for (int j = 0; j < strlen(arr[i]); j++) {
            if (isdigit(arr[i][j])) {
                sum += arr[i][j] - '0';
            }
        }
        if (sum == 13) {
            arr[i] = NULL;
        }
    }
    funcPrint(arr, len);
}
int isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}
void func4(char** arr, int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] != NULL && (isdigit(arr[i][0]) || isVowel(arr[i][0]))) {
            printf("%s\n", arr[i]);
        }
    }
}
void func9(char** arr, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < strlen(arr[i]) - 1; j++) {
            printf("%c", arr[i][j]);
        }
        printf(" ");
        for (int j = 0; j < strlen(arr[i]) - 1; j++) {
            printf("%c", arr[i][j]);
        }
        printf(".\n");
    }
}
int textInput(char*** arrReal) {
    char** arr = *arrReal;
    int k = 0, buflen = 16, len = 0, slen = 32, reallen = 0;
    char* s = malloc(slen * sizeof(char));
    while (1) {
        char c = getchar();
        if (c == '\n') {
            k++;
            if (k == 2) {
                break;
            }
        }
        else {
            k = 0;
            s[reallen] = c;
            reallen++;
            if (reallen == slen) {
                slen *= 2;
                s = realloc(s, slen * sizeof(char));
                if (s == NULL) {
                    printf("Error: memory limit");
                    return 0;
                }
            }
        }
        if (c == '.') {
            arr[len] = malloc((reallen + 1) * sizeof(char));
            s[reallen] = '\0';
            strcpy(arr[len], s);
            len++;
            if (len == buflen) {
                buflen *= 2;
                arr = realloc(arr, buflen * sizeof(char*));
                if (arr == NULL) {
                    printf("Error: memory limit");
                    return 0;
                }
            }
            if (s != NULL)
                free(s);
            slen = 32;
            reallen = 0;
            s = malloc(slen * sizeof(char));
        }

    }
    free(s);
    *arrReal = arr;
    return len;
}
int main() {
    printf("Course work for option 4.9, created by Aleksei Kulakov.\n");
    int n;
    scanf("%i", &n);
    if (n == 5) {
        printf("Программа может выполнить одно из введенных пользователем действий и завершить работу:\n");
        printf("1 - Заменить в тексте подстроки “Robin” (могут быть внутри слова) на подстроку “I am Batman”.\n");
        printf("2 - Отсортировать предложения по увеличению количества запятых в предложении.\n");
        printf("3 - Удалить все предложения в которых сумма цифр в предложении равняется 13.\n");
        printf("4 - Вывести все предложения в которых первое слово начинается с гласной буквы или цифры.\n");
        printf("5 - Вывод справки о функциях, которые реализует программа.\n");
    }
    else if ((n >= 0 && n <= 4) || n == 9) {
        int len = 0;
        char** arr = malloc(16 * sizeof(char*));
        len = textInput(&arr);
        clearFunc(arr, len);
        if (n == 0) {
            funcPrint(arr, len);
        }
        else if (n == 1) {
            func1(arr, len);
        }
        else if (n == 2) {
            func2(arr, len);
        }
        else if (n == 3) {
            func3(arr, len);
        }
        else if (n == 4) {
            func4(arr, len);
        }
        else {
            func9(arr, len);
        }
        for (int i = 0; i < len; i++) {
            if (arr[i] != NULL)
                free(arr[i]);
        }
        if (arr != NULL)
            free(arr);
    }
    else {
        printf("Error: there is no such command.\nEnter 5 to see the list of commands.");
    }
}
