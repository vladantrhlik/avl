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

	return new;
}

void node_print( node *n ) {
	if (!n) return;
	printf("(");
	node_print(n->left);
	printf("%s", n->data);
	node_print(n->right);
	printf(")");
}

int abs(int a) {
	return a > 0 ? a : -a;
}

void rot_left(node *x, node *z) {
	if (!x || !z) return;

	printf("rot_left: x=%s, z=%s\n", x->data, z->data);

	node *t23 = z->left;

	x->right = t23;
	if (t23) t23->parent = x;

	z->left = x;
	z->parent = x->parent;
	if (z->parent) {
		if (z->parent->left == x) z->parent->left = z;
		if (z->parent->right == x) z->parent->right = z;
	}
	x->parent = z;
}

void rot_right(node *x, node *z) {
	if (!x || !z) return;

	printf("rot_right: x=%s, z=%s\n", x->data, z->data);


	node *t23 = z->right;

	x->left = t23; /* fix balance factor */
	if (z->bfactor == 0) {
		x->bfactor = 1;
		z->bfactor = -1;
	} else {
		x->bfactor = 0;
		z->bfactor = 0;
	};
	if (t23) t23->parent = x;

	z->right = x;
	z->parent = x->parent;
	if (z->parent) {
		if (z->parent->left == x) z->parent->left = z;
		if (z->parent->right == x) z->parent->right = z;
	}
	x->parent = z;
}

void fix_subtree(node *n, int lh, int rh) {
	printf("fixing subtree on %s: lh = %d, rh = %d\n", n->data, lh, rh);

	if (rh > lh) {
		if (n->right->bfactor >= 0) {
			/* right right */
			rot_left(n, n->right);
		} else {
			/* right left */ 
			rot_right(n->right, n->right->left);
			rot_left(n, n->right);
		}
	} else {
		if (n->left->bfactor <= 0) {
			/* left left */
			rot_right(n, n->left);
		} else {
			/* left right */
			rot_left(n->left, n->left->right);
			rot_right(n, n->left);
		}
	}

}

/**
 * Checks balance of subtrees
 *
 * @return int height of subtrees
 */
int check_balance(node *n) {
	/* sanity check */
	if (!n) return 0;
	
	/* heights of subtrees */
	int lh = check_balance(n->left);
	int rh = check_balance(n->right);

	n->bfactor = rh - lh;

	if (n->bfactor <= -2 || n->bfactor >= 2) {
		fix_subtree(n, lh, rh);
	}

	lh = check_balance(n->left);
	rh = check_balance(n->right);

	n->bfactor = rh - lh;


	int height = abs(lh) > abs(rh) ? abs(lh) : abs(rh);
	return height + 1;
}


void avl_print( avl_tree *avl ) {
	node_print(avl->root);
	printf("\n");
}

avl_tree *avl_init( int(comparator)(void *a, void *b) ) {
	/* sanity check */
	if (!comparator) return NULL;

	avl_tree *tree = malloc(sizeof(avl_tree));
	if (!tree) return NULL;

	tree->root = NULL;
	tree->comparator = comparator;

	return tree;
}


int avl_insert( avl_tree *avl, void *data ) {
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
			avl_print(avl);
			/* check balance from root */
			check_balance(avl->root);
			return 0;
		}
		jonny = *next;
	}

	return 0;
}



