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


void filtr(int *vstup, int *stav, int *vystup){
    switch (*stav){
        case fs0:{
            if (*vstup == 1){
                *stav = fs1;
            }
            else{
                *stav = fs3;
            }
            *vystup = 0;           
            break;
        }   
        
        case fs1:{
            if (*vstup == 1){
                *stav = fs2;
            }
            else{
                *stav = fs3;
            }
            *vystup = 0;
            break;
        }    
        
        case fs2:{
            if (*vstup == 1){
                *stav = fs2;
                *vystup = 1;
            }
            else{
                *stav = fs3;
                *vystup = 0;                
            }
            break;
        }   
        
        case fs3:{
            if (*vstup == 1){
                *stav = fs1;
            }
            else{
                *stav = fs4;
            }
            *vystup = 0;            
            break;
        }
        
        case fs4:{
            if (*vstup == 1){
                *stav = fs1;                
            }
            else{
                *stav = fs4;
                *vystup = 0;
            }
            break;
        }
    }
}
