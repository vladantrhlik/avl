#include <stdio.h>
#include <string.h>
#include "avl.h"

int str_comparator(void *a, void *b) {
	return strcmp(a, b);
}

int main(int argc, char *argv[]) {
	avl_tree *tree = avl_init(&str_comparator, NULL);

	while (1) {
		char *space = malloc(sizeof(char) * 32);
		if (!space) return 1;
		printf(": ");
		scanf("%s", space);

		if (!strcmp(space, "quit")) return 0;
		
		avl_insert(tree, space);
		avl_print(tree);
	}

	avl_print(tree);
	
}
