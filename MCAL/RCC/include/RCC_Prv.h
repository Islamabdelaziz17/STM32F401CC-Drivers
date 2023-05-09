#include "Std_Types.h"

/*RCC REGISTERS*/
#define RCC_BASE_ADDRESS 0x40023800
#define RCC_CR *(((volatile u32*)(0x00+RCC_BASE_ADDRESS)))
#define RCC_PLLCFGR *(((volatile u32*)(0x04+RCC_BASE_ADDRESS)))
#define RCC_CFGR *(((volatile u32*)(0x08+RCC_BASE_ADDRESS)))
#define RCC_PLLI2SCFGR *(((volatile u32*)(0x84+RCC_BASE_ADDRESS)))
#define RCC_CIR *(((volatile u32*)(0x0C+RCC_BASE_ADDRESS)))

#define RCC_AHB1ENR *(((volatile u32*)(0x30+RCC_BASE_ADDRESS)))
#define RCC_AHB2ENR *(((volatile u32*)(0x34+RCC_BASE_ADDRESS)))
#define RCC_APB1ENR *(((volatile u32*)(0x40+RCC_BASE_ADDRESS)))
#define RCC_APB2ENR *(((volatile u32*)(0x44+RCC_BASE_ADDRESS)))

#define RCC_AHB1RSTR *(((volatile u32*)(0x10+RCC_BASE_ADDRESS)))
#define RCC_AHB2RSTR *(((volatile u32*)(0x14+RCC_BASE_ADDRESS)))
#define RCC_APB1RSTR *(((volatile u32*)(0x20+RCC_BASE_ADDRESS)))
#define RCC_APB2RSTR *(((volatile u32*)(0x24+RCC_BASE_ADDRESS)))


/*RCC CONTROL REGISTER ENABLES AND FLAGS*/
#define HSI_ON  0
#define HSI_RDY 1
#define HSE_ON  16
#define HSE_RDY 17
#define PLL_ON  24
#define PLL_RDY 25
#define PLLI2S_ON  26
#define PLLI2S_RDY 27

/*################################################*/

/*RCC PLL CONFIGURATIONN REGISTER*/
/*------M PRESCALER------*/
#define PLLM0 0
#define PLLM1 1
#define PLLM2 2
#define PLLM3 3
#define PLLM4 4
#define PLLM5 5
/*------N PRESCALER------ 192 <= VALUE <= 432MHZ*/
#define PLLN0 6
#define PLLN1 7
#define PLLN2 8
#define PLLN3 9
#define PLLN4 10
#define PLLN5 11
#define PLLN6 12
#define PLLN7 13
#define PLLN8 14
/*------P PRESCALER------ <= 84MHZ*/
#define PLLP0 16
#define PLLP1 17
/*------SRC-------------*/
#define PLLSRC 22
/*------Q PRESCALER------ <= 48MHZ*/
#define PLLQ0 24
#define PLLQ1 25
#define PLLQ2 26
#define PLLQ3 27


/*################################################*/

/*RCC CLOCK CONFIGURATIONN REGISTER*/
/*--------SW---------*/
#define SW0 0
#define SW1 1
/*--------SWS-------*/
#define SWS0 2
#define SWS1 3
/*----AHB PRESCALER----*/
#define HPRE0 4
#define HPRE1 5
#define HPRE2 6
#define HPRE3 7
/*----APB1-LOW-SPEED PRESCALER----*/
#define PPRE1_0 10
#define PPRE1_1 11
#define PPRE1_2 12
/*----APB2-HIGH-SPEED PRESCALER----*/
#define PPRE2_0 13
#define PPRE2_1 14
#define PPRE2_2 15
/*----RTCPRE: HSE division factor for RTC clock----*/
#define RTCPRE_0 16
#define RTCPRE_1 17
#define RTCPRE_2 18
#define RTCPRE_3 19
#define RTCPRE_4 20
/*----MCO1: MicroController clock output 1----*/
#define MCO1_0 21
#define MCO1_1 22
/*----I2SSRC: I2S clock selection----*/
#define I2SSRC 23
/*----MCO1PRE: MCO1 PreScaler----*/
#define MCO1PRE_0 24
#define MCO1PRE_1 25
#define MCO1PRE_2 26
/*----MCO2PRE: MCO2 PreScaler----*/
#define MCO2PRE_0 27
#define MCO2PRE_1 28
#define MCO2PRE_2 29
/*----MCO2: MicroController clock output 2----*/
#define MCO2_0 30
#define MCO2_1 31

/*RESET REGISTERS VALUES*/
#define RCC_CR_RESET 0x00000081
#define RCC_PLLCFGR_RESET 0x24003010
#define RCC_CFGR_RESET 0x00000000
/*################################################*/


#define RCC_2BIT_Mask  0b11






