CFLAGS=-O3 -std=c11 -lm
CC=clang

primes:
	$(CC) $(CFLAGS) main.c -o primes

clean:
	rm primes