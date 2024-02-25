#include <stdlib.h>
#include "structs.h"

void pushToQueue(Queue *q, Limit *limit){

    QueueItem *newItem = malloc(sizeof(QueueItem));
    newItem->limit = limit;

    if(q->head != NULL){
        q->head->previous = newItem;
    }

    q->head = newItem;
    newItem->previous = q->tail;
    q->tail = newItem;
    q->size++;

}

Limit *popFromQueue(Queue *q){

    if(q->tail == NULL){
        return NULL;
    }

    QueueItem *poppedItem = q->tail;
    Limit *poppedLimit = q->tail->limit;
    q->tail = q->tail->previous;

    if(q->tail == NULL){
        q->head == NULL;
    }

    q->size--;
    free(poppedItem);

    return poppedLimit;

}

int queueIsEmpty(Queue *q){
    if(q->tail == NULL){
        return 1;
    }

    return 0;
}
