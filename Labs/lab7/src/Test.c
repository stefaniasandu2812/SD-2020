#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"

#define MAX_NODES 100

void dfs_connected_comps(ListGraph *lg, int *node, int *visited) {
    /* TODO */
    Stack *s;
    s = malloc(sizeof(Stack));
    LinkedList *component;
    component = malloc(sizeof(LinkedList));
    init_list(component);
    init_stack(s);

    visited[*node] = 1;
    push_stack(s, (int*)node);
    add_nth_node(component, get_size(component), node);
    while(!is_empty_stack(s)){
        int *curr = peek_stack(s);
        LinkedList *l = get_neighbours_list_graph(lg, *curr);
        Node *aux = l->head;
        while(aux != NULL){
            if(visited[*(int*)aux->data] == 0){
                visited[*(int*)aux->data] = 1;
                push_stack(s, aux->data);
                add_nth_node(component, get_size(component), aux->data);
                break;
            }
            aux = aux->next;
        }
        if(aux == NULL){
            visited[*curr] = 2;
            pop_stack(s);
        }
    }
    print_int_linkedlist(component);
    purge_stack(s);
    free_list(&component);
    free(component);
    free(s);
}

void connected_components(ListGraph *lg, int *nodes_index, int *visited) {
    /* TODO */
    int cmp = 0;
    for(int i = 0; i < lg->nodes; ++i){
        if(visited[nodes_index[i]] == 0){
            cmp ++;
            dfs_connected_comps(lg, &nodes_index[i], visited);
        }
    }
    printf("Numarul componentelor conexe:%d\n", cmp);
}

void dfs_topo_sort(ListGraph *lg, int *node,int *t_desc, int *t_fin, int *visited, int *time) {
    /* TODO */
    Stack *s;
    LinkedList *result;
    result = malloc(sizeof(LinkedList));
    s = malloc(sizeof(Stack));
    init_stack(s);
    init_list(result);
    visited[*node] = 1;
    push_stack(s, node);
    while(!is_empty_stack(s)){
        int *curr = (int*)peek_stack(s);
        Node *aux;
        aux = lg->neighbors[*curr]->head;
        while(aux != NULL){
            if(visited[*(int*)aux->data] == 0){
                push_stack(s, aux->data);
                t_desc[*(int*)aux->data] = ++(*time);
                visited[*(int*)aux->data] = 1;
                break;
            }
            aux = aux->next;
        }
        if(aux == NULL){
            visited[*curr] = 2;
            t_fin[*curr] = ++(*time);
            add_nth_node(result, 0, (int*)curr);
            pop_stack(s);    
        }
    }
    free_list(&result);
    purge_stack(s);
    free(s);
    free(result);
}

void topo_sort(ListGraph *lg, int *nodes_index, int *visited) {
    /* TODO */
    int t_desc[MAX_NODES], t_fin[MAX_NODES];
    int time = 0;
    int aux;
    for(int i = 0; i < lg->nodes; ++i){
        t_desc[i] = 0;
        t_fin[i] = 0;
    }
    for(int i = 0; i < lg->nodes; ++i){
        if(visited[i] == 0){
        dfs_topo_sort(lg, &i, t_desc, t_fin, visited, &time);
    }
    }
    for(int i = 0; i < lg->nodes - 1; ++i){
        for(int  j = i+1; j < lg->nodes; ++j){
            if(t_fin[i] < t_fin[j]){
                aux = t_fin[i];
                t_fin[i] = t_fin[j];
                t_fin[j] = aux;

                aux = nodes_index[i];
                nodes_index[i] = nodes_index[j];
                nodes_index[j] = aux;
            }
        }
    }
    printf("Topo sort:\n");
    for(int i = 0; i < lg->nodes; ++i){
        printf("%d\n", nodes_index[i]);
    }
}

void min_path(ListGraph *lg, int *visited) {
    /* TODO */
    int src, dest;
    scanf("%d %d", &src, &dest);
    Queue *q;
    int d[MAX_NODES], p[MAX_NODES];
    for(int i = 0; i < lg->nodes; ++i){
        p[i] = -1;
        d[i] = MAX_NODES+1;
    }
    q = malloc(sizeof(Queue));
    init_q(q);
    int t;
    visited[src] = 1;
    d[src] = 0;
    enqueue(q, &src);
    int OK = 0;
    while(!is_empty_q(q)){
        int *curr = front(q);
        dequeue(q);
        Node *aux = lg->neighbors[*curr]->head;
        while(aux != NULL){
            if(visited[*(int*)aux->data] == 0){
                visited[*(int*)aux->data] = 1;
                p[*(int*)aux->data] = *curr;
                d[*(int*)aux->data] = d[*curr] + 1;
                enqueue(q, aux->data);
                if(*(int*)aux->data == dest){
                    OK = 1; 
                    t = *(int*)aux->data;
                }
            }
            if(OK == 1){
                break;
            }
            aux = aux->next;
        }
        visited[*curr] = 2;
        if(OK == 1)
            break;
    }
    printf("Min path:");
    int *v = calloc(50, sizeof(int));
    int k = 0;
    v[k] = t;
    while(t != src){
        k++;
        v[k] = p[t];
        t = p[t];
    }
    for(int i = k; i >= 0; --i){
        printf("%d ", v[i]);
    }
    printf("\n");
    free(v);
    purge_q(q);
    free(q);
}

