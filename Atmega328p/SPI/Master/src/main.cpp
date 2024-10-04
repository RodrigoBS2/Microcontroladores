#include "AVRincludes.h"

// SPI Master
/*
  PB5 : SCK   out
  PB4 : MISO  in
  PB3 : MOSI  out
  PB2 : SS    out
*/



// Configuração dos pinos 
void Confg_Pins(){
  DDRB |= (1<<DDB5) | (1<<DDB3) | (1<<DDB2);
  DDRB &= ~(1<<DDB4);
  PORTB &= ~((1<<PB5) | (1<<PB3) | (1<<PB2));
}

// Inicialização do SPI no master
void SPI_MasterInit(){
  // Habilitando o SPI (SPE), modo Master (MSTR), na frequencia fck/16
  SPCR |= (1<<SPE)|(1<<MSTR)|(1 << SPR0);
}

void SPI_Send_Byte(unsigned char data){
  /* Start transmission */
  SPDR = data;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF))){
  };
}

 
int main(){
  unsigned char D ='A';  //  Dado
  Confg_Pins();
  SPI_MasterInit();
  
  SPI_Send_Byte(D);
  
  while(1);

  return 0;
}





