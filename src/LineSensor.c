#include "LineSensor.h"

uint8_t IR[5], MUXSELECTOR = 0;
short int AVRG;
int P=0, D=0, previous_P=0;
long int I=0;

float Kp= 0.075;
float Ki=0.00060;
float Kd=13.5;
long Motor_speed=0;

#define TETOINTEGRADOR 230000

ISR(ADC_vect)
{   
    //MUXSELECTOR escolhe o porto para ler; quando lido passa o próximo. IR[0] é o sensor mais à esquerda, IR[4] é o sensor mais à direita
    
    //Le o registo e incrementa variaveis de leitura
    if(ADCH >= 230) IR[MUXSELECTOR] = 250;
    else if((ADCH > 31) && (ADCH < 230)) IR[MUXSELECTOR] = ADCH;
    else IR[MUXSELECTOR] = 0;
  
    ADMUX = ADMUX + 1;
    MUXSELECTOR++;
    
    //reset das variaveis leitura
    if(MUXSELECTOR>4)
    {   
        MUXSELECTOR = 0;
        ADMUX &= 0b11110000;            //~(1 << MUX0) & ~(1 << MUX1) & ~(1 << MUX2) & ~(1 << MUX3) (código menos eficaz)
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
    cli();
    AVRG = ((int) -10 * IR[0] + (int) -4 * IR[1] + (int) 0 * IR[2] + (int) 4 * IR[3] + (int) 10 * IR[4]);
    sei();
}
void PID()
{   
    P = (int) AVRG;
    if((I<=TETOINTEGRADOR  &&  I>=(-TETOINTEGRADOR)) || (I>TETOINTEGRADOR && P<0) || (I<(-TETOINTEGRADOR) && P>0))
    I += P;
    D = (int) P - (int) previous_P;
    previous_P = (int) P;

    Motor_speed = P*Kp + I*Ki + D*Kd;
    //printf("P:%d  I:%ld   D:%d  motor_speed:%d \n",P,I,D,Motor_speed);
}

