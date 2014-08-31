#include <math.h>

// super lame seive of atkin implementation
void prime_gen(int *sieve, int max, int min) {
	fprintf(stderr, "max: %d, min: %d, addr: %p\n", max, min, sieve);
	fflush(stdout);
	//Create the various different variables required
	int root = (int) ceil(sqrt((double) max));
	const int sieve_size = max - (min - 1);

	for (int i = 0; i < sieve_size; i++) {
		sieve[i] = 0;
	}

	for (int x = 1; x <= root; x++) {
		for (int y = 1; y <= root; y++) {
			int n = (4 * x * x) + (y * y);
			if (n <= max && n > min && (n % 12 == 1 || n % 12 == 5)) {
					sieve[n - min] ^= 1;
			}
			n = (3 * x * x) + (y * y);
			if (n <= max && n > min && n % 12 == 7) {
				if ((n-min) > 0 && (n-min) < (max - min)){
					sieve[n - min] ^= 1;
				}
			}
			n = (3 * x * x) - (y * y);
			if (x > y && n <= max && n > min && n % 12 == 11) {
					sieve[n - min] ^= 1;
			}
		}
	}

	//Mark all multiples of squares as non-prime
	for (int i = min; i <= root; i++) {
		if (sieve[i - min]) {
			for (int j = i * i; j < max; j += i * i) {
				sieve[j - min] = 0;
			}
		}
	}

	// account for 2 & 3
	if (min < 2 && 2 < max) {sieve[2 - min] = 1;}
	if (min < 3 && 3 < max) {sieve[3 - min] = 1;}
}