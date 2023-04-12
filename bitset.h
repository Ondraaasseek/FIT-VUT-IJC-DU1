// bitset.h
// Řešení IJC-DU1, příklad a) 21.2.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0
// Bez -O2 Zlobí a nevím proč.
 
#ifndef BITSET_H
#define BITSET_H

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#include "error.h"

typedef unsigned long bitset_t;
typedef unsigned long bitset_index_t;

/*
Podpůrná makra
*/

//Zjištění velikosti unsigned longu.
#define U_LONG_SIZE_MAX (sizeof(bitset_t)*(__CHAR_BIT__))

//Zjistění výsledku zbytku po dělení
#define NEEDED_SIZE(velikost) (velikost%U_LONG_SIZE_MAX)? (1):(0)

//Výpočet potřebné velikosti pole
#define VELIKOST_ARR(velikost) ((velikost / (U_LONG_SIZE_MAX)) + (NEEDED_SIZE(velikost)) + 1)

// Ostatní Makra

//Vytvoření bitset pole na základě velikosti
#define bitset_create(jmeno_pole, velikost) \
    do { \
        static_assert((UINT_FAST64_MAX > (bitset_t)(velikost)), "bitset_create: Selhání alokace paměti"); \
        static_assert((0 < (velikost)), "bitset_create: Chyba překladu"); \
        const size_t bitset_size = VELIKOST_ARR((velikost)); \
        bitset_t (jmeno_pole)[bitset_size] = { [0] = (velikost) }; \
        memset(&(jmeno_pole)[1], 0, (bitset_size - 1) * sizeof(bitset_t)); \
    } while (0)

//Alokace bitset pole na základě velikosti
#define bitset_alloc(jmeno_pole, velikost) \
    assert(UINT_FAST64_MAX > (bitset_t)(velikost)); \
    assert(0 < (velikost)); \
    bitset_t *(jmeno_pole) = (bitset_t*)calloc(VELIKOST_ARR((velikost)), sizeof(bitset_t)); \
    if(!(jmeno_pole)){ \
         error_exit("bitset_alloc: Selhání alokace paměti",0); \
    } \
    (jmeno_pole)[0] = (velikost) \

// inline funkce
#ifndef INLINE_FUNKCE

#define bitset_free(jmeno_pole) free((jmeno_pole))

#define bitset_size(jmeno_pole) ((jmeno_pole)[0]) 

#define bitset_setbit(jmeno_pole, index, vyraz) do {\
        bitset_index_t __index = (index);\
        if (__index >= bitset_size(jmeno_pole))\
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", __index, (bitset_t)bitset_size((jmeno_pole)));\
        bitset_t* __p = (jmeno_pole) + (__index / U_LONG_SIZE_MAX) + 1;\
        bitset_index_t __bit_offset = __index % U_LONG_SIZE_MAX;\
        if (vyraz)\
            *__p |= (1UL << __bit_offset);\
        else\
            *__p &= ~(1UL << __bit_offset);\
    } while(0)


#define bitset_getbit(jmeno_pole, index) (((jmeno_pole)[((index) / U_LONG_SIZE_MAX) + 1] >> ((index) % U_LONG_SIZE_MAX)) & 1)



#else
/*
Inline funkce extern
*/
extern void bitset_free(bitset_t *jmeno_pole);

extern bitset_t bitset_size(bitset_t *jmeno_pole);

extern void bitset_setbit(bitset_t *jmeno_pole, bitset_index_t index, bool vyraz);

extern bool bitset_getbit(bitset_t *jmeno_pole, bitset_index_t index);

#endif //INLINE_FUNKCE

#endif //BITSET_H