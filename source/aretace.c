/*
 * Soubor:      aretace.c
 * Autor:       Petr Honig
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

//----------------------------------------------------------------------------
/* Hlavickove soubory*/
#include "./../header/aretace.h"

void aretace(Spinac *struktura, int *stav, int *vystup) {
    switch (*stav){
        case s0:{
            if (struktura->filtr == 1){
                *stav = s1;
                *vystup = 1;
            }           
            break;
        }   
        
        case s1:{
            if (struktura->filtr == 0){
                *stav = s2;
            }
            
            break;
        }    
        
        case s2:{
            if (struktura->filtr == 1){
                *stav = s3;
                *vystup = 0;
            }
            break;
        }   
        
        case s3:{
            if (struktura->filtr == 0){
                *stav = s0;
            }
                        
            break;
        }
    }
}

