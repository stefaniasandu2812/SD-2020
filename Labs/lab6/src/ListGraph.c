#include <stdlib.h>
#include <stdio.h>

#include "ListGraph.h"

void init_list_graph(ListGraph *graph, int nodes) {
    /* TODO */
    graph->nodes = nodes;
    graph->neighbors = calloc(nodes, sizeof(LinkedList*));
    for(int i = 0;i < graph->nodes;i++){
    	graph->neighbors[i] = calloc(1, sizeof(LinkedList));
    	init_list(graph->neighbors[i]);
    }
}

void add_edge_list_graph(ListGraph *graph, int src, int *dest) {
    /* TODO */
    add_nth_node(graph->neighbors[src], get_size(graph->neighbors[src]), dest);
    // int *aux = calloc(1,sizeof(int));
    // *aux = src;
    // add_nth_node(graph->neighbors[*dest], get_size(graph->neighbors[*dest]), aux);
}

int has_edge_list_graph(ListGraph *graph, int src, int dest) {
    /* TODO */
    struct Node *curr;
    curr = graph->neighbors[src]->head;
    while(curr != NULL){
    	if(*(int*)curr->data == dest){
    		return 1;
    	}
    	curr = curr->next;
    }
    return 0;
}

LinkedList* get_neighbours_list_graph(ListGraph *graph, int node) {
    /* TODO */
    return graph->neighbors[node];
}

void remove_edge_list_graph(ListGraph *graph, int src, int dest) {
    /* TODO */
    struct Node *p, *curr;
    int n;
    curr = graph->neighbors[src]->head;
    n = 1;
    while(curr != NULL){
    	if(*(int*)curr->data == dest){
    		p = remove_nth_node(graph->neighbors[src], n);
    		break;
    	}
    	n++;
    	curr = curr->next;
    }
    free(p);
}

void clear_list_graph(ListGraph *graph) {
    /* TODO */
    for(int i = 0;i < graph->nodes; i++){
    	free_list(&graph->neighbors[i]);
    }
    free(graph->neighbors);
}