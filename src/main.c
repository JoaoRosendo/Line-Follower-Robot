#include <avr/io.h>
#include <avr/interrupt.h> 
#include "serial_printf.h"
#include "LineSensor.h"
#include <util/delay.h>
#include "lcd.h"


void pin_read()             
{
    
}


int main(void)
{      
    sei();
    printf_init(); 
    ADC_init();

    LCD_Init();
    LCD_WriteString("TOU");
   
  
while (1) 
{   
  
    LCD_WriteString("TOU");
    pin_read();
   // printf("IR1:%d  IR2:%d  IR3:%d  IR4:%d  IR5:%d \n",IR[0],IR[1],IR[2],IR[3],IR[4]); //valores do sensor de linha
   // lcd_printf("%d",IR[0]);
    //printf("%d    %d\n",ADMUX,MUXSELECTOR); //teste do interrupt do ADC
}       
}