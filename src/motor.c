#include "motor.h"
#include "LineSensor.h"

int MOTOR_SPEED_A=0;
int MOTOR_SPEED_B=0;
int base_speed=180;

#define REVERSECONSTANT 100


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
    
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10); // Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM (non-inverting mode) 
    TCCR1B |= (1 << WGM12); //Escolha do modo (fast pwm 8 bit)
    TCCR1B |= (1 << CS12) | (1 << CS10); //Set timer prescaler 1024 (15625 Hz)<100kHz ( 100kHz -> maximo do driver do motor)
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); //Liga interrupts
    
}

void set_speed()
{
    MOTOR_SPEED_A=base_speed-Motor_speed;
    MOTOR_SPEED_B=base_speed+Motor_speed;

    //printf("A:%d  B:%d",MOTOR_SPEED_A, MOTOR_SPEED_B);

    if ( (int) MOTOR_SPEED_A > 0)
    {
        PORTB &= ~(1 << PB3);
        PORTB |=  (1 << PB0);

         if (MOTOR_SPEED_A > 255)
        {
            MOTOR_SPEED_A = 255;
        } 
    }
    
    else
    {   
        MOTOR_SPEED_A = -MOTOR_SPEED_A;
        PORTB &= ~(1 << PB0);
        PORTB |=  (1 << PB3);

         if (MOTOR_SPEED_A > REVERSECONSTANT)
        {
            MOTOR_SPEED_A = REVERSECONSTANT;
        }
    }






    if ( (int) MOTOR_SPEED_B > 0)
    {
        PORTB &= ~(1 << PB5);
        PORTB |=  (1 << PB4);

        if (MOTOR_SPEED_B > 255)
        {
            MOTOR_SPEED_B = 255;
        }
    }
    
    else
    {   
        MOTOR_SPEED_B = -MOTOR_SPEED_B;
        PORTB &= ~(1 << PB4);
        PORTB |=  (1 << PB5);

        if (MOTOR_SPEED_B > REVERSECONSTANT)
        {
            MOTOR_SPEED_B = REVERSECONSTANT;
        }
    }

     //printf("A:%d  B:%d",MOTOR_SPEED_A, MOTOR_SPEED_B); 

    OCR1AL=MOTOR_SPEED_A;
    OCR1BL=MOTOR_SPEED_B;

}

//fazer funcao que rtecebe parametros com velocidade do motor de 0 a 100, que modifica o pwm dos motores
//max pwm freq = 100kHz