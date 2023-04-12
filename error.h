// error.h
// Řešení IJC-DU1, příklad b) 24.2.2023
// Autor: Ondřej Novotný (xnovot2p)
// Přeloženo: gcc 9.4.0

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

extern void warning(const char *fmt, ...);

extern void error_exit(const char *fmt, ...);

#endif

