#include "AVRincludes.h"

// SPI Master
/*
  PB5 : SCK   in
  PB4 : MISO  out
  PB3 : MOSI  in
  PB2 : SS    in
*/



// Configuração dos pinos 
void Confg_Pins(){
  DDRB |= (1<<DDB4);
  DDRB &= ~((1<<DDB3)|(1<<DDB5)| (1<<DDB2));
  PORTB &= ~(1<<PB4);

  // LED
  DDRD |= (1<<DDD7);
  PORTD &= ~(1<<PD7);
}
// Inicialização do SPI no master
void SPI_MasterInit(){
  // Habilitando o SPI (SPE), modo slave (MSTR)
  SPCR |= (1<<SPE);
  SPCR &= ~(1<<MSTR);

}
unsigned char SPI_Receive_data(){
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)))
    ;
    /* Return Data Register */
    return SPDR;
}


int main(){
  unsigned char D;
  Confg_Pins();
  SPI_MasterInit();
  
  D = SPI_Receive_data();

  while(1){
    if(D == 'A'){
      PIND |= (1<<PD7);
    }
    else{
      D = SPI_Receive_data();
    }
  }



  return 0;
}