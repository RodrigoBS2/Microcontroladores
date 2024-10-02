/* O código a seguir mostra como usar o Timer/Counter0 no modo de opreção normal
  para piscar um led a cada segundo*/
/*
  Passa a Passo:
  1 - Configure o modo de operação do timer (WGM00, WGM01 e WGM02) Pág 86
  2 - Use o prescaler para dimuniuir a frequencia do clock (CS00, CS01 e CS02) Pág 87
  3 - Habilite a interrupção (TIMSK0) Pág 88
*/

// Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

/*O include a seguir será necessário para fazer manipulação de bits nos registradores*/
#include <stdint.h>

void timer0_init()
{
    // Set up timer to normal mode with clkI/O / 1024 (from prescaler) (16 Mhz / 1024) gera uma frequencia de 15625 Hz e período de 0.064 ms
    TCCR0B |= (1 << CS02)|(1 << CS00);

    // Initialize counter
    // TCNT0 = 0;       Não precisa colocar. Já começa no zero a n ser q vc queira começar em um tempo diferente de zero.

    // Enable overflow interrupt
    TIMSK0 |= (1 << TOIE0);

    // Enable global interrupts
    sei();
}

// Interrupt service routine for Timer0 overflow
ISR(TIMER0_OVF_vect)    // A interrupção é chamada após o overflow (255 x 0.064 ms = 16.32 ms) 
{   
    static int n;
    n += 1;
    if (n >= 61 || n <0){              // Irá fazer o LED piscar em mais ou menos 1 segundo 
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
