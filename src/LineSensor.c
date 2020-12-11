#include "LineSensor.h"

uint8_t IR[5], MUXSELECTOR = 0;
uint8_t AVRG;
uint8_t P, I, D, previous_P, Motor_speed;
uint8_t Kp=0;
uint8_t Ki=0;
uint8_t Kd=0;


ISR(ADC_vect)
{   
    //MUXSELECTOR escolhe o porto para ler; quando lido passa o próximo. IR[0] é o sensor mais à esquerda, IR[4] é o sensor mais à direita
    
    //Le o registo e incrementa variaveis de leitura
    IR[MUXSELECTOR] = (255-ADCH);  
    ADMUX = ADMUX + 1;
    MUXSELECTOR++;
    
    //reset das variaveis leitura
    if(MUXSELECTOR>4)
    {   
        MUXSELECTOR = 0;
        ADMUX &= ~(1 << MUX0) & ~(1 << MUX1) & ~(1 << MUX2) & ~(1 << MUX3); 
    }

    //começa uma nova leitura ADC
    ADCSRA |= (1 << ADSC) ;
}

void ADC_init()
{
    // Inicialização Conversor AD 
    ADCSRA |=  (1 << ADEN) | (1 << ADSC)| (1 << ADIE); //Liga conversor AD, começa primeira conversao e liga interrupcoes
    ADCSRA |= (1 << ADPS0)  | (1 << ADPS1) | (1 << ADPS2); //Escolhe o prescaler maximo (128) 
    ADMUX |= (1 << ADLAR); //Torna o registo left adjusted (facilita leitura)
    ADMUX |= (1 << REFS0); //Escolhe a referência (AVCC with external capacitor at AREF pin)
}
void AVRG_IR()
{
    AVRG = (0 * IR[0] + 1000 * IR[1] + 2000 * IR[2] + 3000 * IR[3] +4000 * IR[4]) / (IR[0] + IR[1] + IR[2] + IR[3] + IR[4]);
}
void PID()
{
    P = AVRG - 2000;
    I += P;
    D = P - previous_P;

    previous_P = P;

    Motor_speed = P * Kp + I * Ki + D * Kd;
}
