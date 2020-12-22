#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial_printf.h"
#include <avr/eeprom.h>
#include "LineSensor.h"
#include "lcd.h"
#include "motor.h"
#include "IRreceiver.h"

int on=0;
int code=0;
volatile uint8_t nec_ok = 0;
volatile uint8_t  i, nec_state = 0;
volatile unsigned long ir_code;

void read_IRcode()
{
  code = button_press();

  if (code == 0xa25d)
  {
    on = !on;
  }

  else if (code == 0xe21d)
  {
    if (print_ready)
    {
      lcd_info_print();
    }
  }

  else if (code == 0x22dd) // undo track button
  {
    Kp += 0.01;
  }

  else if (code == 0xe01f) // down arrow button
  {
    Kp -= 0.01;
  }

  else if (code == 0x02fd) // pause track button
  {
    Ki += 0.00001;
  }
  else if (code == 0xa857) // VOL- button
  {
    Ki -= 0.00001;
  }

  else if (code == 0xc23d) // skip track button
  {
    Kd += 0.1;
  }
  else if (code == 0x906f) // up arrow button
  {
    Kd -= 0.1;
  }

  else if (code == 0x6897) // 0 button
  {
    if (base_speed != 250)
    {
      base_speed += 5;
    }
  }
  else if (code == 0x30cf) // 1 button
  {
    if (base_speed != 0)
    {
      base_speed -= 5;
    }
  }

  
}

void IR_init()
{
  setup_timer2();
  setup_int0(1);
}

ISR(TIMER2_OVF_vect) {                           // Timer1 interrupt service routine (ISR)
  nec_state = 0;                                 // Reset decoding process
  TCCR2B = 0;                                    // Disable Timer2 module
}

void setup_int0 (int T){
  if (T!=0) {
    EICRA=0;
    EICRA |=  (1<< ISC00);                           //set interrupt to occur on change
    EIMSK=0;
    EIMSK |= (1<<INT0);                             // Enable external interrupt (INT0)
  }
  else if (T==0) {
    EICRA &=  ~(1<< ISC00);                          
    EIMSK &= ~(1<<INT0);   
  }
}

ISR(INT0_vect) {
  unsigned int timer_value;
  if(nec_state != 0){
    timer_value = TCNT2;                         // Store Timer1 value
    TCNT2 = 0;                                   // Reset Timer1
  }
  switch(nec_state){
  case 0 :       
                                                  // Start receiving IR data (we're at the beginning of 9ms pulse)
    TCNT2  = 0;                                  // Reset Timer2
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);     // Enable Timer1 module with 1/1024 prescaler ( 2 ticks every 1 us)
    nec_state = 1;                               // Next state: end of 9ms pulse (start of 4.5ms space)
    i = 0;
    break;
  case 1 :                                      // End of 9ms pulse
    if((timer_value > 148) || (timer_value < 132)){         // Invalid interval ==> stop decoding and reset
      nec_state = 0;                             // Reset decoding process
      TCCR2B = 0;                                // Disable Timer1 module
    }
    else
      nec_state = 2;                             // Next state: end of 4.5ms space (start of 562µs pulse)
    break;
  case 2 :                                      // End of 4.5ms space
    if((timer_value > 78) || (timer_value < 62)){
      nec_state = 0;                             // Reset decoding process
      TCCR2B = 0;                                // Disable Timer1 module
    }
    else
      nec_state = 3;                             // Next state: end of 562µs pulse (start of 562µs or 1687µs space)
    break;
  case 3 :                                      // End of 562µs pulse
    if((timer_value > 10) || (timer_value < 6)){           // Invalid interval ==> stop decoding and reset
      TCCR2B = 0;                                // Disable Timer1 module
      nec_state = 0;                             // Reset decoding process
    }
    else
      nec_state = 4;                             // Next state: end of 562µs or 1687µs space
    break;
  case 4 :                                      // End of 562µs or 1687µs space
    if((timer_value > 28) || (timer_value < 6)){           // Time interval invalid ==> stop decoding
      TCCR2B = 0;                                // Disable Timer1 module
      nec_state = 0;                             // Reset decoding process
      break;
    }
    if( timer_value > 15) {                     // If space width > 1ms (short space)
      cli();
      ir_code |= (1 << (31 - i));                // Write 1 to bit (31 - i)
      sei();  
    }
    else{                                         // If space width < 1ms (long space)
      cli();
      ir_code &= ~(1 << (31 - i));               // Write 0 to bit (31 - i)
      sei();
    }
    i++;
    if(i > 31){                                  // If all bits are received
      nec_ok = 1;                                // Decoding process OK          
      setup_int0(0);                              // Disable external interrupt (INT0)  
      break;
    }
    nec_state = 3;  
    break;                             // Next state: end of 562µs pulse (start of 562µs or 1687µs space)
  }
}

void setup_timer2() {
  // Timer2 module configuration
  TCCR2A = 0;
  TCCR2B = 0;                                    // Disable Timer2 module
  TCNT2  = 0;                                    // Set Timer2 preload value to 0 (reset)
  TIMSK2 = 1;                                    // enable Timer2 overflow interrupt
}



int button_press()
{
   if(nec_ok){                       
      nec_ok = 0;                                // Reset decoding process
      nec_state = 0;
      TCCR2B = 0;                                // Disable Timer2 module
      ir_code = ir_code & 0x0000FFFF;          
      setup_int0(1);  
      return ir_code;                           // Enable external interrupt (INT0)
   }
   else
   {
     return 0;
   }
   
}


