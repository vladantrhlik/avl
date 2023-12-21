#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "avl_print.h"

#define MAX_NODE_LEN 6

int str_comparator(void *a, void *b) {
	return strcmp(a, b);
}

void str_print(void *a) {
	printf("%s", (char *) a);
}

int int_comparator(void *a, void *b) {
	return *((int *) a) - *((int *) b);
}	

char *itostr(void *a) {
	char *out = malloc(MAX_NODE_LEN * sizeof(char));
	sprintf(out, "%d", *((int*) a));
	return out;
}

void int_free(void *a) {
	free(a);
}

int main(int argc, char *argv[]) {
	/*
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
	*/

	avl_tree *tree = avl_init(&int_comparator, &int_free, &itostr);

	for (int i = 0; i<20; i++) {
		int *d = malloc(sizeof(int));
		*d = rand()%100;
		avl_insert(tree, d);
	}
	avl_print(tree);
	printf("\n");
	avl_cool_print(tree);
	
}
