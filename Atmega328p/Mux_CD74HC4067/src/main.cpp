#include <Serial.h>

/*
   Definições dos pinos do Mux CD74HC4067
    PB0: S0 pino 8    PB1: S1 pino 9    PB2: S2 pino 10    PB3: S3 pino 11    PB4: SIG pino 12
*/

// Variável usada para função delay
uint16_t T; 

// Configuranção  do timer0 
void timer0_init(){
  // Mode CTC
  TCCR0A |= (1 << WGM01);
  /*Set up timer to normal mode with clkI/O / 1024 (from prescaler) (16 Mhz / 1024) gera uma 
  frequencia de 15625 Hz e período de 0.064 ms*/ 
  TCCR0B |= (1 << CS02)|(1 << CS00);
  // Output Compare Register A to match with TCNT0
  OCR0A = 16;  // O match irá ocorrer aproximadamente em + - 1 ms
  // Disable overflow interrupt
  TIMSK0 &= ~(1 << OCIE0A);
  // Enable global interrupts
  sei();
}

void delay(uint16_t time){
    uint16_t *P=&T; *P = time;
    // Enable overflow interrupt
    TIMSK0 |= (1 << OCIE0A); 
    while((TIMSK0 & (1 << OCIE0A))){}
}

// Interrupt service routine for Timer0 Compare Match A 
ISR(TIMER0_COMPA_vect)    // A interrupção é chamada no tempo de + - 1 ms
{   
    static uint16_t n = 0;
    n += 1;
    if (n >= T ){              // Delay de T milisegundos
        n = 0;
        // Disable overflow interrupt
        TIMSK0 &= ~(1 << OCIE0A);
    }
}

void Setup_IO_Ports(){
  // Configurando do Mux 
  DDRB |=  (1 << DDB5)| (1 << DDB3) | (1 << DDB2) | (1 << DDB1) | (1 << DDB0);           
  PORTB &= ~((1 << PB5) |(1 << PB3) | (1 << PB2) | (1 << PB1) | (1 << PB0)); 
  // Confirgurando o pino do LED
  DDRB |=(1 << PD7);
  PORTD &= ~(1 << PD7);
}

unsigned char Feedback(){
  unsigned char FB = 0, n = 0, aux = 0;
  while(n <= 3){
    // Ativa os pinos de entrada do MUX (S0, S1, S2 e S3) a cada ciclo (para verificar apenas as quatro primeiras saídas)
    PORTB |= (n << 0);
    delay(1);    
    // Lê o pino SIG e adiciona a informação em FB
    aux = PINB & (1<<PB4);   
    aux = (aux >> 4); 
    FB |= (aux << n);
    // Limpar os pinos S0, S1, S2, S3 para uma nova leitura
    PORTB &= ~(n << 0);
    n++;
  }
  return FB;
}


int main(){
  Init_Serial(MYUBRR);
  unsigned char FB, a = 'A';
  timer0_init();
  Setup_IO_Ports();
  

  FB = Feedback();
  if(FB == 0b00001000){   // Sinta-se livre para modificar os pinos de entrada do MUX, no cirucito.  
    PORTD |= (1 << PD7);    
  }
  //  A seguir temos um loop onde ficará aguardando por um determinado dado chegar para enviar byte da variável "a"
  while(1){
    delay(10);
    if(Receive_byte() == 1){
      Send_byte(&a);
      a = 'B';
      Send_byte(&a);
    }
  }
  return 0;
}