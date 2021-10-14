#include <stdlib.h>
#include <stdio.h>

#include "Queue.h"

void init_q(struct Queue *q) {
    q->list = malloc(sizeof(struct LinkedList));
    if (q->list == NULL) {
        perror("Not enough memory to initialize the queue!");
        return;
    }

    init_list(q->list);
}

int get_size_q(struct Queue *q) {
    /* TODO */
    return q->list->size;
}

int is_empty_q(struct Queue *q) {
    /* TODO */
    if(q->list->size == 0){
        return 1;
    }
    return 0;
}

void* front(struct Queue *q) {
    /* TODO */
    return q->list->head->data;
}

void dequeue(struct Queue *q) {
    /* TODO */
    if(is_empty_q(q) == 1){
        printf("Error: empty q\n");
    }
    struct Node *p;
    p = remove_nth_node(q->list, 0);
    free(p);
}

 void enqueue(struct Queue *q, void *new_data) {
    /* TODO */
     if(is_empty_q(q) == 1){
        add_nth_node(q->list, 0, new_data);
        return;
    }
    add_nth_node(q->list, q->list->size, new_data);
}

void clear_q(struct Queue *q) {
    /* TODO */
    while(is_empty_q(q) == 0){
        dequeue(q);
    }
}

void purge_q(struct Queue *q) {
    /* TODO */
    clear_q(q);
    free(q->list);
}