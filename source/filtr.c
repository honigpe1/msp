/*
 * Soubor:      filtr.c
 * Autor:       Petr Honig
 * Spolecnost:  CVUT-FEL-K13114
 *
 * Kompilator:  XC8-v2.36
 * Procesor:    PIC18F87J11
 */

//----------------------------------------------------------------------------
/* Hlavickove soubory*/
#include "./../header/filtr.h"


void filtr(zpracovani *struktura){
    switch (struktura->stav_filtru){
        case fs0:{
            if (struktura->vstup == 1){
                struktura->stav_filtru = fs1;
            }
            else{
                struktura->stav_filtru = fs3;
            }
            struktura->filtrovane = 0;           
            break;
        }   
        
        case fs1:{
            if (struktura->vstup == 1){
                struktura->stav_filtru = fs2;
            }
            else{
                struktura->stav_filtru = fs3;
            }
            struktura->filtrovane = 0;
            break;
        }    
        
        case fs2:{
            if (struktura->vstup == 1){
                struktura->stav_filtru = fs2;
                struktura->filtrovane = 1;
            }
            else{
                struktura->stav_filtru = fs3;
                struktura->filtrovane = 0;                
            }
            break;
        }   
        
        case fs3:{
            if (struktura->vstup == 1){
                struktura->stav_filtru = fs1;
            }
            else{
                struktura->stav_filtru = fs4;
            }
            struktura->filtrovane = 0;            
            break;
        }
        
        case fs4:{
            if (struktura->vstup == 1){
                struktura->stav_filtru = fs1;                
            }
            else{
                struktura->stav_filtru = fs4;
                struktura->filtrovane = 0;
            }
            break;
        }
    }
}
