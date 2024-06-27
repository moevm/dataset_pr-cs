#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct maspar{
    int kolvosimvolov;
    char *naborpredlojeniy;
} maspar;

typedef struct razbit{
    int kolvopred;
    char** naborstrok;
} razbit;

razbit povtor(struct maspar *k){
    int numSentences = 0;
    int len = k->kolvosimvolov;
    char** stroki = malloc(len * sizeof(char*));
    char** stroki_bez_povtorov = malloc(len * sizeof(char*));
    char* token;
    char* sentences = k->naborpredlojeniy;
    token = strtok(sentences, ".");
    while (token != NULL) {
        stroki[numSentences] = malloc(strlen(token));
        stroki[numSentences] = token;
        numSentences++;
        token = strtok(NULL, ".");
    }
    int z = 0;
    for (int i = 0; i < numSentences; i++) {
        int prov = 0;
        for (int j = 0; j < z; j++) {
            if (strcmp(stroki[i], stroki_bez_povtorov[j]) == 0) {
                prov = 1;
                break;
            }
        }
        if (prov == 0){
            stroki_bez_povtorov[z] = malloc(strlen(stroki[i]));
            stroki_bez_povtorov[z] = stroki[i];
            z++;
        }
    }
    razbit kortej;
    kortej.kolvopred = z;
    kortej.naborstrok = stroki_bez_povtorov;
    return kortej;
}

maspar readSentences() {
    char* sentences = calloc(1, sizeof(char));
    int len = 0;
    int sizemas = 1;
    char symbol;
    int prov = 0;
    int chprov=0;
    while (1){
        symbol = getchar();
        if (symbol=='\n'&&sizemas==1){
            if (chprov==1){
                prov=1;
                sentences[len]=symbol;
                len++;
                sizemas=1000;
                sentences=realloc(sentences, sizemas *sizeof(char));
                continue;
            }
            chprov++;
            continue;
        }
        if (symbol == '.'){
            sentences[len]=symbol;
            len++;
            if (len == sizemas) {
            	sizemas= sizemas+1000;
            	sentences = realloc(sentences, sizemas * sizeof(char));
            }
        }
        else{
            if (symbol =='\n'&& prov==1){
                break;
            }
            if (symbol!='\n' || (symbol=='\n' && sentences[len-1]!='.')){
                if ((symbol==' ' && len==0)||(symbol==' ' && sentences[len-1]=='.')){
                    continue;
                }
                sentences[len] = symbol;
                len++;
                if (len == sizemas) {
            	    sizemas= sizemas+1000;
            	    sentences = realloc(sentences, sizemas * sizeof(char));
            	}
                prov=0;
            }
            if (symbol=='\n'){
                prov++; 
            }
        }


    }
    maspar kortej;
    kortej.kolvosimvolov = len;
    kortej.naborpredlojeniy = sentences;
    return kortej;
}

void new_func(struct razbit *m){
    int numSentences = m->kolvopred;
    char** stroki = m->naborstrok;
    int sum1=0;
    for (int i=0;i<strlen(stroki[0]);i++){
        if (isdigit(stroki[0][i])){
            sum1=sum1+(stroki[0][i]-'0');
        }
    }
    for (int i=1;i<numSentences;i++){
        int sum2=0;
        for (int j=0;j<strlen(stroki[i]);j++){
            if (isdigit(stroki[i][j])){
                sum2=sum2+(stroki[i][j]-'0');
            } 
        }
        if(sum2-sum1>0){
            printf("(%d) %s.\n",sum2-sum1,stroki[i]);
        }
    }
}

void about_prog(){
    printf("Справка о функциях:\n");
    printf("0: Вывод текста после первичной обязательной обработки.\n");
    printf("1: Преобразование предложений так, что каждое слово в них начинается с заглавной буквы, а остальные символы слова строчные.\n");
    printf("2: Удаление всех предложений, в которых есть число 2018.\n");
    printf("3: Сортировка предложений по увеличению суммы цифр встречаемых в предложении.\n");
    printf("4: Вывод на экран всех предложений, в которых встречаются все цифры хотя бы один раз.\n");
    printf("5: Вывод справки о функциях, которые реализует программа.\n");
}

void vibori2018(struct razbit *m) {
    int numSentences = m->kolvopred;
    char** stroki = malloc(numSentences * sizeof(char*));
    stroki = m->naborstrok;
    if (numSentences==0 || (numSentences==1 && strchr(stroki[0], '\n') && strlen(stroki[0])==1)){
        printf("Error: пустой ввод");
    }
    else{
        for (int i = 0; i < numSentences; i++) {
            if (!(strstr(stroki[i],"2018"))){
                printf("%s.\n", stroki[i]);
            }
        }
    }
}

