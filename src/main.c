#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial_printf.h"

uint8_t IR[5], MUXSELECTOR = 0;

ISR(ADC_vect)
{   
    //MUXSELECTOR escolhe o porto para ler; quando lido passa o próximo. IR[0] é o sensor mais à esquerda, IR[0] é o sensor mais à direita
    IR[MUXSELECTOR] = ADCH;
    MUXSELECTOR++;
    ADMUX= ADMUX + 1;
    
    if(MUXSELECTOR>4)
    {   
        MUXSELECTOR = 0;
        ADMUX &= (1 << ADLAR) | (1 << REFS0);  //FAZER UMA MELHOR SOLUCAO
    }
}

void io_init()
{
    //Conversor AD
    ADCSRA |=  (1 << ADEN) | (1 << ADSC)| (1 << ADATE) | (1 << ADIE); //Liga conversor AD e interrupcoes
    ADCSRA |= (1 << ADPS0)  | (1 << ADPS1) | (1 << ADPS2);
    ADMUX |= (1 << ADLAR); //Torna o registo left adjusted (facilita leitura)
    ADMUX |= (1 << REFS0); //Escolhe a referência
    sei();

}

void pin_read()             
{
    
}



int main(void)
{
    printf_init(); 
    io_init();

while (1) 
{   
    pin_read();
    printf("IR1:%d  IR2:%d  IR3:%d  IR4:%d  IR5:%d ADMUX:%d \n",IR[0],IR[1],IR[2],IR[3],IR[4], ADMUX);
}       
}