/*	Author: Charles Hong
 *  Partner(s) Name: N/A
 *	Lab Section: 022
 *	Assignment: Lab #8  Exercise #1
 *	Exercise Description: ADC onto 10 LEDs
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *  
 *  Demo Link: 
 */
#include <avr/io.h>

#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned short adc;
unsigned char tmpB,tmpD;
volatile unsigned char TimerFlag = 0; //TimerISR sets it to 1, programmer sets it to 0
unsigned long _avr_timer_M = 1; //start count from here, down to 0. Default 1ms
unsigned long _avr_timer_cntcurr = 0; //current internal count of 1ms ticks

void TimerOn() {
    TCCR1B = 0x0B;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1  = 0;
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;
}

void TimerOff() {
    TCCR1B = 0x00;
}

void TimerISR() {
    TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0) {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

void ADC_init() {
    ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
    //ADEN: setting this bit enables analog to digital conversion
    //ADSC: setting this bit starts the first conversion
    //ADATE:    setting this bit enables auto-triggering. Since we are
    //          in Free Running Mode, a new conversion will trigger 
    //          whenever the previous conversion completes.
}


void Tick() {
    adc = ADC;
    tmpB = (char)adc;
    tmpD = (char)(adc>>8);
    PORTB = tmpB;
    PORTD = tmpD;
}
int main(void) {
    DDRA = 0x00; PORTA = 0xFF; 
    DDRB = 0xFF; PORTB = 0x00; 
    DDRC = 0xFF; PORTC = 0x00; 
    DDRD = 0xFF; PORTD = 0x00; 
    TimerSet(100);
    TimerOn();
    ADC_init();
    adc=0;
    tmpB=tmpD=0;

    while (1) {
        Tick();
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}
