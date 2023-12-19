#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int str_comparator(void *a, void *b) {
	return strcmp(a, b);
}

void str_print(void *a) {
	printf("%s", (char *) a);
}

int main(int argc, char *argv[]) {
	avl_tree *tree = avl_init(&str_comparator, NULL, str_print);

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
