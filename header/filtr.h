/*
 * Soubor:      filtr.h
 * Autor:       Petr Honig
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

#ifndef _filtr_H
#define _filtr_H

#if defined(__XC)
#include <xc.h>      // Vtazeni obecneho soubory pro XC8
#include <stdint.h>  // Definice celociselnych promennych
#include <stdbool.h> // Definice logicke promenne false/true */
#else
#error "Invalid compiler selection"
#endif

#include "./../header/strukturaZpracovani.h" // nahrani nove struktury
enum {fs0, fs1, fs2, fs3, fs4}; // ocislovani stavu


// Deklarace funkce
void filtr(zpracovani *struktura);

#endif /* _FILTR_H */
