#include "include/DMA.h"

#define DMA1_BASEADDRESS 0x40026000
#define DMA2_BASEADDRESS 0x40026400

#define DMA_StreamRegBaseOffset 0x10
#define DMA_StreamRegEntryPoint 0x18

#define CHECK_PARAMETER 0x10000000

typedef struct
{
    volatile u32 CR;   /*!< DMA stream x configuration register      */
    volatile u32 NDTR; /*!< DMA stream x number of data register     */
    volatile u32 PAR;  /*!< DMA stream x peripheral address register */
    volatile u32 M0AR; /*!< DMA stream x memory 0 address register   */
    volatile u32 M1AR; /*!< DMA stream x memory 1 address register   */
    volatile u32 FCR;  /*!< DMA stream x FIFO control register       */
} DMA_strStreamReg_t;

typedef struct
{
    volatile u32 LISR;  /*!< DMA low interrupt status register,      Address offset: 0x00 */
    volatile u32 HISR;  /*!< DMA high interrupt status register,     Address offset: 0x04 */
    volatile u32 LIFCR; /*!< DMA low interrupt flag clear register,  Address offset: 0x08 */
    volatile u32 HIFCR; /*!< DMA high interrupt flag clear register, Address offset: 0x0C */
} DMA_InterruptReg_t;

volatile DMA_InterruptReg_t *const DMA_InterruptReg[DMA_enuInstanceCount] =
    {
        [0] = (volatile DMA_InterruptReg_t *)DMA1_BASEADDRESS,
        [1] = (volatile DMA_InterruptReg_t *)DMA2_BASEADDRESS};

volatile DMA_strStreamReg_t *const DMA_StreamReg[DMA_enuInstanceCount][DMA_enuStreamCount] =
    {
        [0] = {[0] = (volatile DMA_strStreamReg_t *)(DMA1_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream0))),
               [1] = (volatile DMA_strStreamReg_t *)(DMA1_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream1))),
               [2] = (volatile DMA_strStreamReg_t *)(DMA1_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream2))),
               [3] = (volatile DMA_strStreamReg_t *)(DMA1_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream3))),
               [4] = (volatile DMA_strStreamReg_t *)(DMA1_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream4))),
               [5] = (volatile DMA_strStreamReg_t *)(DMA1_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream5))),
               [6] = (volatile DMA_strStreamReg_t *)(DMA1_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream6))),
               [7] = (volatile DMA_strStreamReg_t *)(DMA1_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream7)))},

        [1] = {[0] = (volatile DMA_strStreamReg_t *)(DMA2_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream0))),
               [1] = (volatile DMA_strStreamReg_t *)(DMA2_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream1))),
               [2] = (volatile DMA_strStreamReg_t *)(DMA2_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream2))),
               [3] = (volatile DMA_strStreamReg_t *)(DMA2_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream3))),
               [4] = (volatile DMA_strStreamReg_t *)(DMA2_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream4))),
               [5] = (volatile DMA_strStreamReg_t *)(DMA2_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream5))),
               [6] = (volatile DMA_strStreamReg_t *)(DMA2_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream6))),
               [7] = (volatile DMA_strStreamReg_t *)(DMA2_BASEADDRESS + (DMA_StreamRegBaseOffset + (DMA_StreamRegEntryPoint * DMA_enuStream7)))}};

/**
 * @return Error status if wrong configurations or Null Pointer Exception
 * @param Addr_pstrCfg : Address pointer to created object for the post compile configurations
 * @brief Initialize DMA Module
 */
