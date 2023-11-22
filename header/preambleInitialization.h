/* 
 * Soubor:      preambleInitialization.h
 * Autor:       VLOZTE_AUTORA
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

#ifndef _preambleInitialization_H
#define	_preambleInitialization_H

#if defined(__XC)
    #include <xc.h>             // Vtazeni obecneho soubory pro XC8
    #include <stdint.h>         // Definice celociselnych promennych
    #include <stdbool.h>        // Definice logicke promenne false/true */
    
#else
#error "Invalid compiler selection"
#endif

// Volba oscilatoru
#pragma config FOSC = HSPLL

// Dva oscilatory jsou pouzity
#pragma config IESO = OFF

/* Monitor systemovych hodin */
#pragma config FCMEN = OFF

// Zakladni mod procesoru, pouze vnitrni pamet
#pragma config MODE = MM

// Rozsirena instrukcni sada a indexove adresovani
#pragma config XINST = OFF

// Pri preteceni nebo podteceni zasobniku generovat RESET
#pragma config STVREN = ON

// Watchdog timer
#pragma config WDTEN = OFF

// Preddelicka pro Watchdog timer
#pragma config WDTPS = 32768

// Zamek na pamet programu
#pragma config CP0 = OFF


// Deklarace funkci pro reseni preruseni - specificke pro XC8 kompiler

// Vyssi priorita preruseni
void __interrupt(high_priority) high_isr(void);

// Nizsi priorita preruseni
void __interrupt(low_priority) low_isr(void);


// Deklarace funkce pro povoleni vsech preruseni
void enableAllInterrupts(void);

// Deklarace funkce pro zakazani vsech preruseni
void disableAllInterrupts(void);

// Deklarace funkce pro automatickou inicializaci potrebnych registru aby fungovaly zakladni funkce a periferie procesoru
void preambleInitialization(void);

#endif

