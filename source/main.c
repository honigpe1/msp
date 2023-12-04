/*
 * Soubor:      main.c
 * Autor:       VLOZTE_AUTORA
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

// Systemove hlavickove soubory:
// v pripade, ze je pouzit jako kompilator XC8 - include souboru
// pokud ne, vypise chybu

#if defined(__XC)
#include <stdbool.h> // Definice logicke promenne false/true */
#include <stdint.h>  // Definice celociselnych promennych
#include <xc.h>      // Vtazeni obecneho soubory pro XC8
#else
#error "Invalid compiler selection"
#endif

// Pripravena zakladni inicializace od k13114 pro PIC18F87J11
#include "./../header/preambleInitialization.h"

//----------------------------------------------------------------------------
/* ZDE ZACINA BLOK #include PRO VLASTNI HEADER SOUBORY */
#include "./../header/filtr.h"
#include "./../header/aretace.h"
#include "./../header/smerOtaceniPocitadloHran.h"

// #include "XXXXXX.h"

/* ZDE KONCI BLOK PRO #include PRO VLASTNI HEADER SOUBORY */
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
/* ZDE ZACINA BLOK PRO DEKLARACI VLASTNICH GLOBALNICH PROMENNYCH */
typedef struct{
    int vstup;
    int filtr;
    int stav;
}spinac;

int vstup, filtrovane_tlacitko_S4, stav_tlacitka;
int stav_aretace, zaaretovane_tlacitko;
int A, B, filtrA, filtrB, stav_koderu, stav, smer, pocet;
bool casove_preruseni;
// Priklad pro deklaraci promenne typu uint8_t, se jmenem a
// uint8_t x;

// Priklad pro deklaraci promenne typu uint8_t se jmenem XXX na adrese
// 0xA00 uint8_t XXX __at(0xA00);

/* ZDE KONCI BLOK PRO DEKLARACI VLASTNICH GLOBALNICH PROMENNYCH */
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
// hlavni program
void main(void)
{
  // Inizializacni cast pro zakladni funkci programu/procesoru
  preambleInitialization();
  
  // Inicializujte vlastni casti programu vlastnimi inicializacnimi funkcemi
  
  
  
  
  //TIMER0 init
  T0CON = 0;
  T0CONbits.PSA = 1; // vypnuta preddelicka
  TMR0H = 0xD8;
  TMR0L = 0xEF;
    
  
  T0CONbits.TMR0ON = 1; // zapnuti timeru
  

  // Interrupt init
  INTCON2 = 0;
  INTCONbits.TMR0IE = 1;
  
  T0CONbits.TMR0ON = 1;//zapnuti timeru
  
  INTCONbits.GIEL = 1;
  INTCONbits.GIEH = 1;

  // Zde v nekonecne smycce je beh programu na pozadi
  while (1)
  {
      if(casove_preruseni == 1){
          casove_preruseni = 0;             //filtr a aretace tlacitka
          vstup = PORTJbits.RJ7;
          filtr(&vstup, &stav_tlacitka, &filtrovane_tlacitko_S4);
          aretace(&filtrovane_tlacitko_S4, &stav_aretace, &zaaretovane_tlacitko);
          
          A = PORTJbits.RJ0;
          filtr(&A, &)
          B = PORTJbits.RJ1;
          smerOtaceniPocitadloHran(&A, &B, &stav_koderu, &smer, &pocet);
          
      }
      // Piste svuj kod pro program na pozadi
  }
}

//----------------------------------------------------------------------------
/* Sekce obsahujici obsluhu preruseni */

// Vyssi priorita preruseni
void __interrupt(high_priority) high_isr(void)
{

}

// Nizsi priorita preruseni
void __interrupt(low_priority) low_isr(void){
    if (INTCONbits.TMR0IF == 1){
        TMR0H = 0xD8;
        TMR0L = 0xEF;
        INTCONbits.TMR0IF = 0;
        
        casove_preruseni=1;
    }
        
}
//----------------------------------------------------------------------------