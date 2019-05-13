/*
 * File:   rfid_sandbox.c
 * Author: chester
 *
 * Created on May 13, 2019, 3:32 PM
 */

#include <xc.h>
#include "amt.h"
#include <String.h>

#include <stdio.h>


#pragma config XINST = OFF 
#pragma config FOSC = HS
#pragma config WDT = OFF           



void main(void) {
    
    uart_init();
    clr_screen();
    delay_ms(50);
    
    char msg[] = "Authorized...";
    unsigned char data[11], temp;
    unsigned char ID1[] = "6A00148410";
    int i;
    
    while(1) {
        
        while (PIR1bits.RCIF == 0); 
           
        temp = RCREG;
        if (temp = 0x02) {
            for (i = 0; i<10; i++) {
                while(PIR1bits.RCIF == 0);
                data[i] = RCREG;
            }
            
        }
        data[10] = 0;                       // change data into string
        
        for (i = 0; i<5; i++) {
            while(PIR1bits.RCIF == 0);
            
            temp = RCREG;

        }
        
        for (i=0; i<10; i++) uart_send_char(data[i]);
        if (strcmp(data, ID1) == 0) {
            
            // authorized
            for (i=0; msg[i] != 0; i++) {
                uart_send_char(msg[i]);
                
            }
            
   
        }
         
    }
    
    
    
   
    
}
