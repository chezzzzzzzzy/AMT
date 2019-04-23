/*
 * File:   lcd_sandbox.c
 * Author: chester
 *
 * Created on April 22, 2019, 1:46 PM
 */


#include <xc.h>
#include "amt.h"
#include <stdio.h>


#pragma config XINST = OFF 
#pragma config FOSC = HS
#pragma config WDT = OFF



void main(void) {
    
    char msg[] = "Hello ...";
    char buffer[16];
    
    int i;
    
    LCD8init();
   
    sprintf(buffer, "Data of i = %d" ,i );
    
    // find last character and terminate it
    for (i=0; buffer[i] != 0 ; i++ ) {
        LCD8send(buffer[i], 1);
    }
    
    i = 10;
    LCD8send(0x80, 0); // set cursor at row 1 position 1 - home position
            
   
    
    
}

