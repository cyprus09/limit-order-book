#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void balanceBranch(Limit *limit){
    asser(getHeight(limit) < 2);

    int balancefactor = getBalancedFactor(limit);
    if(balancefactor > 1){
        balancefactor = getBalancedFactor(limit->rightChild);
        if(balancefactor < 0){
            rotateRightLeft(limit);
        }
        else if(balancefactor > 0){
            rotateRightRight(limit);
        }
    }
    else if(balancefactor < -1){
        balancefactor = getBalancedFactor(limit->leftChild);
        if(balancefactor < 0){
            rotateLeftLeft(limit);
        }
        else if(balancefactor > 0){
            rotateLeftRight(limit);
        }
    }
}

void rotateLeftLeft(Limit *limit){
    Limit *child = limit->leftChild;
    if(limitIsRoot(limit->parent) == 1 || limit->limitPrice > limit->parent->limitPrice){
        limit->parent->rightChild = child;
    }else{
        limit->parent->leftChild = child;
    }

    child->parent = limit->parent;
    limit->parent = child;
    Limit* temp = child->rightChild;
    child->rightChild = limit;
    limit->leftChild = temp;

    return;
}

void rotateLeftRight(Limit *limit) {
    Limit *child = limit->leftChild;
    Limit *grandChild = limit->leftChild->rightChild;
    child->parent = grandChild;
    grandChild->parent = limit;

    Limit* tempOne = child->leftChild;
    Limit* tempTwo = grandChild->leftChild;
    Limit* tempThree = grandChild->rightChild;

    child->rightChild = grandChild->leftChild;
    limit->leftChild = grandChild;
    grandChild->leftChild = child;
    grandChild->rightChild = tempThree;
    child->leftChild = tempOne;
    child->rightChild = tempTwo;

    rotateLeftLeft(limit);
    return;
}

void rotateRightRight(Limit *limit){
    Limit *child = limit->rightChild;

    if(limitIsRoot(limit->parent)==1 || limit->limitPrice > limit->parent->limitPrice){
        limit->parent->rightChild = child;
    }
    else{
        limit->parent->leftChild = child;
    }

    child->parent = limit->parent;
    limit->parent = child;
    Limit* tmp_ptr = child->leftChild;
    child->leftChild = limit;
    limit->rightChild = tmp_ptr;

    return;
}

void rotateRightLeft(Limit *limit){
    Limit *child = limit->rightChild;
    Limit *grandChild = limit->rightChild->leftChild;
    child->parent = grandChild;
    grandChild->parent = limit;
    Limit* tempOne = child->rightChild;
    Limit* tempTwo = grandChild->rightChild;
    Limit* tempThree = grandChild->leftChild;
    limit->rightChild = grandChild;
    grandChild->rightChild = child;
    grandChild->leftChild = tempThree;
    child->leftChild = tempTwo;
    child->rightChild = tempOne;

    rotateRightRight(limit);
    return;
}