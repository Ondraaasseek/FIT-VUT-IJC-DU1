// ppm.h
// Řešení IJC-DU1, příklad b) 28.2.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0


#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

struct ppm{
    unsigned xsize;
    unsigned ysize;
    char data[]; 
};

extern struct ppm *ppm_read(const char *filename);

extern void ppm_free(struct ppm *p);

#endif