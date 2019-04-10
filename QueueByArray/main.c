#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "QueueByArray.h"

//////////////////////////////////////////////////
typedef struct Element {
    int value;
} Element_t;

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int value);
bool destroyElement(Element_t *element);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    
#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int capacity = 10;
    int numOfValues = 15;
    int count = 0;
    
    Queue_t *queue = createQueue(capacity);
    
    printf("*** enqueue [%s] ***\n", __func__);
    count = 0;
    for (int i=0; i<numOfValues; i++) {
        count++;
        Element_t *element = createElement(i);
        bool check = enQueue(queue, element);
        if (check) {
            printf("enqueue #%4d : %10d\n", count, element->value);
        }
        else {
            printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
            destroyElement(element);
        }
    }
    
    printf("*** dequeue [%s] ***\n", __func__);
    count = 0;
    while (!isEmptyQueue(queue)) {
        count++;
        Element_t *element = deQueue(queue);
        if (element != NULL) {
            printf("dequeue #%4d : %10d\n", count, element->value);
            destroyElement(element);
        }
        else {
            printf("error [%s] : could not dequeue value.\n", __func__);
        }
    }
    
    destroyQueue(queue, QUEUE_OPTION_WITH_ELEMENT);
}

Element_t *createElement(int value) {
    Element_t *element = malloc(sizeof(Element_t));
    if (element == NULL) return NULL;
    element->value = value;
    return element;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}
