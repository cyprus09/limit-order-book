#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

Limit* createRoot(void){

    Limit *limit = malloc(sizeof(Limit));
    initLimit(limit);
    limit->limitPrice = -INT32_MAX;
    return limit;

}

int addNewLimit(Limit* root, Limit *limit){

    if(limitExists(root, limit) == 1){
        return 0;
    }

    limit->leftChild = NULL;
    limit->rightChild = NULL;

    Limit *currentLimit = root;
    Limit *child;
    while(1){
        if(currentLimit->limitPrice < limit->limitPrice){
            if(currentLimit->rightChild == NULL){
                currentLimit->rightChild = limit;
                limit->parent = currentLimit;
                return 1;
            }else{
                currentLimit = currentLimit->rightChild;
            }
        }else if(currentLimit->limitPrice > limit->limitPrice){
            if(currentLimit->leftChild == NULL){
                currentLimit->leftChild = limit;
                limit->parent = currentLimit;
                return 1;
            }else{
                currentLimit = currentLimit->leftChild;
            }
        }else{
            break;
        }
        continue;
    }
    return 0;
}

void replaceLimitInparent(Limit *limit, Limit *newLimit){
    if(!limitIsRoot(limit)){
        if(limit == limit->parent->leftChild && !limitIsRoot(limit->parent)){
            limit->parent->leftChild == newLimit;
        }else{
        limit->parent->rightChild = newLimit;
        }
    }
    if(newLimit != NULL){
        newLimit->parent = limit->parent;
    }
}

int removeLimit(Limit *limit){
    if(!hasGrandParent(limit) && limitIsRoot(limit)){
        return 0;
    }

    Limit *successor = limit;
    if(limit->leftChild != NULL && limit->rightChild != NULL){
        successor = getMinimumLimit(limit->rightChild);
        Limit *parent = successor->parent;
        Limit *leftChild = successor->rightChild;
        Limit *rightChild = successor->leftChild;

        if(limit->leftChild != successor){
            successor->leftChild = limit->leftChild;
        }else{
            successor->leftChild = NULL;
        }

        if(limit->rightChild != successor){
            successor->rightChild = limit->rightChild;
        }else{
            successor->rightChild = NULL;
        }

        limit->leftChild = leftChild;
        limit->rightChild = rightChild;
        successor->parent = limit->parent;

        if(successor->parent->rightChild == limit){
            successor->parent->rightChild = successor;
        }
        else if(successor->parent->leftChild == limit){
            successor->parent->leftChild = successor;
        }
        limit->parent = parent;

        removeLimit(limit);
    }
    else if(limit->leftChild != NULL && limit->rightChild == NULL){
        replaceLimitInParent(limit, limit->leftChild);
    }
    else if(limit->leftChild == NULL && limit->rightChild != NULL){
        replaceLimitInParent(limit, limit->rightChild);
    }
    else{
        replaceLimitInParent(limit, NULL);
    }

    return 1;
}
