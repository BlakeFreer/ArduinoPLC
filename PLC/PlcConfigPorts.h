// Read Tags.csv and create a C config header to initialize all of the port pins

#ifndef __AVR_ATmega328P__
#define  __AVR_ATmega328P__
#endif

#ifndef PLC_CONFIG_PORTS
#define PLC_CONFIG_PORTS

#include<avr/io.h>
#include<avr/interrupt.h>

void PlcConfigPorts() {
    // PORTB is DI with pullup resistors enabled
    PORTB = 0xFF;
    DDRB = 0x00;
    
    // PORTD is DO
    DDRD = 0xFF;
}

#endif