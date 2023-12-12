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

int vstupS4, filtrS4, stav_tlacitkaS4;
int vstupS3, filtrS3, stav_tlacitkaS3;
int stav_aretaceS4, zaaretovane_tlacitkoS4;
int stav_aretaceS3, zaaretovane_tlacitkoS3;
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
      if(casove_preruseni == 1){ //filtr a aretace tlacitka
          vstupS4 = PORTJbits.RJ7;
          filtr(&vstupS4, &stav_tlacitkaS4, &filtrS4); //vyfiltrovani tlacitka S4
          aretace(&filtrS4, &stav_aretaceS4, &zaaretovane_tlacitkoS4);  //aretace tlacitka S4
          PORTDbits.RD7 = zaaretovane_tlacitkoS4; //zobrazeni vysledku aretace S4 na diodu 
          
          A = PORTJbits.RJ0; //nacteni a filtrace proudu A
          filtr(&A, &stav_filtru_A, &filtrA);          
          B = PORTJbits.RJ1;  //nacteni a filtrace proudu B
          filtr(&B, &stav_filtru_B, &filtrB);          
          PORTDbits.RD6 = filtrA;  //indikace na LED
          PORTDbits.RD5 = filtrB;  //indikace na LED
          
          smerOtaceniPocitadloHran(&filtrA, &filtrB, &stav_koderu, &pocet); //zjisteni smeru a pocet otocek
          if (pocet == 0){ //zobŕazeni minima
              PORTFbits.RF2 = 1;
          }
          else if (pocet == 255){ //zobrazeni maxima
              PORTFbits.RF1 = 1;
          }
          else{ //vypnuti indikace
              PORTFbits.RF2 = 0;
              PORTFbits.RF1 = 0;
          }
          
          vstupS3 = PORTJbits.RJ6;
          filtr(&vstupS3, &stav_tlacitkaS3, &filtrS3); //vyfiltrovani tlacitka S3
          aretace(&filtrS3, &stav_aretaceS3, &zaaretovane_tlacitkoS3);  //aretace tlacitka S3
          PORTDbits.RD4 = zaaretovane_tlacitkoS3;
                    
                    
          casove_preruseni = 0; //vynulovani indikace preruseni
      }
      
      if(ADhotovo == 1){ //zpracovani AD prevodniku
          if(ADprevod > 1000){ //horni omezeni AD prevodniku
              ADprevod = 1000;
          }
          else if(ADprevod < 50){ //spodni omezeni AD prevodniku
              ADprevod = 50;
          }
          ADprevod = ADprevod - 50;
          ADprevod = ADprevod * 255; //trojclenka
          ADprevod = ADprevod / 950;
          
          ADhotovo = 0; //vynulovani indikace
      }
      
      if (zaaretovane_tlacitkoS3 == 0){
          if (zaaretovane_tlacitkoS4 == 0){ //prepnuti mezi koderem a AD prevodnikem
            PORTH = pocet;  // koder
          }
          else if (zaaretovane_tlacitkoS4 == 1){
            PORTH = ADprevod; //AD prevodnik
          }
      }
      else if (zaaretovane_tlacitkoS3 == 1){
          PORTH = 0;
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
        
        if (citac_ms < 10){ //zjisteni 10ms pro AD prevodnik
            citac_ms = citac_ms + 1;
        }
        else if(citac_ms == 10){
            ADCON0bits.GO = 1;  //zapnuti AD prevodniku
            citac_ms = 0;            
        }
        casove_preruseni = 1; //indikace preruseni pro tlacitko a koder
    }
    
    if (PIR1bits.ADIF == 1){
        ADprevod = ADRESH;  //nacteni hodnoty z AD prevodniku
        ADprevod = ADprevod << 8;
        ADprevod = ADRESL + ADprevod;
        PIR1bits.ADIF = 0;  //vynulovani preruseni AD prevodniku
        ADhotovo = 1;  //AD prevod hotov
    }
        
}
//----------------------------------------------------------------------------