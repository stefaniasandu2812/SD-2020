#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste simplu inlantuite, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct LinkedList *list) {
    /* TODO */
    list->head = NULL;
    list->size = 0;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct LinkedList *list, int n, void *new_data) {
    /* TODO */
    struct Node *new, *curr, *prev;
    int k=0;
    if(list == NULL){
    	return ;
    }
    new=(struct Node*)malloc(sizeof(struct Node));
    if(list->head == NULL){
    	new->data = new_data;
    	new->next = list->head;
    	list->head = new;
    	list->size++;
    	return ;
    }
    if(n >= list->size ){
    	new->data = new_data;
    	new->next=NULL;
    	curr=list->head;
    	while(curr->next != NULL){
    		curr=curr->next;
    	}
    	curr->next=new;
    	list->size++;
    	return;
    }
    if( n==0 ){
    	new->data = new_data;
    	new->next = list->head;
    	list->head = new;
    	list->size++;
    }
    if(n > 0 && n < list->size){
    	new->data = new_data;
    	curr=list->head->next;
    	prev=list->head;
    	k=1;
    	while(k<n && curr->next != NULL){
    		k++;
    		prev=curr;
    		curr=curr->next;
    	}
    	new->next=prev->next;
    	prev->next=new;
    	list->size++;
    }
    if(n<0){
    	return ;
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1,
 * se elimina nodul de la finalul listei. Daca n < 0, eroare.
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct LinkedList *list, int n) {
    /* TODO */
    struct Node *first, *last, *prev, *curr;
    int k=0;
    if(list == NULL){
    	return 0;
    }
    if(list->head == NULL){
    	return 0;
    }
    if( n != 0 && n >= list->size-1){
    	last = list->head->next;
    	prev = list->head;
    	while(last->next != NULL){
    		prev=last;
    		last=last->next;
    	}
    	prev->next=NULL;
    	list->size--;
    	return last;
    }
    if( n==0 ){
    	first = list->head;
    	list->head = first->next;
    	list->size--;
    	return first;
    }
    if(n>0 && n<list->size){
    	curr = list->head->next;
    	prev = list->head;
    	k=1;
    	while(k<n && curr->next!=NULL){
    		k++;
    		prev=curr;
    		curr=curr->next;
    	}
    	prev->next=curr->next;
    	list->size--;
    	return curr;
    }
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct LinkedList *list) {
    /* TODO */
    struct Node *curr;
    int size_nodes=0;
    if(list == NULL){
    	return 0;
    }
    if(list->head->next == NULL){
    	size_nodes=1;
    }
    curr=list->head;
    while(curr->next != NULL){
    	size_nodes++;
    	curr=curr->next;
    }
    return size_nodes;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista si actualizeaza la NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void free_list(struct LinkedList **pp_list) {

    /* TODO */
    struct Node *next, *curr;
    curr=(*pp_list)->head;
    while(curr != NULL){
    	next = curr->next;
    	free(curr);
    	curr=next;
    }
    free(*pp_list);
    *pp_list=NULL;
}



/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista inlantuita separate printr-un spatiu.
 */
void print_int_linkedlist(struct LinkedList *list) {
    /* TODO */
    struct Node *curr;
    if(list == NULL){
    	return ;
    }
    curr = list->head;
    while(curr->next != NULL){
    	printf("%d ", *((int*)curr->data));
    	curr=curr->next;
    }
    printf("%d ", *((int*)curr->data));
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista inlantuita, separate printr-un spatiu.
 */
void print_string_linkedlist(struct LinkedList *list) {
    /* TODO */
    struct Node *curr;
    if(list == NULL){
    	return;
    }
    curr = list->head;
    while(curr->next != NULL){
    	printf("%s ", (char*)curr->data);
    	curr=curr->next;
    }
    printf("%s ", (char*)curr->data);
    printf("\n");
}
