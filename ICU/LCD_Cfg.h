/*
 * LCD_Cfg.h
 *
 * Created: 08/08/2020 04:25:00 PM
 *  Author: Ibrahim
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "DIO.h"

#define  LCD_8BIT_CMD_PORT     DIO_PORTB
#define  LCD_8BIT_DATA_PORT    DIO_PORTA

#define  LCD_4BIT_CMD_PORT     DIO_PORTB
#define  LCD_4BIT_DATA_PORT    DIO_PORTA


#define  LCD_RS_PIN            DIO_PIN4
#define  LCD_RW_PIN            DIO_PIN5
#define  LCD_E_PIN             DIO_PIN6

#define  LCD_D0                DIO_PIN0
#define  LCD_D1                DIO_PIN1
#define  LCD_D2                DIO_PIN2
#define  LCD_D3                DIO_PIN3
#define  LCD_D4                DIO_PIN4
#define  LCD_D5                DIO_PIN5
#define  LCD_D6                DIO_PIN6
#define  LCD_D7                DIO_PIN7

#define  LCD_MODE              4

#endif /* LCD_CFG_H_ */