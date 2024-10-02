
/* Piscando o LED com as interupções externas INTO e INT1
   - INT0 está relacionado ao pino PD2;
   - INT1 está relacionado ao pino PD3;
   - Sobre o código:
      O código abaixo faz com que a interrupção INT1 modifique o tipo de ativação da interrupção
     INT0, e este, quando ativada, muda o estado lógico de sáida do pino PB5 (alto para baixo 
     ou o inverso), onde se encontra o LED do arduino).
   - Capítulos do datasheet: 11, 12 e 13.
*/
/*  Passo a passo:
    1 - Veja primeiro a função "int main(void)"
        1.1 - Configure as portas de interesse (nesse caso PB4, PB5) como saída ou entrada usando o DDRB. Pág 72;
        1.2 - Configure essas portas para nível lógico alto ou baixa usando PORTB. Pág 72;
        1.3 - Habilitando as interrupções (respeite a ordem dos comandos):
            1.3.1 - Determine a maneira como as interrupções externas de interesse (nesse caso INT0 e INT1) serão chamadas, usando EICRA. Pág 54;
            1.3.2 - Habilite individualmente as duas interrupções externas. Pág 55;
            1.3.3 - Habilite a interrupção global usando o comando "sei()".
    2 - Veja as funções de interrupções "ISR" de INTO e INT1:
        2.1 - Em ISR(INT0_vect):
            2.1.1 - Use PINB para ficar mudando o nível lógico da porta de interesse. Pág 72, 58 (Overview) e 60 (Toggling the Pin).
*/
/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

/*O include a seguir será necessário para fazer manipulação de bits nos registradores*/
#include <stdint.h>

// Função para das interrupções INT0 e INT1
ISR(INT0_vect) {    // 
    PINB |= (1<< PINB5);           // Ou PINB |= (1 << PB5)         // Alterando o nível lógico do pino
}

ISR(INT1_vect) {    
    if ((EICRA & ((1 << ISC01) | (1 << ISC00))) == 0x03){           // Verificando se INT0 está configurado como borda de subida
        EICRA &=  ~(0x03);
        EICRA |=  (0 << ISC01) | (1 << ISC00);     // Ativando INT0 como qualquer mudança de nível lógico    
    }
    else if((EICRA & ((1 << ISC01) | (1 << ISC00))) == 0x01){       // Verificando se INT0 está configurado como qualquer mudança de nível lógico
        EICRA |=  (1 << ISC01) | (1 << ISC00);      // Ativando INT0 como borda de subida        
    }

}

int main(void) {
    // Configuring the ports:

    DDRB |= (1 << DDB5) | (1 << DDB4);           // Ou DDRB |= (1 << PB5)           // Configurando os pinos como saída
    PORTB |= (1 << PB5) | (1 << PB4);            // Definindo os pinos como nível lógico alto 

    // Configuring the INT0 interrupt (Respeite a ordem dos comandos):

    EICRA |=  (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);    // Ativando INT0 e INT1 como borda de subida
    EIMSK |= (1 << INT1) | (1 << INT0);         // Habilitando individualmente as interrupções
    sei();      // Habilitando a interrupção global

    
    
    return 0;
}
