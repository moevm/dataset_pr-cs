#include "../include/coord_queue.h"

// This function creates new CoordQueue
//
// Return:
// ptr to new CoordQueue, NULL if malloc error occured
CoordQueue *coordqueue_new()
{
    CoordQueue *result = (CoordQueue *)malloc(sizeof(CoordQueue));
    if(result == NULL) return NULL;
    result->head = NULL;
    result->tail = NULL;
    result->len = 0;
    return result;
}


// This function adds (x, y) point to the end of the queue
//
// Arguments:
// queue - ptr to CoordQueue to add point in
// x - point X coordinate
// y - point Y coordinate
//
// Return:
// status_code - ptr to variable to put status_code into
//
// Status codes should be handled with handle_error() from "errors.h"
void coordqueue_push(CoordQueue *queue, uint32_t x, uint32_t y,
                     int *status_code)
{
    struct CoordQueueNode *el =
        (struct CoordQueueNode *)malloc(sizeof(struct CoordQueueNode));
    if(el == NULL)
    {
        *status_code = RETCODE_MEMORY_ERROR;
        return;
    }
    el->x = x;
    el->y = y;
    el->next = NULL;
    
    if(queue->len == 0)
    {
        queue->head = el;
        queue->tail = el;
        queue->len = 1;
    }
    else
    {
        queue->tail->next = el;
        queue->tail = el;
        queue->len++;
    }
    *status_code = RETCODE_OK;
}


// This function pops (x, y) point from the top of the queue
//
// Arguments:
// queue - ptr to CoordQueue to pop point from
//
// Return:
// x - ptr to variable to put point X coordinate into
// y - ptr to variable to put point Y coordinate into
void coordqueue_pop(CoordQueue *queue, uint32_t *x, uint32_t *y)
{
    struct CoordQueueNode *el = queue->head;
    *x = el->x;
    *y = el->y;
    
    if(queue->len == 1)
    {
        queue->head = NULL;
        queue->tail = NULL;
        queue->len = 0;
    }
    else
    {
        queue->head = el->next;
        queue->len--;
    }

    free(el);
}


// This function returns len of the CoordQueue
//
// Arguments:
// queue - ptr to CoordQueue to check len
//
// Return:
// len of the CoordQueue
size_t coordqueue_len(CoordQueue *queue)
{
    return queue->len;
}


// This function destroys CoordQueue object
//
// Arguments:
// queue - ptr to CoordQueue to destroy
void coordqueue_destroy(CoordQueue *queue)
{
    // Free elements if queue's not empty
    struct CoordQueueNode *el = queue->head;
    while(el != NULL)
    {
        struct CoordQueueNode *tmp = el;
        el = el->next;
        free(tmp);
    }
    free(queue);
}
