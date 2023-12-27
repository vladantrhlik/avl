#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_print.h"

#define TILE_WIDTH 6 /* total width of one item */
#define ITEM_WIDTH 3 /* width of item inside of tile */

void render_subtree(avl_tree *avl, node *n, int x, int y, int width, char **buffer) {
	/* render node */
	char *tilebuf = malloc(sizeof(char) * width);
	if (n) {
		char *str = avl->to_str(n->data, ITEM_WIDTH);
		int off = (width - ITEM_WIDTH) / 2;

		sprintf(tilebuf, "%*s%*s%*s", off, "", ITEM_WIDTH, str, off, "");
		free(str);

		if (n->left || n->right) {
			for (int i = 0; i<off/2; i++) {
				char c = i == off/2 - 1 ? '|' : '-';
				if (n->left) tilebuf[off-i-1] = c;
				if (n->right) tilebuf[off+ITEM_WIDTH+i] = c;
			}
			render_subtree(avl, n->left, x, y+1, width/2, buffer);
			render_subtree(avl, n->right, x+width/2, y+1, width/2, buffer);
		}
	} else {
		sprintf(tilebuf, "%*s", width, "");
	}
	/* copy tile buffer to main buffer */
	memcpy(&buffer[y][x], tilebuf, width);
	free(tilebuf);
}

void avl_cool_print(avl_tree *avl) {
	/* number of tiles in buffer */
	int height = avl->root->hsub + 1;
	int width = 1 << (height-1);

	char **buffer = malloc(height * sizeof(char *));
	for (int i = 0; i<height; i++) {
		buffer[i] = malloc(width * TILE_WIDTH * sizeof(char));
		memset(buffer[i], ' ', width*TILE_WIDTH);
	}

	render_subtree(avl, avl->root, 0, 0, width*TILE_WIDTH, buffer);

	/* print rendered tree */
	for (int y = 0; y<height; y++) {
		for (int x = 0; x<width*TILE_WIDTH; x++) {
	  		printf("%c", buffer[y][x]);
		}
		printf("\n");
		/* free buffer line */
		free(buffer[y]);
	}
	free(buffer);
	
}
