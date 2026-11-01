#include "adc.h"
#include "stm32f103xb.h"
void adc_init(){
    //habilito clock del ADC
    RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;
    //enciendo ADC 1 y espero a que se estabilice
    ADC1->CR2|=ADC_CR2_ADON;
    for(int i=0;i<=1000;i++);
    //reseteo registros y espero a que se ponga en 0
    ADC1->CR2|=ADC_CR2_RSTCAL;
    while(ADC1->CR2&ADC_CR2_RSTCAL);
    //calibro y espero a que se ponga en 0
    ADC1->CR2|=ADC_CR2_CAL;
    while(ADC1->CR2&ADC_CR2_CAL);
    //defino el disparo de las conversiones
    ADC1->CR2|=ADC_CR2_EXTSEL;
    ADC1->CR2|=ADC_CR2_EXTTRIG;
}
int adc_read(canal){
    //activo los correspondientes clocks y configuro los correspondientes pines como entrada analogica
    //canales del 0 al 7 (PA0-PA7) en el puerto A
    if(canal<8){
        RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
        GPIOA->CRL&=~(0xF<<canal*4);
    }
    //canales 8 y 9 (PB0 y PB1) en el puerto B
    else{
        RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
        GPIOB->CRL&=~(0xF<<(canal%2)*4);
    }
    //configuro el tiempo de muestreo en el canal correspondiente
    ADC1->SMPR2|=(0b111<<canal*3);
    //configuro el orden en que va a hacer la conversion(como solo uso un canal utilizo SQ1 en SQR3)
    ADC1->SQR3|=canal;
    //empiezo la conversion
    ADC1->CR2|=ADC_CR2_SWSTART;
    //espero a que termine la conversion.(se pone en 1 cuando termina)
    ADC1->SR|=ADC_SR_EOC;
    while(!(ADC1->SR&ADC_SR_EOC));
    //retorno la conversion
    return ADC1->DR;
}