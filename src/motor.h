#include <avr/interrupt.h> 
#include <avr/io.h>


ISR(TIMER1_COMPA_vect);
void motor_init();