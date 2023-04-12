// steg-decode.c
// Řešení IJC-DU1, příklad b) 28.2.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.h"

/*
*   Tento kód je implementací programu "steg-decode", který slouží k dekódování zprávy skryté v obrázku ve formátu PPM pomocí techniky steganografie. 
*   Program nejprve načte obrázek ze vstupního souboru pomocí funkce "ppm_read" z knihovny "ppm.h" a alokuje paměť pro pole bitů reprezentujících prvočísla v daném rozsahu pomocí funkce "bitset_alloc" z knihovny "bitset.h". 
*   Poté spustí funkci "Eratosthenes" z knihovny "eratosthenes.h", která vyplní bitset hodnotami 0 a 1 podle toho, zda se index v bitsetu odpovídající číslu je prvočíslo nebo ne.
*   Následně program projde bitset a pro každé prvočíslo v rozmezí od PRIME_START do velikosti bitsetu (3x šířka obrázku x výška obrázku) zkontroluje, zda je dané prvočíslo v bitsetu 
*   označeno jako prvočíslo (tj. zda je na dané pozici v bitsetu hodnota 0). Pokud ano, program z bitu na stejné pozici v poli obrazku->data extrahuje jeden nejméně 
*   významný bit a přidá ho do proměnné "znak" na pozici určené proměnnou "lsb_count". Pokud "lsb_count" dosáhne hodnoty 8, program vytiskne znak odpovídající hodnotě proměnné "znak", resetuje "lsb_count" a 
*   pokud byl právě vytisknutý znak nulový znak, skončí iteraci a dekódování je dokončeno. Pokud "lsb_count" není 8 na konci cyklu, program skončí s chybovým kódem.
*/



#define PRIME_START 101

int main(int argc, char *argv[]) {
    if (argc != 2) error_exit("steg-decode: Chybný počet argumentů! %d", argc);

    struct ppm *obrazek = ppm_read(argv[1]);
    if (obrazek == NULL) error_exit("steg-decode: ppm_read vrátil chybu\n", 0);

    bitset_index_t velikost = 3 * obrazek->xsize * obrazek->ysize;
    bitset_alloc(primes, velikost);
    Eratosthenes(primes);

    int znak = 0;
    int lsb_count = 0;

    for (size_t i = PRIME_START; i < velikost; i++) {
        if (bitset_getbit(primes, i) == 0) {
            int bit = obrazek->data[i] & 1;
            znak |= bit << lsb_count;
            lsb_count++;
        }
        if (lsb_count == 8) {
            printf("%c", znak);
            lsb_count = 0;
            if (znak == '\0') {
                break;
            }
            znak = 0;
        }
    }

    if (lsb_count != 0) {
        error_exit("steg-decode: Zpráva není korektně ukončena.'\0'\n", 0);
    }

    printf("\n");

    ppm_free(obrazek);
    bitset_free(primes);

    return 0;
}
