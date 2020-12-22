#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>
#include "LineSensor.h"
#include "motor.h"
#include "serial_printf.h"
#include "lcd.h"
#include "IRreceiver.h"

int main(void)
{
   sei();
   LCD_init();
   Send_A_String("Começando");
   ADC_init();
   motor_init(); 
   IR_init();

   while (1)
   {  
      read_IRcode();

      if (on)
      {
         AVRG_IR();
         PID();
         set_speed();
      }
      else
      {
         OCR1AL = 0;
         OCR1BL = 0;
      }
   }
}