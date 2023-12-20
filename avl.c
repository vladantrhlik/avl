#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

node *node_init(node *parent, void *data) {
	/* sanity check */
	if (!data) return NULL;

	node *new = malloc(sizeof(node));
	if (!new) return NULL;
	new->data = data;
	new->parent = parent;
	new->left = NULL;
	new->right = NULL;
	new->hsub = 0;

	return new;
}

/**
 * Prints node and its children
 */
void node_print(node *n, void(*print)(void *a)) {
	if (!n) return;
	printf("(");
	node_print(n->left, print);
	print(n->data);
	node_print(n->right, print);
	printf(")");
}

/**
 * Absolute values of int
 */
int abs(int a) {
	return a > 0 ? a : -a;
}

/**
 * Simple rotation left
 */
void rot_left(node *x, node *z, node **root) {
	if (!x || !z) return;

	node *t23 = z->left;

	x->right = t23;
	if (t23) t23->parent = x;

	z->left = x;
	if (*root == x) *root = z;
	z->parent = x->parent;
	if (z->parent) {
		if (z->parent->left == x) z->parent->left = z;
		if (z->parent->right == x) z->parent->right = z;
	}
	x->parent = z;
}

/**
 * Simple rotation right
 */
void rot_right(node *x, node *z, node **root) {
	if (!x || !z) return;

	node *t23 = z->right;

	x->left = t23; /* fix balance factor */
	if (t23) t23->parent = x;

	z->right = x;
	if (*root == x) *root = z;
	z->parent = x->parent;
	if (z->parent) {
		if (z->parent->left == x) z->parent->left = z;
		if (z->parent->right == x) z->parent->right = z;
	}
	x->parent = z;
}

/**
 * Balances subtrees of given node
 */
void fix_subtree(avl_tree *avl, node *n, int lh, int rh) {
	if (rh > lh) {
		if (n->right->bfactor >= 0) {
			/* right right */
			rot_left(n, n->right, &avl->root);
		} else {
			/* right left */ 
			rot_right(n->right, n->right->left, &avl->root);
			rot_left(n, n->right, &avl->root);
		}
	} else {
		if (n->left->bfactor <= 0) {
			/* left left */
			rot_right(n, n->left, &avl->root);
		} else {
			/* left right */
			rot_left(n->left, n->left->right, &avl->root);
			rot_right(n, n->left, &avl->root);
		}
	}
}

/**
 * Checks balance of subtrees
 *
 * @return int height of subtrees
 */
int check_balance(avl_tree *avl, node *n) {
	/* sanity check */
	if (!avl || !n) return 0;
	
	/* heights of subtrees */
	int lh = check_balance(avl, n->left);
	int rh = check_balance(avl, n->right);

	n->bfactor = rh - lh;

	if (n->bfactor <= -2 || n->bfactor >= 2) {
		fix_subtree(avl, n, lh, rh);
	}

	lh = check_balance(avl, n->left);
	rh = check_balance(avl, n->right);

	n->bfactor = rh - lh;

	int height = abs(lh) > abs(rh) ? abs(lh) : abs(rh);
	n->hsub = height;

	return height + 1;
}


void avl_print(avl_tree *avl) {
	if (!avl->print) return;
	node_print(avl->root, avl->print);
	printf("\n");
}

avl_tree *avl_init(int(comparator)(void *a, void *b), void(*free_f)(void *a), void(*print)()) {
	/* sanity check */
	if (!comparator) return NULL;

	avl_tree *tree = malloc(sizeof(avl_tree));
	if (!tree) return NULL;

	tree->root = NULL;
	tree->comparator = comparator;
	tree->free_f = free_f;
	tree->print = print;

	return tree;
}


int avl_insert(avl_tree *avl, void *data) {
	/* sanity check */	
	if (!avl || !data) return -1;

	/* allocate new node */
	node *n = node_init(NULL, data);
	if (!n) return -1;
	
	/* empty tree */
	if (!avl->root) {
		avl->root = n;
		return 0;
	}
	
	node *jonny = avl->root, **next = NULL;
	while (jonny) {
		int res = avl->comparator(data, jonny->data);
		if (!res) {
			/* equal data */
			free(n);
			return 1;
		} else if (res < 0) {
			next = &jonny->left;
		} else {
			next = &jonny->right;
		}
		
		/* append data to leaf */
		if (!*next) {
			n->parent = jonny;
			*next = n;
			/* check balance from root */
			check_balance(avl, avl->root);
			return 0;
		}
		jonny = *next;
	}

	return 0;
}

int avl_remove(avl_tree *avl, void *data) {
	/* sanity check */
	if (!avl || !data) return 1;
	
	node *jonny = avl->root;
	while (jonny) {
		int res = avl->comparator(data, jonny->data);
		if (!res) {
			/* get pointer from parent of jonny (or pointer to root) */
			node **parent_pointer = NULL;
			if (jonny->parent) {
				if (jonny->parent->left == jonny) parent_pointer = &jonny->parent->left; 
				else parent_pointer = &jonny->parent->right;
			} else if (jonny == avl->root) {
				parent_pointer = &avl->root;
			}

			/* no children */
			if (!jonny->left && !jonny->right) {
				if (parent_pointer) *parent_pointer = NULL;	
				if (avl->free_f) avl->free_f(jonny->data);
			}
			/* one child */
			else if (!jonny->left || !jonny->right) {
				node *replace = jonny->left;
				if (jonny->right) replace = jonny->right;

				if (parent_pointer) {
					*parent_pointer = replace;
					replace->parent = jonny->parent;
				}

				if (avl->free_f) avl->free_f(jonny->data);
			}
			/* two children */
			else {
				/* get rightest left child */
				node *rightest = jonny->left;
				while (rightest->right) rightest = rightest->right;

				if (avl->free_f) avl->free_f(jonny->data);
				jonny->data = rightest->data;

				rightest->parent->right = rightest->left;
				if (rightest->left) {
					rightest->left->parent = rightest->parent;
				}

				jonny = rightest;
			}

			free(jonny);
			check_balance(avl, avl->root);
			return 0;
		} else if (res < 0) {
			jonny = jonny->left;
		} else {
			jonny = jonny->right;
		}

	}

	return 1;
}

int avl_contains( avl_tree *avl, void *data ) {
	if (!avl || !data) return 0;
	
	node *jonny = avl->root;
	while (jonny) {
		int res = avl->comparator(data, jonny->data);
		if (!res) {
			return 1;
		} else if (res > 0) {
			jonny = jonny->right;
		} else {
			jonny = jonny->left;
		}
	}

	return 0;
}
