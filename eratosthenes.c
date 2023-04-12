// eratosthenes.c
// Řešení IJC-DU1, příklad a) 23.2.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "eratosthenes.h"
#include <math.h>

/*
* Implementace Eratosthenesova síta.
*/
void Eratosthenes(bitset_t *arr){
    bitset_setbit(arr, 0, 1);
    bitset_setbit(arr, 1, 1);
    bitset_index_t max_num = bitset_size(arr);
    bitset_index_t sqrt_max_num = sqrt(max_num);

    for(bitset_index_t i = 2; i <= sqrt_max_num; i++){
        if(!bitset_getbit(arr, i)){
            for(bitset_index_t j = 2; i*j < max_num; j++){
                bitset_setbit(arr, i*j, 1);
            }
        } 
    }
}