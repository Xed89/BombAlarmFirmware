#include "core.h"
#include "timer1.h"
#include "display7seg4digit.h"

volatile uint8_t m_elapsed_ticks;
void timer1_callback_one_second();

void main() {
  display7seg4digit_t m_display;
  uint8_t m_seconds = 0;
  m_elapsed_ticks = 0;

  ADCON1 = 6; //All PORTA outputs are digital
  
  display4seg4digit_init(&m_display);

  timer1_start(timer1_callback_one_second);


  while(1) {
    //You can test for >0 withouth a critical section because the callback only increments
    //But you need to use a critical section to decrement it to avoid a race condition on write
    //Should never happen because of fast loop execution, but better be sure
    if (m_elapsed_ticks > 0) {
        //---- Critical section begin ----
        GIE_bit = 0;
        m_elapsed_ticks--;
        GIE_bit = 1;
        //---- Critical section end   ----

        m_seconds++;
        m_display.digit1_dot = !m_display.digit1_dot;
        if (m_seconds >= 60) {
          m_seconds = 0;
          display4seg4digit_increment_as_HHMM(&m_display);
        }
    }
    display4seg4digit_output(&m_display);
  }
}

void timer1_callback_one_second() {
  m_elapsed_ticks++;
}

void Interrupt() {
  if (TMR1IF_bit) {
    timer1_interrupt();
    TMR1IF_bit = 0;
  }
}