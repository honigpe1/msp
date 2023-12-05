/*
 * Soubor:      smerOtaceniPocitadloHran.c
 * Autor:       VLOZTE_AUTORA
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

//----------------------------------------------------------------------------
/* Hlavickove soubory*/
#include "./../header/smerOtaceniPocitadloHran.h"

void smerOtaceniPocitadloHran(int *A, int *B, int *stav, int *pocet){
    switch (*stav){
        case ks0:{
            if (*A == 1 && *B==0){
                if (*pocet == 255){
                    *pocet=255;
                }
                else{
                    *pocet = *pocet +1;
                }
                *stav = ks1;
            }
            else if (*A == 0 && *B==1){
                if (*pocet == 0){
                    *pocet=0;
                }
                else{
                    *pocet = *pocet - 1;
                }
                *stav = ks3;
            }        
            break;
        }   
        
        case ks1:{
            if (*A == 1 && *B==1){
                *stav = ks2;
            }
            else if (*A == 0 && *B==0){
               *stav = ks0;
            }
            break;
        }
        
        case ks2:{
            if (*A == 0 && *B==1){
                *stav = ks3;
            }
            else if (*A == 1 && *B==0){
                *stav = ks1;
            }         
            break;
        }   
        
        case ks3:{
            if (*A == 0 && *B==0){
                *stav = ks0;
            }
            else if (*A == 1 && *B==1){
               *stav = ks2;
            }
            break;
        }
    }    
}

