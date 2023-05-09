
#include "Std_Types.h"

#ifndef LCD_CFG_H
#define LCD_CFG_H

#define NUMBER_OF_LCDS          1
#define LCD_NUMBER_OF_PINS 		10

#define _BIT_INIT_MODE          8

#define LCD_NUMBER_OF_LINES     1
#define LCD_FONT_CFG            1
#define LCD_DISPLAY_ON          1
#define LCD_CURSOR_ON           0
#define LCD_CURSOR_BLINK        0

#define NUMBER_OF_USER_REQS     1

typedef enum
{
	LCD_enuPin0 = 0,
	LCD_enuPin1,
	LCD_enuPin2,
	LCD_enuPin3,
	LCD_enuPin4,
	LCD_enuPin5,
	LCD_enuPin6,
	LCD_enuPin7,
	LCD_enuRS,
	LCD_enuRW,
	LCD_enuEnable

}LCD_PortPinsCfg_t;

typedef enum
{
	LCD_enuPortA = 0,
    LCD_enuPortB,
    LCD_enuPortC,
    LCD_enuPortD,
    LCD_enuPortE
}LCD_PortCfg_t;

typedef struct{
	u8* Lcd_pu8Pins;
    LCD_PortCfg_t Port;
}LCD_strCfg_t;

extern const LCD_strCfg_t LCD_strCfg[NUMBER_OF_LCDS];

#endif