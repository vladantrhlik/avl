#include <stdio.h>
#include <string.h>
#include "avl.h"

int str_comparator(void *a, void *b) {
	return strcmp(a, b);
}

int main(int argc, char *argv[]) {
	avl_tree *tree = avl_init(&str_comparator);

	char *names[] = {
		"Hozna",
		"Verča",
		"Hanka",
		"Antonín",
		"Vladan",
		"Olín",
		"Adam",
		"Ahoj",
		"Aboj",
		"Acoj"
	};
	int n = 10;
	for (int i = 0; i<n; i++) {
		avl_insert(tree, names[i]);
	}

	avl_print(tree);
	
}
