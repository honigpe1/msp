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

void aretace(int *vstup, int *stav, int *vystup) {
    switch (*stav){
        case as0:{
            if (*vstup == 1){
                *stav = as1;
                *vystup = 1;
            }           
            break;
        }   
        
        case as1:{
            if (*vstup == 0){
                *stav = as2;
            }
            
            break;
        }    
        
        case as2:{
            if (*vstup == 1){
                *stav = as3;
                *vystup = 0;
            }
            break;
        }   
        
        case as3:{
            if (*vstup == 0){
                *stav = as0;
            }
                        
            break;
        }
    }
}

