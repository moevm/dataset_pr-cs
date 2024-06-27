#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char* udalenie_tabulacii(char* predlozhenie) {
    if ((predlozhenie[0] == ' ') || (predlozhenie[0]) == '\t') {
        memmove(predlozhenie, predlozhenie + 1, strlen(predlozhenie));
    }
    return predlozhenie;
}
int main(){
    char** vvod_texta = (char**)malloc(sizeof(char*));
    int schetchik_vvedennogo_texta = 0;
    int schetchik_izmenennogo_texta = 0;
    while (1) {
        char* predlozhenie = (char*)malloc(sizeof(char));
        char simvol = ' ';
        int schet_predlozheniy = 0;
        int proverka_1 = 0, proverka_2 = 0, proverka_3 = 0;
        int proverka_predlozheniy = 1;
        while (simvol != '.' && simvol != ';' && simvol != '?' && simvol != '!') {
            simvol = getchar();
            if (simvol == '\n') {
                simvol = ' ';
            }
            if (simvol == ' ') {
                proverka_1 = 0;
                proverka_2 = 0;
                proverka_3 = 0;
            }
            if (isalpha(simvol)) {
                proverka_1 = 1;
            }
            if (isdigit(simvol) && proverka_1 == 1) {
                proverka_2 = 1;
            }
            if (isalpha(simvol) && proverka_1 == 1 && proverka_2 == 1) {
                proverka_3 = 1;
            }
            if (proverka_1 == 1 && proverka_2 == 1 && proverka_3 == 1) {
                proverka_predlozheniy = 0;
            }
            predlozhenie[schet_predlozheniy++] = simvol;
            predlozhenie = realloc(predlozhenie, sizeof(char)*(schet_predlozheniy + 1));
        }
        predlozhenie[schet_predlozheniy] = '\0';
        udalenie_tabulacii(predlozhenie);
        schetchik_vvedennogo_texta++;
        if (proverka_predlozheniy) {
            vvod_texta[schetchik_izmenennogo_texta++] = predlozhenie;
            vvod_texta = realloc(vvod_texta, sizeof(char*)*(schetchik_izmenennogo_texta + 1));
        }
        if (strstr(predlozhenie, "Dragon flew away!")) { 
            break;
        }
    }
    for (int i = 0; i < schetchik_izmenennogo_texta; i++){
        printf("%s\n", vvod_texta[i]);
        free(vvod_texta[i]);
    }
    free(vvod_texta);
    printf("Количество предложений до %d и количество предложений после %d\n", schetchik_vvedennogo_texta - 1, schetchik_izmenennogo_texta - 1);
    return 0;
}