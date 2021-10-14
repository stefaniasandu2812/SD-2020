#include <stdio.h>
#include <stdlib.h>

#include "Dequeue.h"

int main() {
	int nr;
    int ok=1;
    struct Dequeue *dq = malloc(sizeof(struct Dequeue));
    if (dq == NULL) {
        perror("Not enough memory to create the queue!");
        return -1;
    }
    scanf("%d", &nr);
    init_dq(dq);
    while(nr != 0){
    	int x = nr%10;
    	push_front(dq, &x);
    	nr = nr/10;
    }
    while(is_empty_dq(dq) == 0){
    	if(*(int*)front(dq) == *(int*)back(dq)){
    		pop_front(dq);
    		if(is_empty_dq(dq) == 0){
    			pop_back(dq);
    		} else{
    			ok = 0;
    			break;
    		}
    	} else{
    		ok = 0;
    		break;
    	}
    }
    if(ok == 1){
    	printf("Nr este palindrom\n");
    } else{
    	printf("Nr nu este palindrom\n");
    }
    purge_dq(dq);
    free(dq);
    return 0;
}