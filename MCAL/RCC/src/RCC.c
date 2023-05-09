
#include "RCC_Prv.h"
#include "RCC.h"
#include "math.h"


#define SET_BIT(REG,Bit_NO)     (REG) |= (1<<(Bit_NO))
#define GET_BIT(REG,Bit_NO)     (REG >> Bit_NO) & 0x01

void RCC_enuGetSelectedClock(u8*Add_pu8SelectedClock)
{
	RCC_enuErrorStatus Local_enuErrorstat = RCC_enuOK;
	u8 Local_u8SelectedClock = 0;

	Local_u8SelectedClock |= GET_BIT(RCC_CFGR,SWS0);
	Local_u8SelectedClock |= (GET_BIT(RCC_CFGR,SWS1) << 1);
	*Add_pu8SelectedClock = Local_u8SelectedClock;
}

RCC_enuErrorStatus RCC_enuCheckClockReady(RCC_enuClockType Cpy_enuClockType)
{
	RCC_enuErrorStatus Local_enuErrorstat = RCC_enuOK;
	u8 Local_u8CheckStatus = 0;
	u8 Local_u8CounterFlag = 0;
	u8 Local_u8ClockBITMacro = 0;

	if(Cpy_enuClockType == RCC_HSI)
	{
		Local_u8ClockBITMacro = HSI_RDY;
	}
	else if(Cpy_enuClockType == RCC_HSE)
	{
		Local_u8ClockBITMacro = HSE_RDY;
	}
	else if(Cpy_enuClockType == RCC_PLL)
	{
		Local_u8ClockBITMacro = PLL_RDY;
	}
	else if(Cpy_enuClockType == RCC_PLLI2S)
	{
		Local_u8ClockBITMacro = PLLI2S_RDY;
	}
	else
	{
		Local_enuErrorstat = RCC_enuNotOk;
	}

	while((Local_u8CheckStatus != 1) && (Local_u8CounterFlag <= MAXIMUM_NUMBER_OF_ITERATIONS_FOR_READY_STATE))
	{
		Local_u8CheckStatus = GET_BIT(RCC_CR,Local_u8ClockBITMacro);
		/*Verifying if the clock is selected or not*/
		if(Local_u8CheckStatus == 1)
		{
			Local_enuErrorstat = RCC_enuOK;
		}
		else
		{
			Local_enuErrorstat = RCC_enuNotOk;
		}

		Local_u8CounterFlag++;
	}
	return Local_enuErrorstat;

}

RCC_enuErrorStatus RCC_enuCheckClockStatus(RCC_enuClockType Cpy_enuClockType)
{
	RCC_enuErrorStatus Local_enuErrorstat = RCC_enuOK;
	u8 Local_u8CheckStatus = 6, Local_u8CounterFlag = 5;

	while((Local_u8CheckStatus != 1) && (Local_u8CounterFlag <= MAXIMUM_NUMBER_OF_ITERATIONS_FOR_READY_STATE))
	{
		RCC_enuGetSelectedClock(&Local_u8CheckStatus);
		/*Verifying if the clock is selected or not*/
		if(Local_u8CheckStatus == Cpy_enuClockType)
		{
			Local_enuErrorstat = RCC_enuOK;
		}
		else
		{
			Local_enuErrorstat = RCC_enuNotOk;
		}

		Local_u8CounterFlag++;
	}
	return Local_enuErrorstat;

}
RCC_enuErrorStatus RCC_enuSetClock(RCC_enuClockType Cpy_enuClockType)
{
	RCC_enuErrorStatus Local_enuErrorstat = RCC_enuOK,Local_enuCheckReadyStatus = RCC_enuOK;
	u8 Local_u8ClockBITMacro = 0;

	if(Cpy_enuClockType == RCC_HSI)
	{
		Local_u8ClockBITMacro = HSI_ON;
	}
	else if(Cpy_enuClockType == RCC_HSE)
	{
		Local_u8ClockBITMacro = HSE_ON;
	}
	else if(Cpy_enuClockType == RCC_PLL)
	{
		Local_u8ClockBITMacro = PLL_ON;
	}
	else if(Cpy_enuClockType == RCC_PLLI2S)
	{
		Local_u8ClockBITMacro = PLLI2S_ON;
	}
	else
	{
		Local_enuErrorstat = RCC_enuNotOk;
	}

	if(Local_enuErrorstat != RCC_enuNotOk)
	{
		SET_BIT(RCC_CR,Local_u8ClockBITMacro);

		Local_enuCheckReadyStatus = RCC_enuCheckClockReady(Cpy_enuClockType);

		Local_enuErrorstat = Local_enuCheckReadyStatus;

	}


	return Local_enuErrorstat;
}

