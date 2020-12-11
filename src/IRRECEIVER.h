#include <avr/interrupt.h> 
#include <avr/io.h>

extern volatile uint8_t nec_ok;
extern volatile uint8_t  nec_state;
extern volatile unsigned long ir_code;
void setup_timer2();
void setup_int0(int T);