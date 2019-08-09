/*
 * File:   sample.c
 * Author: chester
 *
 * Created on July 1, 2019, 3:23 PM
 */



#include <xc.h>
#include "amt.h"

#pragma config XINST = OFF
#pragma config FOSC = HS
#pragma config WDT = OFF 


void main(void) {
    
    SPI1init();   
    SPI1out(0x00);
    delay_ms(10);
    
       
    int i;
    LCD8init();
    
//
//    while(1) {
//        // display 1
//        SPI1out(0b00000110);
//        delay_ms(1000);
//
//        // display 2
//        SPI1out(0b01011011);
//        delay_ms(1000);
//
//        // display 3
//        SPI1out(0b01001111);
//        delay_ms(1000);
//    }
    

    
//    while(1) {
//         if (PORTBbits.RB0 == 0) {
//        
//        SPI1out(0b01110111);
//        delay_ms(10);
//        }
//
//        if (PORTBbits.RB1 == 0) {
//
//            SPI1out(0b01111111);
//            delay_ms(10);
//        }
//
//         if (PORTBbits.RB2 == 0) {
//
//            SPI1out(0b00111001);
//            delay_ms(10);
//        }
//    }

    
  
    
   
    
//

    
    while(1) {
        
        if (PORTBbits.RB0 == 0) {
        
            SPI1out(0b11110111);
            LCD8send(0x01, 0);
            delay_ms(2000);
            LCD8send(0xC0, 0);

            char msg[] = "2 sec timeout";
                for (i = 0; msg[i] != 0; i++) {
                    LCD8send(msg[i], 1);

                }
            delay_ms(500);
            SPI1out(0b00000000);
            

            }
    
        if (PORTBbits.RB1 == 0) {

            SPI1out(0b11111111);
            LCD8send(0x01, 0);
            delay_ms(2000);
            LCD8send(0xC0, 0);

            char msg[] = "2 sec timeout";
            for (i = 0; msg[i] != 0; i++) {
                LCD8send(msg[i], 1);

            }
            delay_ms(500);
            SPI1out(0b00000000);



        }
    
        if (PORTBbits.RB2 == 0) {

            SPI1out(0b00111001);
            LCD8send(0x01, 0);
            delay_ms(2000);
            LCD8send(0xC0, 0);

           char msg[] = "2 sec timeout";
           for (i = 0; msg[i] != 0; i++) {
               LCD8send(msg[i], 1);

           }
           delay_ms(500);
           SPI1out(0b00000000);

       }
        
    }


    
 
    
    return;
}