RCC_enuErrorStatus RCC_enuResetClock(RCC_enuClockType Cpy_enuClockType)
{

	RCC_enuErrorStatus Local_enuErrorstat = RCC_enuOK;
	if(Cpy_enuClockType == RCC_HSI)
	{
		CLR_BIT(RCC_CR,HSI_ON);
	}
	else if(Cpy_enuClockType == RCC_HSE)
	{
		CLR_BIT(RCC_CR,HSE_ON);
	}
	else if(Cpy_enuClockType == RCC_PLL)
	{
		CLR_BIT(RCC_CR,PLL_ON);
	}
	else if(Cpy_enuClockType == RCC_PLLI2S)
	{
		CLR_BIT(RCC_CR,PLLI2S_ON);
	}
	else
	{
		Local_enuErrorstat = RCC_enuNotOk;
	}

	return Local_enuErrorstat;
}

RCC_enuErrorStatus RCC_enuSelectSystemClock(RCC_enuClockType Cpy_enuClockType)
{
	RCC_enuErrorStatus Local_enuErrorstat = RCC_enuOK,Local_enuCheckClockStat = RCC_enuOK;
	u32 Local_u32TempRegister = 0;

	Local_u32TempRegister = RCC_CFGR;
	Local_u32TempRegister &= ~(RCC_2BIT_Mask);
	Local_u32TempRegister |= Cpy_enuClockType;
	RCC_CFGR = Local_u32TempRegister;

	Local_enuCheckClockStat = RCC_enuCheckClockStatus(Cpy_enuClockType);

	Local_enuErrorstat = Local_enuCheckClockStat;

	// switch (Cpy_enuClockType)
	// {
	// case RCC_HSI:
	// 	Local_u32TempRegister |= RCC_HSI;
	// 	break;
	// case RCC_HSE:
	// 	Local_u32TempRegister |= RCC_HSE_SW_STATUS;
	// 	break;
	// case RCC_PLL:
	// 	Local_u32TempRegister |= RCC_PLL_SW_STATUS;
	// 	break;
	// default:
	// 	Local_enuErrorstat = RCC_enuNotOk;
	// 	break;
	// }

	return Local_enuErrorstat;

	
}

