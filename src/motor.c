#include "motor.h"

ISR(TIMER1_COMPA_vect)
{

}

ISR(TIMER1_COMPB_vect)
{

}


void motor_init()
{   
    //Inicialização dos portos do controlar do motor

    DDRB|= (1<< PB0) //BIN1
         | (1<< PB1) //PWMB
         | (1<< PB2) //PWMA
         | (1<< PB3) //BIN2
         | (1<< PB4) //AIN1
         | (1<< PB5);//AIN2

    //Inicialização do timer gerador de PWM
    
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << WGM12); //Escolha do modo (fast pwm 8 bit)
    TCCR1B |= (1 << CS12) | (1 << CS10); //Set timer prescaler 1024 (15625 Hz)<100kHz ( 100kHz -> maximo do driver do motor)
    
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); //Liga interrupts
    
}

//fazer funcao que rtecebe parametros com velocidade do motor de 0 a 100, que modifica o pwm dos motores
//max pwm freq = 100kHz