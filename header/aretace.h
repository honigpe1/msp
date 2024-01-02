/*
 * Soubor:      aretace.h
 * Autor:       Petr Honig
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

#include "./../header/strukturaZpracovani.h" // nahrani nove struktury
enum {as0, as1, as2, as3}; // ocislovani stavu


// Deklarace ukazkove funkce
void aretace(zpracovani *struktura);

#endif /* ARETACE_H */
