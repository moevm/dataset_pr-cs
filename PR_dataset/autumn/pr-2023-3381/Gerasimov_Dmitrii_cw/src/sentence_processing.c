#include "sentence_processing.h"

void option0(vector* text){}

int cmpOpt_1(const void *a, const void* b, size_t _){
    return *(wchar_t*)a!=L':';
}

int get_time_from_sentence(size_t index, vector *sentence, struct tm *start){
    int h0 = ((wchar_t*)(sentence->data))[index-2] - 48;
    int h1 = ((wchar_t*)(sentence->data))[index-1] - 48;
    int m0 = ((wchar_t*)(sentence->data))[index+1] - 48;
    int m1 = ((wchar_t*)(sentence->data))[index+2] - 48;
    if(!((h0*10+h1)<24 && (m0*10+m1)<60)){
        return -1;
    }
    return abs(start->tm_hour-(h0*10+h1))*60 + abs(start->tm_min-(m0*10+m1));
}

void option1(vector* text){
    time_t t = time(NULL);
    struct tm *start = localtime(&t);
    for(size_t i = 0;i<text->size;i++){
        vector* sentence = &(((vector*)(text->data))[i]);
        vector* indexes = vfind(sentence,cmpOpt_1,NULL);
        for(size_t j = 0;j<indexes->size;j++){
            int ind = ((int*)(indexes->data))[j];
            if(!(ind>=2 && ind <=sentence->size-2))
                continue;
            for(size_t k = ind-2;k<=ind+2;k++){
                if(k==ind) continue;
                if(!iswdigit(((wchar_t*)(sentence->data))[k])){
                    ind = -1;
                    break;
                }
            }
            if(ind!=-1){
                ind = get_time_from_sentence(ind,sentence,start);
                if(ind!=-1)
                    wprintf(L"Sentence: %d Time: %d\n",i+1,ind);
            }
        }
        vfree(indexes);
    }
}

int cmpOpt2(const void* a, const void* b, size_t _){
    return !(*(int*)a<=90 && *(int*)a>=65);
}

void option2(vector* text){
    for(size_t i = 0;i<text->size;i++){
        void* sentence_ptr = &(((vector*)(text->data))[i]);
        vector* indexes = vfind(sentence_ptr,cmpOpt2,NULL);
        verr(vmdelete(sentence_ptr,indexes,0));
        vfree(indexes);
    }
}

int cmpOpt3_2(const void* a, const void* b, size_t el_size){
    return !(iswalpha(*(wchar_t*)a) && !(*(int*)a>=65 && *(int*)a<=122));
}

int cmpOpt3_1(const void* a, const void* b){
    vector* indA = vfind((vector*)a,cmpOpt3_2,NULL);
    vector* indB = vfind((vector*)b,cmpOpt3_2,NULL);
    int r = indA->size<indB->size;
    vfree(indA);
    vfree(indB);
    return r;
}

void option3(vector* text){
    vsort(text,cmpOpt3_1);
}

int cmpOpt4_1(const void* a, const void* b, size_t _){
    size_t len = ((vector*)a)->size;
    wchar_t* tmp = malloc((len+1)*sizeof(wchar_t));
    memcpy(tmp,((vector*)a)->data,len*sizeof(wchar_t));
    tmp[len] = L'\0';
    if(wcspbrk(tmp,L"№*$#@")!=NULL){
        free(tmp);
        return 1;
    }
    free(tmp);
    return 0;
}

void option4(vector* text){
    vector* indexes = vfind(text,cmpOpt4_1,NULL);
    verr(vmdelete(text,indexes,1));
    vfree(indexes);
}

void option5(){
    wprintf(L"Варинты действий:\n0 - вывод текста после первичной обязательной обработки\n1 - Для каждой подстроки в тексте, задающей время вида “часы:минуты”, вывести номер предложения в котором она  встречается и количество минут до текущего времени (время, в которое начала выполняться данная задача).\n2 - В каждом предложении удалить все заглавные латинские буквы.\n3 - Отсортировать предложения по уменьшению количеству кириллических букв.\n4 - Удалить все предложения в которых нет специальных символов (№*$#@).\n5 - вывод справки о функциях, которые реализует программа\n");
    exit(0);
}

void free_text(vector* text){
    for(size_t i = 0;i<text->size;i++){
        free((((vector*)(text->data))[i]).data);
    }
    vfree(text);
}

int cmpOpt9(const void* a, const void* b, size_t _){
    return !(iswspace(*(wchar_t*)a) || *(wchar_t*)a==L','|| *(wchar_t*)a==L'.');
}

void option9(vector* text, size_t word_len){
    wchar_t* str = L"(большое слово)";
    size_t len = 15;
    for(size_t i = 0;i<text->size;i++){
        vector* sentence = &(((vector*)(text->data))[i]);
        vector* indexes = vfind(sentence,cmpOpt9,NULL);
        int a = -1;
        vaddb(indexes,&a);
        vector* new_sentence = vcreate(sizeof(wchar_t));
        size_t k = 0;
        for(size_t i = 0;i<sentence->size;i++){
            if(i==((int*)indexes->data)[k]+1 && k<indexes->size-1 && (abs(((int*)indexes->data)[k+1] - ((int*)indexes->data)[k])-1>word_len)){
                for(size_t j = 0;j<len;j++){
                    vadd(new_sentence,&str[j]);
                }
                i=((int*)indexes->data)[k+1]-1;
                k++;
                continue;
            }
            if(i==((int*)indexes->data)[k]+1)
                k++;
            vadd(new_sentence,&((wchar_t*)sentence->data)[i]);
        }
        free(sentence->data);
        ((vector*)(text->data))[i] = *new_sentence;
        free(new_sentence);
        vfree(indexes);
    }
}