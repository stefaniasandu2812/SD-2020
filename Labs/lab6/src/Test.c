#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Queue.h"
#include "Stack.h"

#define MAX_NODES 10

void print_matrix_graph(MatrixGraph *mg) {
    /* TODO */
    for(int i = 0;i < mg->nodes; i++){
        for(int j = 0;j < mg->nodes; j++){
            printf("%d ", mg->matrix[i][j]);
        }
        printf("\n");
    }
}

void print_list_graph(ListGraph *lg) {
    /* TODO */
    for(int i = 0;i < lg->nodes; i++){
        printf("%d:", i);
        print_int_linkedlist(lg->neighbors[i]);
    }
}

void dfs_list_graph(ListGraph *lg, int node, int *visited, int *t_desc, int *t_fin) {
    /* TODO */
    Stack *s;
    s = malloc(sizeof(Stack));
    init_stack(s);
    int time = 0;
    visited[node] = 1;
    push_stack(s, &node);
    while(!is_empty_stack(s)){
        int *curr = (int*)peek_stack(s);
        Node *aux;
        aux = lg->neighbors[*curr]->head;
        while(aux != NULL){
            if(visited[*(int*)aux->data] == 0){
                push_stack(s, aux->data);
                t_desc[*(int*)aux->data] = ++time;
                visited[*(int*)aux->data] = 1;
                break;
            }
            aux = aux->next;
        }
        if(aux == NULL){
            visited[*curr] = 2;
            t_fin[*curr] = ++time;
            pop_stack(s);    
        }
    }
    purge_stack(s);
    free(s);
}

void dfs_matrix_graph(MatrixGraph *mg, int node, int *visited, int *t_desc, int *t_fin) {
    /* TODO */
    Stack *s;
    s = malloc(sizeof(Stack));
    init_stack(s);
    int *aux = malloc(mg->nodes*sizeof(int));
    for(int i = 0; i < mg->nodes; i++){
        aux[i] = i;
    }
    int time = 0;
    visited[node] = 1;
    t_desc[node] = time;
    push_stack(s, &node);
    while(!is_empty_stack(s)){
        int *curr = (int*)peek_stack(s);
        int ok = 0;
        for(int i = 0; i < mg->nodes; i++){
            if(has_edge_matrix_graph(mg, *curr, i) == 1 && visited[i] == 0){
                ok = 1;
                visited[i] = 1;
                t_desc[i] = ++time;
                push_stack(s, &aux[i]);
                break;
            }
        }
        if(ok == 0){
            t_fin[*curr] = ++time;
            visited[*curr] = 2;
            pop_stack(s);
        }
        
    }
    free(aux);
    purge_stack(s);
    free(s);

}

void bfs_list_graph(ListGraph *lg, int node, int *visited, int *parents) {
    /* TODO */
    Queue *q;
    q = malloc(sizeof(Queue));
    init_q(q);
    visited[node] = 1;
    enqueue(q, &node);
    while(!is_empty_q(q)){
        int *curr = front(q);
        dequeue(q);
        Node *aux;
        aux = lg->neighbors[*curr]->head;
        while(aux != NULL){
            if(visited[*(int*)aux->data] == 0){
                visited[*(int*)aux->data] = 1;
                parents[*(int*)aux->data] = *curr;
                enqueue(q, aux->data);
            }
            aux = aux->next;
        }
        visited[*curr] = 2;
    }
    purge_q(q);
    free(q);
}

void bfs_matrix_graph(MatrixGraph *mg, int node, int *visited, int *parents) {
    /* TODO */
    Queue *q;
    q = malloc(sizeof(Queue));
    init_q(q);
    visited[node] = 1;
    enqueue(q, &node);
    int *aux = calloc(mg->nodes,sizeof(int));
    for(int i = 0; i < mg->nodes; i++){
        aux[i] = i;
    }
    while(!is_empty_q(q)){
        int *curr = front(q);
        dequeue(q);
        // int *aux = calloc(1,sizeof(int));
        for(int i = 0; i< mg->nodes; i++){
            
            if(has_edge_matrix_graph(mg, *curr, i) == 1){
                if(visited[i] == 0){
                    
                    enqueue(q, &aux[i]);
                    visited[i] = 1;
                    parents[i] = *curr;
                    
                }
            }
        }
        visited[*curr] = 2;
        
    }
    free(aux);
    purge_q(q);
    free(q);
}

