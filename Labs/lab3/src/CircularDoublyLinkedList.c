#include <stdio.h>
#include <stdlib.h>

#include "CircularDoublyLinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct CircularDoublyLinkedList *list) {
    /* TODO */
    list->size = 0;
    list->head = NULL;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Daca n >= nr_noduri, atunci se intoarce nodul de pe pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe
 * lista si am trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem afla pozitia dorita fara sa
 * simulam intreaga parcurgere?
 * Daca n < 0, eroare.
 */
struct Node* get_nth_node(struct CircularDoublyLinkedList *list, int n) {
    /* TODO */
    struct Node *p;
    int k;
    if(list == NULL){
        return NULL;
    }
    p = list->head;
    k=1;
    list->size = get_size(list);
    if(n < 0){
        return NULL;
    }
    if(n > 0 && n < list->size){
        while(k < n+1 && p != list->head->prev){
            p = p->next;
            k++;
        }
        return p;
    }
    if(n >= list->size){
        int new_n;
        new_n = n % (list->size);
        while(k < new_n+1 && p != list->head->prev){
            p = p->next;
            k++;
        }
        return p;
    }


    return NULL;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0).
 * Cand indexam pozitiile nu "ciclam" pe lista circulara ca la get, ci consideram nodurile in ordinea de la head la
 * ultimul (adica acel nod care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci adaugam nodul
 * nou la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct CircularDoublyLinkedList *list, int n, void *new_data) {
    /* TODO */
    struct Node *p, *new;
    int k;
    if(list == NULL || n<0){
        return;
    }
    new = (struct Node*)malloc(sizeof(struct Node));
    new->data = new_data;
    if(list->head == NULL){
        list->head = new; 
        new->next = new;
        new->prev = new;
        list->size++;
        return;
    }
    
    if(n == 0){
        new->next = list->head;
        new->prev = list->head->prev;
        list->head->prev->next = new;
        list->head->prev = new;
        list->head = new;
        list->size++;
        return;
    }
    if(list->size == 1){
        new->next = list->head;
        new->prev = list->head->prev;
        list->head->prev->next = new;
        list->head->prev = new;
        list->size++;
        return;
    }
    if(n < list->size){
    p = list->head;
    k=1;
    while(k <= n){
        p = p->next;
        k++;
    }
    new->next = p;
    new->prev = p->prev;
    p->prev->next = new;
    p->prev = new;
    list->size++;
    return;
    }
    if(n >= list->size){
        new->next = list->head;
        new->prev = list->head->prev;
        list->head->prev->next = new;
        list->head->prev = new;
        list->size++;
        return;
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct CircularDoublyLinkedList *list, int n) {
    /* TODO */
    struct Node *first, *last, *p, *q;
    int k;
    if(n<0 || list==NULL){
        return NULL;
    }
    if(list->head == NULL){
        return NULL;
    }
    if(list->size == 1){
        p = list->head;
        list->head = NULL;
        list->size--;
        return p;
    }
    if(n == 0 && list->size > 1){
        first = list->head;
        last = list->head->prev;
        list->head = first->next;
        list->head->prev = last;
        last->next = list->head;
        list->size--;
        return first;
    }
    if(n<list->size){
        p = list->head;
        k = 1;
        while(k <= n){
            p = p->next;
            k++;
        }
        q = p->prev;
        q->next = p->next;
        p->next->prev = q;
        list->size--;
        return p;
    }
    if(n>=list->size){
        last = list->head->prev;
        list->head->prev = last->prev;
        last->prev->next = list->head;
        list->size--;
        return last;
    }

    return NULL;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct CircularDoublyLinkedList *list) {
    /* TODO */

    struct Node *p;
    int size_nodes;
    if(list == NULL){
        return 0;
    }
    p = list->head;
    size_nodes = 1;
    while(p->next != list->head->prev){
        size_nodes++;
        p = p->next;
    }
    return size_nodes;

    return -1;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista.
 */
void free_list(struct CircularDoublyLinkedList **pp_list) {
    /* TODO */

    struct Node *nextp, *p, *last;
    p = (*pp_list)->head;
    last = (*pp_list)->head->prev;
    while(p!=last){
        nextp = p->next;
        free(p);
        p = nextp;
    }
    
    free(*pp_list);
    *pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_int_list(struct CircularDoublyLinkedList *list) {
    /* TODO */
    struct Node *p;
    int i;
    if(list == NULL){
        return;
    }
    p = list->head;
    for( i = 0;i < list->size;i++){
        printf("%d ", *((int*)p->data));
        p = p->next;
    }


    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_string_list(struct CircularDoublyLinkedList *list) {
    /* TODO */
    struct Node *p;
    int i;
    if(list == NULL){
        return;
    }
    p = list->head;
    for( i = 0;i < list->size;i++){
        printf("%s ", (char*)p->data);
        p = p->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la stanga in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_left_circular(struct Node *start) {
    /* TODO */
    struct Node *q;
    q = start->next;;
    while(start != q){
        printf("%d ", *((int*)start->data));
        start = start->prev;
    }
    printf("%d ", *((int*)start->data));

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_right_circular(struct Node *start) {
    /* TODO */
    struct Node *q;
    q = start->prev;
    while(start != q){
        printf("%d ", *((int*)start->data));
        start = start->next;
    }
    printf("%d ", *((int*)start->data));

    printf("\n");
}
