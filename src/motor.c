#include "motor.h"

ISR(TIMER1_COMPA_vect){

}

ISR(TIMER1_COMPB_vect){

}


void motor_init()
{
    TCCR1A |=  (1 << COM1A1) | ;
    TCCR2A |=  
}

//fazer funcao que rtecebe parametros com velocidade do motor de 0 a 100, que modifica o pwm dos motores
//max pwm freq = 100kHz