void vse_cif(struct razbit *m){
    int numSentences = m->kolvopred;
    char** stroki = malloc(numSentences * sizeof(char*));
    stroki = m->naborstrok;
    if (numSentences==0 || (numSentences==1 && strchr(stroki[0], '\n') && strlen(stroki[0])==1)){
        printf("Error: пустой ввод");
    }
    else{
        for (int i =0;i<numSentences;i++){
            if (strchr(stroki[i], '0')&&strchr(stroki[i], '1')&&strchr(stroki[i], '2')&&strchr(stroki[i], '3')&&strchr(stroki[i], '4')&&strchr(stroki[i], '5')&&strchr(stroki[i], '6')&&strchr(stroki[i], '7')&&strchr(stroki[i], '8')&&strchr(stroki[i], '9')){
                printf("%s.\n", stroki[i]);
            }
        }
    }
}

int digitSum(const char *stroka) {
    int sum = 0;
    int len = strlen(stroka);
    int prov = 0;
    for (int i = 0; i < len; i++) {
        if (isdigit(stroka[i])) {
            sum += (stroka[i] - '0');
            prov = 1;
        }
    }
    if (prov == 0) {
        return -1;
    }
    else {
        return sum;
    }
}

int compareStrings(const void *str1, const void *str2) {
    const char *a = *(const char **)str1;
    const char *b = *(const char **)str2;

    int sum1 = digitSum(a);
    int sum2 = digitSum(b);

    if (sum1 == -1 && sum2 == -1) {
        return 0;
    }
    else if (sum1 == -1) {
        return 1;
    }
    else if (sum2 == -1) {
        return -1;
    }
    else {
        if (sum1 > sum2) {
            return 1;
        }
        else if (sum1 < sum2) {
            return -1;
        }
        else {
            return 0;
        }
    }
}

void summa_cifr(razbit *m) {
    int numSentences = m->kolvopred;
    char **stroki = m->naborstrok;

    if (numSentences == 0 || (numSentences == 1 && strchr(stroki[0], '\n') && strlen(stroki[0]) == 1)) {
        printf("Error: пустой ввод");
    }
    else {
        qsort(stroki, numSentences, sizeof(char *), compareStrings);
        for (int i = 0; i < numSentences; i++) {
            printf("%s.\n", stroki[i]);
        }
    }
}

void top_bottom(struct razbit *m) {
    int numSentences = m->kolvopred;
    char** stroki = m->naborstrok;
    char** stroki_bez_povtorov = malloc(numSentences * sizeof(char*));
    if (numSentences==0 || (numSentences==1 && strchr(stroki[0], '\n') && strlen(stroki[0])==1)){
        printf("Error: пустой ввод");
    }
    else{
        for (int i = 0; i < numSentences; i++) {
            char* top_bottom_str = malloc(strlen(stroki[i]));
            strcpy(top_bottom_str, stroki[i]);
            int len_top_bottom = strlen(top_bottom_str);
            int prov = 0;
            for (int j = 0; j < len_top_bottom-1; j++) {
                if (isalpha(top_bottom_str[j]) && prov == 0) {
                    top_bottom_str[j] = toupper(top_bottom_str[j]);
                    prov = 1;
                    continue;
                }
                if (isspace(top_bottom_str[j]) || (ispunct(top_bottom_str[j])&&top_bottom_str[j]==',')) {
                    prov = 0;
                    continue;
                }
                if (isalpha(top_bottom_str[j]) && prov == 1) {
                    top_bottom_str[j] = tolower(top_bottom_str[j]);
                    continue;
                }
            }
            strcpy(stroki[i], top_bottom_str);
        }
        int z = 0;
        for (int i = 0; i < numSentences; i++) {
            int prov = 0;
            for (int j = 0; j < z; j++) {
                if (strcmp(stroki[i], stroki_bez_povtorov[j]) == 0) {
                    prov = 1;
                    break;
                }
            }
            if (prov == 0){
                stroki_bez_povtorov[z] = malloc(strlen(stroki[i]));
                stroki_bez_povtorov[z] = stroki[i];
                z++;
            }
        }
        for (int i = 0; i < z; i++) {
            printf("%s.\n", stroki_bez_povtorov[i]);
        }
    }
}

void prosto_vivod(struct razbit *m){
    int numSentences = m->kolvopred;
    char** stroki = m->naborstrok;
    if (numSentences==0 || (numSentences==1 && strchr(stroki[0], '\n') && strlen(stroki[0])==1)){
        printf("Error: пустой ввод");
    }
    else{
        for (int i = 0; i < numSentences; i++) {
            printf("%s.\n", stroki[i]);
        }
    }

}

int vibor (){
    int komanda;
    scanf("%d",&komanda);
    return komanda;
}

void info(){
    printf("Course work for option 4.2, created by Petr Yakushev.\n");
}

int main(){
    info();
    int komanda =vibor();
    if ((komanda>5 || komanda<0) && komanda!=8){
        printf("Error: число должно быть от 0 до 5");
    }
    else{
        if (komanda ==5){
        about_prog(); 
        }
        else{
            maspar k= readSentences();
            razbit m = povtor(&k);
            switch (komanda) {
                case 0:
                    prosto_vivod(&m);
                    break;
                case 1:
                    top_bottom(&m);
                    break;
                case 2:
                    vibori2018(&m);
                    break;
                case 3:
                    summa_cifr(&m);
                    break;
                case 4:
                    vse_cif(&m);
                    break;
                case 8:
                    new_func(&m);
                    break;
            }
        }
    return 0;
    }
} 
