// error.c
// Řešení IJC-DU1, příklad b) 24.2.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#include "error.h"

/*
* Implementace chybových hlášení.
*/
void warning(const char *fmt, ...){
    va_list(args);
    va_start(args, fmt);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ...){
    va_list(args);
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}