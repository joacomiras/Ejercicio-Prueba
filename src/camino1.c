/*Crear una señal PWM con un timer, esa señal la leerá un ADC, hará la conversión a tensión, y
  mandará el valor de esa tensión a otro microprocesasor a través de USART.

  ACLARACIÓN: MANDO EL VALOR DE 12 BITS DE UNA
*/
#include "stm32f103xb.h"
#include "pwm.h"
#include "adc.h"
#include "usart.h"
#include "stdint.h"


int main (){
    void pwm_init(1,1000);          //PA6
    void adc_init();
    void usart_init(USART1,9600);   //PA9 y PA10

    while(1){
        uint16_t valor_adc = adc_read(0); //PA0
        // ME QUEDO SOLO CON LOS 8 BITS MSB HACIENDO UNA AND CON 0b111111111 EL RESTO SON 0 Y ENTONCES LOS VUELO 
        uint8_t adc_low = (valor_adc & 0xFF); 
        // DESPLAZANDO VUELO A LOS PRIMEROS 8 BITS Y ME QUEDAN LOS 6 RESTANTES. PARA ASEGURARME QUE SEAN SOLO 6 HAGO UNA AND CON 0x3F (0b111111) Y TENGO SOLO ESOS 6 BITS
        uint8_t adc_high = ((valor_adc >> 8) & 0x3F); 
        // AHORA MANDO POR BYTES
        usart_send_char(USART1, adc_low);
        usart_send_char(USART1, adc_high);
        //SALIO CON FRITAS
    }
}