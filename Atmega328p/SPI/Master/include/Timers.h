#ifndef TIMERS_H
#define TIMERS

#include "AVRincludes.h"

 
void timer0_init(); // Configuranção  do timer0
void delay(uint16_t time);  // Função delay
ISR(TIMER0_COMPA_vect);


#endif