DMA_enuErrorStatus_t DMA_enuInit(DMA_strCfg_t *Addr_pstrCfg)
{
    DMA_enuErrorStatus_t Local_enuDMAErrorStatus = DMA_enuOK;
    u32 Local_u32CR = 0, Local_u32FCR = 0;
    if (Addr_pstrCfg)
    {
        if ((Addr_pstrCfg->Channel & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->Channel &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->MemBurst & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->MemBurst &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->Direction & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->Direction &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->FIFOMode & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->FIFOMode &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->FIFOThreshold & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->FIFOThreshold &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->Instance == DMA1) || (Addr_pstrCfg->Instance == DMA2))
        {
            /*Do Nothing*/
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->MemDataAlignment & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->MemDataAlignment &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->PeriphDataAlignment & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->PeriphDataAlignment &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->Stream >= DMA_enuStream0) && (Addr_pstrCfg->Stream <= DMA_enuStream7))
        {
            /*Do Nothing*/
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->MemInc & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->MemInc &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->PeriphInc & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->PeriphInc &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->PeriphBurst & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->PeriphBurst &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->Mode & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->Mode &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->Priority & CHECK_PARAMETER) == CHECK_PARAMETER)
        {
            Addr_pstrCfg->Priority &= ~(CHECK_PARAMETER);
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if((DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->CR & DMA_ENABLE) == 0)
        {
            if (Local_enuDMAErrorStatus == DMA_enuOK)
            {
                Local_u32CR |= Addr_pstrCfg->Channel             | Addr_pstrCfg->Direction |
                            Addr_pstrCfg->MemDataAlignment    | Addr_pstrCfg->MemInc    |
                            Addr_pstrCfg->PeriphDataAlignment | Addr_pstrCfg->PeriphInc |
                            Addr_pstrCfg->Mode                | Addr_pstrCfg->Priority;
                if (Addr_pstrCfg->FIFOMode != (DMA_FIFOMODE_DISABLE & (~CHECK_PARAMETER)))
                {
                    Local_u32CR  |= Addr_pstrCfg->MemBurst | Addr_pstrCfg->PeriphBurst;
                    Local_u32FCR |= Addr_pstrCfg->FIFOMode | Addr_pstrCfg->FIFOThreshold;
                }
                else
                {
                    /*Do Nothing*/
                }

                /*Assign the cfg to the registers*/
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->CR = Local_u32CR;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->FCR = Local_u32FCR;
            }
            else
            {
                /*Do Nothing, Wrong Config*/
            }
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
    }
    else
    {
        Local_enuDMAErrorStatus = DMA_enuNullPtr;
    }
    return Local_enuDMAErrorStatus;
}
/**
 * @return Error status if wrong configurations or Null Pointer Exception
 * @param Addr_pstrCfg : Address pointer to created object for the post compile configurations
 * @param Addr_pu32SrcAddress : Source address
 * @param Addr_pu32DstAddress : Destination address
 * @param Cpy_u16DataLength : Data Length
 * @brief Start DMA specified stream
 */
