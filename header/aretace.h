/*
 * Soubor:      aretace.h
 * Autor:       VLOZTE_AUTORA
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

#ifndef _aretace_H
#define _aretace_H

#if defined(__XC)
#include <xc.h>      // Vtazeni obecneho soubory pro XC8
#include <stdint.h>  // Definice celociselnych promennych
#include <stdbool.h> // Definice logicke promenne false/true */
#else
#error "Invalid compiler selection"
#endif

enum {as0, as1, as2, as3};

// Deklarace ukazkove funkce
void aretace(int *vstup, int *stav, int *vystup);

#endif /* ARETACE_H */
