/*Crear una señal PWM con un timer, esa señal la leerá un ADC, hará la conversión a tensión, y
  mandará el valor de esa tensión a otro microprocesasor a través de USART
*/
#include "stm32f100xb.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"
#include "stdint.h"

int main (){
    void pwm_init(1,1000);          //PA6
    void adc_init();
    void usart_init(USART1,9600);   //PA9 y PA10

    while(1){
        int valorADC = adc_read(0); //PA0
        float valorAN = (valorADC/4095)*3.3; // HAGO QUE LA CUENTA SEA FLOTANTE PARA LA COMA
        // AHORA USO MISMA LÓGICA QUE EL BRR PERO CON UN NUMERO SOLO DESPUES DE LA COMA, OSEA QUE MULTIPLICO POR 10
        uint8_t entero = valorAN; // AL IGUALARLO POR UN ENTERO ME VUELA LA PARTE DE LA COMA
        uint8_t coma = ((valorAN-entero)*10); //COMO SOLO VOY A TOMAR UN DECIMAL DESPUES DE LA COMA LO MULTIPLICO POR 10 Y ESTAMOS
        usart_send_char(USART1, entero);
        usart_send_char(USART1, coma);
        /*
        TAMBIEN SE PUEDE MANDAR TODO JUNTO PERO HABRIA QUE HACER UNA NUEVA VARIABLE. QUEDARIA ASI
        uint16_t conversion_en_dos_bytes = ((entero<<8) | coma);
        usart_send_string(USART1, conversion_en_dos_bytes);
        ES LO MISMO :)

        */
    }
}