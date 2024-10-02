#include "Serial.h"
#include "Timer0.h"

int main(void) {
    USART_Init(MYUBRR); // Inicializa a USART com o valor de UBRR calculado
    // Initialize Timer0
    timer0_init();
    while (1) {
    
    }

    return 0;
}

// Interrupt service routine for Timer0 overflow
ISR(TIMER0_OVF_vect)    // A interrupção é chamada após o overflow (255 x 0.064 ms = 16.32 ms) 
{   
    static int n;
    n += 1;
    if (n >= 61 || n <0){      // Irá fazer a comunicação serial em mais ou menos 1 segundo 
        // Transmite o caractere '1'
        USART_Transmit('1'); 
        n = 0;
    }
}
