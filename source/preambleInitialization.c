/* 
 * Soubor:      preambleInitialization.c
 * Autor:       VLOZTE_AUTORA
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */


// Je treba pro include pouzit VLASTNI CESTU k souboru
// Linter a a LSP (Language Server Protocol)
#include "./../header/preambleInitialization.h"

// Definice funkce pro automatickou inicializaci potrebnych registru aby fungovaly zakladni funkce a periferie procesoru
void preambleInitialization(void)
{

    /* O S C I L A T O R 
       Pro zvyseni 4x vnitrnich hodin je nutne:
        1.) Konfiguracni bit FOSC nastaven na HSPLL
        2.) Odblokovat PLL u hodin oscilatoru
     */
    
    // Pouzivat pouze primarni oscilator
    OSCCONbits.SCS = 0;

    OSCTUNEbits.PLLEN = 1;



    // Povoleni vysoke a nizke priority preruseni
    RCONbits.IPEN = 1;
}


// Volejte tuto funkci v main.c v pripade pozadavku na POVOLENI vysoke i nizke urovne preruseni
void enableAllInterrupts(void) {
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
}

// Volejte tuto funkci v main.c v pripade pozadavku na ZAKAZANI vysoke i nizke urovne preruseni
void disableAllInterrupts(void) {
    INTCONbits.GIEH = 0;
    INTCONbits.GIEL = 0;
}
