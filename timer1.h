#ifndef _TIMER1_H_
#define _TIMER1_H_

typedef void (*timer1_callback_t)();
void timer1_start(timer1_callback_t callback);
void timer1_interrupt();

#endif