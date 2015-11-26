/*
 * List.c
 *
 *  Created on: 04/11/2015
 *      Author: Cursos
 */

#include "List.h"
#include <stdlib.h>

struct strNode {
	Type data;
	struct strNode *prior, *next;
};
typedef struct strNode* Node;

struct strList {
	struct strNode *first, *last;
	struct strNode *preFirst, *postLast;
	int size;
};

List list_create() {
	List l = (List) malloc(sizeof(struct strList));
	l->size=0;
	l->last=NULL;
	l->first=NULL;
	l->preFirst = (Node) malloc(sizeof(struct strNode));
	l->preFirst->next  = NULL;
	l->preFirst->prior = NULL;
	l->preFirst->data  = NULL;
	l->postLast = (Node) malloc(sizeof(struct strNode));
	l->postLast->next  = NULL;
	l->postLast->prior = NULL;
	l->postLast->data  = NULL;
	return l;
}

void list_destroy(List l){
	Node current, next;
	current = l->first;
	if(l->first != NULL){
		next=l->first->next;
		while(next != NULL){
			free(current);
			current = next;
			next = current->next;
		}
		free(current);
	}
	free(l->preFirst);
	free(l->postLast);
	free(l);
}

int list_size(List l) {
	return l->size;
}

void list_add(List l, Type t) { //añade un elemento al final de la lista e incrementa en uno
	Node newNode = (Node) malloc(sizeof(struct strNode));
	newNode->data = t;
	newNode->next = NULL;
	if (l->size == 0) {
		newNode->prior = NULL;
		l->first = newNode;
		l->preFirst->next = l->first;
	} else {
		newNode->prior = l->last;
		l->last->next = newNode;
	}
	l->last = newNode;
	l->postLast->prior = l->last;
	l->size++;
}

Type list_get(List l, int p) {
	if(p < 0 || p >= l->size) return 0;
	Node current = l -> first;
	int i;
	for(i = 0; i < p ; i++) {
		current = current -> next;
	}
	return current->data;
}

void list_set(List l, Type t, int p) {
	if (p < 0 || p >= l->size) return;
	Node current = l->first;
	int i;
	for(i = 0; i < p; i++){
		current = current -> next;
	}
	current->data = t;
}

Type list_remove(List l, int p) {
	if (p < 0 || p >= l->size) return NULL;
	Node current = l->first;
	int i;
	for(i = 0; i < p; i++){
		current = current -> next;
	}
	Type Rescue = current->data;
	if(current->prior != NULL) current->prior->next = current->next;
	else {
		l->first = current->next;
		l->preFirst->next = l->first;
	}
	if(current->next  != NULL) current->next->prior = current->prior;
	else {
		l->last = current->prior;
		l->postLast->prior = l->last;
	}
	free(current);
	l->size--;
	return Rescue;
}

// Todo lo referente con iteradores
Iterator list_begin(List l) {
	return l->preFirst;
}

Iterator list_end(List l) {
	return l->postLast;
}

Bool list_hasNext(Iterator ite) {
	if(ite->next != NULL) return TRUE;
	else return FALSE;
}

Bool list_hasPrior(Iterator ite) {
	if(ite->prior != NULL) return TRUE;
	else return FALSE;
}

Iterator list_next(Iterator ite) {
	if(!list_hasNext(ite)) return NULL;
	else return ite->next;
}

Iterator list_prior(Iterator ite) {
	if(!list_hasPrior(ite)) return NULL;
	else return ite->prior;
}

Type list_data(Iterator ite) {
	return ite->data;
}










