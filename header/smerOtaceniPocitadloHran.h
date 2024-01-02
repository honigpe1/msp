/*
 * Soubor:      smerOtaceniPocitadloHran.h
 * Autor:       VLOZTE_AUTORA
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

#ifndef _smerOtaceniPocitadloHran_H
#define _smerOtaceniPocitadloHran_H

#if defined(__XC)
#include <xc.h>      // Vtazeni obecneho soubory pro XC8
#include <stdint.h>  // Definice celociselnych promennych
#include <stdbool.h> // Definice logicke promenne false/true */
#else
#error "Invalid compiler selection"
#endif

#include "./../header/strukturaZpracovani.h" // nahrani nove struktury
enum {ks0,ks1,ks2,ks3}; //ocislovani stavu

void smerOtaceniPocitadloHran(kvadraturni *koder);

#endif /* _SMEROTACENIPOCITADLOHRAN_H */
