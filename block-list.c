#include <stdlib.h>
#include <stdio.h>

// block based linked-list
typedef struct {
	void *mem;
	size_t size;
	size_t len;
	void *next;
} block_list;

// returns an initialized block
block_list *bl_init(size_t size) {
	block_list *blp = (block_list *) malloc(sizeof (block_list));
	if (blp == NULL){return NULL;}
	blp->mem = malloc(size);
	if (blp->mem == NULL){return NULL;}
	blp->size = size;
	blp->len = (size_t) 0;
	blp->next = NULL; // no next pointer yet.
	return blp;
}

// concatenates two blocks
block_list *bl_concat(block_list *x, block_list *y) {
	x->next = y;
	return x;
}

// INTEGER SPECIFIC

// pushes int to a block, returns NULL if out of space
block_list *bl_push_int(block_list *bl, int n) {
	//printf("pushing %d to %p!\n", n, &((int *) bl->mem)[bl->len / sizeof (int)]);
	if ((bl->len + sizeof (int)) > bl->size) {
		return NULL;
	} else {
		((int *) bl->mem)[bl->len / sizeof (int)] = n;
		bl->len += sizeof (int);
		return bl;
	}
}

// print int
void bl_print_int(block_list *bl) {
	int blocks = 0;
	while (bl != NULL) {
		for (int i = 0; i < (bl->len / sizeof (int)); i++) {
			printf("%d, ", ((int *) bl->mem)[i]);
		}
		bl = (block_list *) bl->next; blocks++;
	}
	printf("\n");
	fprintf(stderr, "blocks: %d\n", blocks);
}