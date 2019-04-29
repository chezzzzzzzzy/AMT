/*
 * File:   clock_sandbox.c
 * Author: chester
 *
 * Created on April 29, 2019, 10:09 PM
 */


#include <xc.h>
#include "amt.h"
#include <stdio.h>

#pragma config XINST = OFF 
#pragma config FOSC = HS
#pragma config WDT = OFF

void main2(void) {
    int i;
    int count = 0,h=0,m=0,s=0;
    LCD8init();

    char buffer[8];
    TRISJ = 0x00;
    PORTJ = 0x00;
    T2CON = 0b01111111;     // pre-scalar = 16 post scalar = 16 TMR4 on
    PR2 = 243;
    PIR1bits.TMR2IF = 0;   // clear flag
    
    while(1) {
        while(PIR1bits.TMR2IF != 1);    // 10ms not up
        count++;
        
        
        if (count == 100) {
            
            s++;

            
            if (m == 60) {
                LCD8send(0x01, 0);
                h++;
                s = 0;
                m = 0;
            }
        

            if (s == 60) {
                LCD8send(0x01, 0);
                m++;
                s = 0;
            }
        
            
            
            PORTJbits.RJ0 = PORTJbits.RJ0 ^ 1;
            sprintf(buffer, "%d: %d: %d", h,m,s);
            LCD8send(0x80, 0);   // set LCD cursor at home position
            for (i = 0; buffer[i] != 0; i++) {
                LCD8send(buffer[i], 1);   // set LCD cursor at home position
            }
            
            count = 0;
        }
        PIR1bits.TMR2IF = 0;
    }
    
}
