#include "motor.h"

ISR(TIMER1_COMPA_vect){
  
}

ISR(TIMER1_COMPB_vect){
    //OCR1BL++;
}


void motor_init()
{
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << WGM12); //Escolha do modo (fast pwm 8 bit)
    TCCR1B |= (1 << CS12) | (1 << CS10); //Set timer prescaler 1024 (15625 Hz)<100kHz ( 100kHz -> maximo do driver do motor)
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); //Liga interrupts
    OCR1BL = 130;
}

//fazer funcao que rtecebe parametros com velocidade do motor de 0 a 100, que modifica o pwm dos motores
//max pwm freq = 100kHz