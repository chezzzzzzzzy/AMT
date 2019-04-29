/*
 * File:   interrupt_sandbox.c
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

int loopCounter = 0;

void interrupt HighIsr (void){  //High priority interrupt
    loopCounter++;  //increment loopCounter by 1 every 10ms
    PIR1bits.TMR2IF = 0;
}

void interrupt low_priority LowIsr(void){   //Low priority interrupt
    loopCounter += 10;
    PIR1bits.TMR2IF = 0;
}

void main(void) {
    int count = 0;
    char buffer[20];
    int h = 0, m = 59, s = 50;
    LCD8init();
    TRISJ = 0x00;
    PORTJ = 0x00;
    T2CON = 0b01111111; //Prescaler = 16 Postscaler = 16 TMR2 on
    PR2 = 243;
    PIR1bits.TMR2IF = 0;    //Clear flag
    T2intr();
    LCD8send(0x01, 0);
    
    while(1){
        //while(PIR1bits.TMR2IF == 0);    //10ms not up, wait for flag to go up (10ms)
        //count++;  //loopcounter ^
        if(loopCounter >= 100){     //replace count 
            LCD8send(0x80, 0);  //move to first row
            s++;
            if (s == 60){
                //LCD8send(0x01, 0);
                m++;
                s = 0;
            }
            if (m == 60){
                //LCD8send(0x01, 0);
                h++;
                m = 0;
                s = 0;
            }
            sprintf(buffer, "%02d : %02d : %02d" , h, m, s);      //sprintf(buffer, "Time: %02d:%02d" , sec/60, sec%60);
            for (int i = 0; buffer[i] != 0; i++){  //when buffer[] is null char, stop
                LCD8send(buffer[i], 1);
            }
            //count = 0;
            loopCounter = 0;
        }
        //PIR1bits.TMR2IF = 0;    //Clear flag
    }
    return;
}