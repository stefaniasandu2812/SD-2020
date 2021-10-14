#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"

#define MAX_NODES 10

void print_matrix_graph(MatrixGraph *mg) {
    /* TODO */
    for(int i = 0;i < g->nodes; i++){
        for(int j = 0;j < g->nodes; j++){
            printf("%d ", g->matrix[i][j]);
        }
        printf("\n");
    }
}

void print_list_graph(ListGraph *lg) {
    /* TODO */
    for(int i = 0;i < g->nodes; i++){
        printf("%d:", i);
        print_int_linkedlist(g->neighbors[i]);
    }
}

void dfs_list_graph(ListGraph *lg, int node, int *visited, int *t_desc, int *t_fin) {
    /* TODO */
}

void dfs_matrix_graph(MatrixGraph *mg, int node, int *visited, int *t_desc, int *t_fin) {
    /* TODO */
}

void bfs_list_graph(ListGraph *lg, int node, int *visited, int *parents) {
    /* TODO */
}

void bfs_matrix_graph(MatrixGraph *mg, int node, int *visited, int *parents) {
    /* TODO */
    Queue *q;
    inti_q(q);
    color[node] = 1;
    enqueue(q, &node);
    while(is_empty_q(q) == 0){
        int *curr = front(q);
        dequeue(q);
        for(i = 0; i< lg->nodes; i++){
            if(has_edge_matrix_graph(lg, node, i) == 1){
                if(color[i] == 0){
                    enqueue(i);
                    color[i] = 1;
                    parent[i] = *curr;
                }
            }
        }
        visited[*curr] = 2;
    }
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
    int time;
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

    time = 0;
    memset(visited, 0, sizeof(visited));
    dfs_list_graph(lg, 0, visited, t_desc, t_fin, &time);
    printf("====== Timpi de descoperire si finalizare - graf modelat cu liste ======\n");
    print_times(t_desc, t_fin, lg->nodes);

    time = 0;
    memset(visited, 0, sizeof(visited));
    dfs_matrix_graph(mg, 0, visited, t_desc, t_fin, &time);
    printf("====== Timpi de descoperire si finalizare - graf modelat cu matrice ======\n");
    print_times(t_desc, t_fin, mg->nodes);

    printf("====== Parintii nodurilor - graf modelat cu matrice ======\n");
    memset(visited, 0, sizeof(visited));
    memset(parents, 0xff, sizeof(parents));  /* parents[i] = -1; i = 0:(nodes - 1) */
    bfs_list_graph(lg, 0,visited, parents);
    print_parents(parents, lg->nodes);

    printf("====== Parintii nodurilor - graf modelat cu liste ======\n");
    memset(visited, 0, sizeof(visited));
    memset(parents, 0xff, sizeof(parents));  /* parents[i] = -1; i = 0:(nodes - 1) */
    bfs_matrix_graph(mg, 0,visited, parents);
    print_parents(parents, mg->nodes);

    printf("====== Distantele dintre oricare doua noduri - graf modelat cu matrice ======\n");
    floyd_warshall(mg);
    print_distances(mg);

    clear_list_graph(lg);
    clear_matrix_graph(mg);
    free(lg);
    free(mg);
    return 0;
}