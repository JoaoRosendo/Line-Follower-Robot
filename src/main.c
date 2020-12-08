#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>
#include "LineSensor.h"
#include "motor.h"
#include "serial_printf.h"
#include "lcd.h"

uint8_t teste = 100;


void pin_read()             
{
    
}


int main(void)
{   
   _delay_ms(2500);
   sei();
   printf_init(); 
   ADC_init();
   motor_init(); //desligar para retornar funcionalidade aos pinos que usam PWM
   LCD_init();
   
   
     /*clearScreen();
   Send_A_String("tou    TOU ttttttttttt");
   _delay_ms(1000);

   clearScreen();*/

   lcd_info_print("O numero e %d \n", teste);
   
    
while (1) 
{   
   // lcd_print("TOU");
   /* PORTB |= (1<< PB0) | (1<< PB4);
    OCR1AL=255;
    OCR1BL=255; */
                                             //-     Display initialization
        
                                              //-     Move to position (line 2, row 4)
        
        //-     Turn cursor off and activate blinking
        //lcd_command(LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKINGON);
    

    //printf("IR1:%d  IR2:%d  IR3:%d  IR4:%d  IR5:%d \n",IR[0],IR[1],IR[2],IR[3],IR[4]); //valores do sensor de linha
}       
}