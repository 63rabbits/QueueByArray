#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "QueueByArray.h"

//////////////////////////////////////////////////
Queue_t *createQueue(int capacity) {
    // Block illegal parameters.
    if (capacity <= 0) return NULL;
    
    Queue_t *q = malloc(sizeof(Queue_t));
    if (q == NULL) return NULL;
    q->array = malloc(capacity * sizeof(void*));
    if (q->array == NULL) {
        free(q);
        return NULL;
    }
    q->capacity = capacity;
    q->head = -1;
    q->tail = -1;
    
    return q;
}

bool destroyQueue(Queue_t *Queue, QUEUE_OPTION_e option) {
    // Block illegal parameters.
    if (Queue == NULL) return false;
    
    bool result = clearQueue(Queue, option);
    if (!result) {
        return false;
    }
    if (Queue->array != NULL) {
        free(Queue->array);
    }
    free(Queue);
    
    return true;
}

bool clearQueue(Queue_t *Queue, QUEUE_OPTION_e option) {
    // Block illegal paramters.
    if (Queue == NULL) return false;
    
    while (!isEmptyQueue(Queue)) {
        void *element = deQueue(Queue);
        if ((option == QUEUE_OPTION_WITH_ELEMENT) &&
            (element != NULL)) {
            free(element);
        }
    }
    
    return true;
}

bool enQueue(Queue_t *Queue, void *element) {
    // Block illegal parameters.
    if (Queue == NULL) return false;
    if (element == NULL) return false;
    
    // for 1st enqueue
    if (Queue->tail < 0) {
        Queue->array[0] = element;
        Queue->head = 0;
        Queue->tail = 0;
        return true;
    }
    
    int next = (Queue->tail + 1) % Queue->capacity;
    if (next != Queue->head) {
        Queue->array[next] = element;
        Queue->tail = next;
        return true;
    }
    
    return false;
}

void *deQueue(Queue_t *Queue) {
    if (isEmptyQueue(Queue)) return NULL;
    
    void *element = NULL;
    element = Queue->array[Queue->head];
    if (Queue->head == Queue->tail) {   // for dequeue last elemet.
        Queue->head = -1;
        Queue->tail = -1;
        return element;
    }
    Queue->head = (Queue->head + 1) % Queue->capacity;
    
    return element;
}

bool isEmptyQueue(Queue_t *Queue) {
    if (Queue == NULL) return true;
    if (Queue->head < 0) return true;
    return false;
}

