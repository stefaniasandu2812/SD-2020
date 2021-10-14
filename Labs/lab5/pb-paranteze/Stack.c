#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

void init_stack(struct Stack *stack) {
    stack->list = malloc(sizeof(struct LinkedList));
    if (stack->list == NULL) {
        perror("Not enough memory to initialize the stack!");
        return;
    }

    init_list(stack->list);
}

int get_size_stack(struct Stack *stack) {
    /* TODO */
    return stack->list->size;
}

int is_empty_stack(struct Stack *stack) {
    /* TODO */
    if(stack->list->size == 0){
    	return 1;
    }
    return 0;
}

void* peek_stack(struct Stack *stack) {
    /* TODO */
    if(is_empty_stack(stack) != 1){
    	return stack->list->head->data;
    }
    return NULL;
}

void pop_stack(struct Stack *stack) {
    /* TODO */
    if(is_empty_stack(stack) == 1){
    	printf("Error: empty stack\n");
    	return;
    }
    struct Node *p;
    p = remove_nth_node(stack->list,0);
    free(p);
}

void push_stack(struct Stack *stack, void *new_data) {
    /* TODO */
    add_nth_node(stack->list, 0, new_data);
}

void clear_stack(struct Stack *stack) {
    /* TODO */
    while(is_empty_stack(stack) != 1){
    	pop_stack(stack);
    }
}

void purge_stack(struct Stack *stack) {
    /* TODO */
    clear_stack(stack);
    free(stack->list);
}