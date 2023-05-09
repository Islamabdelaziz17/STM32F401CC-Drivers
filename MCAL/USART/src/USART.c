#include "USART.h"
#include "math.h"

#define USART1_BASEADDRESS 0x40011000
#define USART2_BASEADDRESS 0x40004400
#define USART6_BASEADDRESS 0x40011400

#define USART_DIV_FRACTION 0
#define USART_MANTISSA 4
#define OVERSAMPLING_MASK 0x00008000
#define OV8 8
#define OV16 16

#define STOPBITS_MASK 0x00000000F
#define STOP_POS 12
#define USART_EN_POS 13
#define USART_SEND_BREAK_POS 0

#define USART_ENABLE_INTERRUPTS_MASK 0x10000000

#define USART_RXNE_FLAG 0x00000020
#define USART_TXE_FLAG 0x00000080
#define USART_TXC_FLAG 0x00000040
#define USART_LIN_BREAK_DETECTION_FLAG 0x00000100

typedef struct
{
    u32 USART_SR;
    u32 USART_DR;
    u32 USART_BRR;
    u32 USART_CR1;
    u32 USART_CR2;
    u32 USART_CR3;
    u32 USART_GTPR;
} USART_strReg_t;

volatile USART_strReg_t *const USART[USART_COUNT] =
    {
        (volatile USART_strReg_t *)USART1_BASEADDRESS,
        (volatile USART_strReg_t *)USART2_BASEADDRESS,
        (volatile USART_strReg_t *)USART6_BASEADDRESS};

u8 *Global_USART_DR;

USART_strREQ_Handler_t USART_strSendRequest[USART_COUNT], USART_strReceiveRequest[USART_COUNT];

USART_enuErrorStatus USART_Init(USART_strCfg_t *Add_pstrUSART_cfg)
{

    USART_enuErrorStatus Local_enuErrorStatus = USART_enuOK;
    u32 Local_Mode;
    u32 Local_USART_CR1, Local_USART_CR2, Local_BRR, Local_u32Mantissa;
    u16 Local_u16Carry;
    f32 Local_f32USARTDIV, Local_f32Fraction;

    if (!Add_pstrUSART_cfg)
    {
        Local_enuErrorStatus = USART_enuNULLPTR;
    }
    else
    {
        Local_USART_CR1 = USART[Add_pstrUSART_cfg->Channel]->USART_CR1;
        Local_USART_CR2 = USART[Add_pstrUSART_cfg->Channel]->USART_CR2;

        Local_Mode = Add_pstrUSART_cfg->Mode;

        if (Local_Mode == USART_MODE_LIN_BREAK_10BITS || Local_Mode == USART_MODE_LIN_BREAK_11BITS)
        {
            /*Enable Usart*/
            Local_USART_CR1 |= (1 << USART_EN_POS);
            Local_USART_CR2 |= Local_Mode;
        }
        else
        {
            /*Set stop bits based on the cfgs*/
            Local_USART_CR2 |= ((Local_Mode & STOPBITS_MASK) << STOP_POS);

            Local_Mode = (Local_Mode >> 4);

            /*Configure the usart based on the selected mode option*/
            Local_USART_CR1 |= Local_Mode;
        }

        // OVERSAMPLING BY 8
        if ((Local_Mode & OVERSAMPLING_MASK) == OVERSAMPLING_MASK)
        {
            Local_f32USARTDIV = (f32)((f64)SYSCLK / (f64)(OV8 * Add_pstrUSART_cfg->BaudRate));

            Local_f32Fraction = (f32)(Local_f32USARTDIV - (u32)Local_f32USARTDIV);
            Local_f32Fraction = (f32)(Local_f32Fraction * (f32)OV8);
            Local_f32Fraction = ceil(Local_f32Fraction);
        }
        // OVERSAMPLING BY 16
        else
        {
            Local_f32USARTDIV = (f32)((f64)SYSCLK / (f64)(OV8 * 2 * Add_pstrUSART_cfg->BaudRate));
            Local_f32Fraction = (f32)(Local_f32USARTDIV - (u32)Local_f32USARTDIV);
            Local_f32Fraction = (f32)(Local_f32Fraction * (f32)OV16);
            Local_f32Fraction = (u16)ceil(Local_f32Fraction);
        }

        Local_u16Carry = (u16)((u16)Local_f32Fraction - (u8)Local_f32Fraction);
        if (!Local_u16Carry)
        {
            Local_u32Mantissa = (u32)Local_f32USARTDIV;
        }
        else
        {
            Local_u32Mantissa = (u32)(floor((u32)Local_f32USARTDIV) + ((u16)Local_u16Carry));
            Local_f32Fraction = (u8)Local_f32Fraction;
        }

        /*Setting USERDIV for the desired baudrate*/
        Local_BRR = (Local_u32Mantissa << USART_MANTISSA);
        Local_BRR |= ((u32)Local_f32Fraction << USART_DIV_FRACTION);

        // Enable TX OR RX OR BOTH DIRECTIONS
        Local_USART_CR1 |= Add_pstrUSART_cfg->DataDirection;

        USART[Add_pstrUSART_cfg->Channel]->USART_CR2 = Local_USART_CR2;
        USART[Add_pstrUSART_cfg->Channel]->USART_BRR = Local_BRR;
        USART[Add_pstrUSART_cfg->Channel]->USART_CR1 = Local_USART_CR1;
    }

    return Local_enuErrorStatus;
}

