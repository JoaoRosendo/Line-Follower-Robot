#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>
#include "LineSensor.h"
#include "motor.h"
#include "serial_printf.h"
#include "lcd.h"
#include "IRRECEIVER.h"

#define UPDATEFREQ 50 //Frequencia de update do LCD (minimo ~= 50)


uint8_t clockdivider = 0;
uint8_t print_ready;

ISR(TIMER0_OVF_vect)
{
	clockdivider++;
	if(clockdivider == UPDATEFREQ)
	{	
		printf("%d\n",print_ready);
		clockdivider = 0;
		print_ready = 1;
		printf("%d\n",print_ready);
	}
}

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
   OCR1AL= 50;
   OCR1BL= 50;
  // PORTB |= (1<< PB0) | (1<< PB4);
  
   while (1) 
{   
   if(print_ready)
   {
      lcd_info_print();
      print_ready = 0;
   }

   // printf("IR1:%d  IR2:%d  IR3:%d  IR4:%d  IR5:%d MUXSELECTOR:%d ADMUX:%d \n",IR[0],IR[1],IR[2],IR[3],IR[4], MUXSELECTOR, ADMUX); //valores do sensor de linha
}
}