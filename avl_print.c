#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_print.h"

#define TILE 5

void render_subtree(avl_tree *avl, node *n, int x, int y, int width, char **buffer) {
	/* render node */
	char *tilebuf = malloc(sizeof(char) * width);
	if (n) {
		char *str = avl->to_str(n->data);
		int off = (width - TILE) / 2;

		sprintf(tilebuf, "%*s%*s%*s", off, "", TILE+1, str, off, "");
		//free(str);

		if (n->left || n->right) {
			for (int i = 1; i<off/2; i++) {
				char c = i == off/2 - 1 ? '|' : '-';
				if (n->left) tilebuf[off-i] = c;
				if (n->right) tilebuf[off+TILE+i] = c;
			}
			render_subtree(avl, n->left, x, y+1, width/2, buffer);
			render_subtree(avl, n->right, x+width/2, y+1, width/2, buffer);
		}
	} else {
		sprintf(tilebuf, "%*s", width, "");
	}
	/* copy tile buffer to main buffer */
	memcpy(&buffer[y][x], tilebuf, width);
	//free(tilebuf);
}

void avl_cool_print(avl_tree *avl) {
	/* number of tiles in buffer */
	int height = avl->root->hsub + 1;
	int width = 1 << (height-1);

	char **buffer = malloc(height * sizeof(char *));
	for (int i = 0; i<height; i++) {
		buffer[i] = malloc(width * TILE * sizeof(char));
		memset(buffer[i], ' ', width*TILE);
	}

	render_subtree(avl, avl->root, 0, 0, width*TILE, buffer);

	/* print rendered tree */
	for (int y = 0; y<height; y++) {
		for (int x = 0; x<width*TILE; x++) {
	  		printf("%c", buffer[y][x]);
		}
		printf("\n");
	}
	
}
