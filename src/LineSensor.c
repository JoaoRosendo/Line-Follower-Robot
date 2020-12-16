#include "LineSensor.h"

uint8_t IR[5], MUXSELECTOR = 0;
int AVRG;
long P=0, I=0, D=0, previous_P=0;

float Kp=0.15;
float Ki=0;
float Kd=0.9;
long Motor_speed=0;

#define TETOINTEGRADOR 1000000

ISR(ADC_vect)
{   
    //MUXSELECTOR escolhe o porto para ler; quando lido passa o próximo. IR[0] é o sensor mais à esquerda, IR[4] é o sensor mais à direita
    
    //Le o registo e incrementa variaveis de leitura
    IR[MUXSELECTOR] = ADCH;  
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
    AVRG = ( (uint32_t) 0 * IR[0] + (uint32_t) 1000 * IR[1] + (uint32_t) 2000 * IR[2] + (uint32_t) 3000 * IR[3] + (uint32_t) 4000 * IR[4]) / (IR[0] + IR[1] + IR[2] + IR[3] + IR[4]);
}
void PID()
{
    P = (long) AVRG-2000;
    if(I<TETOINTEGRADOR && I>(-TETOINTEGRADOR))
    I += (long) P;
    D = (long) P - previous_P;
    
    previous_P = P;

    Motor_speed = (long) P * Kp + (long) I * Ki + (long) D * Kd;

}

