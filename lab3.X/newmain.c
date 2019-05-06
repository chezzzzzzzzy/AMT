/*
 * File:   newmain.c
 * Author: chester
 *
 * Created on May 6, 2019, 2:20 PM
 */

#include <xc.h>
#include "amt.h"
#include <stdio.h>

#pragma config XINST = OFF
#pragma config FOSC = HS
#pragma config WDT = OFF 

void main(void) {
    
    char Code[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    char Acode[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    
    char key;
    char msg[] = "Hello world";
    
    int i;
    
    
    SPI1init();
    KeyPadinit();
    SPI_LCD4init();
    
//    SPI1out(0b01101101);
    
//    while(1) {
        
        for (i = 0; msg[i] != 0; i++) {
            SPI_LCD4send(msg[i], 1);

        }
        while(1);
        
        
        
//    }
    
    while(1) {
        key = Read_KeyPad();
        if (key != 0xFF) {
            SPI_LCD4send(0xC5, 0);
            SPI_LCD4send(Acode[key], 1);

            // key pressed
            SPI1out(Code[key]);
            delay_ms(100);
            
        }
    }
    
    
    
    
}
