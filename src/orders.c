#include<stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "structs.h"

int pushOrder(Limit *limit, Order *newOrder){

    if(limit->limitPrice != newOrder->limit){
        return 0;
    }
    newOrder->parentLimit = limit;
    newOrder->nextOrder = limit->headOrder;
    newOrder->prevOrder = NULL;

    if(limit->headOrder != NULL){
        limit->headOrder->prevOrder = newOrder;
    }
    else{
        limit->tailOrder = newOrder;
    }

    limit->headOrder = newOrder;
    limit->orderCount++;
    limit->size += newOrder->shares;
    limit->totalVolume += (newOrder->shares * limit->limitPrice);

    return 1;
}

Order *popOrder(Limit *limit){

    if(limit->tailOrder == NULL){
        return NULL;
    }

    Order *poppedOrder = limit->tailOrder;

    if(limit->tailOrder->prevOrder != NULL){
        limit->tailOrder = limit->tailOrder->prevOrder;
        limit->tailOrder->nextOrder = NULL;
        limit->orderCount--;
        limit->size -= poppedOrder->shares;
        limit->totalVolume -= poppedOrder->shares * limit->limitPrice;
    }
    else{
        limit->headOrder = NULL;
        limit->tailOrder = NULL;
        limit->orderCount = 0;
        limit->size = 0;
        limit->totalVolume = 0;
    }

    return poppedOrder;
}

int removeOrder(Order *order){

    if(order->parentLimit->headOrder == order && order->parentLimit->tailOrder == order){
        order->parentLimit->headOrder = NULL;
        order->parentLimit->tailOrder = NULL;
    }
    else if(order->prevOrder != NULL && order->nextOrder != NULL){
        order->prevOrder->nextOrder = order->nextOrder;
        order->nextOrder->prevOrder = order->prevOrder;
    }
    else if(order->nextOrder == NULL && order->parentLimit->tailOrder == order){
        order->prevOrder->nextOrder = NULL;
        order->parentLimit->tailOrder = order->prevOrder;
    }
    else if(order->prevOrder == NULL && order->parentLimit->headOrder == order){
        order->nextOrder->prevOrder = NULL;
        order->parentLimit->headOrder = order->nextOrder;
    }
    else{
        return -1;
    }

    return 1;
}