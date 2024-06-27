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
int replacingString(char** arr, int len) {
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
void sorting(char** arr, int len) {
    qsort(arr, len, sizeof(char*), comp);
    funcPrint(arr, len);
}
void deletingOffers(char** arr, int len) {
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
int isVowel(char character) {
    character = tolower(character);
    return (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u' || character == 'y');
}
void vowelLetter(char** arr, int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] != NULL && (isdigit(arr[i][0]) || isVowel(arr[i][0]))) {
            printf("%s\n", arr[i]);
        }
    }
}
int func_sum(char* str){
    int sum = 0;
    for (int i=0; str[i]; i++){
        if (isdigit(str[i])){
            sum += (str[i] - '0');
        }
    }
    return sum;
}

void printStringsAboveSum(char** arr, int len, int sum){
    for (int i = 0; i < len; i++){
        if (func_sum(arr[i]) > sum){
            printf("(%d) %s\n", func_sum(arr[i]) - sum, arr[i]);
        }
    }
}
int textInput(char*** arrReal) {
    char** arr = *arrReal;
    int newlineCount = 0, buflen = 16, len = 0, slen = 32, reallen = 0;
    char* inputBuffer = malloc(slen * sizeof(char));
    while (1) {
        char c = getchar();
        if (c == '\n') {
            newlineCount++;
            if (newlineCount == 2) {
                break;
            }
        }
        else {
            newlineCount = 0;
            inputBuffer[reallen] = c;
            reallen++;
            if (reallen == slen) {
                slen *= 2;
                inputBuffer = realloc(inputBuffer, slen * sizeof(char));
                if (inputBuffer == NULL) {
                    printf("Error: memory limit");
                    return 0;
                }
            }
        }
        if (c == '.') {
            arr[len] = malloc((reallen + 1) * sizeof(char));
            inputBuffer[reallen] = '\0';
            strcpy(arr[len], inputBuffer);
            len++;
            if (len == buflen) {
                buflen *= 2;
                arr = realloc(arr, buflen * sizeof(char*));
                if (arr == NULL) {
                    printf("Error: memory limit");
                    return 0;
                }
            }
            if (inputBuffer != NULL)
                free(inputBuffer);
            slen = 32;
            reallen = 0;
            inputBuffer = malloc(slen * sizeof(char));
        }

    }
    free(inputBuffer);
    *arrReal = arr;
    return len;
}

void printInfo() {
    printf("Course work for option 4.9, created by Glebova Viktoriya.\n");
}

int main() {
    printInfo();
    int n;
    scanf("%i", &n);
    getchar();
    if (n == 5) {
        printf("Программа может выполнить одно из введенных пользователем действий и завершить работу:\n");
        printf("1 - Заменить в тексте подстроки “Robin” (могут быть внутри слова) на подстроку “I am Batman”.\n");
        printf("2 - Отсортировать предложения по увеличению количества запятых в предложении.\n");
        printf("3 - Удалить все предложения в которых сумма цифр в предложении равняется 13.\n");
        printf("4 - Вывести все предложения в которых первое слово начинается с гласной буквы или цифры.\n");
        printf("5 - Вывод справки о функциях, которые реализует программа.\n");
    }
    else if ((n >= 0 && n <= 4) || n == 8) {
        char str[250];
        if (n == 8){
            fgets(str, 249, stdin);
        }
        int len = 0;
        char** arr = malloc(16 * sizeof(char*));
        len = textInput(&arr);
        clearFunc(arr, len);
        if (n == 0) {
            funcPrint(arr, len);
        }
        else if (n == 1) {
            replacingString(arr, len);
        }
        else if (n == 2) {
            sorting(arr, len);
        }
        else if (n == 3) {
            deletingOffers(arr, len);
        }
        else if (n == 4) {
            vowelLetter(arr, len);
        }
        else if (n == 8){
            printStringsAboveSum(arr, len, func_sum(str));
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
