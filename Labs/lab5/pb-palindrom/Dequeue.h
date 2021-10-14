#ifndef __DEQUEUE_H__
#define __DEQUEUE_H__

#include "LinkedList.h"

struct Dequeue {
    struct LinkedList *list;
};

void init_dq(struct Dequeue *dq);

int get_size_dq(struct Dequeue *dq);

int is_empty_dq(struct Dequeue *dq);

void* front(struct Dequeue *dq);

void* back(struct Dequeue *dq);

void push_front(struct Dequeue *dq, void* new_value);

void push_back(struct Dequeue *dq, void* new_value);

void pop_front(struct Dequeue *dq);

void pop_back(struct Dequeue *dq);

void clear_dq(struct Dequeue *dq);

void purge_dq(struct Dequeue *dq);

#endif /* __DEQUEUE_H__ */