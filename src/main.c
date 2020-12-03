#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial_printf.h"

uint8_t IR[5]; MUXSELECTOR = 0;

ISR(ADC_vect)
{   //MUXSELECTOR escolhe o porto para ler; quando lido passa o próximo. IR[0] é o sensor mais à esquerda, IR[0] é o sensor mais à direita
    IR[MUXSELECTOR] = ADCH;
    
    MUXSELECTOR++;
    
    if(MUXSELECTOR>=5)
    {   
        MUXSELECTOR = 0;
    }
}

void io_init()
{
    //Conversor AD
    ADCSRA |=  (1 << ADEN) |  (1 << ADIE); //Liga conversor AD e interrupcoes
    ADMUX |= (1 << ADLAR); //Torna o registo left adjusted (facilita leitura)

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
    printf("IR1:%d  IR2:%d  IR3:%d  IR4:%d  IR5:%d  \n",IR[0],IR[1],IR[2],IR[3],IR[4]);
}       
}