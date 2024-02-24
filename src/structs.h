#ifndef STRUCTS_H_
#define STRUCTS_H_

//find below defined custom structs for the book
typedef struct Order{

    char *tid;
    unsigned buyOrSell;
    double shares;
    double limit;
    double entryTime;
    double eventTime;
    struct Order *nextOrder;
    struct Order *prevOrder;
    struct Limit *parentLimit;
    int exchangeId;

} Order;

typedef struct Limit{

    double limitPrice;
    double size;
    double totalVolume;
    int orderCount;
    struct Limit *parent;
    struct Limit *leftChild;
    struct Limit *rightChild;
    struct Order *headOrder;
    struct Order *tailOrder;

} Limit;

typedef struct QueueItem{

    Limit *limit;
    struct QueueItem *previous;

} QueueItem;

typedef struct Queue{
    
    int size;
    QueueItem *head;
    QueueItem *tail;

} Queue;

//init functions

void initOrder(Order *order);

void initLimit(Limit *limit);

void initQueueItem(QueueItem *queueItem);

void initQueue(Queue *queue);

//order functions

int pushOrder(Limit *limit, Order *newOrder);

Order* popOrder(Limit *limit);

int removeOrder(Order *order);

//queue functions

void pushToQueue(Queue *q, Limit *limit);

Limit* popFromQueue(Queue *q);

int queueIsEmpty(Queue *q);

//bst functions
Limit* createRoot(void);

int addNewLimit(Limit *root, Limit *limit);

void replaceLimitInParent(Limit *limit, Limit *newLimit);

int removeLimit(Limit *limit);

//bst balancing functions
void balanceBranch(Limit *limit);

void rotateLeftLeft(Limit *limit);

void rotateLeftRight(Limit *limit);

void rotateRightRight(Limit *limit);

void rotateRightLeft(Limit *limit);

//functions for bst operations;
int limitExists(Limit *root, Limit *limit);

int limitIsRoot(Limit *limit);

Limit* hasGrandParent(Limit *limit);

Limit* getGrandParent(Limit* limit);

Limit* getMinimumLimit(Limit *limit);

Limit* getMaximumLimit(Limit *limit);

int getHeight(Limit *limit);

int getBalancedFactor(Limit *limit);

void copyLimit(Limit *limit);

#endif



