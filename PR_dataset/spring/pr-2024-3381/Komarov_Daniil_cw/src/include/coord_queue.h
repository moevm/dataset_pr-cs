#ifndef COORD_STACK_H
#define COORD_STACK_H

#include <stdlib.h>
#include <stdint.h>
#include "errors.h"

struct CoordQueueNode
{
    uint32_t x, y;
    struct CoordQueueNode *next;
};

typedef struct CoordQueue_struct
{
    struct CoordQueueNode *head;
    struct CoordQueueNode *tail;
    size_t len;
} CoordQueue;

CoordQueue *coordqueue_new();

void coordqueue_push(CoordQueue *queue, uint32_t x, uint32_t y,
                     int* status_code);

void coordqueue_pop(CoordQueue *queue, uint32_t *x, uint32_t *y);

size_t coordqueue_len(CoordQueue *queue);

void coordqueue_destroy(CoordQueue *queue);

#endif
