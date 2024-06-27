#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 1000
int read_str(char* text, char* end_str){
    char c;
    int j =0;
    int check = 0;
    int flag = 1;
    c=getchar();
    while((c ==' ')||(c == '\n')||(c=='\t')){
        c = getchar();
    }
     // пробел или энтер между строками не их часть
    while((c!='.')&&(c!=';')&&(c!='?')){
        text[j] = c;
        if(c == end_str[j++]){
            check+=1;
        }
        if(check == strlen(end_str)){
            flag = 0;
            break;
        }
        if(j-2 == Max){
            char* newArray = realloc(text, sizeof(char)*j*100);
            if (newArray != NULL) {
                text = newArray;
                // массив успешно расширен до j*100 элементов
            }
        }
        c = getchar();
    }
    if(flag){
        text[j++] = c; //разделитель тоже часть строки

    }
    text[j] = '\0';
    return flag;
}
// считываем строку посимвольно и проверяем равен ли он символу из end_str такого же индекса
// если кол-во одинаковых символов равны, то это end_str и мы должны завершить считывание текста
// все \n внутри строки я оставляю, тк в задании не указано их удалять. удаляю только символ после одного из разделителей  ',' '.' '?'
int read_text(char** text, char* end_str){
    int i =0, n = 0; // i индекс строк, n - кл-во строк
    char c;
    int flag = 1;
    while(flag){
        text[i]=(char*)malloc(Max*sizeof(char));
        if (text[i] == NULL){
            printf("error i %d", i);
            break;
        }
        flag = read_str(text[i++], end_str);
        n+=1;
        if(n-2 == Max){
            char** newArray = realloc(text, sizeof(char*)*n*100);
            if (newArray != NULL) {
                text = newArray;
                // массив успешно расширен до n*n элементов
            }
        }
    }
    return n;
}
// построчно выделяю память под строку и считываю ее функцией read_str, фиксируя флаг
// возвращаю n - кол-во строк в тексте
int formating(char** text, char** form_text, int n){
    int m = 0;
    for(int i =0; i<n; i++){
        int len = strlen(text[i]);
        
        // если последний символ не ? то копирую его в form_text который явл ответом к заданию
        if(text[i][len-1] != '?'){
            form_text[m] = (char*)malloc(len*sizeof(char));
            form_text[m++] = text[i];
            
        }
    }
    return m;
}
// форматирование теста согласно условию

int main()
{
    char** text = (char**)malloc(Max*sizeof(char*));
    if (text == NULL){
        printf("error 2");
        exit(1);
    }
    char end[18] = "Dragon flew away!";
    char* end_str = (char*)malloc(Max*sizeof(char));
    if (end_str == NULL){
        printf("error 2");
        exit(1);
    }
    strcpy(end_str, end);
    int n = read_text(text, end_str);
    char** form_text = (char**)malloc(n*sizeof(char*));
    if (form_text == NULL){
        printf("error 2");
        exit(1);
    }
    int m = formating(text, form_text, n);
    
    for(int j =0; j<m;j++){
        printf("%s\n", form_text[j]);
    }
    printf("Количество предложений до %d и количество предложений после %d", n-1, m-1);
    
    for (int i = 0; i<n; i++){
        free(text[i]);
    }
    free(text);
    free(end_str);
    return 0;
}
