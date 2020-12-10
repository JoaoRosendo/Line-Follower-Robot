#include <avr/interrupt.h> 
#include <avr/io.h>

extern uint16_t IR[5];
extern uint16_t MUXSELECTOR;
extern uint16_t AVRG;

ISR(ADC_vect);
void ADC_init();
void AVRG_IR();