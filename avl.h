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
	/* height of subtree */
	int hsub;
} node;

node *node_init(node *parent, void *data);

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
	char *(*to_str)(void *a, int width);
} avl_tree;

/**
 * Initializes AVL tree
 *
 * @param comparator function for comparing two data
 */
avl_tree *avl_init( int(comparator)(void *a, void *b), void(*free_f)(void *a), char *(*to_str)(void *a, int w));

/**
 * Inserts data into AVL tree
 */
int avl_insert( avl_tree *avl, void *data );

/**
 * Removes data from AVL tree
 */
int avl_remove( avl_tree *avl, void *data );

/**
 * Checks if AVL contains given data
 */
int avl_contains( avl_tree *avl, void *data );

/**
 * Prints whole AVL tree
 */
void avl_print( avl_tree *avl );

/**
 * Deallocates all memory used by avl
 */
void avl_free( avl_tree **avl);

#endif