int check_bipartite(ListGraph *lg, int *color) {
    /* TODO */
    int src;
    scanf("%d", &src);
    // 0 pentru par, 1 pentru impar si -1 pentru nedefinit
    for(int i = 0; i < lg->nodes; ++i){
        color[i] = -1;
    }

    Queue *q;
    q = malloc(sizeof(Queue));
    init_q(q);

    color[src] = 0;
    enqueue(q, &src);
    
    while(!is_empty_q(q)){
        int *curr = front(q);
        dequeue(q);
        Node *aux = lg->neighbors[*curr]->head;
        while(aux != NULL){
            if(color[*(int*)aux->data] == -1 && color[*(int*)aux->data] != color[*curr]){
                if(color[*curr] == 0){
                    color[*(int*)aux->data] = 1;
                    enqueue(q, aux->data);
                }
                if(color[*curr] == 1){
                    color[*(int*)aux->data] = 0;
                    enqueue(q, aux->data);
                }
            }
            if( color[*(int*)aux->data] == color[*curr]){
                purge_q(q);
                free(q);
                return 0;
            }
            aux = aux->next;
        }
    }
    purge_q(q);
    free(q);
    return 1;
}

int main() {
    int nodes, edges;
    int color[MAX_NODES], visited[MAX_NODES];
    int nodes_index[MAX_NODES];
    int x[MAX_NODES], y[MAX_NODES];
    int t_desc[MAX_NODES], t_fin[MAX_NODES];
    ListGraph *lg = malloc(sizeof(ListGraph));

    /* Ex 1 */
    printf("Ex1:\n");
    lg = malloc(sizeof(ListGraph));

    scanf("%d %d ", &nodes, &edges);
    init_list_graph(lg, nodes);
    for (int i = 0; i < nodes; ++i) {
        nodes_index[i] = i;
    }

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }
    memset(visited, 0, sizeof(visited));
    connected_components(lg, nodes_index, visited);
    clear_list_graph(lg);
    free(lg);

    /* Ex 2 */
    printf("Ex2:\n");
    lg = malloc(sizeof(ListGraph));

    scanf("%d %d ", &nodes, &edges);
    init_list_graph(lg, nodes);
    for (int i = 0; i < nodes; ++i) {
        nodes_index[i] = i;
    }

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }
    memset(visited, 0, sizeof(visited));
    memset(t_desc, 0, sizeof(t_desc));
    memset(t_fin, 0, sizeof(t_fin));
    topo_sort(lg, nodes_index, visited);
    clear_list_graph(lg);
    free(lg);

    /* Ex 3 */
    printf("Ex3:\n");
    lg = malloc(sizeof(ListGraph));

    scanf("%d %d ", &nodes, &edges);
    init_list_graph(lg, nodes);
    for (int i = 0; i < nodes; ++i) {
        nodes_index[i] = i;
    }

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }
    memset(visited, 0, sizeof(visited));
    min_path(lg, visited);
    clear_list_graph(lg);
    free(lg);

    /* Ex 4 */
    printf("Ex4:\n");
    lg = malloc(sizeof(ListGraph));

    scanf("%d %d ", &nodes, &edges);
    init_list_graph(lg, nodes);
    for (int i = 0; i < nodes; ++i) {
        nodes_index[i] = i;
    }

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
        add_edge_list_graph(lg, y[i], &x[i]);

    }
    if (check_bipartite(lg, color)) {
        for (int i = 0; i < lg->nodes; ++i) {
            if (color[i] == 1) {
                printf("%d ", i);
            }
        } 
        printf("\n");
        for (int i = 0; i < lg->nodes; ++i) {
            if (color[i] == 0) {
                printf("%d ", i);
            }
        } 
        printf("\n");
    } else {
        printf("The graph is not bipartite\n");
    }

    clear_list_graph(lg);
    free(lg);
    return 0;
}