RCC_enuErrorStatus RCC_enuConfigurePLLClock(RCC_enuClockType Cpy_u32PllClockSrc,RCC_enuPLLM Cpy_enuPllM, RCC_enuPLLN Cpy_enuPllN,RCC_enuPLLP Cpy_enuPllP,RCC_enuPLLQ Cpy_enuPllQ)
{
	RCC_enuErrorStatus Local_enuErrorstat = RCC_enuOK;

	u32 Local_u32PllCfg = 0;
	u8 Local_u8ReminderBit[9];
	u8 Local_u8BitCounter = 0;
	/*Reset PLL CFG Register*/
	RCC_PLLCFGR = RCC_PLLCFGR_RESET;

	/*Select Clock Source Whether [HSI || HSE]*/
	switch (Cpy_u32PllClockSrc)
	{
	case RCC_HSI:
		CLR_BIT(Local_u32PllCfg,PLLSRC);  // PLLSRC = 0 FOR HSI
		break;
	case RCC_HSE:
		SET_BIT(Local_u32PllCfg,PLLSRC);   // PLLSRC = 1 FOR HSE
		break;
	default:
		Local_enuErrorstat = RCC_enuNotOk;
		break;
	}

	/*
	---------------------------------------------------------------------
	Verifying the Division Factor is inside the Boundary for the main PLL & PLLI2S
	TRUE: SHIFT THE VALUE TO MEET THE RIGHT POSITION IN THE REGISTER TO SET IT
	FALSE: SET ERROR STATUS TO INDICATE WRONG CONFIGURATION
	--------------------------------------------------------------------------
	*/
	if(Cpy_enuPllM >= RCC_PLL_MIN_M && Cpy_enuPllM <= RCC_PLL_MAX_M)
	{
		Local_u32PllCfg |= LSHFT_REG(Cpy_enuPllM,PLLM0);
	}
	else
	{
		Local_enuErrorstat = RCC_enuNotOk;
	}

	/*
	---------------------------------------------------------------------
	Verifying the Division Factor is inside the Boundary for the VCO
	TRUE: SHIFT THE VALUE TO MEET THE RIGHT POSITION IN THE REGISTER TO SET IT
	FALSE: SET ERROR STATUS TO INDICATE WRONG CONFIGURATION
	--------------------------------------------------------------------------
	*/
	if(Cpy_enuPllN >= RCC_PLL_MIN_N && Cpy_enuPllN <= RCC_PLL_MAX_N)
	{
		Local_u32PllCfg |= LSHFT_REG(Cpy_enuPllN,PLLN0);
	}
	else
	{
		Local_enuErrorstat = RCC_enuNotOk;
	}
	/*
	---------------------------------------------------------------------
	Verifying the Division Factor is inside the Boundary for the main system clock
	TRUE: SHIFT THE VALUE TO MEET THE RIGHT POSITION IN THE REGISTER TO SET IT
	FALSE: SET ERROR STATUS TO INDICATE WRONG CONFIGURATION
	--------------------------------------------------------------------------
	*/
    if(Cpy_enuPllP >= RCC_PLL_MIN_P && Cpy_enuPllP <= RCC_PLL_MAX_P)
	{
		Local_u32PllCfg |= LSHFT_REG(Cpy_enuPllP,PLLP0);
	}
	else
	{
		Local_enuErrorstat = RCC_enuNotOk;
	}
	/*
	---------------------------------------------------------------------
	Verifying the Division Factor is inside the Boundary for the USB OTG FS
	TRUE: SHIFT THE VALUE TO MEET THE RIGHT POSITION IN THE REGISTER TO SET IT
	FALSE: SET ERROR STATUS TO INDICATE WRONG CONFIGURATION
	--------------------------------------------------------------------------
	*/
	if(Cpy_enuPllQ >= RCC_PLL_MIN_Q && Cpy_enuPllQ <= RCC_PLL_MAX_Q)
	{
		Local_u32PllCfg |= LSHFT_REG(Cpy_enuPllQ,PLLQ0);
	}
	else
	{
		Local_enuErrorstat = RCC_enuNotOk;
	}

	//Setting the configuration in the pllcfgr register
	RCC_PLLCFGR = Local_u32PllCfg;


	return Local_enuErrorstat;

}

