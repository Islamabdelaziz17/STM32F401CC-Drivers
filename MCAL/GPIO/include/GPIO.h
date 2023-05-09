/*
 * GPIO.h
 *
 *  Created on: Feb 16, 2023
 *      Author: islam
 */

#include "Std_Types.h"

#ifndef GPIO_H_
#define GPIO_H_

#define PORT_CAPACITY 16
#define GPIO_PORTA  0
#define GPIO_PORTB  1
#define GPIO_PORTC  2
#define GPIO_PORTD  3
#define GPIO_PORTE  4
#define GPIO_PORTH  5

#define GPIO_PIN0   0
#define GPIO_PIN1   1
#define GPIO_PIN2   2
#define GPIO_PIN3   3
#define GPIO_PIN4   4
#define GPIO_PIN5   5
#define GPIO_PIN6   6
#define GPIO_PIN7   7
#define GPIO_PIN8   8
#define GPIO_PIN9   9
#define GPIO_PIN10  10
#define GPIO_PIN11  11
#define GPIO_PIN12  12
#define GPIO_PIN13  13
#define GPIO_PIN14  14
#define GPIO_PIN15  15

#define GPIO_MODER_BIT_CFG_NUM 2

#define GPIO_MODE_CLEAR_MASK 0xFFFFFFFC

#define GPIO_MODE_INPUT      0x00000000
#define GPIO_MODE_OUTPUT     0x00000001
#define GPIO_MODE_AF         0x00000002
#define GPIO_MODE_ANALOG     0x00000003

#define GPIO_MODE_OUTPUT_PP        0x001
#define GPIO_MODE_OUTPUT_PP_PU     0x101
#define GPIO_MODE_OUTPUT_PP_PD     0x201
#define GPIO_MODE_OUTPUT_OD        0x011
#define GPIO_MODE_OUTPUT_OD_PU     0x111
#define GPIO_MODE_OUTPUT_OD_PD     0x211

#define GPIO_MODE_AF_PP        0x002
#define GPIO_MODE_AF_PP_PU     0x102
#define GPIO_MODE_AF_PP_PD     0x202
#define GPIO_MODE_AF_OD        0x012
#define GPIO_MODE_AF_OD_PU     0x112
#define GPIO_MODE_AF_OD_PD     0x212

#define GPIO_MODE_INPUT_PU     0x10
#define GPIO_MODE_INPUT_PD     0x20
#define GPIO_MODE_INPUT_FLOAT  0x00

//#define GPIO_OUT_STAT_CLEAR_MASK    0xFFFFFFFE
#define GPIO_OUT_STATE_PUSH_PULL    0x00000000
#define GPIO_OUT_STATE_OPEN_DRAIN   0x00000001

#define GPIO_SPEED_CLEAR_MASK     0xFFFFFFFC
#define GPIO_SPEED_LOW            0x00000000
#define GPIO_SPEED_MED            0x00000001
#define GPIO_SPEED_HIGH           0x00000002
#define GPIO_SPEED_VHIGH          0x00000003

#define GPIO_PUPD_CLEAR_MASK      0xFFFFFFFC
#define GPIO_INTERAL_NO_PU_PD     0x00000000
#define GPIO_INTERNAL_PULL_UP     0x00000001
#define GPIO_INTERNAL_PULL_DOWN   0x00000002

#define GPIO_BIT_SET 1
#define GPIO_BIT_RESET 0

#define  GPIO_AF0	0
#define  GPIO_AF1	1
#define  GPIO_AF2	2
#define  GPIO_AF3	3
#define  GPIO_AF4	4
#define  GPIO_AF5	5
#define  GPIO_AF6	6
#define  GPIO_AF7	7
#define  GPIO_AF8	8
#define  GPIO_AF9	9
#define  GPIO_AF10	10
#define  GPIO_AF11	11
#define  GPIO_AF12	12
#define  GPIO_AF13	13
#define  GPIO_AF14	14
#define  GPIO_AF15	15


typedef enum
{

    GPIO_enuOK,
    GPIO_enuNOTOK

} GPIO_enuErrorStatus_t;

typedef struct
{
    u32 Pin_Num;
    u32 Port_Num;
    u32 Mode;
    u32 Speed;

}GPIO_Cfg_t;


GPIO_enuErrorStatus_t GPIO_enuInit(GPIO_Cfg_t * Addrpstr_ModuleCfg);

GPIO_enuErrorStatus_t GPIO_enuWritePin(u32 Cpy_PortNum,u32 Cpy_PinNum,u32 Cpy_GPIO_SetReset_Val);

GPIO_enuErrorStatus_t GPIO_enuSelectAF(u32 GPIO_AF_Num,u8 Cpy_PortNum,u8 Cpy_PinNum);

GPIO_enuErrorStatus_t GPIO_enuSetPort(u8 Cpy_u8PortNum,u16 Cpy_u16PortVal);

GPIO_enuErrorStatus_t GPIO_enuReadPort(u8 Cpy_u8PortNum,u16* Addrpu16PortReading);

#endif /* GPIO_H_ */
