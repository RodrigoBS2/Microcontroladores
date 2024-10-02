#include "IO.h"

void config_port(){
    DDRB |= (1 << DDB5);           // Ou DDRB |= (1 << PB4)           // Configurando os pinos como saída
    PORTB &= ~(1 << PB5);            // Definindo o pino como nível lógico baixo 
}

void change_state_pin(){
    PINB |= (1<< PINB5); 
}
