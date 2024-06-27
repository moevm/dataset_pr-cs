#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <strings.h>
#include <ctype.h>
char* readtxt(){ 
    char* array_txt = (char *)malloc(200 * sizeof(char));
    if (array_txt == NULL){
        printf("Error: the required memory for the array_txt variable has not been allocated"); 
        exit(1);
    }
    int pamat=200;
    char current_char; 
    char last_char=' ';
    int kolvo_char=0;
    int flag=1;
    while(1){ 
        current_char=getchar();
        if (current_char =='\n' && last_char == '\n'){ 
            array_txt[kolvo_char-1]='\0';
            break;
        }
        else{
            if (last_char == '.'){
                flag=1;
            }
            if( ( (last_char == '.' || last_char == ' ' || last_char == '\n' || last_char == '\t') && (current_char == ' ' || current_char == '\n' || current_char == '\t') && flag == 1) || ((last_char == '.' || last_char == '\n') && (current_char == ' ' || current_char == '\n' || current_char == '\t'))){
                last_char=current_char;
                continue;
            }
            flag=0;
            kolvo_char+=1;
            if (kolvo_char == pamat){ 
                pamat += 20; 
                array_txt=(char *)realloc(array_txt, pamat * sizeof(char));
            }
            array_txt[kolvo_char-1]=current_char;
            last_char=current_char;
        }
    }
    return array_txt;
}
char** obrabotka_txt(char* array_txt, int *kolvo_predl){ 
    char* istr = strtok(array_txt,"."); 
    int i = 0;
    char** array = (char**)malloc(sizeof(char*));
    if (array == NULL){
        printf("Error: the required memory for the array variable has not been allocated");
        exit(1);
    }
    while (istr != NULL){ 
        int flag=0; 
        for (int j=0; j<i; ++j){ 
            if (strcasecmp(istr, array[j])==0){
                flag=1;
                break;
            } 
        }
        if (flag == 0){ 
            array=(char**)realloc(array, (i+1)*sizeof(char*)); 
            array[i]=(char*)malloc((strlen(istr)+1)*sizeof(char));
            strcpy(array[i], istr);
            i += 1;
        }
        istr = strtok(NULL,".");
    }
    *kolvo_predl = i;
    return array;
}
void right_data(char** array_txt, int *kolvo_predl){
    char months[12][4] = {"Jun", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int nevis[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int vis[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int j=0; j<*kolvo_predl; ++j){
        char* month = malloc(sizeof(char)*4);
        if (month == NULL){
        printf("Error: the required memory for the month variable has not been allocated");
        }
        char* chislo = malloc(sizeof(char)*3);
        if (chislo == NULL){
            printf("Error: the required memory for the chislo variable has not been allocated"); 
            exit(1);
        }
        char* poteryann = malloc(sizeof(char)*5);
        if (poteryann == NULL){
            printf("Error: the required memory for the poteryann variable has not been allocated"); 
            exit(1);
        }
        char *god = strtok(array_txt[j]," ");
        char *istr = strtok(NULL, " ");
        int kolvo_slov = 0;
            if(istr == NULL){
                printf("%s.\n", god);
                kolvo_slov = 1;
                god=NULL;
            }
        int error = 0;
        int flag1=0;
        int pr=0;
        int flag_obman = 0;
        while (istr != NULL){
                int count=0;
                int i=0;
                int flag = 0;
                flag1=0;
                for (; i<12; ++i){
                    if (strcmp (istr, months[i]) == 0){
                        strcpy(month, istr);
                        flag = 1;
                        break;
                    }
                }
                if(flag){
                    if (strtol(god, NULL, 10)>0 || strcmp(god, "0") == 0){
                            strcpy(poteryann, istr);
                            istr = strtok (NULL," ");
                            if(istr == NULL){
                                strcpy(chislo, "er");
                                error = 1;
                            }
                            else{
                                strcpy(chislo, istr);
                            }
                            //printf("%s\n", chislo);
                            if ((strtol(chislo, NULL, 10)>0 && (strtol(chislo, NULL, 10)<=31))){
                                flag1=1;
                                if ((strtol(god, NULL, 10)%4 == 0 && strtol(god, NULL, 10)%100 != 0) || (strtol(god, NULL, 10)%400 == 0)){
                                    for(int a=i; a<12; ++a){
                                            count+=vis[a];
                                    }
                                    count = count - strtol(chislo, NULL, 10) + 1;
                                }
                                else{
                                    for(int a=i; a<12; ++a){
                                        count+=nevis[a];
                                    }
                                    count = count - strtol(chislo, NULL, 10) + 1;
                                }
                                    printf("%d hours to the end of the year", count*24);
                                    if(chislo[strlen(chislo) - 1] == ','){
                                        printf("%c", ',');
                                    }
                                    pr = 1;
                                flag = 0;
                            }
                            else{
                                flag_obman = 1;
                            }
                        }
                }
                if(flag1 == 0){
                    if(pr == 0){
                        printf("%s ", god);
                        if(flag_obman == 1){
                            if(error == 0){
                                printf("%s ", poteryann);
                            }
                            else{
                                printf("%s", poteryann);
                            }
                            flag_obman = 0;
                        }
                    }
                    if (pr==1){
                        strcpy(god, istr);
                        printf(" ");
                        pr = 0;
                    }
                    if(error==0 && istr != NULL){
                        strcpy(god, istr);
                    }
                }
                else{    
                    strcpy(god, istr);
                    flag1 = 0;
                }
                istr = strtok (NULL," ");
                if(istr == NULL){
                    if(pr == 0 && error == 0){
                        printf("%s", god);
                    }
                }
        }
        if(kolvo_slov == 0){
            printf(".\n");
        }
        free(month);
        free(chislo);
        free(poteryann);
    }
}
void color_words(char** array_txt, int *kolvo_predl){
    for (int i=0; i<*kolvo_predl; ++i){
        char* istr = strtok(array_txt[i]," ");
        int i=0;
        while (istr != NULL){
            if (i%2 == 0){
                printf("\x1b[31m%s\x1b[0m", istr);
            }
            else{
                printf("\x1b[32m%s\x1b[0m", istr);
            }
            i += 1;
            istr = strtok(NULL," ");
            if (istr == NULL){
                printf(".\n");
            }
            else{
                printf(" ");
            }
        }
    }
}
void delete_predl(char** array_txt, int *kolvo_predl){
    for (int j=0; j<*kolvo_predl; ++j){
        int n = strlen(array_txt[j]);
        char* sent = malloc(sizeof(char)*(n+1));
        if (sent == NULL){
            printf("Error: the required memory for the sent variable has not been allocated"); 
            exit(1);
        }
        sent[0] = '\0';
        char* istr = strtok(array_txt[j], " \t");
        char* pervoe = malloc(sizeof(char)*100+1);
        if (pervoe == NULL){
            printf("Error: the required memory for the pervoe variable has not been allocated"); 
            exit(1);
        }
        char* pred = malloc(sizeof(char)*100+1);
        if (pred == NULL){
            printf("Error: the required memory for the pred variable has not been allocated"); 
            exit(1);
        }
        strcpy(pervoe, istr);
        while(istr != NULL){
            strcpy(pred, istr);
            strcat(sent, pred);
            istr = strtok(NULL, " \t");
            if(istr==NULL){
                if ( pervoe[strlen(pervoe)-1] == ',' ){
                        pervoe[strlen(pervoe)-1] = '\0';
                }
                if(strcmp(pervoe, pred) != 0){
                    sent[strlen(sent)] = '\0';
                    printf("%s.\n", sent);
                }
            }
            else{
                strcat(sent, " ");
            }
        }
        free(sent);
        free(pred);
        free(pervoe);
    }
}
int count_simv(char *s1_1){
    int c1=0;
    char *istr = strtok(s1_1, " ");
    int n = strlen(istr);
    for (int i=0; i<n; ++i){
        c1 += istr[i];
    }
    return c1;
}
int compr(const void * p1, const void * p2){
    char * s1 = *(char**)p1; 
    char * s2 = *(char**)p2;
    char *s1_1=malloc((strlen(s1)+1)*sizeof(char));
    if (s1_1 == NULL){
        printf("Error: the required memory for the s1_1 variable has not been allocated"); 
        exit(1);
    }
    char *s2_2=malloc((strlen(s2)+1)*sizeof(char));
     if (s2_2 == NULL){
        printf("Error: the required memory for the s2_2 variable has not been allocated"); 
        exit(1);
    }
    strcpy(s1_1, s1);
    strcpy(s2_2, s2);
    int c1 = count_simv(s1_1);
    int c2 = count_simv(s2_2);
    free(s1_1);
    free(s2_2);
    if (c1>c2){
        return 1;
        }
    if (c2>c1){
        return -1;
        }
    return 0;
}
void sort(char** array_txt, int *kolvo_predl){
    qsort(array_txt, *kolvo_predl, sizeof(char*), compr);
    for (int i = 0; i<*kolvo_predl; ++i){
        printf("%s.\n", array_txt[i]);
    }
}


int pupu(char** array_txt, int *kolvo_predl){
    char *istr = strtok(array_txt[0], "\n");
    char *istr1 = strtok(NULL, ".");
    int n= strlen(istr);
    int n1 = strlen(istr1);
    int count = 0;
    int count1 = 0;
    for (int i= 0; i<n; ++i){
        if (istr[i]>=65 && istr[i]<=90){
            count+=1;
        }
    }
    for (int j = 0; j<n1; ++j){
        if(istr1[j]>=65 && istr1[j]<=90){
            count1+=1;
        }
    }
    if (count1<=count){
        printf("%s.\n", istr1);
    }
    for (int k =1; k<*kolvo_predl; ++k){
        int n2=strlen(array_txt[k]);
        int count2=0;
        for (int l=0; l<n2; ++l){
            if (array_txt[k][l]>=65 && array_txt[k][l]<=90){
                count2+=1;
            }
        }
        if (count2<=count){
            printf("%s.\n", array_txt[k]);
        }
    }
    return 0;
}


int main(){
    printf("Course work for option 4.17, created by Elizaveta Kotelnikova.\n");
    int n;
    scanf("%d", &n);
    if (n==5){ 
        printf("0 - Text output after initial processing.\n");
        printf("1 - Find all dates in the text in the form <year> <month> <day> and replace them with a line showing how many hours are left until the end of the year.\n");
        printf("2 - Print all lines of text by highlighting the words in even positions in red, and in odd positions in green.\n");
        printf("3 - Delete all sentences that begin and end with the same word.\n");
        printf("4 - Sort the sentences by increasing the sum of the character codes of the first word in the sentence.\n");
        return 0;
    }
    getchar();
    int kolvo_predl = 0;
    char* text = readtxt();
    char** array_text = obrabotka_txt(text, &kolvo_predl);
    if (n==0){ 
        for (int k=0; k<kolvo_predl; k++){ 
            printf("%s.\n", array_text[k]); 
        }
    }
    else if (n==1){
        right_data(array_text, &kolvo_predl);
    }
    else if (n==2){
        color_words(array_text, &kolvo_predl);
    }
    else if (n==3){
        delete_predl(array_text, &kolvo_predl);
    }
    else if (n==4){
        sort(array_text, &kolvo_predl);
    }
    else if (n==8){
        pupu(array_text, &kolvo_predl);
    }
    else if (n==9){
        exit(0);
    }
    else{
        printf("the number entered is not 0-5.\n");
        exit(1);
    }
    free(text);
    for (int k=0; k<kolvo_predl; k++){ 
       free(array_text[k]);
    } 
    free(array_text);
    return 0;
}