USART_enuErrorStatus USART_EnableInterrupts(Stm32f401_USART_enuChannel_t Channel, u32 Cpy_u32InterruptFlag)
{
    USART_enuErrorStatus Local_enuErrorStatus = USART_enuOK;
    u32 Local_USART_CR2, Local_USART_CR1;
    if ((Channel >= USART1) && (Channel <= USART6))
    {
        /*USART-CR2 REGISTER ACCESS*/
        if ((Cpy_u32InterruptFlag & USART_ENABLE_INTERRUPTS_MASK) == USART_ENABLE_INTERRUPTS_MASK)
        {
            Local_USART_CR2 = USART[Channel]->USART_CR2;
            Cpy_u32InterruptFlag = Cpy_u32InterruptFlag & (~USART_ENABLE_INTERRUPTS_MASK);
            Local_USART_CR2 |= Cpy_u32InterruptFlag;
            USART[Channel]->USART_CR2 = Local_USART_CR2;
        }
        /*USART-CR1 REGISTER ACCESS*/
        else
        {
            Local_USART_CR1 = USART[Channel]->USART_CR1;
            Local_USART_CR1 |= Cpy_u32InterruptFlag;
        }
        USART[Channel]->USART_CR1 = Local_USART_CR1;
    }
    else
    {
        Local_enuErrorStatus = USART_enuNOK;
    }
    return Local_enuErrorStatus;
}

USART_enuErrorStatus USART_DisableInterrupts(Stm32f401_USART_enuChannel_t Channel, u32 Cpy_u32InterruptFlag)
{
    USART_enuErrorStatus Local_enuErrorStatus = USART_enuOK;
    u32 Local_USART_CR2, Local_USART_CR1;
    if (Channel >= USART1 && Channel < USART6)
    {
        /*USART-CR2 REGISTER ACCESS*/
        if ((Cpy_u32InterruptFlag & USART_ENABLE_INTERRUPTS_MASK) == USART_ENABLE_INTERRUPTS_MASK)
        {
            Local_USART_CR2 = USART[Channel]->USART_CR2;
            Cpy_u32InterruptFlag = Cpy_u32InterruptFlag & (~USART_ENABLE_INTERRUPTS_MASK);
            Local_USART_CR2 &= (~Cpy_u32InterruptFlag);
            USART[Channel]->USART_CR2 = Local_USART_CR2;
        }
        /*USART-CR1 REGISTER ACCESS*/
        else
        {
            Local_USART_CR1 = USART[Channel]->USART_CR1;
            Local_USART_CR1 &= (~Cpy_u32InterruptFlag);
        }
        USART[Channel]->USART_CR1 = Local_USART_CR1;
    }
    else
    {
        Local_enuErrorStatus = USART_enuNOK;
    }
    return Local_enuErrorStatus;
}

USART_enuErrorStatus USART_IsRX(Stm32f401_USART_enuChannel_t Channel)
{
    USART_enuErrorStatus Local_enuErrorStatus = USART_enuOK;
    if ((Channel >= USART1) && (Channel <= USART6))
    {
        if ((USART[Channel]->USART_SR & USART_RXNE_FLAG) == USART_RXNE_FLAG)
        {
            Local_enuErrorStatus = USART_enuRX_DONE;
        }
        else
        {
            Local_enuErrorStatus = USART_enuRX_BUSY;
        }
    }
    else
    {
        Local_enuErrorStatus = USART_enuNOK;
    }
    return Local_enuErrorStatus;
}

