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

void smerOtaceniPocitadloHran(kvadraturni *koder){
    switch (koder->stav_koderu){
        case ks0:{
            if (koder->A == 1 && koder->B==0){
                if (koder->pocet == 255){
                    koder->pocet=255;
                }
                else{
                    koder->pocet = koder->pocet +1;
                }
                koder->stav_koderu = ks1;
            }
            else if (koder->A == 0 && koder->B==1){
                if (koder->pocet == 0){
                    koder->pocet=0;
                }
                else{
                    koder->pocet = koder->pocet - 1;
                }
                koder->stav_koderu = ks3;
            }        
            break;
        }   
        
        case ks1:{
            if (koder->A == 1 && koder->B==1){
                koder->stav_koderu = ks2;
            }
            else if (koder->A == 0 && koder->B==0){
               koder->stav_koderu = ks0;
            }
            break;
        }
        
        case ks2:{
            if (koder->A == 0 && koder->B==1){
                koder->stav_koderu = ks3;
                if (koder->pocet == 255){
                    koder->pocet=255;
                }
                else{
                    koder->pocet = koder->pocet +1;
                }

            }
            else if (koder->A == 1 && koder->B==0){
                koder->stav_koderu = ks1;
                if (koder->pocet == 0){
                    koder->pocet=0;
                }
                else{
                    koder->pocet = koder->pocet - 1;
                }
            }         
            break;
        }   
        
        case ks3:{
            if (koder->A == 0 && koder->B==0){
                koder->stav_koderu = ks0;
            }
            else if (koder->A == 1 && koder->B==1){
               koder->stav_koderu = ks2;
            }
            break;
        }
    }    
}