RCC_enuErrorStatus RCC_SetPrescaler(RCC_enuAHB_PRESCALER_HPRE Cpy_enuAHB_Pre, RCC_enuAPB_Prescaler_PPRE Cpy_enuAPB1_Pre, RCC_enuAPB_Prescaler_PPRE Cpy_enuAPB2_Pre, RCC_enuHSE_DivFactor_RTCPRE Cpy_enuRTC_Pre, RCC_enuMCO_DivFactor_MCOPRE Cpy_enuMCO1_Pre, RCC_enuMCO_DivFactor_MCOPRE Cpy_enuMCO2_Pre)
{
	RCC_enuErrorStatus Local_enuErrorstat = RCC_enuOK;

	u32 Local_u32TempReg = RCC_CFGR;

	Local_u32TempReg |= LSHFT_REG(Cpy_enuAHB_Pre,HPRE0) | LSHFT_REG(Cpy_enuAPB1_Pre,PPRE1_0) | LSHFT_REG(Cpy_enuAPB2_Pre,PPRE2_0) | LSHFT_REG(Cpy_enuRTC_Pre,RTCPRE_0) | LSHFT_REG(Cpy_enuMCO1_Pre,MCO1PRE_0) | LSHFT_REG(Cpy_enuMCO2_Pre,MCO2PRE_0);

	RCC_CFGR = Local_u32TempReg;

	return Local_enuErrorstat;
}

