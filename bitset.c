// bitset.c
// Řešení IJC-DU1, příklad a) 23.2.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "bitset.h"

#ifdef INLINE_FUNKCE

/**
* In-line funkce 
*/


extern inline void bitset_free(bitset_t *jmeno_pole){
    free(jmeno_pole);
}

extern inline bitset_t bitset_size(bitset_t *jmeno_pole){
    return jmeno_pole[0];
}

extern inline void bitset_setbit(bitset_t *jmeno_pole, bitset_index_t index, bool vyraz) {
    if (index >= bitset_size(jmeno_pole)) {
        error_exit("bitset_setbit: Index %lu mimo rozsah\n", (bitset_t)index);
    }
    bitset_t mask = (bitset_t)1UL << (index % U_LONG_SIZE_MAX);
    bitset_t *slot = jmeno_pole + (index / U_LONG_SIZE_MAX) + 1;
    if (vyraz) {
        *slot |= mask;
    } else {
        *slot &= ~mask;
    }
}

extern inline bool bitset_getbit(bitset_t *jmeno_pole, bitset_index_t index){
    if ((bitset_size((jmeno_pole))) < (index))
        error_exit("bitset_setbit: Index %lu mimo rozsah.",(bitset_t)(index));
    return ((jmeno_pole)[((index)/U_LONG_SIZE_MAX)+1] & ((bitset_t)1UL << ((index)%U_LONG_SIZE_MAX)));
}

#endif