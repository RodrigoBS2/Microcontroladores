#include "Serial.h"

void Init_Serial(uint16_t baud_rate){
     // Configura a taxa de transmissão
    UBRR0H = (unsigned char)(baud_rate>>8);
    UBRR0L = (unsigned char)baud_rate;
    // Ativa a transmissão 
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    // Configura o formato do frame: 8 bits de dados, 1 bit de parada e sem paridade
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void Send_byte(unsigned char * data){
    // Espera o buffer de transmissão estar vazio
    while (!(UCSR0A & (1<<UDRE0)));
    // Coloca o dado no buffer, enviando-o
    UDR0 = *data;

}

unsigned char Receive_byte(){
        /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)))
    ;
    /* Get and return received data from buffer */
    return UDR0;
}

void Print_data(unsigned char *p){
    unsigned char n=0,m=0;
    *p = Receive_byte();
        if(*p != '\n'){
            p+=1;n+=1;
        }
        else{
            m = n;
            p-=n;
            while(n > 0){
                Send_byte(p);
                p+=1;n-=1;
            }
            Send_byte(p);
            p-=m;
            m=0;
        }
}
