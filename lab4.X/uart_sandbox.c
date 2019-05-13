/*
 * File:   uart_sandbox.c
 * Author: chester
 *
 * Created on May 13, 2019, 1:51 PM
 */


#include <xc.h>
#include "amt.h"
#include <stdio.h>


#pragma config XINST = OFF 
#pragma config FOSC = HS
#pragma config WDT = OFF           



void main2(void) {
    
    uart_init();
    
    while(1) {
        uart_send_char('A');
        char message = "Hello World";
        for (int i = 0; i < sizeof(message); i++) {
            printf(i);
        }
        delay_ms(1000);

        
        
           
        
        
    }
    
   
    
}

