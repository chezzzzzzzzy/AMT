/*
 * File:   segment_sandbox.c
 * Author: chester
 *
 * Created on May 6, 2019, 10:49 PM
 */


#include <xc.h>
#include "amt.h"
#include <stdio.h>

#pragma config XINST = OFF
#pragma config FOSC = HS
#pragma config WDT = OFF 

void main2(void) {
    
    char Code[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    char key;
    
    int i;
    
    
    SPI1init();
    KeyPadinit();
    
    
    while(1) {
        key = Read_KeyPad();
        if (key != 0xFF) {
            // key pressed
            SPI1out(Code[key]);
        }
    }
    
    
    
    
}


