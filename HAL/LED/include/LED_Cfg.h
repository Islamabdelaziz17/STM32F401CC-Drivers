
#include "Std_Types.h"
#ifndef LED_CFG_H_
#define LED_CFG_H_


#define ACTIVE_HIGH 0
#define ACTIVE_LOW 1

typedef enum{

 Led_enu20ms,
 Led_enu100ms,
 Led_enu500ms,
 Led_enuCount

}Leds_enu_t;

typedef struct
{
  u8 LED_ActiveMode;
  u8 LED_Port;
  u8 LED_Pin;
  u8 SPEED;

}LED_strPinCfg_t;

extern const LED_strPinCfg_t LED_strPinCfg[Led_enuCount];

#endif /* LED_CFG_H_ */
