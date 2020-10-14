/*
 * Timer.c
 *
 * Created: 21/08/2020 06:33:49 PM
 *  Author: Ibrahim
 */ 



#include <avr/interrupt.h>
#include "Timer.h"

#define  NULL  ((void*)(0))

void (*ptr)(void) = NULL ;


uint8    Init_Value = 0;
uint32   Number_OVRflows = 0;


volatile uint32 Timer1_OVF = 0;

volatile uint32 ICU_CaptValue_1 = 0;
volatile uint32 ICU_CaptValue_2 = 0;
volatile uint32 ICU_CaptValue_3 = 0;

volatile uint8 Cap_Counter = 0;



void Timer0_Init(void)
{
	
	TCCR0 |= 0x00;
	
	TIMSK |= 0x01;
	
	SREG |= 0x80;
	
}

void Timer0_Start(void)
{
	TCCR0 |= 0x05;
}

void Timer0_Stop(void)
{
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}



void Timer0_SetDelay(uint32 Delay_Ms)
{
	
	uint8 Tick_Time = (1024 / 8) ;
	
	uint32 Total_Ticks = (Delay_Ms * 1000) / Tick_Time ;
	
	Number_OVRflows = Total_Ticks / 256 ;
	
	Init_Value  =   256 - (Total_Ticks % 256) ;
	
	TCNT0 = Init_Value ;
	
	Number_OVRflows++;
	
}



void Timer1_Init(void)
{
	TCCR1B |= 0X08 ;
	TIMSK  |= 0X10;
	SREG   |= 0X80;
}

void Timer1_Start(void)
{
	TCCR1B |= 0X05 ;
}

void Timer1_Stop(void)
{
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}


void Timer1_SetDelay(uint32 Delay_Ms)
{
	
	if(Delay_Ms <= 4000)
	{
		uint8 Tick_Time = 1024 / 16;
		
		uint32 Num_Ticks = (Delay_Ms * 1000) / Tick_Time ;
		
		OCR1A = Num_Ticks - 1;
	}
	
}

void PWM1_Init(void)
{
	//setting pin 5 in port D to output direction
	DDRD |= 0x20;
	
	TCCR1A |= 0x02;
	TCCR1B |= 0x18;
	
	// setting the top of TCNT to our desired max value
	ICR1	= 625; // 625; //if osc 8MHZ , 1250 for 16mhz
}

void PWM1_Generate(uint16 Duty_cycle)
{
						// 625 //if osc 8MHZ ,, 1250 for 16mhz
	OCR1A = ((Duty_cycle * 625)/100) -1 ;
	
}

void PWM1_Start(void)
{
	TCCR1B |= 0x04;  // enable clk in a pre-scaler clk/256	
}

void PWM2_Init(void)
{
	DDRD  |= 0x80;	//PD7 Direction output
	TCCR2 |= 0x6A; // fast pwm // non inverted //prescaler clk/8
}

void PWM2_Generate(uint32 duty_cycle)
{
	OCR2 = ((duty_cycle *256)/100)-1 ;
}

void PWM2_Start(void)
{
	
	TCCR2 |= 0x07 ; //prescaler clk/128
	
}


void Set_CallBack(void(*p)(void))
{
	
	ptr = p ;
	
}



ISR(TIMER0_OVF_vect)
{
	static uint32 cnt = 0;
	
	cnt++;
	
	if(cnt == Number_OVRflows)
	{
		TCNT0 = Init_Value;
		
		cnt = 0;
		
		(*ptr)();
	}
}



ISR(TIMER1_COMPA_vect)
{
	static counter = 0;
	
	counter++;
	
	if(counter == 1)
	{
		counter = 0;
		
		(*ptr)();
	}
}


void PWM0_Init(void)
{
	DDRB |= 0x08;
	
	TCCR0 |= 0x68;
	
}


void PWM0_Generate(uint16 Duty_Cycle)
{
	OCR0 = ((Duty_Cycle * 256 ) /100 ) - 1;
}



void PWM0_Start(void)
{
	
	TCCR0 |= 0x01 ;
	
}


void ICU_Init(void)
{
	//input capture pin (ICP) port D pin-6 set to input(0)
	CLR_BIT(DDRD , 6); 
	
	// Initial ICR1 Value of zero
	ICR1  |= 0x0000;

	TCCR1B  |= 0x41;  //to enable rising edge detection by setting bit 6  and ad setting bit 0 to enable clock
	
	//enable ICU interrupt bit 5 & Timer1 overflow interrupt bit 2  (0010 0100)
	TIMSK |= 0x24;
	
	//Enable global interrupt
	
	SREG |= 0x80; // set 7th bit 1000 0000
	
}

ISR(TIMER1_CAPT_vect)
{
	Cap_Counter++;
	if (Cap_Counter == 1)
	{
		ICU_CaptValue_1 = ICR1;
		
		Timer1_OVF = 0;
		
		// change next edge detection to falling edge
		CLR_BIT(TCCR1B , 6);
	}
	else if (Cap_Counter == 2)
	{
		ICU_CaptValue_2 = ICR1 +(Timer1_OVF * 65535);
		
		// change next detection to Rising edge
		SET_BIT(TCCR1B , 6);
	}
	
		else if (Cap_Counter == 3)
		{
			ICU_CaptValue_3 = ICR1 +(Timer1_OVF * 65535);
			
			//disable ICU interrupt
			CLR_BIT (TIMSK , 5);
		}
}

// timer 1 overflow interrupt to count overflows
ISR(TIMER1_OVF_vect)
{
	Timer1_OVF ++;
	
}