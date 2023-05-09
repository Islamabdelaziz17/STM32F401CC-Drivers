/*
 * Led File.c
 *
 * Created: 1/17/2023 8:28:31 PM
 * Author : Islam
 */ 

#include "include/GPIO.h"
#include "LED.h"



void LED_vidInit()
{
	u8 Local_u8Counter = 0;
	GPIO_Cfg_t GPIO_Cfg;
	for(Local_u8Counter = 0;Local_u8Counter < Led_enuCount;Local_u8Counter++)
	{
		GPIO_Cfg.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_Cfg.Port_Num = LED_strPinCfg[Local_u8Counter].LED_Port;
		GPIO_Cfg.Pin_Num = LED_strPinCfg[Local_u8Counter].LED_Pin;
		GPIO_Cfg.Speed = LED_strPinCfg[Local_u8Counter].SPEED;
		GPIO_enuInit(&GPIO_Cfg);
	}
}



LED_tenuErrorStatus  LED_enuSetLedStatus(Leds_enu_t Cpy_enuLed ,u8 Cpy_LedState)
{
	LED_tenuErrorStatus Local_enuLEDErrorStat = LED_enuOk;
	GPIO_enuErrorStatus_t Local_enGPIOErrorStat = GPIO_enuOK;
	/*Validating Arguments*/
	/*IF THE LED NUMBER EXCEEDS THE PRE-CONFIGUERD NUMBER OF LEDS IN CONFIGURATION FILE*/
	if(Cpy_enuLed >= Led_enuCount)
	{
		Local_enuLEDErrorStat = LED_enuNotOk;
	}
	else
	{
		Local_enGPIOErrorStat = GPIO_enuWritePin(LED_strPinCfg[Cpy_enuLed].LED_Port,LED_strPinCfg[Cpy_enuLed].LED_Pin,Cpy_LedState ^ LED_strPinCfg[Cpy_enuLed].LED_ActiveMode);
	
		/*VALIDATING PIN STATUS AS OUTPUT*/
		if(Local_enGPIOErrorStat != GPIO_enuOK)
		{
			Local_enuLEDErrorStat = LED_enuNotOk;
		}
	}
	return Local_enuLEDErrorStat;
}

