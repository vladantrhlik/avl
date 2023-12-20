#include <stdio.h>
#include "avl_print.h"

#define WIDTH 4

int powoftwo(int pow) {
	int a = 1;
	for (int i = 0; i < pow; i++) a *= 2;
	return a;
}

void centered_int(int a, int width) {
	printf("%*s%d%*s", width/2*WIDTH, " ", a, width/2*WIDTH, " ");
}

void floor_print(node *n, int rem, int width) {
	if (!n) {
		printf("%*s", powoftwo(width), " ");
		return;
	}
	//printf("val: %d, rem: %d\n", *((int*)n->data), rem);
	if (rem == 0) {
		centered_int(*((int *) n->data), powoftwo(width));
	} else {
		floor_print(n->left, rem-1, width-1);
		floor_print(n->right, rem-1, width-1);
	}
}

void avl_cool_print(avl_tree *avl) {
	int i;
	printf("printing cool AVL:\n");
	for (i = 0; i <= avl->root->hsub; i++) {
		floor_print(avl->root, i, avl->root->hsub);
		printf("\n");
	}
}
