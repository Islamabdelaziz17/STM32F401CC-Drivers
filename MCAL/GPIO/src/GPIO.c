/*
 * GPIO.c
 *
 *  Created on: Feb 16, 2023
 *      Author: islam
 */
#include "Std_Types.h"
#include "include/GPIO.h"

#define NUMBER_OF_GPIOS 6
#define GPIOA_BASEADDRESS 0x40020000
#define GPIOB_BASEADDRESS 0x40020400
#define GPIOC_BASEADDRESS 0x40020800
#define GPIOD_BASEADDRESS 0x40020C00
#define GPIOE_BASEADDRESS 0x40021000
#define GPIOH_BASEADDRESS 0x40021C00

typedef struct
{
    u32 GPIO_MODER;
    u32 GPIO_OTYPER;
    u32 GPIO_OSPEEDR;
    u32 GPIO_PUPDR;
    u32 GPIO_IDR;
    u32 GPIO_ODR;
    u32 GPIO_BSRR;
    u32 GPIO_LCKR;
    u32 GPIO_AFRL;
    u32 GPIO_AFRH;
} GPIOx_t;

volatile GPIOx_t *const GPIOx[NUMBER_OF_GPIOS] = {(volatile GPIOx_t *)GPIOA_BASEADDRESS,
                                                  (volatile GPIOx_t *)GPIOB_BASEADDRESS,
                                                  (volatile GPIOx_t *)GPIOC_BASEADDRESS,
                                                  (volatile GPIOx_t *)GPIOD_BASEADDRESS,
                                                  (volatile GPIOx_t *)GPIOE_BASEADDRESS,
                                                  (volatile GPIOx_t *)GPIOH_BASEADDRESS};

GPIO_enuErrorStatus_t GPIO_enuInit(GPIO_Cfg_t *Addrpstr_ModuleCfg)
{
    GPIO_enuErrorStatus_t Local_enuErrorstat = GPIO_enuOK;
    u32 Local_u32GPIO_MODER,
        Local_u32GPIO_OTYPER,
        Local_u32GPIO_OSPEEDR,
        Local_u32GPIO_PUPDR,
        Local_u32ClearMask,
        Local_u32CurrentCfg;

    if (Addrpstr_ModuleCfg != 0)
    {

        Local_u32GPIO_MODER = GPIOx[Addrpstr_ModuleCfg->Port_Num]->GPIO_MODER;
        Local_u32GPIO_OSPEEDR = GPIOx[Addrpstr_ModuleCfg->Port_Num]->GPIO_OSPEEDR;
        Local_u32CurrentCfg = Addrpstr_ModuleCfg->Mode;

        Local_u32ClearMask = GPIO_MODE_CLEAR_MASK;
        Local_u32ClearMask = (Local_u32ClearMask << (Addrpstr_ModuleCfg->Pin_Num * GPIO_MODER_BIT_CFG_NUM)) | (Local_u32ClearMask >> (8 * sizeof(Local_u32ClearMask) - Addrpstr_ModuleCfg->Pin_Num * GPIO_MODER_BIT_CFG_NUM));

        
        Local_u32GPIO_MODER &= Local_u32ClearMask;

        //Local_u32CurrentCfg &= 0x001;

        Local_u32GPIO_MODER |= (Local_u32CurrentCfg << (Addrpstr_ModuleCfg->Pin_Num * GPIO_MODER_BIT_CFG_NUM));
        GPIOx[Addrpstr_ModuleCfg->Port_Num]->GPIO_MODER = Local_u32GPIO_MODER;

        if (Addrpstr_ModuleCfg->Mode != GPIO_MODE_INPUT_FLOAT || Addrpstr_ModuleCfg->Mode != GPIO_MODE_INPUT_PD || Addrpstr_ModuleCfg->Mode != GPIO_MODE_INPUT_PU)
        {
            Local_u32GPIO_OTYPER = GPIOx[Addrpstr_ModuleCfg->Port_Num]->GPIO_OTYPER;
           
            Local_u32CurrentCfg >>= 4;
            Local_u32CurrentCfg &= 0x001;
            Local_u32GPIO_OTYPER &= ~(Local_u32CurrentCfg << Addrpstr_ModuleCfg->Pin_Num);
            Local_u32GPIO_OTYPER |= (Local_u32CurrentCfg << Addrpstr_ModuleCfg->Pin_Num);
            GPIOx[Addrpstr_ModuleCfg->Port_Num]->GPIO_OTYPER = Local_u32GPIO_OTYPER;
        }

        Local_u32GPIO_OSPEEDR &= Local_u32ClearMask;
        Local_u32GPIO_OSPEEDR |= (Addrpstr_ModuleCfg->Speed << (Addrpstr_ModuleCfg->Pin_Num * GPIO_MODER_BIT_CFG_NUM));
        GPIOx[Addrpstr_ModuleCfg->Port_Num]->GPIO_OSPEEDR = Local_u32GPIO_OSPEEDR;

        Local_u32GPIO_PUPDR &= Local_u32ClearMask;
        Local_u32CurrentCfg >>= 4;
        Local_u32CurrentCfg &= 0x001;
        Local_u32GPIO_PUPDR |= (Local_u32CurrentCfg << (Addrpstr_ModuleCfg->Pin_Num * GPIO_MODER_BIT_CFG_NUM));
        GPIOx[Addrpstr_ModuleCfg->Port_Num]->GPIO_PUPDR = Local_u32GPIO_PUPDR;
    }
    else
    {
        Local_enuErrorstat = GPIO_enuNOTOK;
    }

    return Local_enuErrorstat;
}

