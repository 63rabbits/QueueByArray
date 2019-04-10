#ifndef QueueByArray_h
#define QueueByArray_h

#include <stdbool.h>

//////////////////////////////////////////////////
typedef enum QueueOption {
    QUEUE_OPTION_NONE,
    QUEUE_OPTION_WITH_ELEMENT
} QUEUE_OPTION_e;

typedef struct Queue {
    int capacity;
    int head;
    int tail;
    void **array;
} Queue_t;

//////////////////////////////////////////////////
Queue_t *createQueue(int capacity);
bool destroyQueue(Queue_t *Queue, QUEUE_OPTION_e option);
bool clearQueue(Queue_t *Queue, QUEUE_OPTION_e option);
bool enQueue(Queue_t *Queue, void *element);
void *deQueue(Queue_t *Queue);
bool isEmptyQueue(Queue_t *Queue);

#endif