USART_enuErrorStatus USART_IsTX(Stm32f401_USART_enuChannel_t Channel)
{
    USART_enuErrorStatus Local_enuErrorStatus = USART_enuOK;
    u32 Local_USART_SR;
    if ((Channel >= USART1) && (Channel <= USART6))
    {

        Local_USART_SR = USART[Channel]->USART_SR;

        if ((Local_USART_SR & USART_TXC_FLAG) == USART_TXC_FLAG)
        {
            Local_enuErrorStatus = USART_enuTX_DONE;
        }
        else
        {
            Local_enuErrorStatus = USART_enuTX_BUSY;
        }
    }
    else
    {
        Local_enuErrorStatus = USART_enuNOK;
    }
    return Local_enuErrorStatus;
}

USART_enuErrorStatus USART_SendBufferAsyncZeroCopy(u8 *Add_pu8Buffer, u32 Cpy_u32Size, USART_Cbf NotifyCbf, Stm32f401_USART_enuChannel_t Channel)
{
    USART_enuErrorStatus Local_enuErrorStatus = USART_enuOK;
    if (Add_pu8Buffer)
    {
        if (USART_strSendRequest[Channel].Status == USART_enuIDLE)
        {
            USART_strSendRequest[Channel].Buffer = Add_pu8Buffer;
            USART_strSendRequest[Channel].Size = Cpy_u32Size;
            USART_strSendRequest[Channel].Idx = 0;
            USART_strSendRequest[Channel].NotifyCbf = NotifyCbf;
            USART_strSendRequest[Channel].Status = USART_enuBUSY;
            USART[Channel]->USART_DR = (u8)USART_strSendRequest[Channel].Buffer[USART_strSendRequest[Channel].Idx];
            USART_EnableInterrupts(Channel, USART_TX_COMPLETE_INTERRUPT_FLAG);
            USART_strSendRequest[Channel].Idx++;
        }
        else
        {
            Local_enuErrorStatus = USART_enuTX_BUSY;
        }
    }
    else
    {
        Local_enuErrorStatus = USART_enuNULLPTR;
    }
    return Local_enuErrorStatus;
}

USART_enuErrorStatus USART_ReceiveBufferAsyncZeroCopy(u8 *Add_pu8Buffer, u32 Cpy_u32Size, USART_Cbf NotifyCbf, Stm32f401_USART_enuChannel_t Channel)
{
    USART_enuErrorStatus Local_enuErrorStatus = USART_enuOK;
    u32 Local_USART_SR;

    if (Add_pu8Buffer)
    {
        if (USART_strReceiveRequest[Channel].Status == USART_enuIDLE)
        {
            USART_strReceiveRequest[Channel].Buffer = Add_pu8Buffer;
            USART_strReceiveRequest[Channel].Size = Cpy_u32Size;
            USART_strReceiveRequest[Channel].Idx = 0;
            USART_strReceiveRequest[Channel].NotifyCbf = NotifyCbf;

            /*CLEARING RX COMPLETE IN THE STATUS REGISTER*/
            Local_USART_SR = USART[Channel]->USART_SR;
            Local_USART_SR &= (~USART_RXNE_FLAG);
            USART_strReceiveRequest[Channel].Status = USART_enuBUSY;

            /*ENABLING RX INTERRUPT*/
            USART_EnableInterrupts(Channel, USART_RX_COMPLETE_INTERRUPT_FLAG);
        }
        else
        {
            Local_enuErrorStatus = USART_enuTX_BUSY;
        }
    }
    else
    {
        Local_enuErrorStatus = USART_enuNULLPTR;
    }
    return Local_enuErrorStatus;
}

void USART_vidSendBreak(Stm32f401_USART_enuChannel_t Channel)
{
    u32 Local_USART_CR1;

    Local_USART_CR1 = USART[Channel]->USART_CR1;
    Local_USART_CR1 |= (1<<USART_SEND_BREAK_POS);
    
    USART[Channel]->USART_CR1 = Local_USART_CR1;
}

