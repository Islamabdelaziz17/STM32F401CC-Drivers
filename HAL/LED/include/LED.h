/**********************/
/*LED INTERAFCE FILE  */
/*********************/

#include "LED_Cfg.h"

#ifndef LED_H_
#define LED_H_

#define LED_STATE_ON  1
#define LED_STATE_OFF 0

typedef enum
{
	LED_enuOk = 0,
	LED_enuNotOk = 1

}LED_tenuErrorStatus;

/**************************/
/* LED Initialization Function
------------------------------*/
void LED_vidInit();

/**************************/
/* LED Set Status Function
Input: LedNumber (Range according to led enum cfg)
*/
/**************************/
LED_tenuErrorStatus LED_enuSetLedStatus(Leds_enu_t Cpy_enuled, u8 Cpy_LedState);

#endif /* LED_H_ */
