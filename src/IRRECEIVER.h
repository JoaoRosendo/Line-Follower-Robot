#include <avr/interrupt.h> 
#include <avr/io.h>

void setup_timer2();
void setup_int0(int T);
int button_press();