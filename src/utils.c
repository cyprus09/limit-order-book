#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void initOrder(Order *order){
    
    order->tid = NULL;
    order->buyOrSell = -1;
    order->shares = 0;
    order->limit = 0;
    order->entryTime = 0;
    order->eventTime = 0;
    order->nextOrder = NULL;
    order->prevOrder = NULL;
    order->parentLimit = NULL;
    order->exchangeId = 0;

};

void initLimit(Limit *limit){

    limit->limitPrice = 0;
    limit->size = 0;
    limit->totalVolume = 0;
    limit->orderCount = 0;
    limit->leftChild = NULL;
    limit->rightChild = NULL;
    limit->headOrder = NULL;
    limit->tailOrder = NULL;

};

void initQueueItem(QueueItem *item){
    
    item->limit = NULL;
    item->previous = NULL;

};

void initQueue(Queue *queue){

    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

}

int limitExists(Limit *root, Limit *limit){

    if(root->parent == NULL && root->rightChild == NULL){
        return 0;
    }
    Limit *currentLimit = root;
    while(currentLimit->limitPrice != limit->limitPrice){
        if(currentLimit->rightChild == NULL && currentLimit->leftChild == NULL){
            return 0;
        }
        else{
            if(currentLimit->leftChild != NULL && currentLimit->limitPrice > limit->limitPrice){
                currentLimit = currentLimit->rightChild;
            }
            else if(currentLimit->leftChild != NULL && currentLimit->limitPrice > limit->limitPrice){
                currentLimit = currentLimit->leftChild;
            }
            else{
                return -1;
            }
            continue;
        }
    }

    return 1;
}

Limit *getGrandParent(Limit *limit){
    if(hasGrandParent(limit)){
        return limit->parent->parent;
    }
    return NULL;
}

Limit *getMinimumLimit(Limit *limit){

    Limit *minimumLimit;

    if(limitIsRoot(limit)){
        minimumLimit = limit->rightChild;
    }
    else{
        minimumLimit = limit;
    }

    while(minimumLimit->leftChild != NULL){
        minimumLimit = minimumLimit->leftChild;
    }

    return minimumLimit;
}

Limit *getMaximumLimit(Limit *limit){

    Limit *maximumLimit = limit;
    while(maximumLimit->rightChild != NULL){
        maximumLimit = maximumLimit->rightChild;
    }
    return maximumLimit;
}

int getHeight(Limit *limit){

    if(limit == NULL){
        return -1;
    }

    int height = -1;
    int queueSize = 0;

    Queue *queue = malloc(sizeof(Queue));
    initQueue(queue);
    Limit *current;
    pushToQueue(queue, limit);

    while(1){
        queueSize = queue->size;
        if(queueSize == 0){
            break;
        }
        height++;
        while(queueSize > 0){
            current = popFromQueue(queue);
            if(current->leftChild != NULL){
                pushToQueue(queue, current->leftChild);
            }
            if(current->rightChild != NULL){
                pushToQueue(queue, current->rightChild);
            }
            queueSize--;
        }
    }

    free(queue);
    return height;
}

int getBalancedFactor(Limit *limit){
    
    int rightHeight = -1;
    int leftHeight = -1;

    if(limit->leftChild != NULL){
        leftHeight = getHeight(limit->leftChild);
    }

    if(limit->rightChild != NULL){
        rightHeight = getHeight(limit->rightChild);
    }

    return rightHeight - leftHeight;
}

void copyLimit(Limit *source, Limit *target){
    target->limitPrice = source->limitPrice;
    target->size = source->size;
    target->headOrder = source->headOrder;
    target->orderCount = source->orderCount;
    target->tailOrder = source->tailOrder;
    target->totalVolume = source->totalVolume;

    Order *headOrder = target->headOrder;

    while(headOrder != NULL){
        headOrder->parentLimit = target;

        if(headOrder != NULL){
            headOrder = headOrder->nextOrder;
        }
    }
}