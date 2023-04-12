# Ondřej Novotný
LC_ALL = cs_CZ.utf8
Compiler = gcc
Flagy = -g -std=c11 -pedantic -Wall -Wextra -O2

.PHONY: all zip clean run

all: primes primes-i steg-decode

error.o: error.c error.h
	$(Compiler) $(Flagy) -c error.c -o error.o

bitset.o: bitset.c bitset.h
	$(Compiler) $(Flagy) -c bitset.c -o bitset.o

bitset-i.o: bitset.c bitset.h
	$(Compiler) -DINLINE_FUNKCE $(Flagy) -c bitset.c -o bitset-i.o

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
	$(Compiler) $(Flagy) -c eratosthenes.c -o eratosthenes.o

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h
	$(Compiler) -DINLINE_FUNKCE $(Flagy) -c eratosthenes.c -o eratosthenes-i.o

primes.o: primes.c bitset.h eratosthenes.h
	$(Compiler) $(Flagy) -c primes.c -o primes.o

primes-i.o: primes.c bitset.h eratosthenes.h
	$(Compiler) -DINLINE_FUNKCE $(Flagy) -c primes.c -o primes-i.o

steg-decode.o: steg-decode.c error.h bitset.h eratosthenes.h ppm.h 
	$(Compiler) $(Flagy) -fstack-protector -c steg-decode.c -o steg-decode.o -fstack-protector

#spustitelné binárky
primes: primes.o error.o bitset.o eratosthenes.o 
	$(Compiler) primes.o error.o bitset.o eratosthenes.o -o primes -lm

primes-i: primes-i.o error.o bitset-i.o eratosthenes-i.o 
	$(Compiler) primes-i.o error.o bitset-i.o eratosthenes-i.o $(Flagy) -o primes-i -lm

steg-decode: steg-decode.o error.o bitset.o eratosthenes.o ppm.o
	$(Compiler) steg-decode.o error.o bitset.o eratosthenes.o ppm.o $(Flagy) -o steg-decode -lm

#Final help

zip: 
	zip xnovot2p.zip *.c *.h makefile

clean:
	rm -f *.o primes primes-i steg-decode xnovot2p.zip

run: primes primes-i
	./primes
	./primes-i
	ulimit -s 16384 && ./primes
	ulimit -s 16384 && ./primes-i
	./steg-decode du1-obrazek.ppm