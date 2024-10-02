/* O código a seguir mostra como fazer um led piscar em aproximadamente 1s
  atraves do timer/counter0 no modo CTC */
/*
  Passa a Passo:
  1 - Configure o modo de operação do timer (WGM00, WGM01 e WGM02) Pág 86
  2 - Use o prescaler para dimuniuir a frequencia do clock (CS00, CS01 e CS02) Pág 87
  3 - Defina o número do Match na variável OCR0A, póis ela será comparada com o contador TCNT0, para quando TCNT0 = OCR0A, a 
     interrupção será chamada para piscar o LED. Pág 87
  4 - Habilite a interrupção (TIMSK0). Pág 88
*/
/* 
  Capítulo no datasheet: 14 
  Tópico do modo CTC: 14.7.2 
*/ 


/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

/*O include a seguir será necessário para fazer manipulação de bits nos registradores*/
#include <stdint.h>

void timer0_init()
{   // Mode CTC
    TCCR0A |= (1 << WGM01);   

    /*Set up timer to normal mode with clkI/O / 1024 (from prescaler) (16 Mhz / 1024) gera uma 
     frequencia de 15625 Hz e período de 0.064 ms*/ 
    TCCR0B |= (1 << CS02)|(1 << CS00);

    // Output Compare Register A to match with TCNT0
    OCR0A = 156;  // O match irá ocorrer aproximadamente em + - 10 ms

    // Enable overflow interrupt
    TIMSK0 |= (1 << OCIE0A);

    // Enable global interrupts
    sei();
}

// Interrupt service routine for Timer0 Compare Match A 
ISR(TIMER0_COMPA_vect)    // A interrupção é chamada no tempo de + - 10 ms
{   
    static uint8_t n;
    n += 1;
    if (n >= 100 || n <0){              // Irá fazer o LED piscar em mais ou menos 1 segundo 
        // Toggle a LED connected to PORTB5
        PINB |= (1 << PINB5);
        n = 0;
    }
}

int main(void)
{
    // Set PORTB5 as output
    DDRB |= (1 << DDB5);

    // Set PORTB5 as logic level HIGH
    PORTB |= (1 << PB5);

    // Initialize Timer0
    timer0_init();

    // Loop forever
    while(1)
    {
        
    }
}