/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - Binary Tree implementation (test file)
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "queue.h"
#include "binary_tree.h"


int check_complete(b_tree_t *b_tree)
{
    /* TODO */
    /* return 1/0 if binary tree is complete or not */

	int OK = 0;
	// OK este 0 daca am intalnit un nod care are ambii fii
	// OK este 1 daca am intalnit un nod care nu are ambii fii

    Queue *q;
    q = malloc(sizeof(Queue));
	DIE(q == NULL, "q malloc");
	init_q(q);

    enqueue(q, b_tree->root);

    while (!is_empty_q(q)){
    	b_node_t *b_node_tmp;
    	b_node_tmp = front(q);
    	dequeue(q);

    	if (b_node_tmp->left != NULL){

    		if(OK == 1){
    			purge_q(q);
    			free(q);
    			return 0;
    		}

    		enqueue(q, b_node_tmp->left);
    	} else{
    		OK = 1;
    	}

    	if (b_node_tmp->right != NULL){

    		if (OK == 1){
    			purge_q(q);
    			free(q);
    			return 0;
    		}

    		enqueue(q, b_node_tmp->right);
    	} else{
    		OK = 1;
    	}
    }

    purge_q(q);
    free(q);

    return 1;
}

void read_tree(b_tree_t *b_tree)
{
    int i, data, N;

    scanf("%d\n", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d ", &data);
        b_tree_insert(b_tree, data);
    }
}

int main(void)
{
    b_tree_t *binary_tree;

    binary_tree = b_tree_create();

    read_tree(binary_tree);

    printf("%d\n", check_complete(binary_tree));

    /* remove one branch of the tree */
    DIE(binary_tree->root == NULL, "binary_tree root null");
    DIE(binary_tree->root->left == NULL, "binary_tree->left root null");
    DIE(binary_tree->root->left->left == NULL,
            "binary_tree->left->left root null");

    __b_tree_free(binary_tree->root->left->left);
    binary_tree->root->left->left = NULL;

    printf("%d\n", check_complete(binary_tree));

    b_tree_free(binary_tree);

    return 0;
}
