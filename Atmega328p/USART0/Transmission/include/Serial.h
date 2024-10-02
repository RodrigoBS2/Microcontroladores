#ifndef SERIAL_H   
#define SERIAL_H

#include <avr/io.h>
#define BAUD 115200 // Defina a taxa de baud desejada
#define MYUBRR F_CPU/16/BAUD-1 // Calcula o valor do registro UBRR

// Inicializa a comunicação serial
void USART_Init(unsigned int ubrr);
// Transmite um dado pela USART0
void USART_Transmit(unsigned char data);

#endif