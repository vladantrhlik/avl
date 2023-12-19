#ifndef AVL
#define AVL

/**
 * Node of the tree
 */
typedef struct thenode{
	void *data;
	struct thenode *left, *right, *parent;
	/* balance factor */
	int bfactor;
} node;

node *node_init();

/**
 * AVL tree structure
 */
typedef struct avl {
	/* root of the tree */
	node *root;
	/* comparator function */
	int (*comparator)(void *a, void *b);
} avl_tree;

/**
 * Initializes AVL tree
 *
 * @param comparator function for comparing two data
 */

avl_tree *avl_init( int(comparator)(void *a, void *b) );

/**
 * Inserts data into AVL tree
 */
int avl_insert( avl_tree *avl, void *data );

int avl_remove( avl_tree *avl, void *data );

void avl_print( avl_tree *avl );

#endif
