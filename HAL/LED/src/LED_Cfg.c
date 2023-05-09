
#include "LED_Cfg.h"
#include "include/GPIO.h"

extern const LED_strPinCfg_t LED_strPinCfg[Led_enuCount] = 
{
	
	[Led_enu20ms] = {.LED_ActiveMode =  ACTIVE_HIGH, .LED_Port = GPIO_PORTC, .LED_Pin = GPIO_PIN13,.SPEED = GPIO_SPEED_VHIGH},
	[Led_enu100ms] = {.LED_ActiveMode =  ACTIVE_HIGH, .LED_Port = GPIO_PORTA, .LED_Pin = GPIO_PIN11 ,.SPEED = GPIO_SPEED_VHIGH},
	[Led_enu500ms] = {.LED_ActiveMode =  ACTIVE_HIGH, .LED_Port = GPIO_PORTA, .LED_Pin = GPIO_PIN12 ,.SPEED = GPIO_SPEED_VHIGH},
};