GPIO_enuErrorStatus_t GPIO_enuWritePin(u32 Cpy_PortNum,u32 Cpy_PinNum,u32 Cpy_GPIO_SetReset_Val)
{
    GPIO_enuErrorStatus_t local_enuErrorstat = GPIO_enuOK;
    u32 Local_u32GPIO_BSRR;

    if(Cpy_PortNum >= GPIO_PORTA && Cpy_PortNum <= GPIO_PORTH)
    {
        if(Cpy_PinNum >= GPIO_PIN0 && Cpy_PinNum <= GPIO_PIN15)
        {
            Local_u32GPIO_BSRR = GPIOx[Cpy_PortNum]->GPIO_BSRR;
            if(Cpy_GPIO_SetReset_Val == GPIO_BIT_SET)
            {
                Local_u32GPIO_BSRR |= (1<<Cpy_PinNum);
                GPIOx[Cpy_PortNum]->GPIO_BSRR = Local_u32GPIO_BSRR;
                
            }
            else if(Cpy_GPIO_SetReset_Val == GPIO_BIT_RESET)
            {
                Local_u32GPIO_BSRR |= (1<<(Cpy_PinNum+PORT_CAPACITY));
                GPIOx[Cpy_PortNum]->GPIO_BSRR = Local_u32GPIO_BSRR;
            }
            else
            {
                local_enuErrorstat = GPIO_enuNOTOK;
            }

        }
        else
        {
            local_enuErrorstat = GPIO_enuNOTOK;
        }
    }
    else
    {
        local_enuErrorstat = GPIO_enuNOTOK;
    }
    return local_enuErrorstat;
}

GPIO_enuErrorStatus_t GPIO_enuSelectAF(u32 GPIO_AF_Num,u8 Cpy_PortNum,u8 Cpy_PinNum)
{
    GPIO_enuErrorStatus_t local_enuErrorstat = GPIO_enuOK;
    u32 Local_u32GPIO_AFR;

    if((Cpy_PortNum >= GPIO_PORTA) && (Cpy_PortNum <= GPIO_PORTH))
    {
        if((Cpy_PinNum >= GPIO_PIN0) && (Cpy_PinNum <= GPIO_PIN7))
        {
			Local_u32GPIO_AFR = GPIOx[Cpy_PortNum]->GPIO_AFRL;
			Local_u32GPIO_AFR |=  (GPIO_AF_Num << ((Cpy_PinNum * 4)));
			GPIOx[Cpy_PortNum]->GPIO_AFRL = Local_u32GPIO_AFR;
        }
		else if((Cpy_PinNum >= GPIO_PIN8) && (Cpy_PinNum <= GPIO_PIN15))
		{
			Local_u32GPIO_AFR = GPIOx[Cpy_PortNum]->GPIO_AFRH;
			Local_u32GPIO_AFR |= (GPIO_AF_Num << ((Cpy_PinNum-8) * 4));
			GPIOx[Cpy_PortNum]->GPIO_AFRH = Local_u32GPIO_AFR;
		}
        else
        {
            local_enuErrorstat = GPIO_enuNOTOK;
        }
    }
    else
    {
        local_enuErrorstat = GPIO_enuNOTOK;
    }
    return local_enuErrorstat;

}


GPIO_enuErrorStatus_t GPIO_enuSetPort(u8 Cpy_u8PortNum,u16 Cpy_u16PortVal)
{
    GPIO_enuErrorStatus_t local_enuErrorstat = GPIO_enuOK;
    u32 Local_u32GPIO_ODR;

    if(Cpy_u8PortNum >= GPIO_PORTA && Cpy_u8PortNum <= GPIO_PORTH)
    {
        Local_u32GPIO_ODR = GPIOx[Cpy_u8PortNum]->GPIO_ODR;
        Local_u32GPIO_ODR = Cpy_u16PortVal;
        GPIOx[Cpy_u8PortNum]->GPIO_ODR = Local_u32GPIO_ODR;
    }
    else
    {
        Local_u32GPIO_ODR = GPIO_enuNOTOK;
    }
    return local_enuErrorstat;
}

GPIO_enuErrorStatus_t GPIO_enuReadPort(u8 Cpy_u8PortNum,u16* Addrpu16PortReading)
{
    GPIO_enuErrorStatus_t local_enuErrorstat = GPIO_enuOK;
    u32 Local_u32GPIO_IDR;

    if(Cpy_u8PortNum >= GPIO_PORTA && Cpy_u8PortNum <= GPIO_PORTH)
    {
        Local_u32GPIO_IDR = GPIOx[Cpy_u8PortNum]->GPIO_IDR;
        *Addrpu16PortReading = Local_u32GPIO_IDR;
    }
    else
    {
        Local_u32GPIO_IDR = GPIO_enuNOTOK;
    }
    return local_enuErrorstat;

}
