/*
 * Set.c
 *
 *  Created on: 11/11/2015
 *      Author: Cursos
 */
#include "Set.h"
#include <stdlib.h>

struct strNode {
	Type data;
	struct strNode *left, *right;
};

typedef struct strNode* Node;

struct strSet {
	Node root;
	int size;
	CompareFunc compareFunc;
};

Set set_create(CompareFunc cf) {
	Set s = (Set) malloc(sizeof(struct strSet));
	s->root = NULL;
	s->size = 0;
	s->compareFunc = cf;
}

int set_size(Set s) {
	return s->size;
}

Bool set_add(Set s, Type t) {
	if(s->root == NULL) {
		Node newNode = (Node) malloc(sizeof(struct strNode));
		newNode->data  = t;
		newNode->left  = NULL;
		newNode->right = NULL;
		s->size = 1;
		return TRUE;
	}

	Node current = s->root;
	Bool found = FALSE;
	Bool added = FALSE;
	while(!found && !added) {
		int c = s->compareFunc(t, current->data);  // t < current->data
		if(c == 0) {
			found = TRUE;
		} else if(c < 0) {
			if(current->left == NULL) {
				Node newNode = (Node) malloc(sizeof(struct strNode));
				newNode->data  = t;
				newNode->left  = NULL;
				newNode->right = NULL;
				current->left = newNode;
				added = TRUE;
			} else {
				current = current->left;
			}
		} else {  // c > 0
			if(current->right == NULL) {
				Node newNode = (Node) malloc(sizeof(struct strNode));
				newNode->data  = t;
				newNode->left  = NULL;
				newNode->right = NULL;
				current->right = newNode;
				added = TRUE;
			} else {
				current = current->right;
			}
		}
	}

	if(added) s->size ++;
	return added;
}


