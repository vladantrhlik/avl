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
	/* freeing function */
	void (*free_f)(void *a);
	/* print function */
	void (*print)(void *a);
} avl_tree;

/**
 * Initializes AVL tree
 *
 * @param comparator function for comparing two data
 */
avl_tree *avl_init( int(comparator)(void *a, void *b), void(*free_f)(void *a), void(*print)());

/**
 * Inserts data into AVL tree
 */
int avl_insert( avl_tree *avl, void *data );

/**
 * Removes data from AVL tree
 */
int avl_remove( avl_tree *avl, void *data );

/**
 * Prints whole AVL tree
 */
void avl_print( avl_tree *avl );

#endif
