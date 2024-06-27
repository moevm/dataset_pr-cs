#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>

#define BLOCK_SIZE 20

enum ERR {NO_ERR = 0, ALLOC_ERR = 1};

typedef struct vector vector;

struct vector{
    void* data;
    size_t size;
    size_t element_size;
};

void vset_element_not_safe(vector* vec, void* element, size_t index);

vector* vcreate(size_t element_size);

int vadd(vector *vec, void* element);

int vresize(vector *vec, size_t aSize);

int vmdelete(vector *vec, vector *indexes, bool is2d);

int _vcontainsCmp(const void* a,const void* b, size_t _);

vector* vfind(vector *vec, int(*cmp)(const void*,const void*,size_t),void* el);

void vfree(vector *vec);

size_t vcontains(vector *vec, void *element);

vector* vsort(vector *vec,int(*cmp)(const void*,const void*));

void verr(int err);

int vaddb(vector* vec, void* element);