/*
 * Timer.h
 *
 * Created: 21/08/2020 06:33:35 PM
 *  Author: Ibrahim
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "ATmega_Registers.h"
#include "BIT_Math.h"

void Timer0_Init(void);

void Timer0_Start(void);

void Timer0_Stop(void);

void Timer0_SetDelay(uint32 Delay_Ms);


void PWM0_Init(void);

void PWM0_Generate(uint16 Duty_Cycle);

void PWM0_Start(void);



void Set_CallBack(void(*p)(void));

void Timer1_Init(void);

void Timer1_Start(void);

void Timer1_Stop(void);

void Timer1_SetDelay(uint32 Delay_Ms);


void PWM1_Init(void);

void PWM1_Generate(uint16 Duty_cycle);

void PWM1_Start(void);


void PWM2_Init(void);

void PWM2_Generate(uint32 duty_cycle);


void ICU_Init(void);




#endif /* TIMER_H_ */