void floyd_warshall(MatrixGraph *mg) {
    /* TODO BONUS */
}

/* Afiseaza timpii de descoperire si de finalizare ai fiecarui nod din graf. */
void print_times(int* t_desc, int* t_fin, int nodes)
{
    int i;

    for (i = 0; i < nodes; ++i)
    {
        printf("%d: %d/%d\n", i, t_desc[i], t_fin[i]);
    }
    printf("\n");
}

/* Afiseaza parintii nodurilor din graf. */
void print_parents(int* parents, int nodes)
{
    int i;

    for (i = 0; i < nodes; ++i)
    {
        printf("%d: %d\n", i, parents[i]);
    }
    printf("\n");
}

/* Afiseaza distantele dintre oricare doua noduri din graf */
void print_distances(MatrixGraph* mg)
{
    int i, j;

    for (i = 0; i < mg->nodes; ++i)
    {
        printf("%d:", i);
        for (j = 0; j < mg->nodes; ++j)
        {
            printf(" %d", mg->matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int nodes, edges;
    int x[MAX_NODES], y[MAX_NODES];
    int visited[MAX_NODES], t_desc[MAX_NODES], t_fin[MAX_NODES];
    int parents[MAX_NODES];
    ListGraph *lg = malloc(sizeof(ListGraph));
    MatrixGraph *mg = malloc(sizeof(MatrixGraph));

    scanf("%d %d", &nodes, &edges);

    init_list_graph(lg, nodes);
    init_matrix_graph(mg, nodes);

    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        add_edge_matrix_graph(mg, x[i], y[i]);
        add_edge_list_graph(lg, x[i], &y[i]);
    }

    printf("====== Graf modelat cu matrice de adiacenta ======\n");
    print_matrix_graph(mg);

    printf("====== Graf modelat cu liste de adiacenta ======\n");
    print_list_graph(lg);

    memset(visited, 0, sizeof(visited));
    memset(t_desc, 0, sizeof(t_desc));
    memset(t_fin, 0, sizeof(t_fin));
    dfs_list_graph(lg, 0, visited, t_desc, t_fin);
    printf("====== Timpi de descoperire si finalizare - graf modelat cu liste ======\n");
    print_times(t_desc, t_fin, lg->nodes);

    memset(visited, 0, sizeof(visited));
    memset(t_desc, 0, sizeof(t_desc));
    memset(t_fin, 0, sizeof(t_fin));
    dfs_matrix_graph(mg, 0, visited, t_desc, t_fin);
    printf("====== Timpi de descoperire si finalizare - graf modelat cu matrice ======\n");
    print_times(t_desc, t_fin, mg->nodes);

    printf("====== Parintii nodurilor - graf modelat cu matrice ======\n");
    memset(visited, 0, sizeof(visited));
    memset(parents, 0xff, sizeof(parents));  /* parents[i] = -1; i = 0:(nodes - 1) */
    bfs_list_graph(lg, 0, visited, parents);
    print_parents(parents, lg->nodes);

    printf("====== Parintii nodurilor - graf modelat cu liste ======\n");
    memset(visited, 0, sizeof(visited));
    memset(parents, 0xff, sizeof(parents));  /* parents[i] = -1; i = 0:(nodes - 1) */
    bfs_matrix_graph(mg, 0, visited, parents);
    print_parents(parents, mg->nodes);

    // printf("====== Distantele dintre oricare doua noduri - graf modelat cu matrice ======\n");
    // floyd_warshall(mg);
    // print_distances(mg);

    clear_list_graph(lg);
    clear_matrix_graph(mg);
    free(lg);
    free(mg);
    return 0;
}