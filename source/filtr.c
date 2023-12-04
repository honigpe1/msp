/*
 * Soubor:      example.c
 * Autor:       VLOZTE_AUTORA
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

//----------------------------------------------------------------------------
/* Hlavickove soubory*/
#include "./../header/filtr.h"


void filtr(Spinac *struktura){
    switch (struktura->stav){
        case s0:{
            if (struktura->vstup == 1){
                struktura->stav = s1;
            }
            else{
                struktura->stav = s3;
            }
            struktura->filtr = 0;           
            break;
        }   
        
        case s1:{
            if (struktura->vstup == 1){
                struktura->stav = s2;
            }
            else{
                struktura->stav = s3;
            }
            struktura->filtr = 0;
            break;
        }    
        
        case s2:{
            if (struktura->vstup == 1){
                struktura->stav = s2;
                struktura->filtr = 1;
            }
            else{
                struktura->stav = s3;
                struktura->filtr = 0;                
            }
            break;
        }   
        
        case s3:{
            if (struktura->vstup == 1){
                struktura->stav = s1;
            }
            else{
                struktura->stav = s4;
            }
            struktura->filtr = 0;            
            break;
        }
        
        case s4:{
            if (struktura->vstup == 1){
                struktura->stav = s1;                
            }
            else{
                struktura->stav = s4;
                struktura->filtr = 0;
            }
            break;
        }
    }
}
