/*
 * File:   keypad_sandbox.c
 * Author: chester
 *
 * Created on April 22, 2019, 2:34 PM
 */


#include <xc.h>
#include "amt.h"
#include <stdio.h>

#pragma config XINST = OFF 
#pragma config FOSC = HS
#pragma config WDT = OFF

void main2(void) {
    
    unsigned char key = 0xFF;
        
    LCD8init();
    KeyPadinit();
    
    while(1) {
        key = Read_KeyPad();
        
        if (key != 0xFF) {
            // key is pressed
            
            LCD8send(0x80, 0); // point cursor at home position
            
            if (key >= 0 && key < 10) LCD8send(key+0x30, 1);
            
            else if (key >=0 && key <14) LCD8send(key+0x41-10, 1);
            
            else if (key==14) LCD8send('*', 1);
            
            else LCD8send('#', 1);
            delay_ms(100);
            

            
        }
    }
    
    
    
}
