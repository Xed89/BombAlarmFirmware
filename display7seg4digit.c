#include "core.h"
#include "display7seg4digit.h"

/* segment to bit number mapping
   --1-
 3|    |0
   --4-
 7|    |5
   --6-  .2
*/
uint8_t display7seg_table[] = {0b00010100, //0
                               0b11011110, //1
                               0b00101100, //2
                               0b10001100, //3
                               0b11000110, //4
                               0b10000101, //5
                               0b00000101, //6
                               0b11011100, //7
                               0b00000100, //8
                               0b11000100};//9

void display4seg4digit_init(display7seg4digit_t* d) {
  d->digit0 = 0;
  d->digit1 = 0;
  d->digit2 = 0;
  d->digit3 = 0;
  d->digit1_dot = false;

  TRISA2_bit = 0;
  TRISA3_bit = 0;
  TRISA4_bit = 0;
  TRISA5_bit = 0;
  TRISB = 0; //All outputs
  
  RA2_bit = 1;
  RA3_bit = 1;
  RA4_bit = 1;
  RA5_bit = 1;
  PORTB = 0;
}

void display4seg4digit_increment_as_HHMM(display7seg4digit_t* d) {
  d->digit0++;
  if (d->digit0 > 9) {
    d->digit0 = 0;
    d->digit1++;
    if (d->digit1 > 5) {
      d->digit1 = 0;
      d->digit2++;
      if (d->digit2 > 9) {
        d->digit2 = 0;
        d->digit3++;
        if (d->digit3 > 5) {
          d->digit3 = 0;
        }
      }
    }
  }
}

void delayL() {
  uint8_t i, j, k;
  for(i=0; i<5; i++)
    ;
}
void delayH() {
  uint8_t i, j, k;
  for(i=0; i<50; i++)
    ;
}

void display4seg4digit_output(display7seg4digit_t* d) {
  PORTB = display7seg_table[d->digit3];
  RA2_bit = 0;
  delayL();
  RA2_bit = 1;
  delayH();
  
  PORTB = display7seg_table[d->digit2];
  //Turn on second dot if this is an even second
  if (d->digit1_dot)
    PORTB &= 0b1111011;
  RA3_bit = 0;
  delayL();
  RA3_bit = 1;
  delayH();
  
  PORTB = display7seg_table[d->digit1];
  RA4_bit = 0;
  delayL();
  RA4_bit = 1;
  delayH();
  
  PORTB = display7seg_table[d->digit0];
  RA5_bit = 0;
  delayL();
  RA5_bit = 1;
  delayH();
}