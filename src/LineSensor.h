#include <avr/interrupt.h> 
#include <avr/io.h>

extern uint8_t IR[5];
extern uint8_t MUXSELECTOR;
ISR(ADC_vect);
void ADC_init();
