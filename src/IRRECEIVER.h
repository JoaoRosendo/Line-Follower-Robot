#include <avr/interrupt.h> 
#include <avr/io.h>

extern int on;

void read_IRcode();
void setup_timer2();
void setup_int0(int T);
int button_press();
void IR_init();
