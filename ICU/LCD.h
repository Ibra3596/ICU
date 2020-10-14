/*
 * LCD.h
 *
 * Created: 08/08/2020 04:24:43 PM
 *  Author: Ibrahim
 */ 


#ifndef LCD_H_
#define LCD_H_

#include  "LCD_Cfg.h"


void LCD_Init(void);

void LCD_WriteCommand(uint8 cmd);

void LCD_WriteData(uint8 data);

void LCD_GoTo(uint8 roe , uint8 col);

void LCD_WriteString(uint8* str);

void LCD_Clear(void);

void LCD_Write_Intiger(sint32 num);


#endif /* LCD_H_ */