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

char *itostr(void *a, int w) {
	char *out = malloc(MAX_NODE_LEN * sizeof(char));
	sprintf(out, "%0*d", w,*((int*) a));
	return out;
}

void int_free(void *a) {
	free(a);
}

int main(int argc, char *argv[]) {
	avl_tree *tree = avl_init(&int_comparator, &int_free, &itostr);

	for (int i = 0; i<20; i++) {
		int *d = malloc(sizeof(int));
		*d = rand()%1000;
		avl_insert(tree, d);
	}

	avl_print(tree);
	printf("\n");
	avl_cool_print(tree);

	avl_free(&tree);

	return 0;
}
