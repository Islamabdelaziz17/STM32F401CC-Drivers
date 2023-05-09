#include "include/NVIC.h"

#define NVIC_BASEADDRESS          0xE000E100
#define AIRCR                     *((volatile u32*)(0xE000ED0C + 0x0C))
#define NVIC_REG_SIZE             32
#define NVIC_PRE_IMPLEMENTED_BITS 4

typedef struct  
{
    u32 ISER[8];
    u32 RESERVED0[24];
    u32 ICER[8];
    u32 RESERVED1[24];
    u32 ISPR[8];
    u32 RESERVED2[24];
    u32 ICPR[8];
    u32 RESERVED3[24];
    u32 IABR[8];
    u32 RESERVED4[56];
    u32 IPR[60];
    u32 RESERVED[644];
    u32 STIR;

} NVIC_def_t;

volatile NVIC_def_t *const NVIC = (volatile NVIC_def_t *)NVIC_BASEADDRESS;

Nvic_enuErrorStatus NVIC_EnableIRQ(IRQn_Type IRQn)
{
    Nvic_enuErrorStatus Local_Nvicenuerrorstat = Nvic_enuOk;
    u8 Local_u8IRQRegIndex = 0;
    u8 Local_u8IRQRegPosition = 0;
    if (IRQn >= WWDG_IRQn && IRQn <= SPI4_IRQn)
    {
        Local_u8IRQRegIndex = IRQn/NVIC_REG_SIZE;
        Local_u8IRQRegPosition = IRQn%NVIC_REG_SIZE;
        NVIC->ISER[Local_u8IRQRegIndex] |= (1<<Local_u8IRQRegPosition);
    }
    else
    {
        Local_Nvicenuerrorstat = Nvic_enuNOk;
    }
    return Local_Nvicenuerrorstat;
}

Nvic_enuErrorStatus NVIC_DisableIRQ(IRQn_Type IRQn)
{
    Nvic_enuErrorStatus Local_Nvicenuerrorstat = Nvic_enuOk;
    u8 Local_u8IRQRegIndex = 0;
    u8 Local_u8IRQRegPosition = 0;
    if (IRQn >= WWDG_IRQn && IRQn <= SPI4_IRQn)
    {
        Local_u8IRQRegIndex = IRQn/NVIC_REG_SIZE;
        Local_u8IRQRegPosition = IRQn%NVIC_REG_SIZE;
        NVIC->ICER[Local_u8IRQRegIndex] |= (1<<Local_u8IRQRegPosition);
    }
    else
    {
        Local_Nvicenuerrorstat = Nvic_enuNOk;
    }
    return Local_Nvicenuerrorstat;
}

Nvic_enuErrorStatus NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    Nvic_enuErrorStatus Local_Nvicenuerrorstat = Nvic_enuOk;
    u8 Local_u8IRQRegIndex = 0;
    u8 Local_u8IRQRegPosition = 0;
    if (IRQn >= WWDG_IRQn && IRQn <= SPI4_IRQn)
    {
        Local_u8IRQRegIndex = IRQn/NVIC_REG_SIZE;
        Local_u8IRQRegPosition = IRQn%NVIC_REG_SIZE;
        NVIC->ISPR[Local_u8IRQRegIndex] |= (1<<Local_u8IRQRegPosition);
    }
    else
    {
        Local_Nvicenuerrorstat = Nvic_enuNOk;
    }
    return Local_Nvicenuerrorstat;
}

Nvic_enuErrorStatus NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    Nvic_enuErrorStatus Local_Nvicenuerrorstat = Nvic_enuOk;
    u8 Local_u8IRQRegIndex = 0;
    u8 Local_u8IRQRegPosition = 0;
    if (IRQn >= WWDG_IRQn && IRQn <= SPI4_IRQn)
    {
        Local_u8IRQRegIndex = IRQn/NVIC_REG_SIZE;
        Local_u8IRQRegPosition = IRQn%NVIC_REG_SIZE;
        NVIC->ICPR[Local_u8IRQRegIndex] |= (1<<Local_u8IRQRegPosition);
    }
    else
    {
        Local_Nvicenuerrorstat = Nvic_enuNOk;
    }
    return Local_Nvicenuerrorstat;
}

