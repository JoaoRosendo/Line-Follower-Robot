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
   //printf_init(); 
   ADC_init();
   motor_init(); //desligar para retornar funcionalidade aos pinos que usam PWM
   LCD_init();
   
   Send_A_String("eita mlk");
   _delay_ms(2000);
   clearScreen();

   PORTB |= (1<< PB0) | (1<< PB4);
   int on=0;
   int code=0;
   
   setup_timer2();
   setup_int0(1);

   while (1) 
   {   
      
      code=button_press();

      if (code == 0xa25d)
      {
         on+=1;
      }

      if (code == 0xe21d)
      {
         if(print_ready)
         {
         lcd_info_print();
         }
      }



      if (code == 0x22dd) // undo track button  
      {
         Kp+=0.05;
      }

      if (code == 0xe01f)
      {
         Kp-=0.05;
      }



      if (code == 0x02fd) // pause track button  
      {
         Ki+=0.00005;
      }
      if (code == 0xa857)
      {
         Ki-=0.00005;
      }
      


      if (code == 0xc13d) // skip track button
      {
         Kd+=0.1;
      }
      if (code == 0x906f)
      {
         Kd-=0.1;
      }


       
      if (code == 0x6897) // skip track button
      {
         if (base_speed!=250)
         {
            base_speed+=10;
         }
      }
      
      if (code == 0x30cf)
      {
         base_speed-=10;
      }





      
      if (on%2 == 0)
      {
         OCR1AL=0;
         OCR1BL=0;
      }

      if (on%2 != 0)
      {
         AVRG_IR();
         PID();
         set_speed();

      }

      //printf("IR1:%d  IR2:%d  IR3:%d  IR4:%d  IR5:%d AVRG:%d PID:%ld MSA:%d MSB:%d  \n",IR[0],IR[1],IR[2],IR[3],IR[4], AVRG, Motor_speed, OCR1AL,OCR1BL); //valores do sensor de linha
   }
}