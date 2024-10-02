#include "Serial.h"
// Inicializa a comunicação serial
void USART_Init(unsigned int ubrr) {
    // Configura a taxa de transmissão
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    // Ativa a transmissão 
    UCSR0B = (1<<TXEN0);
    // Configura o formato do frame: 8 bits de dados, 1 bit de parada e sem paridade
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}
// Transmite um dado pela USART0
void USART_Transmit(unsigned char data) {
    // Espera o buffer de transmissão estar vazio
    while (!(UCSR0A & (1<<UDRE0)));
    // Coloca o dado no buffer, enviando-o
    UDR0 = data;
}