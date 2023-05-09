/****************************************
 * Systick INTERFACE .h
 ****************************************/
#include "Std_Types.h"

#define SYSTICK_CLK_SRC_AHB 		0x00000004U
#define SYSTICK_CLK_SRC_PRESCALER_8 0x00000000U

#define SYSTEMCLOCK_HSI 16
#define SYSTEMCLOCK_HSE 25000000U
#define SYSTEMCLOCK_PLL

#define SYSTEMCLOCK SYSTEMCLOCK_HSI

typedef void (*Cbf)(void);

typedef enum
{
    Systick_enuOk,
    Systick_enuNok,
    Systick_enuNullptr
} Systick_ErrorStatus_t;

extern void Systick_Start(void);

extern void Systick_Stop(void);

extern void Set_Systick_Interrupt(void);

extern void Set_Period_MS(u64 Copy_u64TickTime_ms, u32 *Add_pu32OveflowCounter);

extern Systick_ErrorStatus_t Set_CLK_Source(u8 Systick_Clk_source);

extern Systick_ErrorStatus_t Set_NotificationFunc(Cbf Add_Notification_Function);

//void __attribute__ ((section(".after_vectors"),weak))
//SysTick_Handler (void);
