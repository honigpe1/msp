/*
 * Soubor:      strukturaZpracovani.h
 * Autor:       Petr Honig
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

#ifndef _strukturaZpracovani_H
#define _strukturaZpracovani_H

#if defined(__XC)
#include <xc.h>      // Vtazeni obecneho soubory pro XC8
#include <stdint.h>  // Definice celociselnych promennych
#include <stdbool.h> // Definice logicke promenne false/true */
#else
#error "Invalid compiler selection"
#endif

typedef struct{ //struktura pro filtr a aretaci
    int vstup;
    int filtrovane;
    int stav_filtru;
    int stav_aretace;
    int zaaretovane;
}zpracovani;

typedef struct{ //struktura pro koder
    int A;
    int B;
    int stav_koderu;
    int pocet;
}kvadraturni;

#endif /* strukturaZpracovani_H */
