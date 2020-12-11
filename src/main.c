#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>
#include "LineSensor.h"
#include "motor.h"
#include "serial_printf.h"
#include "lcd.h"
#include "IRRECEIVER.h"


int main(void)
{   
    sei();
   printf_init(); 
   ADC_init();
   motor_init(); //desligar para retornar funcionalidade aos pinos que usam PWM
   LCD_init();
   
   Send_A_String("eita mlk");
   _delay_ms(2000);
   clearScreen();
   OCR1AL= 100;
   OCR1BL= 100;
   //PORTB |= (1<< PB0) | (1<< PB4);
   
   setup_timer2();// setup timer2 (ir receiver)
   setup_int0(1);// setup interrupt da porta 2 (ir receiver)
   


while (1) 
{   
   AVRG_IR();
   
   //printf("IR1:%d  IR2:%d  IR3:%d  IR4:%d  IR5:%d AVRG:%d\n",IR[0],IR[1],IR[2],IR[3],IR[4], AVRG); //valores do sensor de linha
}       
}