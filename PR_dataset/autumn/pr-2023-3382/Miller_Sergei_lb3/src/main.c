#include <stdlib.h>
#include <stdio.h>

int main(){
    int tmp_size = 100;
    int size = tmp_size;
    
    char *t = malloc(size * sizeof(char));
    char a;

    int r = 0;
    int l = 0;

    int cnt_g_snt = 0;
    int cnt_snt = 0;

    int f = 0;

    do {
        a = getchar();
        if (f == 1){
            if (!(a == ' ' || a == ';' || a == '?' || a == '.' || a == '\n')){
                t[l] = '@';
            }
            f = 0;
        }
        if (r > size){
            size += 10;
            char *t1 = realloc(t, size*sizeof(char));
            if (t1 != NULL)
                t = t1;
        }

        if (a == '.' || a == ';' || a == '?'){
            cnt_snt++;
        }


        if ((a == ' ' || a == '\n') && (t[r - 1] == '.' || t[r - 1]  == ';' || t[r - 1]  == '?')){
            if (a != '\n')
                a = '\n';
            l = r + 1;
        }

        if (r > 0){ 
            if ((a >= '0' && a <= '9') && ((t[r - 1] != ' ' || t[r-1] != '\n')) ){
                if (t[r-1] > '9')
                    f = 1;
            }
        }

        t[r] = a;
        ++r;

    } while (a != '!');

    t[r] = '\0';
    r = 0;
    l = 0;
    while (t[r]){
        if (t[r] == '\n'){
            if (t[l] != '@'){
                printf("%c", t[r]);
                cnt_g_snt++;
            }
            
                
            r++;
            l = r;
        }
        if (t[l] == '@'){
            r++;
            
        }
        else {
            printf("%c", t[r]);
            r++;
        }
    }
    printf("\nКоличество предложений до %d и количество предложений после %d\n", cnt_snt,cnt_g_snt);
    free(t);
    return 0;
}
