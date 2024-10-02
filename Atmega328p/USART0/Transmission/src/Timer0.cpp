#include "Timer0.h"
// Habilitando o timer0
void timer0_init()
{
    // Set up timer to normal mode with clkI/O / 1024 (from prescaler) (16 Mhz / 1024) gera uma frequencia de 15625 Hz e período de 0.064 ms
    TCCR0B |= (1 << CS02)|(1 << CS00);

    // Enable overflow interrupt
    TIMSK0 |= (1 << TOIE0);

    // Enable global interrupts
    sei();
}