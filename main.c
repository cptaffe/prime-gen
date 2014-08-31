#include <stdio.h>

#import "block-list.c"
#import "prime-gen.c"

#define MEGABYTE 1048576 // IEC mebibyte, JEDEC megabyte

int bl_prime_gen(block_list *bl, int n, const size_t mem_size) {
	// generate primes
	int *prime = malloc(mem_size * sizeof (int));
	if (prime == NULL){return 1;}

	int iter = n / (mem_size - 1);
	int max, min;

	if (iter > 0) {max = (mem_size - 1); min = 0;}
	else {max = n; min = 0;}

	for (int j = 0; j <= iter; j++) {
		prime_gen(prime, max, min);

		for (int i = 0; i < (max - min); i++) {
			if (prime[i] == 1) {
				block_list *ret  = bl_push_int(bl, i + min);
				if (ret == NULL) {
					// append new block
					block_list *n_bl = bl_init(bl->size);
					if (n_bl == NULL) {return 1;} // malloc error
					bl->next = n_bl;
					bl = n_bl;
					i--;
				}
			}
		}
		min = max; max += (mem_size - 1);
		if (max > n) {
			if (min >= n){break;}
			max = n;
		}
	}
	return 0;
}

int main() {
	const size_t mem_size = MEGABYTE;
	size_t block_size = (512 * mem_size);
	block_list *bl = bl_init(sizeof (int) * block_size);
	if (bl == NULL){fprintf(stderr, "main: Memory allocation failure.\n"); return 1;}
	// TODO: implement resizing (appending and shrinking) of linked-blocks.
	int prime_max = 2000000000;
	if (bl_prime_gen(bl, prime_max, block_size)) {fprintf(stderr, "bl_prime_gen: Memory allocation failure.\n"); return 1;}
	bl_print_int(bl);
}