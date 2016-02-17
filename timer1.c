#include "timer1.h"
#include "core.h"

timer1_callback_t m_callback;
uint32_t m_counter;
void timer1_start(timer1_callback_t callback) {
  m_callback = callback;
  m_counter = 0;

  TMR1IE_bit = 1; //Enable interrupt for TMR1
  GIE_bit = 1;    //And enable all interrupts
  PEIE_bit = 1;

  TMR1ON_bit = 1;
}

void timer1_interrupt() {
  //TMR1H = 236;
  //TMR1L = 120;
  //At Fosc=20Mhz the counter is overflowing every 65536 * (Fosc/4) = 0.0131072 seconds
  //One second is represented by Fosc/4 counts = 5000000 (5 million counts)
  m_counter += 0xffff;
  if (m_counter > 5000000) {
  	m_counter -= 5000000;
    m_callback();
  }
}