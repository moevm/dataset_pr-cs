#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define NACHALNAYA_STROKA "Course work for option 4.17, created by Nikishin Sergei.\n"
#define OBIEM 1000
#define POSLEDNIY_SIMVOL '\n\n'
#define KRASNIY "\x1b[31m"
#define ZELENIY "\x1b[32m"
#define ZAKONCH "\x1b[0m"
 
char *Vvod();
void Vivod(char **text, int kolichestvo_predlozheniy);
char **Rezdelenie_po_tochkam(char *text, int *kolichestvo_predlozheniy);
char **Udalenie_dublirovaniya(char **razdelenniy_text, int *kolichestvo_predlozheniy);
char **Udalenie_predlozheniy(char **noviy_text, int *kolichestvo_predlozheniy);
void Pokraska(char **text, int *num);
void Ostatok_do_goda(char **text, int *num);
void Sortirovka(char **noviy_text, int *kolichestvo_predlozheniy);
int Summirovanie(char *predlozhenie);
int Sravnen(const void* predlozhenieA,const void* predlozhenieB);
int strcasecmp(char* a,char* b);
void redaktirovanie_predlozheniy(char** noviy_text,char* razdelitel, int* kolichestvo_predlozheniy);

int main(){
	printf("%s", NACHALNAYA_STROKA);
	char vibor_polzovatelya = -1;
	scanf("%c", &vibor_polzovatelya);
	getchar();
	if (!isdigit(vibor_polzovatelya)){
		printf("Error: Incorrect input");
	}
	switch (vibor_polzovatelya){
	case '0':{
		int kolichestvo_predlozheniy = 0;
		char *text = Vvod();
		char **razdelenniy_text = Rezdelenie_po_tochkam(text, &kolichestvo_predlozheniy);
		char **noviy_text = Udalenie_dublirovaniya(razdelenniy_text, &kolichestvo_predlozheniy);
		Vivod(noviy_text, kolichestvo_predlozheniy);
		break;
	}
	case '1':{
		int kolichestvo_predlozheniy = 0;
		char *text = Vvod();
		char **razdelenniy_text = Rezdelenie_po_tochkam(text, &kolichestvo_predlozheniy);
		char **noviy_text = Udalenie_dublirovaniya(razdelenniy_text, &kolichestvo_predlozheniy);
		Ostatok_do_goda(noviy_text, &kolichestvo_predlozheniy);
		break;
	}
	case '2':{
		int kolichestvo_predlozheniy = 0;
		char *text = Vvod();
		char **razdelenniy_text = Rezdelenie_po_tochkam(text, &kolichestvo_predlozheniy);
		char **noviy_text = Udalenie_dublirovaniya(razdelenniy_text, &kolichestvo_predlozheniy);
		Pokraska(noviy_text, &kolichestvo_predlozheniy);
		break;
	}
	case '3':{
		int kolichestvo_predlozheniy = 0;
		char *text = Vvod();
		char **razdelenniy_text = Rezdelenie_po_tochkam(text, &kolichestvo_predlozheniy);
		char **noviy_text = Udalenie_dublirovaniya(razdelenniy_text, &kolichestvo_predlozheniy);
		char **otredaktirovaniy_text = Udalenie_predlozheniy(noviy_text, &kolichestvo_predlozheniy);
		Vivod(otredaktirovaniy_text, kolichestvo_predlozheniy);
		break;
	}
	case'4':{
		int kolichestvo_predlozheniy = 0;
		char *text = Vvod();
		char **razdelenniy_text = Rezdelenie_po_tochkam(text, &kolichestvo_predlozheniy);
		char **noviy_text = Udalenie_dublirovaniya(razdelenniy_text, &kolichestvo_predlozheniy);
		Sortirovka(noviy_text,&kolichestvo_predlozheniy);
		Vivod(noviy_text, kolichestvo_predlozheniy);
		break;
	}
	case'5':{
		printf("%s\n%s\n%s\n%s\n%s\n%s\n",
		"0 - вывод текста после первичной обязательной обработки",
		"1 - вызов функции под номером 1 из списка задания",
		"2 - вызов функции под номером 2 из списка задания",
		"3 - вызов функции под номером 3 из списка задания",
		"4 - вызов функции под номером 4 из списка задания",
		"5 - вывод справки o функциях, которые реализует программа.");
		break;
	}
	case'8':{
		int kolichestvo_predlozheniy = 0;
		char* razdelitel=malloc(100);
		char* temp=malloc(100);
		fgets(temp,100,stdin);
		strncat(razdelitel,temp,strlen(temp)-1);
		char *text = Vvod();
		char **razdelenniy_text = Rezdelenie_po_tochkam(text, &kolichestvo_predlozheniy);
		char **noviy_text = Udalenie_dublirovaniya(razdelenniy_text, &kolichestvo_predlozheniy);
		redaktirovanie_predlozheniy(noviy_text,razdelitel,&kolichestvo_predlozheniy);
		break;
	}
	}
}
char *Vvod(){
	int dlina = 0;
	char buf1;
	char *text = malloc(sizeof(char));
	while (strstr(text,"\n\n")==NULL){
		buf1=getchar();
		text[dlina++]=buf1;
		text=realloc(text,(dlina+1)*sizeof(char));
	}
	text[dlina - 2] = '\0';
	return text;
}
// 0
void Vivod(char **text, int kolichestvo_predlozheniy){
	for (int i = 0; i < kolichestvo_predlozheniy; i++){
		puts(text[i]);
	}
}
char **Rezdelenie_po_tochkam(char *text, int *kolichestvo_predlozheniy){
	char **razdelenniy_text = malloc(sizeof(char *));
	char *token = strtok(text, ".");
	while (token != NULL){
		char *predlozhenie = malloc(strlen(token) + 2);
		memcpy(predlozhenie, token, strlen(token) + 1);
		strcat(predlozhenie, ".");
		while (predlozhenie[0] == ' ' || predlozhenie[0] == '\t' || predlozhenie[0] == '\n'){
			memmove(&predlozhenie[0], &predlozhenie[1], strlen(predlozhenie));
		}
		char *index = strchr(predlozhenie, '\n');
		while (index != NULL){
			*index = ' ';
			index = strchr(predlozhenie, '\n');
		}
		razdelenniy_text[(*kolichestvo_predlozheniy)++] = predlozhenie;
		razdelenniy_text = realloc(razdelenniy_text, ((*kolichestvo_predlozheniy) + 1) * sizeof(char *));
		token = strtok(NULL, ".");
	}
	return razdelenniy_text;
}
int strcasecmp(char* a,char* b){
    char* aNew = malloc(sizeof(char)*strlen(a));
    char* bNew = malloc(sizeof(char)*strlen(b));
    for(int i=0;i<strlen(a);i++){
        aNew[i]=tolower(a[i]);
    }
    for(int i=0;i<strlen(b);i++){
        bNew[i]=tolower(b[i]);
    }
    return strcmp(aNew,bNew);
}
char** Udalenie_dublirovaniya(char** razdelenniy_text, int* kolichestvo_predlozheniy) {
    char** noviy_text = malloc(sizeof(char*) * (*kolichestvo_predlozheniy));
    int nomera_predlozheniy = 1;
    noviy_text[0] = razdelenniy_text[0];
    for (int i = 1; i < (*kolichestvo_predlozheniy); i++) {
        int duplicate = 0;
        for (int j = 0; j < nomera_predlozheniy; j++) {
            if (strcasecmp(razdelenniy_text[i], noviy_text[j]) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            noviy_text[nomera_predlozheniy] = razdelenniy_text[i];
            nomera_predlozheniy++;
        }
    }
    *kolichestvo_predlozheniy = nomera_predlozheniy;
    return noviy_text;
}
// 3
char** Udalenie_predlozheniy(char** noviy_text,int* kolichestvo_predlozheniy){
	char** otredaktirovaniy_text=malloc(sizeof(char*));
	int index_predlozheniya=0;
	for(int i=0;i < *kolichestvo_predlozheniy;i++){
		char* predlozhenie= noviy_text[i];
		char* predlozhenie_copia = malloc(strlen(predlozhenie) + 1);
		memcpy(predlozhenie_copia, predlozhenie, strlen(predlozhenie)+1);
		char* element=strtok(predlozhenie_copia," .");
		char* pervoe_slovo = malloc(strlen(element)+1);
		memcpy(pervoe_slovo,element,strlen(element)+1);
		char* poslednee_slovo;
		while(element!=NULL){
			poslednee_slovo = malloc(strlen(element)+1);
			memcpy(poslednee_slovo,element,strlen(element)+1);
			element=strtok(NULL, " .");
		}
		if(strcmp(pervoe_slovo,poslednee_slovo)!=0){
			otredaktirovaniy_text[index_predlozheniya++]=predlozhenie;
			otredaktirovaniy_text = realloc(otredaktirovaniy_text, (index_predlozheniya+1) * sizeof(char*));
		}
	}
	*kolichestvo_predlozheniy = index_predlozheniya;
	return otredaktirovaniy_text;
}
//2
void Pokraska(char **noviy_text, int *kolichestvo_predlozheniy){
	for (int i = 0; i < *kolichestvo_predlozheniy; i++){
		int schet_slov = 1;
		printf(ZELENIY);
		for (int j = 0; j < strlen(noviy_text[i]); j++){
			printf("%c", noviy_text[i][j]);
			if ((noviy_text[i][j] == ' ')){
				schet_slov++;
				printf(ZAKONCH);
				if (schet_slov % 2 == 0)
					printf(KRASNIY);
				else
					printf(ZELENIY);
			}
		}
		printf("\n");
	}
}
//1
void Ostatok_do_goda(char **noviy_text, int *kolichestvo_predlozheniy){
    char *mesyaci[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < *kolichestvo_predlozheniy; i++){
        char *predlozhenie = noviy_text[i];
        if (strlen(predlozhenie) > 11){
            for (int j = 0; j < strlen(predlozhenie); j++){
                if (isdigit(predlozhenie[j]) && isdigit(predlozhenie[j + 1]) && isdigit(predlozhenie[j + 2]) && isdigit(predlozhenie[j + 3]) && isspace(predlozhenie[j + 4])){
                    char mesyac[4];
                    strncpy(mesyac, predlozhenie + j + 5, 3);
                    mesyac[3] = '\0';
                    for (int z = 0; z < 12; z++){
                        if (strcmp(mesyac, mesyaci[z]) == 0){
                            if (isspace(predlozhenie[j + 8]) && isdigit(predlozhenie[j + 9]) && isdigit(predlozhenie[j + 10])){
                                int den = (predlozhenie[j + 9] - '0') * 10 + (predlozhenie[j + 10] - '0');
                                int rolex = ((12 - z) * 31 - den + 1) * 24;
                                printf("%.*s%d hours to the end of the year%s\n", j, predlozhenie, rolex, predlozhenie + j + 11);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
//4
void Sortirovka(char **noviy_text, int *kolichestvo_predlozheniy) {
    qsort(noviy_text, *kolichestvo_predlozheniy, sizeof(char*), Sravnen);
}
int Summirovanie(char *predlozhenie) {
    int summa_kodov = 0;
    for (int i = 0; i < strlen(predlozhenie); i++) {
        if (!isspace(predlozhenie[i]) && predlozhenie[i] != ',') {
            summa_kodov += (int)predlozhenie[i];
        } else {
            break;
        }
    }
    return summa_kodov;
}
int Sravnen(const void *predlozhenieA, const void *predlozhenieB) {
    return Summirovanie(*(char**)predlozhenieA) - Summirovanie(*(char**)predlozhenieB);
}
//9
void redaktirovanie_predlozheniy(char** noviy_text,char* razdelitel, int* kolichestvo_predlozheniy){
	int kolichestvo_novih=((*kolichestvo_predlozheniy)/2+(*kolichestvo_predlozheniy)%2);
	for (int i=0; i<kolichestvo_novih;i++){
		int leviy_index=i;
		int praviy_index=*kolichestvo_predlozheniy-i-1;
		char* levo=noviy_text[leviy_index];
		char* pravo=noviy_text[praviy_index];
		char *l=malloc(strlen(levo)-1);
		char *r=malloc(strlen(pravo));
		strncat(l,levo,strlen(levo)-1);
		strncat(r,pravo,strlen(pravo));
		printf("%s %s %s\n",l,razdelitel,r);
	}
}
