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

void aretace(zpracovani *struktura) {
    switch (struktura->stav_aretace){
        case as0:{
            if (struktura->filtrovane == 1){
                struktura->stav_aretace = as1;
                struktura->zaaretovane = 1;
            }           
            break;
        }   
        
        case as1:{
            if (struktura->filtrovane == 0){
                struktura->stav_aretace = as2;
            }
            
            break;
        }    
        
        case as2:{
            if (struktura->filtrovane == 1){
                struktura->stav_aretace = as3;
                struktura->zaaretovane = 0;
            }
            break;
        }   
        
        case as3:{
            if (struktura->filtrovane == 0){
                struktura->stav_aretace = as0;
            }
                        
            break;
        }
    }
}

