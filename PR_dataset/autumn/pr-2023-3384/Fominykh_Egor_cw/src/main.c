#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void text(char txt[]){
    printf("%s",txt);
    }
    
void count_line(char s1[], char s2[]){

    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int count;

    for (int i = 0; i <= len1 - len2; i++) {
        int ok = 1;
        for (int j = 0; j < len2; j++) {
            if (s2[j] != s1[j + i]) {
                ok = 0;
                break;
            }
        }

        if (ok) count++;
    }

    printf("%d", count);
}
void count_days(char dan[]){
    int day;
    char month[20];
    int year;
    sscanf(dan,"%d %s %d",&day,month,&year);
    int a=0;
    int b=0;
    int c=0;
    int k =1;
    char *months[] = {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int month_index;
    for (int i = 0; i < 12; i++) {
        if (strcmp(month, months[i]) == 0) {
            month_index = i;
            k=0;
            break;
        }
    }
    if (k == 1 || day >31 || day < 1 || year <0) {
        printf("Error: <Invalid input. Out of range.>");
        return;
    }
    a = days_in_month[month_index]-day;
    for(int i = month_index+1; i<12; i++){
        b += days_in_month[i];
    }
    for(int i=year+1; i+5; i++){
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0)){
            break;
        } else{
            c+=365;
        }
    }
    printf("%d", a+b+c);
}

void remove_spaces(char str[]){

    char str2[100];
    int i;
    int len = strlen(str);
    int flag = 0;
    int k = 0;

    while (str[0] == ' ') {
        for (i = 0; i < len; i++) {
            str[i] = str[i+1];
        }
        len--;
    }

    while (str[len-1] == ' ') {
        str[len-1] = '\0';
        len--;
    }
    for(i=0;i<len;i++){
        if (str[i]!=' '){
            str2[i-k] = str[i];
            flag = 0;
        }
        else{
            if(flag == 0){
                str2[i-k] = str[i];
                flag = 1;
            }
            else{
                k++;
            }
        }
    }
    str2[strlen(str)-k] = '\0';
    printf("%s",str2);
}

void remuve_numbers(char s[]){
    int k = 0;
    int flag = 1;
    char s2[100];
    char ch[] = {'0','1','2','3','4','5','6','7','8','9'};
    for (int i=0; i<strlen(s); i++){
        for (int j = 0; j < 10; j++){
            if (s[i] == ch[j]){
                k++;
                flag = 0;
            }
        }
        if (flag) {
            s2[i-k] = s[i];
        }
        flag = 1;
    }
    s2[strlen(s)-k] = '\0';
    printf("%s", s2);
}
void command_print_help()
{
    puts(
        "List of commands:\n"
        "  1 - a function that takes two strings and returns the number of occurrences of the second string in the first.\n"
        "  2 - The function takes a string representing a date of the form '<day> <month> <year>' (in the format 'dd month yyyy', for example, '09 Jul 1999'). The function should print the number of days until the next leap year.\n"
        "  3 - Function for removing duplicate spaces in a string. Spaces at the beginning and end of the line must be completely removed.\n"
        "  4 - remove all sentences with more then average letter count.\n"
        "  5 - print help message.\n"
        "Functions must support protection against buffer overruns and have a mechanism for notifying about an incorrect situation.\n"
        "\n"
    );
}

int main(){
    printf("Course work for option 3.3, created by Egor Fominykh.\n");
    int i;
    scanf("%d",&i);
    getchar();
    char txt[100];
    char s1[100];
    char s2[100];
    char dan[100];
    char str[100];
    char s[100];

      switch (i) {
        case 0:
            fgets(txt,100,stdin);
            text(txt);
            break;
        case 1:
            fgets(s1, 100, stdin);
            scanf("%s",s2);
            count_line(s1,s2);
            break;
        case 2:
            fgets(dan, sizeof(dan), stdin);
            count_days(dan);
            break;
        case 3:
            fgets(str, 100, stdin);
            remove_spaces(str);
            break;
        case 4:
            fgets(s, 100, stdin);
            remuve_numbers(s);
            break;
        case 5:
            command_print_help();
            break;
        default:
            printf("Error: <Invalid input. Out of range, enter a number from 0 to 5.>");
            break;
}

    return 0;
}
