#include "Timers.h"

uint16_t T; // Variável usada para função delay

// Configuranção  do timer0 
void timer0_init(){
  // Mode CTC
  TCCR0A |= (1 << WGM01);
  /*Set up timer to normal mode with clkI/O / 1024 (from prescaler) (16 Mhz / 1024) gera uma 
  frequencia de 15625 Hz e período de 0.064 ms*/ 
  TCCR0B |= (1 << CS02)|(1 << CS00);
  // Output Compare Register A to match with TCNT0
  OCR0A = 16;  // O match irá ocorrer aproximadamente em + - 1 ms
  // Disable overflow interrupt
  TIMSK0 &= ~(1 << OCIE0A);
  // Enable global interrupts
  sei();

}

// Função delay
void delay(uint16_t time){  
    uint16_t *P=&T; *P = time;
    // Enable overflow interrupt
    TIMSK0 |= (1 << OCIE0A); 
    while((TIMSK0 & (1 << OCIE0A))){}
}

// Interrupt service routine for Timer0 Compare Match A 
ISR(TIMER0_COMPA_vect)    // A interrupção é chamada no tempo de + - 1 ms
{   
    static uint16_t n = 0;
    n += 1;
    if (n >= T ){              // Delay de T milisegundos
        n = 0;
        // Disable overflow interrupt
        TIMSK0 &= ~(1 << OCIE0A);
    }
}