void USART1_IRQHandler(void)
{

    if (USART_IsTX(USART1) == USART_enuTX_DONE)
    {

        if (USART_strSendRequest[USART1].Idx < USART_strSendRequest[USART1].Size)
        {
            USART[USART1]->USART_DR = USART_strSendRequest[USART1].Buffer[USART_strSendRequest[USART1].Idx];
            USART_strSendRequest[USART1].Idx++;
        }
        else
        {
            USART_strSendRequest[USART1].Status = USART_enuIDLE;
            if (USART_strSendRequest[USART1].NotifyCbf)
            {
                USART_strSendRequest[USART1].NotifyCbf();
            }
        }
    }
    if ((USART_IsRX(USART1) == USART_enuRX_DONE) && (USART_strReceiveRequest[USART1].Status == USART_enuBUSY))
    {
        if (USART_strReceiveRequest[USART1].Idx < USART_strReceiveRequest[USART1].Size)
        {
            USART_strReceiveRequest[USART1].Buffer[USART_strReceiveRequest[USART1].Idx] = USART[USART1]->USART_DR;
            USART_strReceiveRequest[USART1].Idx++;
        }
        else
        {
            USART_strReceiveRequest[USART1].Status = USART_enuIDLE;
            USART_DisableInterrupts(USART1, USART_RX_COMPLETE_INTERRUPT_FLAG);
            USART_strReceiveRequest[USART1].NotifyCbf();
        }
    }
    /*if condition for the needed flags to be handled*/
}

void USART2_IRQHandler(void)
{
    if (USART_IsTX(USART2) == USART_enuTX_DONE)
    {
        if (USART_strSendRequest[USART2].Idx < USART_strSendRequest[USART2].Size)
        {
            USART[USART2]->USART_DR = USART_strSendRequest[USART2].Buffer[USART_strSendRequest[USART2].Idx];
            USART_strSendRequest[USART2].Idx++;
        }
        else
        {
            USART_strSendRequest[USART2].Status = USART_enuIDLE;
            if (USART_strSendRequest[USART2].NotifyCbf)
            {
                USART_strSendRequest[USART2].NotifyCbf();
            }
        }
    }
    if ((USART_IsRX(USART2) == USART_enuRX_DONE) && (USART_strReceiveRequest[USART2].Status == USART_enuBUSY))
    {
        if (USART_strReceiveRequest[USART2].Idx < USART_strReceiveRequest[USART2].Size)
        {
            USART_strReceiveRequest[USART2].Buffer[USART_strReceiveRequest[USART2].Idx] = USART[USART2]->USART_DR;
            USART_strReceiveRequest[USART2].Idx++;
        }
        else
        {
            USART_strReceiveRequest[USART2].Status = USART_enuIDLE;
            USART_DisableInterrupts(USART2, USART_RX_COMPLETE_INTERRUPT_FLAG);
            if (USART_strReceiveRequest[USART2].NotifyCbf)
            {
                USART_strReceiveRequest[USART2].NotifyCbf();
            }
        }
    }
    /*if condition for the needed flags to be handled*/
}
void USART6_IRQHandler(void)
{

    if (USART_IsTX(USART6) == USART_enuTX_DONE)
    {
        if (USART_strSendRequest[USART6].Idx < USART_strSendRequest[USART6].Size)
        {
            USART[USART6]->USART_DR = USART_strSendRequest[USART6].Buffer[USART_strSendRequest[USART6].Idx];
            USART_strSendRequest[USART6].Idx++;
        }
        else
        {
            USART_strSendRequest[USART6].Status = USART_enuIDLE;
            if (USART_strSendRequest[USART6].NotifyCbf)
            {
                USART_strSendRequest[USART6].NotifyCbf();
            }
        }
    }
    if ((USART_IsRX(USART6) == USART_enuRX_DONE) && (USART_strReceiveRequest[USART6].Status == USART_enuBUSY))
    {
        if (USART_strReceiveRequest[USART6].Idx < USART_strReceiveRequest[USART6].Size)
        {
            USART_strReceiveRequest[USART6].Buffer[USART_strReceiveRequest[USART6].Idx] = USART[USART6]->USART_DR;
            USART_strReceiveRequest[USART6].Idx++;
        }
        else
        {
            USART_strReceiveRequest[USART6].Status = USART_enuIDLE;
            USART_DisableInterrupts(USART6, USART_RX_COMPLETE_INTERRUPT_FLAG);
            if (USART_strReceiveRequest[USART6].NotifyCbf)
            {
                USART_strReceiveRequest[USART6].NotifyCbf();
            }
        }
    }
    /*if condition for the needed flags to be handled*/
}
