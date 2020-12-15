#include <avr/interrupt.h> 
#include <avr/io.h>


ISR(TIMER1_COMPA_vect);
ISR(TIMER1_COMPB_vect);
void motor_init();
void set_speed();