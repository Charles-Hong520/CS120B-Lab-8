/*	Author: Charles Hong
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #8  Exercise #3
 *	Exercise Description: adc/2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *  
 *  Demo Link: https://drive.google.com/file/d/140uMSARA7LCiQqnIwFzgto23Mvkn8O8p/view?usp=sharing
 */
#include <avr/io.h>

#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned short x;
void ADC_init() {
    ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
    //ADEN: setting this bit enables analog to digital conversion
    //ADSC: setting this bit starts the first conversion
    //ADATE:    setting this bit enables auto-triggering. Since we are
    //          in Free Running Mode, a new conversion will trigger 
    //          whenever the previous conversion completes.
}



int main(void) {
    DDRA = 0x00; PORTA = 0xFF; 
    DDRB = 0xFF; PORTB = 0x00; 
    DDRC = 0xFF; PORTC = 0x00; 
    DDRD = 0x03; PORTD = 0x00;
    ADC_init();
    unsigned short max = 0x03FF; //Every bit.
    unsigned char tmpB = 0;
    unsigned short adc = 0;

    while (1) {
        adc=ADC;
        if(adc>=max/2) tmpB=0x01;
        else tmpB=0x00;
        PORTB=tmpB;
    }

    return 1;
}