DMA_enuErrorStatus_t DMA_enuStart(DMA_strCfg_t *Addr_pstrCfg, u32 *Addr_pu32SrcAddress, u32 *Addr_pu32DstAddress, u16 Cpy_u16DataLength)
{
    DMA_enuErrorStatus_t Local_enuDMAErrorStatus = DMA_enuOK;
    u32 Local_u3NDTR = 0,Local_u32;
    if(Addr_pstrCfg)
    {
        if ((Addr_pstrCfg->Stream  >= DMA_enuStream0) && (Addr_pstrCfg->Stream <= DMA_enuStream7))
        {
            /*Do Nothing*/
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if ((Addr_pstrCfg->Instance == DMA1) || (Addr_pstrCfg->Instance == DMA2))
        {
            /*Do Nothing*/
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNOK;
        }
        if((Addr_pu32DstAddress) && (Addr_pu32SrcAddress))
        {
            if(Addr_pstrCfg->Direction == (DMA_PERIPH_TO_MEMORY & (~CHECK_PARAMETER)))
            {
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->PAR  = Addr_pu32SrcAddress;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->M0AR = Addr_pu32DstAddress;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->NDTR = Cpy_u16DataLength;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->CR |= DMA_ENABLE;
            }
            else if(Addr_pstrCfg->Direction == DMA_MEMORY_TO_PERIPH & (~CHECK_PARAMETER))
            {
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->M0AR = Addr_pu32SrcAddress;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->PAR = Addr_pu32DstAddress;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->NDTR = Cpy_u16DataLength;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->CR |= DMA_ENABLE;
            }
            else if(Addr_pstrCfg->Direction == DMA_MEMORY_TO_MEMORY & (~CHECK_PARAMETER))
            {
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->PAR  = Addr_pu32SrcAddress;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->M0AR = Addr_pu32DstAddress;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->NDTR = Cpy_u16DataLength;
                DMA_StreamReg[Addr_pstrCfg->Instance][Addr_pstrCfg->Stream]->CR |= DMA_ENABLE;
            }
            else
            {
                Local_enuDMAErrorStatus = DMA_enuNOK;
            }
            
        }
        else
        {
            Local_enuDMAErrorStatus = DMA_enuNullPtr;
        }
    }
    else
    {
        Local_enuDMAErrorStatus = DMA_enuNullPtr;   
    }
    
    return Local_enuDMAErrorStatus;
}

/**
 * @return Error status if wrong configurations
 * @param Cpy_enuInstance : Instance of the DMA used
 * @param Stream : Current used Stream
 * @brief Disable DMA specified stream
 */
DMA_enuErrorStatus_t DMA_enuAbort(DMA_enuInstance_t Cpy_enuInstance, DMA_enuStream_t Cpy_u32Stream)
{
}

/**
 * @return Error status if wrong configurations
 * @param Cpy_enuInstance : Instance of the DMA used
 * @param Stream : Current used Stream
 * @param Cpy_u32InterruptEnable : @ref DMA_interrupt_enable_definitions
 * @brief Enable desired interrupts for the DMA module
 */
DMA_enuErrorStatus_t DMA_enuEnableInterrupt(DMA_enuInstance_t Cpy_enuInstance, DMA_enuStream_t Cpy_u32Stream, u32 Cpy_u32InterruptEnable)
{
    DMA_enuErrorStatus_t Local_enuDMAErrorStatus = DMA_enuOK;
    u32 Local_u32CR = 0,
        Local_u32InterruptEnable = Cpy_u32InterruptEnable,
        Local_u32FCR = 0;

    if ((Cpy_u32Stream  >= DMA_enuStream0) && (Cpy_u32Stream <= DMA_enuStream7))
    {
        /*Do Nothing*/
    }
    else
    {
        Local_enuDMAErrorStatus = DMA_enuNOK;
    }
    if ((Cpy_enuInstance == DMA1) || (Cpy_enuInstance== DMA2))
    {
        /*Do Nothing*/
    }
    else
    {
        Local_enuDMAErrorStatus = DMA_enuNOK;
    }
    if((Cpy_u32InterruptEnable & CHECK_PARAMETER) == CHECK_PARAMETER)
    {
        Local_u32InterruptEnable &= (~CHECK_PARAMETER);
        if(Cpy_u32InterruptEnable != DMA_IT_FE)
        {
            Local_u32CR = DMA_StreamReg[Cpy_enuInstance][Cpy_u32Stream]->CR;
            Local_u32CR |= Local_u32InterruptEnable;
            DMA_StreamReg[Cpy_enuInstance][Cpy_u32Stream]->CR = Local_u32CR;
        }
        else
        {
            Local_u32FCR = DMA_StreamReg[Cpy_enuInstance][Cpy_u32Stream]->FCR;
            Local_u32FCR |= Local_u32InterruptEnable;
            DMA_StreamReg[Cpy_enuInstance][Cpy_u32Stream]->FCR = Local_u32FCR;
        } 
    }
    else
    {
         Local_enuDMAErrorStatus = DMA_enuNOK;
    }
    return Local_enuDMAErrorStatus;

}

/**
 * @return Error status if wrong configurations
 * @param Cpy_enuInstance : Instance of the DMA used
 * @param Stream : Current used Stream
 * @param Cpy_u32InterruptEnable : @ref DMA_interrupt_enable_definitions
 * @brief Disable desired interrupts for the DMA module
 */
DMA_enuErrorStatus_t DMA_enuDisableInterrupt(DMA_enuInstance_t Cpy_enuInstance, DMA_enuStream_t Cpy_u32Stream, u32 Cpy_u32InterruptEnable)
{
    DMA_enuErrorStatus_t Local_enuDMAErrorStatus = DMA_enuOK;
    u32 Local_u32CR = 0,
        Local_u32InterruptEnable = Cpy_u32InterruptEnable,
        Local_u32FCR = 0;

    if ((Cpy_u32Stream  >= DMA_enuStream0) && (Cpy_u32Stream <= DMA_enuStream7))
    {
        /*Do Nothing*/
    }
    else
    {
        Local_enuDMAErrorStatus = DMA_enuNOK;
    }
    if ((Cpy_enuInstance == DMA1) || (Cpy_enuInstance== DMA2))
    {
        /*Do Nothing*/
    }
    else
    {
        Local_enuDMAErrorStatus = DMA_enuNOK;
    }
    if((Cpy_u32InterruptEnable & CHECK_PARAMETER) == CHECK_PARAMETER)
    {
        Local_u32InterruptEnable &= (~CHECK_PARAMETER);
        if(Cpy_u32InterruptEnable != DMA_IT_FE)
        {
            Local_u32CR = DMA_StreamReg[Cpy_enuInstance][Cpy_u32Stream]->CR;
            Local_u32CR &= (~Local_u32InterruptEnable);
            DMA_StreamReg[Cpy_enuInstance][Cpy_u32Stream]->CR = Local_u32CR;
        }
        else
        {
            Local_u32FCR = DMA_StreamReg[Cpy_enuInstance][Cpy_u32Stream]->FCR;
            Local_u32FCR &= (~Local_u32InterruptEnable);
            DMA_StreamReg[Cpy_enuInstance][Cpy_u32Stream]->FCR = Local_u32FCR;
        } 
    }
    else
    {
         Local_enuDMAErrorStatus = DMA_enuNOK;
    }
    return Local_enuDMAErrorStatus;
}
