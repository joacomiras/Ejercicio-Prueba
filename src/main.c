/*Crear una señal PWM con un timer, esa señal la leerá un ADC, hará la conversión a tensión, y
  mandará el valor de esa tensión a otro microprocesasor a través de USART
*/
#include "stm32f100xb.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"

int main (){
    void pwm_init(1,1000);          //PA6
    void adc_init();
    void usart_init(USART1,9600);   //PA9 y PA10

    while(1){
        int valorADC = adc_read(0); //PA0
        int valorAN = (valorADC/4095)*3.3;
        usart_send_string(USART1, valorAN);
    }
}