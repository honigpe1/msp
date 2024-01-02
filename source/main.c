/*
 * Soubor:      main.c
 * Autor:       Petr Honig
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
#error "Invalid sumiler selection"
#endif

// Pripravena zakladni inicializace od k13114 pro PIC18F87J11
#include "./../header/preambleInitialization.h"

//----------------------------------------------------------------------------
/* ZDE ZACINA BLOK #include PRO VLASTNI HEADER SOUBORY */
#include "./../header/filtr.h"
#include "./../header/aretace.h"
#include "./../header/smerOtaceniPocitadloHran.h"
#include "./../header/strukturaZpracovani.h"

// #include "XXXXXX.h"

/* ZDE KONCI BLOK PRO #include PRO VLASTNI HEADER SOUBORY */
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
/* ZDE ZACINA BLOK PRO DEKLARACI VLASTNICH GLOBALNICH PROMENNYCH */

zpracovani S4;
zpracovani S3;
zpracovani stopa_A;
zpracovani stopa_B;

kvadraturni koder;

bool casove_preruseni;
int citac_ms, ADhotovo;
long ADprevod;
unsigned int sum, puls, puls_back, new_puls, mezera;

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

  //PWM
  sum = 50000;
  CCPR1H = (sum>>8);
  CCPR1L = (sum&0x00FF);
  
  
  // Zde v nekonecne smycce je beh programu na pozadi
  while (1)
  {
      if(casove_preruseni == 1){ //filtr a aretace tlacitka
          S4.vstup = PORTJbits.RJ7;
          filtr(&S4); //vyfiltrovani tlacitka S4
          aretace(&S4);  //aretace tlacitka S4
          PORTDbits.RD7 = S4.filtrovane; //zobrazeni vysledku aretace S4 na diodu 
          
          stopa_A.vstup = PORTJbits.RJ0; //nacteni a filtrace proudu A
          filtr(&stopa_A);          
          stopa_B.vstup = PORTJbits.RJ1;  //nacteni a filtrace proudu B
          filtr(&stopa_B);          
          PORTDbits.RD6 = stopa_A.filtrovane;  //indikace na LED
          PORTDbits.RD5 = stopa_B.filtrovane;  //indikace na LED
          
          koder.A = stopa_A.filtrovane;
          koder.B = stopa_B.filtrovane;
          
          smerOtaceniPocitadloHran(&koder); //zjisteni smeru a pocet otocek
          if (koder.pocet == 0){ //zobrazeni minima
              PORTFbits.RF2 = 1;
          }
          else if (koder.pocet == 255){ //zobrazeni maxima
              PORTFbits.RF1 = 1;
          }
          else{ //vypnuti indikace
              PORTFbits.RF2 = 0;
              PORTFbits.RF1 = 0;
          }
          
          
          S3.vstup = PORTJbits.RJ6;
          filtr(&S3); //vyfiltrovani tlacitka S3
          aretace(&S3);  //aretace tlacitka S3
          if (S3.zaaretovane == 1){
              PORTDbits.RD4 = 0;
          }
          else{
              PORTDbits.RD4 = 1;
          }
                    
                    
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
      
      if (S3.zaaretovane == 0){
          if (S4.zaaretovane == 0){ //prepnuti mezi koderem a AD prevodnikem
            PORTH = koder.pocet;  // koder
          }
          else if (S4.zaaretovane == 1){
            PORTH = ADprevod; //AD prevodnik
          }
      }
      else if (S3.zaaretovane == 1){ //vybrana PWM
          PORTH = 0;
      }
      
      if (S3.zaaretovane == 0){
          puls_back = (unsigned int) 10*LATH;
          if (puls_back > 2500){
              puls_back = 2500;
              }
      }
      else{
          puls_back = 0;
      }
      new_puls = 1;
      
  }
}

//----------------------------------------------------------------------------
/* Sekce obsahujici obsluhu preruseni */

// Vyssi priorita preruseni
void __interrupt(high_priority) high_isr(void)
{
    if (PIR1bits.CCP1IF == 1){ //PWM
		if (PORTCbits.RC2 == 1){
			CCP1CON = 0b00001001;
			sum = sum + puls;
		}
		else{
			CCP1CON = 0b00001000;
			sum = sum + mezera;

			if (new_puls){  
				puls = puls_back + 2500;
				mezera = 50000 - puls;
				new_puls = 0;
			}
		}
		PIR1bits.CCP1IF = 0;
        
		CCPR1H = (sum>>8);
		CCPR1L = (sum&0x00FF);


		}
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