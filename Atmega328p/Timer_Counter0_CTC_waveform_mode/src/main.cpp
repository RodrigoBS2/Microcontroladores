/* O código a seguir mostra como fazer um led piscar em aproximadamente 1s
  atraves do timer/counter1 no modo CTC, waveform generator */
/*

/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

/* O include a seguir será necessário para fazer manipulação de bits nos registradores*/
#include <stdint.h>

void timer1_init()
{   // Mode CTC - non PWM
    TCCR1A |= (1 << COM1A0); 
    TCCR1B |= (1 << WGM12);   

    //Set up timer to  clkI/O / 1024 (from prescaler) 
    TCCR1B |= (1 << CS12)|(1 << CS10);

    // Output Compare Register A to match with TCNT1
    OCR1A = 15625;  

    // Enable overflow interrupt
    TIMSK1 |= (1 << OCIE1A);        

    // Enable global interrupts
    sei();
}
// Interrupt service routine for Timer0 overflow
ISR(TIMER1_COMPA_vect){

}
int main(void)
{
    // Set PORTB5 and PORTD1 as output
    DDRB |= (1 << DDB5) | (1 << DDB1);
    

    // Set PORTB5 as logic level HIGH
    PORTB |= (1 << PB5);

    // Initialize Timer0
    timer1_init();

    // Loop forever
    while(1)
    {
        
    }
}