#ifndef PWM_H
#define PWM_H
void pwm_init(uint8_t canal, uint32_t frec);
void pwm(uint8_t canal , uint8_t duty);
#endif