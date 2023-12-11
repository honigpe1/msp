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

int vstupS4, filtrS4, stav_tlacitka;
int stav_aretace, zaaretovane_tlacitko;
int A, B, filtrA, filtrB, stav_koderu, stav_filtru_A, stav_filtru_B, pocet;
bool casove_preruseni;
int citac_ms, ADhotovo;
long ADprevod;
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
  
  T0CONbits.TMR0ON = 1; //zapnuti timeru
  
  INTCONbits.GIEL = 1;
  INTCONbits.GIEH = 1;


  
  
  // Zde v nekonecne smycce je beh programu na pozadi
  while (1)
  {
      if(casove_preruseni == 1){
          casove_preruseni = 0; //filtr a aretace tlacitka
          vstupS4 = PORTJbits.RJ7;
          filtr(&vstupS4, &stav_tlacitka, &filtrS4);
          aretace(&filtrS4, &stav_aretace, &zaaretovane_tlacitko);
          PORTDbits.RD7 = zaaretovane_tlacitko;
          
          A = PORTJbits.RJ0;
          filtr(&A, &stav_filtru_A, &filtrA);
          B = PORTJbits.RJ1;
          filtr(&B, &stav_filtru_B, &filtrB);
          PORTDbits.RD6 = filtrA;
          PORTDbits.RD5 = filtrB;
          smerOtaceniPocitadloHran(&filtrA, &filtrB, &stav_koderu, &pocet);
          PORTH = pocet;
          if (pocet == 0){
              PORTFbits.RF2 = 1;
          }
          else if (pocet == 255){
              PORTFbits.RF1 = 1;
          }
          else{
              PORTFbits.RF2 = 0;
              PORTFbits.RF1 = 0;
          }
      }
      
      if(ADhotovo == 1){
          if(ADprevod > 1000){
              ADprevod = 1000;
          }
          else if(ADprevod < 50){
              ADprevod = 50;
          }
          ADprevod = ADprevod - 50;
          ADprevod = ADprevod * 255;
          ADprevod = ADprevod / 950;
          
          ADhotovo = 0;
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
        
        if (citac_ms < 10){
            citac_ms = citac_ms + 1;
        }
        else if(citac_ms == 10){
            ADCON0bits.GO = 1;
            citac_ms = 0;            
        }
        casove_preruseni = 1;
    }
    
    if (PIR1bits.ADIF == 1){
        /*ADprevod = 0b11111111;
        ADprevod = ADprevod << 8;
        */ //pokus rucne s posunem
        ADprevod = ADRESH;
        ADprevod = ADprevod << 8;
        ADprevod = ADRESL + ADprevod;
        PIR1bits.ADIF = 0;
        ADhotovo = 1;
    }
        
}
//----------------------------------------------------------------------------