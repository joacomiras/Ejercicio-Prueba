#include "pwm.h"
#include "stm32f103xb.h"
void pwm_init(canal, frec){
    //habilito clock del timer 3
    RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
    //configuro prescaler y ARR
    TIM3->PSC=7;
    TIM3->ARR=((1000000/frec)-1);
    //genero UG
    TIM3->EGR|=TIM_EGR_UG;
    //arranco el contador
    TIM3->CR1|=TIM_CR1_CEN;
    //configuro el canal
    switch(canal){
        case 1:
                //habilito clock
                RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
                //configuro como alternate function push-pull (0xB)
                GPIOA->CRL&=~(0xF<<6*4);
                GPIOA->CRL|=(0xB<<6*4);
                //selecciono el modo
                TIM3->CCMR1 &=~ (0b111<<4);
                TIM3->CCMR1 |= (0b110<<4);
                //habilito el canal 1 fisico
                TIM3->CCER |= TIM_CCER_CC1E;
                break;
        case 2:
                //habilito clock
                RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
                //configuro como alternate function push-pull (0xB)
                GPIOA->CRL&=~(0xF<<7*4);
                GPIOA->CRL|=(0xB<<7*4);
                //selecciono el modo
                TIM3->CCMR1 &=~ (0b111<<12);
                TIM3->CCMR1 |= (0b110<<12);
                //habilito el canal 2 fisico
                TIM3->CCER |= TIM_CCER_CC2E;
                break;
        case 3:
                //habilito clock
                RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
                //configuro como alternate function push-pull (0xB)
                GPIOB->CRL&=~(0xF<<0*4);
                GPIOA->CRL|=(0xB<<0*4);
                //selecciono el modo
                TIM3->CCMR2 &=~ (0b111<<4);
                TIM3->CCMR2 |= (0b110<<4);
                //habilito el canal 3 fisico
                TIM3->CCER |= TIM_CCER_CC3E;
                break;
        case 4:
                //habilito clock
                RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
                //configuro como alternate function push-pull (0xB)
                GPIOB->CRL&=~(0xF<<1*4);
                GPIOB->CRL|=(0xB<<1*4);
                //selecciono el modo
                TIM3->CCMR2 &=~ (0b111<<12);
                TIM3->CCMR2 |= (0b110<<12);
                //habilito el canal 4 fisico
                TIM3->CCER |= TIM_CCER_CC4E;
                break;
        default:
                break;
    }
}
void pwm(canal, duty){
    if(duty>100) duty = 100;
        if(canal==1)             TIM3->CCR1 = (((TIM3->ARR+1)*duty)/100);
        else if(canal==2)        TIM3->CCR2 = (((TIM3->ARR+1)*duty)/100);
        else if(canal==3)        TIM3->CCR3 = (((TIM3->ARR+1)*duty)/100);
        else if(canal==4)        TIM3->CCR4 = (((TIM3->ARR+1)*duty)/100);
}