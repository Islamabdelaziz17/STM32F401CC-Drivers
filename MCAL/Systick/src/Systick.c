#include "include/Systick.h"
#include "math.h"

#define SYSTICK_BASEADDRESS 0xE000E010

#define ENABLE_SYSTICK 		     0x00000001
#define ENABLE_SYSTICK_INTERRUPT 0x00000002
#define STK_RESOLUTION 16777216

#define STK_CLK_SRC_8 8
#define STK_CLK_SRC_AHB 1

#define TIME_MILISEC 1000

typedef struct
{
    u32 STK_CTRL;
    u32 STK_LOAD;
    u32 STK_VAL;
    u32 STK_CALIB;

} Systick_def_t;

volatile Systick_def_t *const SYSTICK = (volatile Systick_def_t *)SYSTICK_BASEADDRESS;
static Cbf Systick_Global_CBF = Null;
static u32 STK_Global_Clk_Source = STK_CLK_SRC_8;

void Systick_Start(void)
{
    u32 Local_STK_CTRL = 0;
    Local_STK_CTRL = SYSTICK->STK_CTRL;
    Local_STK_CTRL |= ENABLE_SYSTICK;
    SYSTICK->STK_CTRL = Local_STK_CTRL;
}

void Systick_Stop(void)
{
    u32 Local_STK_CTRL = 0;
    Local_STK_CTRL = SYSTICK->STK_CTRL;
    Local_STK_CTRL &= ~(ENABLE_SYSTICK);
    SYSTICK->STK_CTRL = Local_STK_CTRL;
}

Systick_ErrorStatus_t Set_CLK_Source(u8 Systick_Clk_source)
{
    Systick_ErrorStatus_t Local_errorstatus = Systick_enuOk;
    u32 Local_STK_CTRL = 0;

    Local_STK_CTRL = SYSTICK->STK_CTRL;
    if (Systick_Clk_source == SYSTICK_CLK_SRC_AHB)
    {
        Local_STK_CTRL |= SYSTICK_CLK_SRC_AHB;
        SYSTICK->STK_CTRL = Local_STK_CTRL;
        STK_Global_Clk_Source = STK_CLK_SRC_AHB;
    }
    else if (Systick_Clk_source == SYSTICK_CLK_SRC_PRESCALER_8)
    {
        Local_STK_CTRL &= ~(u32)SYSTICK_CLK_SRC_PRESCALER_8;
        SYSTICK->STK_CTRL = Local_STK_CTRL;
        STK_Global_Clk_Source = STK_CLK_SRC_8;
    }
    else
    {
        Local_errorstatus = Systick_enuOk;
    }

    return Local_errorstatus;
}

void Set_Systick_Interrupt(void)
{
    u32 Local_STK_CTRL = 0;
    Local_STK_CTRL = SYSTICK->STK_CTRL;
    Local_STK_CTRL |= ENABLE_SYSTICK_INTERRUPT;
    SYSTICK->STK_CTRL = Local_STK_CTRL;
}

Systick_ErrorStatus_t Set_NotificationFunc(Cbf Add_Notification_Function)
{
    Systick_ErrorStatus_t Local_errorstatus = Systick_enuOk;
    if (Add_Notification_Function)
    {
        Systick_Global_CBF = Add_Notification_Function;
    }
    else
    {
        Local_errorstatus = Systick_enuNullptr;
    }
    return Local_errorstatus;
}

void Set_Period_MS(u64 Copy_u64TickTime_ms, u32 *Add_pu32OveflowCounter)
{

    f64 Local_OV_Time = 0;
    f64 Local_Number_OVS = 0;
    //f64 Local_DecimalPortion = 0;
    //u32 Local_PreLoadValue = 0;
    u32 Local_STK_LOAD = 0;

    //Local_OV_Time = ((f64)STK_Global_Clk_Source / (f64)SYSTEMCLOCK) * ((f32)STK_RESOLUTION);
    Local_Number_OVS = (((f64)Copy_u64TickTime_ms * (SYSTEMCLOCK*1000)) / STK_Global_Clk_Source);
    //Local_DecimalPortion = (Local_Number_OVS - (u64)Local_Number_OVS);
    //Local_PreLoadValue = STK_RESOLUTION * (1 - Local_DecimalPortion);

    Local_STK_LOAD = SYSTICK->STK_LOAD;
    Local_STK_LOAD = (u32)Local_Number_OVS;
    SYSTICK->STK_LOAD = Local_STK_LOAD;

    *Add_pu32OveflowCounter = ceil(Local_Number_OVS);
    Systick_Stop();
    Systick_Start();
}


void SysTick_Handler (void)
{
   if(Systick_Global_CBF)
    {
        Systick_Global_CBF();
    }
    else
    {
        /*Do Nothing*/
    }
}
