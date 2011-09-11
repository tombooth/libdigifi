/*
 *	rbst.c
 *	© 2009 Tom Booth
 *
 *	Implementation of a generic randomised binary search tree
 *
 *  Hopefully thread-safe
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "rbst.h"


// node structure for tree
struct __rbst_node {
	char *key;
	void *value;
	struct __rbst_node *left;
	struct __rbst_node *right;
};

typedef struct __rbst_node rbst_node;


// local functions
static rbst_node* rbst_search(rbst_node* tree, char* key);
static rbst_node* rbst_insert(rbst_node* tree, rbst_node* new_node);
static rbst_node* rbst_deletetree(rbst_node* tree);
static rbst_node* rbst_rootinsert(rbst_node* tree, rbst_node* new_node);
static rbst_node* rbst_rotateleft(rbst_node* node);
static rbst_node* rbst_rotateright(rbst_node* node);
static void rbst_inlineprint(rbst_node* node);


// local variables
static rbst_node* tree_base;
static unsigned int tree_size;

// mutex to lock down rbst
pthread_mutex_t rbst_mutex = PTHREAD_MUTEX_INITIALIZER;



int rbst_get(char* key, void** value) {
	rbst_node* found_node;
	
	pthread_mutex_lock(&rbst_mutex);
	found_node = rbst_search(tree_base, key);
	pthread_mutex_unlock(&rbst_mutex);
	
	if (found_node == NULL) {
		return RBST_ENOTFOUND;
	}
	
	*value = found_node->value;
	
	return 0;
}



int rbst_add(char* key, void* value) {
	rbst_node* new_node;
	int err;
	unsigned int old_size;
	
	// see if its already been cached
	
	if (rbst_get(key, value) != RBST_ENOTFOUND)
		return RBST_EALREADYCACHED;
	
	if ((new_node = malloc(sizeof(rbst_node))) == NULL) {return -RBST_ENOMEM;}
	if ((new_node->key = strdup(key)) == NULL) {return -RBST_ENOMEM;}
	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;
	
	old_size = tree_size;
	
	pthread_mutex_lock(&rbst_mutex);
	tree_base = rbst_insert(tree_base, new_node);
	pthread_mutex_unlock(&rbst_mutex);
	
	
	if (old_size==tree_size) { err = RBST_EADDFAILED; }
	else { err = 0; }
	
	
	return err;
}



void rbst_free(void) {
	// lock it all as it'll be all gone soon
	pthread_mutex_lock(&rbst_mutex);
	tree_base = rbst_deletetree(tree_base);
	tree_base = NULL;
	pthread_mutex_unlock(&rbst_mutex);
}



void rbst_dump(void) {
	rbst_inlineprint(tree_base);
}




static rbst_node* rbst_deletetree(rbst_node* tree) {
	
	// propagate down the right and left branches so we delete up the tree
	if (tree->left!=NULL) {
		rbst_deletetree(tree->left);
	}
	if (tree->right!=NULL) {
		rbst_deletetree(tree->right);
	}
	
	// free allocated space
	if (tree->key!=NULL) { free(tree->key); }
	if (tree->value!=NULL) { free(tree->value); }
	if (tree!=NULL) { free(tree); tree=NULL; }
	
	return NULL;
}


static rbst_node* rbst_search(rbst_node* tree, char* key) {
	int cmp;
	
	#ifdef RBST_DEBUG
	DFDEBUG("tk: %p  k: %p\n", tree, key);
	if (tree != NULL) DFDEBUG("tk: %s  k: %s\n", tree->key, key);
	else DFDEBUG("k: %s\n", key);
	#endif
	
	if (tree == NULL){
		return NULL;
	}
	
	cmp = strcmp(tree->key,key);
	
	if (cmp == 0) {
		return tree;
	}
	else if (cmp < 0) {
		return rbst_search(tree->right, key);
	}
	else {
		return rbst_search(tree->left, key);
	}
	
}


static rbst_node* rbst_insert(rbst_node* tree, rbst_node* new_node) {
	int r;
	
	// see if tree is null if it is return new node
	if (tree==NULL) {
		tree_size++;
		return new_node;
	}
	
	// random number between 1 and size of tree
	r = (int)(((double)rand()/(double)RAND_MAX) * tree_size) +1;
	
	if (r==1) {
		tree_size++;
		return rbst_rootinsert(tree, new_node);
	}
	
	if (strcmp(new_node->key, tree->key) < 0) {
		tree->left = rbst_insert(tree->left, new_node);
	}
	else {
		tree->right = rbst_insert(tree->right, new_node);
	}
	
	tree_size++;
	
	return tree;
}



static rbst_node* rbst_rootinsert(rbst_node* tree, rbst_node* new_node) {
	
	if (tree == NULL) {
		return new_node;
	}
	
	if (strcmp(new_node->key, tree->key) < 0) {
		tree->left = rbst_rootinsert(tree->left, new_node);
		
		return rbst_rotateright(tree);
	}
	else {
		tree->right = rbst_rootinsert(tree->right, new_node);

		return rbst_rotateleft(tree);
	}
	
}




static rbst_node* rbst_rotateleft(rbst_node* node) {
	rbst_node* right;
	
	right = node->right;
	node->right = right->left;
	right->left = node;
	
	return right;
}


static rbst_node* rbst_rotateright(rbst_node* node) {
	rbst_node* left;
	
	left = node->left;
	node->left = left->right;
	left->right = node;
	
	return left;
}

static void rbst_inlineprint(rbst_node* node) {
	if (node==NULL) return;
	
	if (node->left != NULL)
		rbst_inlineprint(node->left);
		
	fprintf(stdout,"%s: %p\n", node->key, node->value);
	
	if (node->right != NULL)
		rbst_inlineprint(node->right);
}