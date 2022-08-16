// Blake Freer
// August 15, 2022

#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

// Digital points can be accessed directly from the input registers


#include<avr/io.h>
#include<avr/interrupt.h>

#include"PlcConfigPorts.h"

#define F_CPU   16000000            // clock speed
#define BAUD    9600                // baud
#define BRC     ((F_CPU/16/BAUD))   // baud calculation
#define TX_BUFFER_SIZE 128

#include<util/delay.h>

char serialBuffer[TX_BUFFER_SIZE];
uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;

void appendSerial(char c);
void serialWrite(char c[], uint8_t len);

int main (void) {

    PlcConfigPorts();

    // Set baud
    UBRR0H = (BRC >> 8);
    UBRR0L =  BRC;

    UCSR0B = (1 << TXEN0) | (1 << TXCIE0);  // enable transmit mode
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // set data frame t0 8 bits

    // sei();

    while(1) {
        if ((PINB>>PINB3)&1){
            UDR0='0';
        } else {
            UDR0='1';
        }
        _delay_ms(1000);
    }

    return 0;
}

// void appendSerial(char c){
//     // Add a character to the TX buffer
//     serialBuffer[serialWritePos++] = c;
//     serialWritePos %= TX_BUFFER_SIZE;
// }
// void serialWrite(char c[], uint8_t len){
//     for (uint8_t i = 0; i < len; i++) {
//         appendSerial(c[i]);
//     }
//     if(UCSR0A & (1 << UDRE0)){
//         UDR0 = 0;
//     }
    
// }

// ISR(USART_TX_vect){
//     if(serialReadPos != serialWritePos){
//         UDR0 = serialBuffer[serialReadPos++];
//         serialReadPos %= TX_BUFFER_SIZE;
//     }
// }

