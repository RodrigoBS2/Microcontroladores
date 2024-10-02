/* O código a seguir mostra o uso da comunicação USART0 */

#include "Serial.h"
#include "IO.h"

int main(){
    Init_Serial(MYUBRR);
    config_port();
    unsigned char data[100],*p=data,n=0,m=0;
    

    // Recebe pelo monitor serial e printa lá 
    while(1){
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
            change_state_pin();
        }
    }

    return 0;
}

