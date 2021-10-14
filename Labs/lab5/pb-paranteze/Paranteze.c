#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"

int main() {
    char c[] = "{[](()())}";
    int n = strlen(c);
    int i;
    struct Stack *st = malloc(sizeof(struct Stack));
    if (st == NULL) {
        perror("Not enough memory to create the stack!");
        return -1;
    }
    init_stack(st);
    for(i=0; i<n;i++){
    	if(c[i] == '{'  || c[i] == '[' || c[i] == '('){
    		push_stack(st, &c[i]);
    	}
    	if(c[i] == '}' && *(char*)peek_stack(st) == '{'){
    		pop_stack(st);
    	}
        if(c[i] == ']' && *(char*)peek_stack(st) == '['){
            pop_stack(st);
        }
        if(c[i] == ')' && *(char*)peek_stack(st) == '('){
            pop_stack(st);
        }
    }
    if(is_empty_stack(st) == 1){
    	printf("Sirul este corect\n");
    } else{
    	printf("Sirul nu este corect\n");
    }
    purge_stack(st);
    free(st);
    return 0;
}