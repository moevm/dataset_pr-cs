#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10000

void razd(char *s, char *st, int *n)
{
    int i = 0;
    while (i < strlen(s))
    {
        if ((s[i] != '.') && (s[i] != ';') && (s[i] != '?'))
        {
            st[i] = s[i];
            i++;
        }
        else
        {
            st[i] = s[i];
            i++;
            st[i] = '\n';
            i++;
            *n = *n + 1;
        }
    }
}

void del(char *st, char *str, int *m)
{
    char *istr;
    int fl = 0;
    int k = 0;
    istr = malloc(10000);
    istr = strtok(st, "\n");
    while (istr != NULL)
    {
        char c = ' ';
        c = istr[0];
        int i = 1;
        while (i < strlen(istr) - 1)
        {
            if ((istr[i] == '5') && (istr[i+1] == '5') &&(istr[i+2] == '5') && (istr[i-1] == ' ') && ((istr[i+3] == ' ') || (istr[i+3] == '.') || (istr[i+3] == ';') || (istr[i+3] == '?'))){
                i = i + 3;
            }
            else if (c == ' '){
                c = istr[i];
                i++;
            }
            else if (c == ',')
            {
                c = istr[i];
                i++;
            }
            else if (istr[i] == ' ')
            {
                c = ' ';
                i++;
            }
            else if (istr[i] == ',')
            {
                c = ',';
                i++;
            }
            else if (((istr[i] == '0') || (istr[i] == '1') || (istr[i] == '2') || (istr[i] == '3') || (istr[i] == '4') || (istr[i] == '5') || (istr[i] == '6') || (istr[i] == '7') || (istr[i] == '8') || (istr[i] == '9')) && (istr[i + 1] != ' ') && (istr[i + 1] != ',') && (istr[i + 1] != '.') && (istr[i + 1] != ';') && (istr[i + 1] != '?'))
            {
                fl = 1;
                break;
            }
            else
            {
                i++;
            }
        }
        if (fl == 0)
        {
            for (int j = 0; j < strlen(istr); j++)
            {
                str[k] = istr[j];
                k++;
            }
            str[k] = '\n';
            k++;
            *m = *m + 1;
        }
        fl = 0;
        istr = strtok(NULL, "\n");
    }
    free(istr);
}

int main()
{
    char *s;
    char *st;
    char *str;
    int n = 0;
    int m = 0;
    s = malloc(N + 1);
    st = malloc(N + 1);
    str = malloc(N + 1);
    fgets(s, N, stdin);
    razd(s, st, &n);
    del(st, str, &m);
    printf("%sКоличество предложений до %i и количество предложений после %i\n", str, n, m-1);
    free(s);
    free(st);
    free(str);
    return 0;
}
