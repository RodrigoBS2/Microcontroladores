#include <avr/io.h>
#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>



//----------------------------------------------------------------------------------
// Declaração das funções serão usadas para tasks:
// Task para ligar o LED PB5
void vTaskBlinkLed_PB5(void *pvParameters);
// Task para ligar o LED PD7
//void vTaskBlinkLed_PB5(void *pvParameters);
//----------------------------------------------------------------------------------

int x=1;

int main(){
  // Configuração do pino para o LED
  DDRB |= (1 << DDB5);           
  PORTB |= (1 << PB5); 
  
  // Cria as tasks
    xTaskCreate(vTaskBlinkLed_PB5, "Blink_LED_PB5", 128,(void *) x, 1, NULL);
   

    // Inicia o scheduler
    vTaskStartScheduler();
  
  return 0;
}

void loop(){}

void vTaskBlinkLed_PB5(void *pvParameters) {
    if((int)pvParameters == 1){
      while(1){
        PINB |= (1 << PB5);  // Liga o LED (coloca o PD4 em nível alto)
        vTaskDelay(1000/portTICK_PERIOD_MS);  // Aguarda 1000 ms
      }
    }
}