RCC_enuErrorStatus RCC_enuSetPeripheralBusesStatus()
{
	RCC_enuErrorStatus Local_enuErrorstat = RCC_enuOK;

	/*AHB1 PERIPHERALS CONFIGS*/
	#if  RCC_GPIO_A == 1
		SET_BIT(RCC_AHB1ENR,RCC_GPIO_A_EN_RST);
	#else
		//SET_BIT(RCC_AHB1RSTR,RCC_GPIO_A_EN_RST);
	#endif
	
	#if RCC_GPIO_B == 1
		SET_BIT(RCC_AHB1ENR,RCC_GPIO_B_EN_RST);
	#else
		//SET_BIT(RCC_AHB1RSTR,RCC_GPIO_B_EN_RST);
	#endif
	#if RCC_GPIO_C == 1
		SET_BIT(RCC_AHB1ENR,RCC_GPIO_C_EN_RST);
	#else
		//SET_BIT(RCC_AHB1RSTR,RCC_GPIO_C_EN_RST);
	#endif
	#if RCC_GPIO_D == 1
		SET_BIT(RCC_AHB1ENR,RCC_GPIO_D_EN_RST);
	#else
		//SET_BIT(RCC_AHB1RSTR,RCC_GPIO_D_EN_RST);
	#endif
	#if RCC_GPIO_E == 1
		SET_BIT(RCC_AHB1ENR,RCC_GPIO_E_EN_RST);
	#else
		//SET_BIT(RCC_AHB1RSTR,RCC_GPIO_D_EN_RST);
	#endif
	#if RCC_GPIO_H == 1
		SET_BIT(RCC_AHB1ENR,RCC_GPIO_H_EN_RST);
	#else
		//SET_BIT(RCC_AHB1RSTR,RCC_GPIO_H_EN_RST);
	#endif
	#if RCC_CRC == 1
		SET_BIT(RCC_AHB1ENR,RCC_CRC_EN_RST);
	#else
		//SET_BIT(RCC_AHB1RSTR,RCC_CRC_EN_RST);
	#endif
	#if RCC_DMA1 == 1
		SET_BIT(RCC_AHB1ENR,RCC_DMA1_EN_RST);
	#else
		//SET_BIT(RCC_AHB1RSTR,RCC_DMA1_EN_RST);
	#endif
	#if RCC_DMA2 == 1
		SET_BIT(RCC_AHB1ENR,RCC_DMA2_EN_RST);
	#else
		//SET_BIT(RCC_AHB1RSTR,RCC_DMA2_EN_RST);
	#endif

	/*AHB2 PERIPHERALS CONFIGS*/
	#if RCC_OTGFS == 1
		SET_BIT(RCC_AHB2ENR,RCC_OTGFS_EN_RST);
	#else
		//SET_BIT(RCC_AHB2RSTR,RCC_OTGFS_EN_RST);
	#endif


	/*APB1 PERIPHERALS CONFIGS*/
	#if RCC_TIM2 == 1
		SET_BIT(RCC_APB1ENR,RCC_TIM2_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_TIM2_EN_RST);
	#endif

	#if RCC_TIM3 == 1
		SET_BIT(RCC_APB1ENR,RCC_TIM3_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_TIM3_EN_RST);
	#endif

	#if RCC_TIM4 == 1
		SET_BIT(RCC_APB1ENR,RCC_TIM4_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_TIM4_EN_RST);
	#endif

	#if RCC_TIM5 == 1
		SET_BIT(RCC_APB1ENR,RCC_TIM5_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_TIM5_EN_RST);
	#endif

	#if RCC_WWDG == 1
		SET_BIT(RCC_APB1ENR,RCC_WWDG_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_WWDG_EN_RST);
	#endif

	#if RCC_SPI2 == 1
		SET_BIT(RCC_APB1ENR,RCC_SPI2_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_SPI2_EN_RST);
	#endif

	#if RCC_SPI3 == 1
		SET_BIT(RCC_APB1ENR,RCC_SPI3_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_SPI3_EN_RST);
	#endif

	#if RCC_USART2 == 1
		SET_BIT(RCC_APB1ENR,RCC_USART2_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_USART2_EN_RST);
	#endif

	#if RCC_I2C1 == 1
		SET_BIT(RCC_APB1ENR,RCC_I2C1_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_I2C1_EN_RST);
	#endif

	#if RCC_I2C2 == 1
		SET_BIT(RCC_APB1ENR,RCC_I2C2_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_I2C2_EN_RST);
	#endif

	#if RCC_I2C3 == 1
		SET_BIT(RCC_APB1ENR,RCC_I2C3_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_I2C3_EN_RST);
	#endif

	#if RCC_PWR == 1
		SET_BIT(RCC_APB1ENR,RCC_PWR_EN_RST);
	#else
		//SET_BIT(RCC_APB1RSTR,RCC_PWR_EN_RST);
	#endif


	/*APB2 PERIPHERALS CONFIGS*/
	#if RCC_TIM1 == 1
		SET_BIT(RCC_APB2ENR,RCC_TIM1_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_TIM1_EN_RST);
	#endif

	#if RCC_USART1 == 1
		SET_BIT(RCC_APB2ENR,RCC_USART1_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_USART1_EN_RST);
	#endif

	#if RCC_USART6 == 1
		SET_BIT(RCC_APB2ENR,RCC_USART6_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_USART6_EN_RST);
	#endif

	#if RCC_ADC1 == 1
		SET_BIT(RCC_APB2ENR,RCC_ADC1_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_ADC1_EN_RST);
	#endif

	#if RCC_SDIO == 1
		SET_BIT(RCC_APB2ENR,RCC_SDIO_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_SDIO_EN_RST);
	#endif

	#if RCC_SPI1 == 1
		SET_BIT(RCC_APB2ENR,RCC_SPI1_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_SPI1_EN_RST);
	#endif

	#if RCC_SPI4 == 1
		SET_BIT(RCC_APB2ENR,RCC_SPI4_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_SPI4_EN_RST);
	#endif

	#if RCC_SYSCF == 1
		SET_BIT(RCC_APB2ENR,RCC_SYSCF_G_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_SYSCF_G_EN_RST);
	#endif

	#if RCC_TIM9 == 1
		SET_BIT(RCC_APB2ENR,RCC_TIM9_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_TIM9_EN_RST);
	#endif

	#if RCC_TIM10 == 1
		SET_BIT(RCC_APB2ENR,RCC_TIM10_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_TIM10_EN_RST);
	#endif

	#if RCC_TIM11 == 1
		SET_BIT(RCC_APB2ENR,RRCC_TIM11_EN_RST);
	#else
		//SET_BIT(RCC_APB2RSTR,RCC_TIM11_EN_RST);
	#endif

	
	return Local_enuErrorstat;
}
