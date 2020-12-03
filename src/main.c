#include <avr/io.h>
#include <avr/interrupt.h> 
#include "serial_printf.h"
#include "LineSensor.h"


void pin_read()             
{
    
}


int main(void)
{   
    sei();
    printf_init(); 
    ADC_init();

while (1) 
{   
    pin_read();
    printf("IR1:%d  IR2:%d  IR3:%d  IR4:%d  IR5:%d \n",IR[0],IR[1],IR[2],IR[3],IR[4]); //valores do sensor de linha
    //printf("%d    %d\n",ADMUX,MUXSELECTOR); //teste do interrupt do ADC
}       
}