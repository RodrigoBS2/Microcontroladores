#ifndef SERIAL_H   
#define SERIAL_H

#include "Includes.h"
#define BAUD 9600 // Defina a taxa de baud desejada
#define MYUBRR F_CPU/16/BAUD-1 // Calcula o valor do registro UBRR

void Init_Serial(uint16_t baud_rate);
void Send_byte(unsigned char * data);
unsigned char Receive_byte();
void Print_data(unsigned char *p);

#endif

