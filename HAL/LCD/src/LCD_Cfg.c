
#include "LCD_Cfg.h"

u8 LCD1_u8Port_Pins[LCD_NUMBER_OF_PINS] =
{
	[0] = LCD_enuPin0,
	[1] = LCD_enuPin1,
	[2] = LCD_enuPin2,
	[3] = LCD_enuPin3,
	[4] = LCD_enuPin4,
	[5] = LCD_enuPin5,
	[6] = LCD_enuPin6,
	[7] = LCD_enuPin7,
	[8] = LCD_enuRS,
	[9] = LCD_enuRW
};

extern const LCD_strCfg_t LCD_strCfg[NUMBER_OF_LCDS] =
{
	{
        .Lcd_pu8Pins = LCD1_u8Port_Pins,
        .Port = LCD_enuPortA
    }
};