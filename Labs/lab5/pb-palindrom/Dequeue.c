#include <stdlib.h>
#include <stdio.h>

#include "Dequeue.h"

void init_dq(struct Dequeue *dq) {
    dq->list = malloc(sizeof(struct LinkedList));
    if (dq->list == NULL) {
        perror("Not enough memory to initialize the queue!");
        return;
    }

    init_list(dq->list);
}

int get_size_dq(struct Dequeue *dq) {
    /* TODO */
    return dq->list->size;
}

int is_empty_dq(struct Dequeue *dq) {
    /* TODO */
    if(dq->list->size == 0){
        return 1;
    }
    return 0;
}

void* front(struct Dequeue *dq) {
    /* TODO */
    return dq->list->head->data;
}

void* back(struct Dequeue *dq) {
    /* TODO */
    return dq->list->tail->data;
}

void push_front(struct Dequeue *dq, void* new_value){
    add_nth_node(dq->list, 0, new_value);
}

void push_back(struct Dequeue *dq, void* new_value){
    add_nth_node(dq->list, dq->list->size, new_value);
}

void pop_front(struct Dequeue *dq){
    if(is_empty_dq(dq) == 1){
        printf("Error: empty dq\n");
        return;
    }
    struct Node *p;
    p = remove_nth_node(dq->list, 0);
    free(p);
}

void pop_back(struct Dequeue *dq){
    if(is_empty_dq(dq) == 1){
        printf("Error: empty dq\n");
        return;
    }
    struct Node *p;
    p = remove_nth_node(dq->list, dq->list->size);
    free(p);
}

void clear_dq(struct Dequeue *dq) {
    /* TODO */
    while(is_empty_dq(dq) == 0){
        pop_front(dq);
    }
}

void purge_dq(struct Dequeue *dq) {
    /* TODO */
    clear_dq(dq);
    free(dq->list);
}