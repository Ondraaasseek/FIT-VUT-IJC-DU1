// primes.c
// Řešení IJC-DU1, příklad a) 23.2.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0


/*
*   Tento kód implementuje program pro nalezení prvních 10 prvočísel s použitím Eratosthenova síta.
*   Nejprve se načte aktuální čas pomocí funkce clock(), aby se později mohl vypočítat celkový čas běhu programu.
*   Pak se alokuje pole bitů o velikosti MAX pomocí funkce bitset_alloc().
*   Funkce Eratosthenes() je pak použita pro výpočet všech prvočísel v daném rozsahu.
*   Následně je vytvořeno pole "primes" s kapacitou 10 prvků, které bude obsahovat nalezených 10 prvočísel.
*   Cyklus "for" prochází "bitset" od nejvyššího indexu (což odpovídá nejmenšímu číslu v rozsahu) a přidává prvočísla do pole "primes". Jakmile je nalezeno 10 prvočísel, cyklus končí.
*   Nakonec jsou nalezená prvočísla vypisována v pořadí od nejmenšího po největší.
*   Po dokončení výpočtů se pole bitů uvolní pomocí funkce bitset_free() a celkový čas běhu programu a posledních 10 prvočisel se vypíše pomocí printf() na standardní výstup -stdout.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bitset.h" 
#include "eratosthenes.h"

#define MAX 230000000

int main(void){
    clock_t start = clock();

    bitset_alloc(arr, MAX);

    Eratosthenes(arr);

    bitset_t primes[10] = {0,};
    int pocet = 0;
    for (bitset_t i = bitset_size(arr) - 1; i > 0 && pocet < 10; i--) {
        if (!bitset_getbit(arr, i)) {
            primes[pocet] = i;
            pocet++;
        }
    }

    for (int i = 9; i >= 0; i--){
        printf("%ld\n",primes[i]);
    }

    bitset_free(arr);
    printf("Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}