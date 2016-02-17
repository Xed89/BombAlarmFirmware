#ifndef _DISPLAY7SEG4DIGIT_H_
#define _DISPLAY7SEG4DIGIT_H_

typedef struct  {
  uint8_t digit0;
  uint8_t digit1;
  uint8_t digit2;
  uint8_t digit3;
  bool digit1_dot;
} display7seg4digit_t;

void display4seg4digit_init(display7seg4digit_t* d);
void display4seg4digit_increment_as_HHMM(display7seg4digit_t* d);
void display4seg4digit_output(display7seg4digit_t* d);

#endif