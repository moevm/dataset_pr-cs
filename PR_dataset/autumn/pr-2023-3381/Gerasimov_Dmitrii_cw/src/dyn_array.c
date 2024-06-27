#include "dyn_array.h"

vector* vcreate(size_t element_size){
    vector *vec = malloc(sizeof(vector*));
    if(!vec)
        verr(ALLOC_ERR);
    vec->data = NULL;
    vec->size = 0;
    vec->element_size = element_size;
    return vec;
}

void vset_element_not_safe(vector* vec, void* element, size_t index){
    if(vec->element_size==1)
        ((char*)vec->data)[index] = *(char*)element;
    else
        memcpy(&(((char*)vec->data)[vec->element_size*index]),element,vec->element_size);
}

int vadd(vector *vec, void* element){
    int err = NO_ERR;
    if((vec->size!=0 && vec->size%BLOCK_SIZE==0) || vec->data==NULL)
        err = vresize(vec,vec->size+BLOCK_SIZE);
    vset_element_not_safe(vec,element,vec->size++);
    return err;
}

int vaddb(vector* vec, void* element){
    int err = NO_ERR;
    if((vec->size!=0 && vec->size%BLOCK_SIZE==0) || vec->data==NULL)
        err = vresize(vec,vec->size+BLOCK_SIZE);
    memmove(&(((char*)vec->data)[vec->element_size]),((char*)vec->data),vec->size*vec->element_size);
    vset_element_not_safe(vec,element,0);
    vec->size++;
    return err;
}

int vresize(vector *vec, size_t aSize){
    if(vec->size)
        vec->data = realloc(vec->data,vec->element_size*aSize);
    else
        vec->data = malloc(vec->element_size*aSize);
    if(!vec->data)
        return ALLOC_ERR;
    return NO_ERR;
}

int vmdelete(vector *vec, vector *indexes, bool is2d){
    if(vec->size==indexes->size){
        if(is2d){
            for(size_t i = 0;i<vec->size;i++){
                free(((vector*)vec->data)[i].data);   
            }
        }
        vec->size = 0;
        free(vec->data);
        vec->data=NULL;
        return NO_ERR;
    }
    size_t c = 0;
    if(is2d){
        for(size_t i = 0;i<vec->size;i++){
            if(vcontains(indexes,&i)){
                free(((vector*)vec->data)[i].data);
            }
        }
    }
    for(size_t i = 0;i<vec->size;i++){
        for(;vcontains(indexes,&i) && i<vec->size;c++,i++){}
        vset_element_not_safe(vec,&((char*)vec->data)[vec->element_size*i],i-c);
    }
    return vresize(vec,vec->size-=indexes->size);
}

int _vcontainsCmp(const void* a,const void* b, size_t _){
    return *(char*)a != *(char*)b; 
}

size_t vcontains(vector *vec, void *element){
    vector *tmp = vfind(vec,(vec->element_size!=1?memcmp:_vcontainsCmp),element);
    size_t len = tmp->size;
    vfree(tmp);
    return len;
}

vector* vfind(vector *vec, int(*cmp)(const void*,const void*,size_t),void* el){
    vector* res = vcreate(sizeof(int));
    for(size_t i = 0;i<vec->size;i++){
        if(!cmp(&((char*)vec->data)[i*vec->element_size],el,vec->element_size)){
            verr(vadd(res,&i));
        }
    }
    return res;
}

vector* vsort(vector *vec,int(*cmp)(const void*,const void*)){
    qsort(vec->data,vec->size,vec->element_size,cmp);
    return vec;
}

void vfree(vector *vec){
    free(vec->data);
    free(vec);
}

void verr(int err){
    if(err == ALLOC_ERR){
        wprintf(L"Error: memory re/allocation error.\n");
        exit(0);
    } 
}