Nvic_enuErrorStatus NVIC_GetPendingIRQ(IRQn_Type IRQn, u8 *Addrpu8CurrentStatus)
{
    Nvic_enuErrorStatus Local_Nvicenuerrorstat = Nvic_enuOk;
    u8 Local_u8IRQRegIndex = 0;
    u8 Local_u8IRQRegPosition = 0;
    if (IRQn >= WWDG_IRQn && IRQn <= SPI4_IRQn)
    {
        Local_u8IRQRegIndex = IRQn/NVIC_REG_SIZE;
        Local_u8IRQRegPosition = IRQn%NVIC_REG_SIZE;
        *Addrpu8CurrentStatus = ((NVIC->ISPR[Local_u8IRQRegIndex]) >> (NVIC_REG_SIZE - Local_u8IRQRegPosition)) & 0x01;
    }
    else
    {
        Local_Nvicenuerrorstat = Nvic_enuNOk;
    }
    return Local_Nvicenuerrorstat;

}

Nvic_enuErrorStatus NVIC_SetPriorityGroup(u32 PriorityGroup)
{
    Nvic_enuErrorStatus Local_Nvicenuerrorstat = Nvic_enuOk;
    if(PriorityGroup == PRIGROUP_16 || PriorityGroup == PRIGROUP_8 || PriorityGroup == PRIGROUP_4 || PriorityGroup == PRIGROUP_2 || PriorityGroup == PRIGROUP_NONE)
    {
        AIRCR = PriorityGroup;
    }
    else
    {
        Local_Nvicenuerrorstat = Nvic_enuNOk;
    }
    return Local_Nvicenuerrorstat;
    
}

Nvic_enuErrorStatus NVIC_SetPriority(IRQn_Type IRQn, u8 priority)
{
    Nvic_enuErrorStatus Local_Nvicenuerrorstat = Nvic_enuOk;
    u8 Local_u8IRQRegIndex = 0;
    u8 Local_u8IRQRegPosition = 0;
    if (IRQn >= WWDG_IRQn && IRQn <= SPI4_IRQn)
    {
        Local_u8IRQRegIndex = IRQn/NVIC_REG_SIZE;
        Local_u8IRQRegPosition = IRQn%NVIC_REG_SIZE;
        NVIC->IPR[Local_u8IRQRegIndex] |= ((priority << NVIC_PRE_IMPLEMENTED_BITS)<<Local_u8IRQRegPosition);
    }
    else
    {
        Local_Nvicenuerrorstat = Nvic_enuNOk;
    }
    return Local_Nvicenuerrorstat;
}



Nvic_enuErrorStatus NVIC_GetPriority(IRQn_Type IRQn, u8 *Addrpu8CurrentPriority)
{
    Nvic_enuErrorStatus Local_Nvicenuerrorstat = Nvic_enuOk;
    u8 Local_u8IRQRegIndex = 0;
    u8 Local_u8IRQRegPosition = 0;
    if (IRQn >= WWDG_IRQn && IRQn <= SPI4_IRQn)
    {
        Local_u8IRQRegIndex = IRQn/NVIC_REG_SIZE;
        Local_u8IRQRegPosition = IRQn%NVIC_REG_SIZE;
        *Addrpu8CurrentPriority = ((NVIC->IPR[Local_u8IRQRegIndex]) >> (8 - NVIC_PRE_IMPLEMENTED_BITS));
    }
    else
    {
        Local_Nvicenuerrorstat = Nvic_enuNOk;
    }
    return Local_Nvicenuerrorstat;
}


Nvic_enuErrorStatus NVIC_SetSWTriggerIRQ(IRQn_Type IRQn)
{
    Nvic_enuErrorStatus Local_Nvicenuerrorstat = Nvic_enuOk;
    if (IRQn >= WWDG_IRQn && IRQn <= SPI4_IRQn)
    {
        NVIC->STIR |= IRQn;
    }
    else
    {
        Local_Nvicenuerrorstat = Nvic_enuNOk;
    }
    return Local_Nvicenuerrorstat;
}
