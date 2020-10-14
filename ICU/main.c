/*
 * ICU.c
 *
 * Created: 8/28/2020 7:02:12 PM
 * Author : Ibrahim
 */ 

#include "Timer.h"
#include "LCD.h"

extern uint32 ICU_CaptValue_1 ;
extern uint32 ICU_CaptValue_2 ;
extern uint32 ICU_CaptValue_3 ;

extern uint8 Cap_Counter;





int main(void)
{
	uint32 duty =0;
	uint32 freq = 0;
	
	PWM2_Init();
	PWM2_Generate(60);
	
	ICU_Init();
	
	LCD_Init();
	
	

    while (1) 
    {
		
		if (Cap_Counter ==3)
		{
			duty = ((ICU_CaptValue_2 - ICU_CaptValue_1) * 100) / (ICU_CaptValue_3 - ICU_CaptValue_1);
			
			freq = 8000000 / (ICU_CaptValue_3 - ICU_CaptValue_1);
			
			LCD_GoTo(0,0);
			LCD_WriteString("DUTY Cycle: ");
			LCD_Write_Intiger(duty);
			LCD_WriteData('%');
			
			LCD_GoTo(1,0);
			LCD_WriteString("Freq:");
			LCD_Write_Intiger(freq);
			LCD_WriteString("Hz");
			
			//reassign cap counter to 0
			Cap_Counter = 0;
			
			//re enable ICU interrupt
			SET_BIT(TIMSK , 5);
		
		}
    }
}

